#include "compiler.hh"

#include <iostream>

#include <string>
#include <unordered_map>
#include <algorithm>

#include "pdm/core/intern.hh"

#include "pdm/ast/script/script.hh"

#include "pdm/feedback/feedback.hh"
#include "pdm/feedback/letter.hh"

#include "pdm/parser/parser.hh"

#include "pdm/dependency_dispatcher/dependency_dispatcher.hh"

#include "pdm/scoper/context.hh"
#include "pdm/scoper/defn.hh"

#include "pdm/typer/typer.hh"


namespace pdm::compiler {

    Compiler::Compiler(std::string&& cwd, std::string&& entry_point_path)
    : m_cwd(std::move(cwd)),
        m_entry_point_path(abspath(std::move(entry_point_path))),
        m_cached_imports(),
        m_all_scripts(),
        m_typer(),
        m_manager(&m_typer),
        m_scoper(&m_typer) 
    {
        m_all_scripts.reserve(8);

        m_scoper.root_frame()->shadow(scoper::ContextKind::RootDefs); {
            m_void_tv_client_astn = help_define_builtin_type("Void", typer()->get_void_tv());
            m_string_tv_client_astn = help_define_builtin_type("String", typer()->get_string_tv());
            m_i8_tv_client_astn = help_define_builtin_type("Bool", typer()->get_u1_tv());
            m_i16_tv_client_astn = help_define_builtin_type("UInt8", typer()->get_u8_tv());
            m_i32_tv_client_astn = help_define_builtin_type("UInt16", typer()->get_u16_tv());
            m_i64_tv_client_astn = help_define_builtin_type("UInt32", typer()->get_u32_tv());
            m_i128_tv_client_astn = help_define_builtin_type("UInt64", typer()->get_u64_tv());
            m_u1_tv_client_astn = help_define_builtin_type("UInt128", typer()->get_u128_tv());
            m_u8_tv_client_astn = help_define_builtin_type("Int8", typer()->get_i8_tv());
            m_u16_tv_client_astn = help_define_builtin_type("Int16", typer()->get_i16_tv());
            m_u32_tv_client_astn = help_define_builtin_type("Int32", typer()->get_i32_tv());
            m_u64_tv_client_astn = help_define_builtin_type("Int64", typer()->get_i64_tv());
            m_u128_tv_client_astn = help_define_builtin_type("Int128", typer()->get_i128_tv());
            m_f16_tv_client_astn = help_define_builtin_type("Float16", typer()->get_f16_tv());
            m_f32_tv_client_astn = help_define_builtin_type("Float32", typer()->get_f32_tv());
            m_f64_tv_client_astn = help_define_builtin_type("Float64", typer()->get_f64_tv());
        }
    }

    ast::Script* Compiler::import(std::string const& from_path, std::string const& type, std::string const& reason) {
        ast::Script* script = help_import_script_1(from_path, type);
        if (script == nullptr) {
            feedback::post(new feedback::Letter(
                feedback::Severity::Error,
                "Failed to load source file \"" + from_path + "\" of type \"" + type + "\"",
                "Required for import '" + reason + "'"
            ));
            return nullptr;
        } else {
            return script;
        }
    }

    ast::BuiltinTypeStmt* Compiler::help_define_builtin_type(intern::String name, typer::Var* typer_var) {
        std::string debug_name = std::string("RootType:") + std::string(name.content());
        ast::BuiltinTypeStmt* stmt = m_manager.new_builtin_type_stmt(std::move(debug_name));
        scoper::Defn defn {scoper::DefnKind::BuiltinType, name, stmt, typer_var};
        assert(m_scoper.root_frame()->define(defn) && "Bad builtins setup.");
        return stmt;
    }

    ast::Script* Compiler::help_import_script_1(std::string const& from_path, std::string const& type) {
        aux::Key key {abspath(from_path), type};

        aux::ImportMap::iterator script_it = m_cached_imports.find(key);
        if (script_it != m_cached_imports.end()) {
            return script_it->second;
        }

        if (type == "pdm.script") {
            std::string abs_from_path = key.import_from_path.native();
            source::Source* source = new source::Source(std::move(abs_from_path));
            ast::Script* script = parser::parse_script(&m_manager, source);
            if (script == nullptr) {
                return nullptr;
            } else {
                help_import_script_2(script);
                return m_cached_imports[key] = script;
            }
        } else {
            // posting feedback: invalid 'type'
            feedback::post(new feedback::Letter(
                feedback::Severity::Error, 
                "Invalid type: " + type, 
                "abspath: \"" + key.import_from_path.native() + "\""
            ));
            return nullptr;
        }
    }

    void Compiler::help_import_script_2(ast::Script* script) {
        std::cout << "Dispatching: " << script->source()->abs_path() << std::endl;
        
        // dispatching all subsequent imports:
        dependency_dispatcher::DDVisitor dd_visitor{this, script};
        dd_visitor.visit(script);
        
        // adding to the 'all_scripts' list.
        m_all_scripts.push_back(script);
    }

    bool Compiler::import_all() {
        // importing the entry point:
        ast::Script* entry_point_script = import(m_entry_point_path, "pdm.script", "entry point");
        if (entry_point_script == nullptr) {
            return false;
        }

        // todo: running until all dispatched dependencies are empty.
        // since each module's dd only runs on first import, this always halts for finite
        // number of imports.

        // all ok!
        return true;
    }
    bool Compiler::typecheck_all() {
        // todo: run scoper here
        // todo: actually solve a typer here...
        return false;
    }

    std::string Compiler::abspath(std::string const& rel_path) const {
        return m_cwd / rel_path;
    }
}
