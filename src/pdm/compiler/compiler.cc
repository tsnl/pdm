#include "compiler.hh"

#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

#include <llvm-c/Core.h>
#include <llvm-c/Analysis.h>

#include "pdm/core/intern.hh"
#include "pdm/core/config.hh"

#include "pdm/ast/source-node/script.hh"

#include "pdm/feedback/feedback.hh"
#include "pdm/feedback/letter.hh"

#include "pdm/parser/parser.hh"

#include "pdm/dependency-dispatcher/dependency-dispatcher.hh"

#include "pdm/scoper/scoper.hh"
#include "pdm/scoper/context.hh"
#include "pdm/scoper/defn.hh"

#include "pdm/types/manager.hh"
#include "pdm/typer/typer.hh"

#include "pdm/source/local-script-source.hh"
#include "pdm/source/local-package-source.hh"

#include "pdm/emitter/llvm-emitter.hh"


namespace pdm {

    Compiler::Compiler(std::string&& cwd, std::string const& entry_point_path, intern::String target_name)
    :   m_cwd(std::move(cwd)),
        m_entry_point_path(abspath(entry_point_path)),
        m_cached_imports(),
        m_all_source_nodes(),
        m_types_mgr(this),
        m_ast_mgr(this),
        m_target_name(target_name),
        m_llvm_builder(LLVMCreateBuilder()),
        m_void_tv_client_astn(nullptr),
        m_string_tv_client_astn(nullptr),
        m_i8_tv_client_astn(nullptr),
        m_i16_tv_client_astn(nullptr),
        m_i32_tv_client_astn(nullptr),
        m_i64_tv_client_astn(nullptr),
        m_i128_tv_client_astn(nullptr),
        m_u1_tv_client_astn(nullptr),
        m_u8_tv_client_astn(nullptr),
        m_u16_tv_client_astn(nullptr),
        m_u32_tv_client_astn(nullptr),
        m_u64_tv_client_astn(nullptr),
        m_u128_tv_client_astn(nullptr),
        m_f16_tv_client_astn(nullptr),
        m_f32_tv_client_astn(nullptr),
        m_f64_tv_client_astn(nullptr)
    {
        m_all_source_nodes.reserve(8);
    }

    Compiler::~Compiler() {
        LLVMDisposeBuilder(static_cast<LLVMBuilderRef>(m_llvm_builder));
    }

    ast::ISourceNode* Compiler::import(std::string const& abs_from_path, std::string const& reason) {
        ast::ISourceNode* source_node = check_cache_or_import(abs_from_path, reason);
        if (source_node == nullptr) {
            feedback::post(new feedback::Letter(
                feedback::Severity::Error,
                "Failed to load source file \"" + abs_from_path + "\"",
                "Required for import '" + reason + "'"
            ));
            return nullptr;
        } else {
            return source_node;
        }
    }

    ast::BuiltinStmt* Compiler::help_define_builtin_type(scoper::Scoper& scoper, intern::String name, types::Var* typer_var) {
        std::string debug_name = std::string("RootType:") + name.cpp_str();
        ast::BuiltinStmt* stmt = m_ast_mgr.new_builtin_stmt(std::move(debug_name));
        auto defn = new scoper::Defn {scoper::DefnKind::BuiltinType, name, stmt, typer_var};
        assert(scoper.root_frame()->define(defn) && "Bad builtins setup.");
        return stmt;
    }

    ast::BuiltinStmt* Compiler::help_define_builtin_class(scoper::Scoper& scoper, intern::String name, types::Var* typer_var) {
        std::string debug_name = std::string("RootClass:") + name.cpp_str();
        ast::BuiltinStmt* stmt = m_ast_mgr.new_builtin_stmt(std::move(debug_name));
        auto defn = new scoper::Defn {scoper::DefnKind::BuiltinClass, name, stmt, typer_var};
        assert(scoper.root_frame()->define(defn) && "Bad builtins setup.");
        return stmt;
    }

    ast::ISourceNode* Compiler::check_cache_or_import(std::string const& from_path_string, std::string const& reason) {
        std::string abs_from_path_string = abspath(from_path_string);
        aux::Key key{abs_from_path_string};

        auto script_it = m_cached_imports.find(key);
        if (script_it != m_cached_imports.end()) {
            return script_it->second;
        } else {
            return m_cached_imports[key] = import_new(from_path_string, abs_from_path_string, reason);
        }
    }

    ast::ISourceNode* Compiler::import_new(std::string const& raw_from_path_string, std::string const& abs_from_path_string, std::string const& reason) {
        std::filesystem::path from_path{abs_from_path_string};

        // verifying the path exists:
        if (!std::filesystem::exists(from_path)) {
            feedback::post(new feedback::Letter(
                feedback::Severity::Error, 
                "Cannot import from non-existent source node",
                "abspath: \"" + abs_from_path_string + "\""
            ));
            return nullptr;
        }

        // importing a script or a package-content:
        if (std::filesystem::is_regular_file(from_path)) {
            return import_new_script(raw_from_path_string, abs_from_path_string, reason);
        } else if (std::filesystem::is_directory(from_path)) {
            return import_new_package(raw_from_path_string, abs_from_path_string, reason);
        } else {
            assert(0 && "NotImplemented: feedback on invalid imported file.");
        }
    }

    ast::Script* Compiler::import_new_script(std::string const& raw_from_path_string, const std::string &abs_from_path_string, const std::string &reason) {
        // check that raw_from_path_string has a '.pd' extension:
        if (!raw_from_path_string.ends_with(".pd")) {
            // todo: consider adding a 'loc' from the source 'imports' statement
            feedback::post(new feedback::Letter(
                feedback::Severity::Error,
                "Script import must end with '.pd' extension",
                "See 'imports' statement for '" + reason + "' from: '" + raw_from_path_string + "'."
            ));
            return nullptr;
        }

        std::string abs_from_path_string_copy = abs_from_path_string;
        auto source = new source::LocalScriptSource(std::move(abs_from_path_string_copy));
        ast::Script* script = parser::parse_script(&m_ast_mgr, source);
        if (script == nullptr) {
            return nullptr;
        } else {
            std::cout << "Dispatching Script:\t" << source->abs_path_string() << std::endl;

            // adding to the 'all_source_nodes' list BEFORE adding more scripts
            // <=> entry_point is always the first script, leaves farther out.
            m_all_source_nodes.push_back(script);

            // dispatching all subsequent imports:
            dependency_dispatcher::dispatch_script_dependencies(this, script);

            return script;
        }
    }

    ast::Package* Compiler::import_new_package(std::string const& raw_from_path_string, const std::string &abs_from_path_string, const std::string &reason) {
        // check that raw_from_path_string has a '/' extension:
        if (!raw_from_path_string.ends_with("/")) {
            // todo: consider adding a 'loc' from the source 'imports' statement
            feedback::post(new feedback::Letter(
                feedback::Severity::Error,
                "Package import must end with '/' character",
                "See 'imports' statement for '" + reason + "' from: '" + raw_from_path_string + "'."
            ));
            return nullptr;
        }

        std::string abs_from_path_string_copy = abs_from_path_string;
        auto source = new source::LocalPackageSource(std::move(abs_from_path_string_copy));
        ast::Package* package = parser::parse_package(&m_ast_mgr, source);
        if (package == nullptr) {
            return nullptr;
        } else {
            std::cout << "Dispatching Package:\t" << source->abs_path_string() << std::endl;

            // adding to the 'all_source_nodes' list BEFORE adding more scripts
            m_all_source_nodes.push_back(package);

            // dispatching all subsequent imports:
            dependency_dispatcher::dispatch_package_dependencies(this, package);
        }
        return package;
    }

    bool Compiler::pass1_import_all(scoper::Scoper& scoper) {
        // importing the entry point, and all dependencies recursively via DependencyDispatcher:
        ast::ISourceNode* entry_point_source_node = import(m_entry_point_path, "entry point");

        // any entry point source node is allowed.
        if (entry_point_source_node == nullptr) {
            return false;            
        }

        //
        // scoping each module, visiting in dependency-dispatched order:
        //

        // first, initializing the shared root frame used by all modules:
        {
            scoper.root_frame()->shadow(scoper::ContextKind::RootDefs); {
                m_void_tv_client_astn = help_define_builtin_type(scoper, "Void", types_mgr()->get_void_tv());
                m_string_tv_client_astn = help_define_builtin_type(scoper, "String", types_mgr()->get_string_tv());
                m_i8_tv_client_astn = help_define_builtin_type(scoper, "Int8", types_mgr()->get_i8_tv());
                m_i16_tv_client_astn = help_define_builtin_type(scoper, "Int16", types_mgr()->get_i16_tv());
                m_i32_tv_client_astn = help_define_builtin_type(scoper, "Int32", types_mgr()->get_i32_tv());
                m_i64_tv_client_astn = help_define_builtin_type(scoper, "Int64", types_mgr()->get_i64_tv());
                m_i128_tv_client_astn = help_define_builtin_type(scoper, "Int128", types_mgr()->get_i128_tv());
                m_u1_tv_client_astn = help_define_builtin_type(scoper, "UInt1", types_mgr()->get_u1_tv());
                m_u8_tv_client_astn = help_define_builtin_type(scoper, "UInt8", types_mgr()->get_u8_tv());
                m_u16_tv_client_astn = help_define_builtin_type(scoper, "UInt16", types_mgr()->get_u16_tv());
                m_u32_tv_client_astn = help_define_builtin_type(scoper, "UInt32", types_mgr()->get_u32_tv());
                m_u64_tv_client_astn = help_define_builtin_type(scoper, "UInt64", types_mgr()->get_u64_tv());
                m_u128_tv_client_astn = help_define_builtin_type(scoper, "UInt128", types_mgr()->get_u128_tv());
                m_f16_tv_client_astn = help_define_builtin_type(scoper, "Float16", types_mgr()->get_f16_tv());
                m_f32_tv_client_astn = help_define_builtin_type(scoper, "Float32", types_mgr()->get_f32_tv());
                m_f64_tv_client_astn = help_define_builtin_type(scoper, "Float64", types_mgr()->get_f64_tv());

                m_signed_int_cv_client_astn = help_define_builtin_class(scoper, "S_INT", types_mgr()->get_signed_int_cv());
                m_unsigned_int_cv_client_astn = help_define_builtin_class(scoper, "U_INT", types_mgr()->get_unsigned_int_cv());
                m_float_cv_client_astn = help_define_builtin_class(scoper, "FLOAT", types_mgr()->get_float_cv());
            }
        }

        // next, scoping each loaded source node in the REVERSE order they were imported, excluding repetitions:
        // - reverse order so that a package may reference a source file's frame
        for (auto it = m_all_source_nodes.rbegin(); it != m_all_source_nodes.rend(); it++) {
            ast::ISourceNode* source_node = *it;

            auto script = dynamic_cast<ast::Script*>(source_node);
            if (script) {
                scoper.scope_script(script);
                continue;
            }

            auto package = dynamic_cast<ast::Package*>(source_node);
            if (package) {
                // assert(0 && "NotImplemented: scoper on ast::Package");
                // std::cout << "NotImplemented: scoper on ast::Package" << std::endl;
                scoper.scope_package(package);
                continue;
            }

            assert(0 && "NotImplemented: unknown ISourceNode in scoper.");
        }
        bool scoper_ok = scoper.finish();
        if (!scoper_ok) {
            feedback::post(new feedback::Letter(
                feedback::Severity::FatalError,
                "A fatal scoper error occurred.",
                "See other error messages for further guidance."
            ));
            return false;
        }

        // all ok, return true
        return true;
    }
    bool Compiler::pass2_type_check_all() {
        // typing each source node:
        bool all_source_nodes_ok = true;
        for (ast::ISourceNode* source_node: m_all_source_nodes) {
            auto script = dynamic_cast<ast::Script*>(source_node);
            if (script) {
                bool script_ok = typer::type_script(&m_types_mgr, script);
                all_source_nodes_ok = all_source_nodes_ok && script_ok;
                continue;
            }

            auto package = dynamic_cast<ast::Package*>(source_node);
            if (package) {
                bool package_ok = typer::type_package(&m_types_mgr, package);
                all_source_nodes_ok = all_source_nodes_ok && package_ok;
                continue;
            }

            assert(0 && "NotImplemented: unknown ISourceNode in pass2_type_check_all.");
        }
        if (!all_source_nodes_ok) {
            feedback::post(new feedback::Letter(
                feedback::Severity::FatalError,
                "Typer Failed!",
                "The compiler could not construct a meaningful type system from the given input, "
                "so either vital type/class specifiers are missing or type/class specifiers are incongruent."
            ));
            return false;
        }
        return m_types_mgr.typecheck();
    }
    bool Compiler::pass3_emit_all() {
        return emitter::emit_llvm(this);
    }

    void Compiler::postpass1_print1_code() {
        printer::Printer* p = printer::create(std::cout, target_name());
        for (ast::ISourceNode* source_node: all_source_nodes()) {
            printer::print_node(p, source_node);
        }
    }
    void Compiler::postpass1_print2_scopes(scoper::Scoper& scoper) {
        printer::Printer* p = printer::create(std::cout, target_name());
        scoper.print(p);
    }
    void Compiler::postpass2_print1_types() {
        printer::Printer* p = printer::create(std::cout, target_name());
        m_types_mgr.print(p, "After pass2");
    }

    bool Compiler::finish() {
        // dump state to stdout after each phase?
        bool disable_all_printing = false;
        bool print_source_code = false && pdm::DEBUG && !disable_all_printing;
        bool print_scopes = false && pdm::DEBUG && !disable_all_printing;
        bool print_types = false && pdm::DEBUG && !disable_all_printing;

        scoper::Scoper scoper{this};

        //
        // Pass 1: Loading (frontend)
        //

        if (!pass1_import_all(scoper)) {
            std::string desc = "Loading Error-- Compilation Terminated";
            std::string headline = (
                "A fatal error occurred while loading your source files, "
                "so no output files will be made."
            );
            feedback::post(new feedback::Letter(
                feedback::Severity::FatalError,
                std::move(headline),
                std::move(desc)
            ));
            return false;
        }

        if (print_source_code) {
            postpass1_print1_code();
        }
        if (print_scopes) {
            postpass1_print2_scopes(scoper);
        }

        //
        // Pass 2: typechecking
        //
        
        bool pass2_ok = pass2_type_check_all();
        if (!pass2_ok) {
            std::string headline = "Typechecking Error-- Compilation Terminated";
            std::string desc = (
                "All loaded assets are syntactically valid, but other errors "
                "occurred while processing, so no output files will be made."
            );
            feedback::post(new feedback::Letter(
                feedback::Severity::FatalError,
                std::move(headline),
                std::move(desc)
            ));
        }

        if (print_types) {
            postpass2_print1_types();
        }

        if (!pass2_ok) {
            return false;
        }

        //
        // Pass 3: emitting (backend)
        //

        bool pass3_ok = pass3_emit_all();
        if (!pass3_ok) {
            std::string headline = "Emitting code failed.";
            std::string desc = (
                "This is a compiler error. "
                "Please upgrade to a newer version of the compiler. "
                
                "If this doesn't fix your issue, you will need to file a bug report. "
                "Try rewriting your code to reproduce and isolate what causes this issue. "
                "Then, work around the issue while we work on the compiler to fix this, "
                "or fix it yourself and submit the code using a Pull Request at "
                PDMSDK_REPO_URL_CMACRO
            );
            feedback::post(new feedback::Letter(
                feedback::Severity::CompilerError,
                headline,
                desc
            ));
            return false;
        }

        return true;
    }

    std::string Compiler::abspath(std::string const& rel_path) const {
        return m_cwd / rel_path;
    }

}
