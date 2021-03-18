#include "compiler.hh"

#include <iostream>

#include <string>
#include <unordered_map>
#include <algorithm>

#include "pdm/core/intern.hh"
#include "pdm/core/config.hh"

#include "pdm/ast/source-node/script.hh"

#include "pdm/feedback/feedback.hh"
#include "pdm/feedback/letter.hh"

#include "pdm/parser/parser.hh"

#include "pdm/dependency_dispatcher/dependency_dispatcher.hh"

#include "pdm/scoper/scoper.hh"
#include "pdm/scoper/context.hh"
#include "pdm/scoper/defn.hh"

#include "pdm/types/manager.hh"
#include "pdm/typer/typer.hh"

#include "pdm/source/local-script-source.hh"
#include "pdm/source/local-package-source.hh"


namespace pdm {

    Compiler::Compiler(std::string&& cwd, std::string const& entry_point_path, u64 print_flags)
    :   m_cwd(std::move(cwd)),
        m_entry_point_path(abspath(entry_point_path)),
        m_cached_imports(),
        m_all_scripts(),
        m_types_mgr(this),
        m_ast_mgr(this),
        m_print_flags(print_flags),
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
        m_all_scripts.reserve(8);
    }

    u64 Compiler::PrintFlags_PrintEverything = (0
        | static_cast<PrintFlagBitset>(PrintFlag::SourceCode)
        | static_cast<PrintFlagBitset>(PrintFlag::Scopes)
        | static_cast<PrintFlagBitset>(PrintFlag::Types)
        | static_cast<PrintFlagBitset>(PrintFlag::Llvm)
        | static_cast<PrintFlagBitset>(PrintFlag::Wasm)
    );

    ast::ISourceNode* Compiler::import(std::string const& from_path, std::string const& reason) {
        ast::ISourceNode* source_node = check_cache_or_import(from_path);
        if (source_node == nullptr) {
            feedback::post(new feedback::Letter(
                feedback::Severity::Error,
                "Failed to load source file \"" + from_path + "\"",
                "Required for import '" + reason + "'"
            ));
            return nullptr;
        } else {
            return source_node;
        }
    }

    ast::BuiltinStmt* Compiler::help_define_builtin_type(scoper::Scoper& scoper, intern::String name, types::Var* typer_var) {
        std::string debug_name = std::string("RootType:") + std::string(name.content());
        ast::BuiltinStmt* stmt = m_ast_mgr.new_builtin_stmt(std::move(debug_name));
        scoper::Defn defn {scoper::DefnKind::BuiltinType, name, stmt, typer_var};
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
            return m_cached_imports[key] = import_new(abs_from_path_string, reason);
        }
    }

    ast::ISourceNode* Compiler::import_new(std::string const& abs_from_path_string, std::string const& reason) {        // todo: determine whether this is a package or script and handle appropriately.
        std::filesystem::path from_path{abs_from_path_string};
        if (std::filesystem::is_regular_file(from_path)) {
            return import_new_script(abs_from_path_string, reason);
        } else if (std::filesystem::is_directory(from_path)) {
            // todo: check if valid package
        }

        // verifying
        if (!std::filesystem::exists(from_path)) {
            feedback::post(new feedback::Letter(
                feedback::Severity::Error, 
                "Cannot import from non-existent",
                "abspath: \"" + abs_from_path_string + "\""
            ));
            return nullptr;
        }
    }

    ast::Script* Compiler::import_new_script(const std::string &abs_from_path_string, const std::string &reason) {
        std::string abs_from_path_string_copy = abs_from_path_string;
        source::ISource* source = new source::LocalScriptSource(std::move(abs_from_path_string_copy));
        ast::Script* script = parser::parse_script(&m_ast_mgr, source);
        if (script == nullptr) {
            return nullptr;
        } else {
            std::cout << "Dispatching: " << script->source()->abs_path() << std::endl;

            // adding to the 'all_scripts' list BEFORE adding more scripts
            // <=> entry_point is always the first script, leaves farther out.
            m_all_scripts.push_back(script);

            // dispatching all subsequent imports:
            dependency_dispatcher::DDVisitor dd_visitor{this, script};
            dd_visitor.visit(script);

            return script;
        }
    }

    bool Compiler::pass1_import_all(scoper::Scoper& scoper) {
        // importing the entry point, and all dependencies recursively via DependencyDispatcher:
        ast::ISourceNode* entry_point_source_node = import(m_entry_point_path, "entry point");
        assert(0 && "NotImplemented: checking entry_point_source_node is a script.")
        if (entry_point_script == nullptr) {
            return false;            
        }

        // scoping each module, visiting in dependency order:
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
        }
        for (ast::Script* script: m_all_scripts) {
            scoper.scope(script);
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

        // all ok
        return true;
    }
    bool Compiler::pass2_type_check_all() {
        bool all_scripts_ok = true;
        for (ast::Script* script: m_all_scripts) {
            bool script_ok = typer::type(&m_types_mgr, script);
            all_scripts_ok = all_scripts_ok && script_ok;
        }
        if (!all_scripts_ok) {
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
        std::cout << "Not Implemented: pass3_emit_all" << std::endl;
        return false;
    }

    void Compiler::postpass1_print1_code() {
        printer::Printer p{std::cout};
        for (ast::Script* script: all_scripts()) {
            p.print_node(script);
        }
    }
    void Compiler::postpass1_print2_scopes(scoper::Scoper& scoper) {
        printer::Printer p{std::cout};
        scoper.print(p);
    }
    void Compiler::postpass2_print1_types() {
        printer::Printer p{std::cout};
        m_types_mgr.print(p, "After pass2");
    }
    void Compiler::postpass3_print1_llvm() {
        std::cout << "Not Implemented: 'postpass3_print1_llvm'" << std::endl;
    }
    void Compiler::postpass3_print2_wasm() {
        std::cout << "Not Implemented: 'postpass3_print2_wasm'" << std::endl;
    }

    bool Compiler::finish() {
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

        if (m_print_flags & static_cast<PrintFlagBitset>(PrintFlag::SourceCode)) {
            postpass1_print1_code();
        }
        if (m_print_flags & static_cast<PrintFlagBitset>(PrintFlag::Scopes)) {
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

        if (m_print_flags & static_cast<u64>(PrintFlag::Types)) {
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
