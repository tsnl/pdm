#include "compiler.hh"

#include <string>
#include <unordered_map>
#include <algorithm>

#include "pdm/core/intern.hh"
#include "pdm/ast/script/script.hh"
#include "pdm/feedback/feedback.hh"
#include "pdm/feedback/letter.hh"
#include "pdm/parser/parser.hh"

namespace pdm::compiler {

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
        // todo: finish processing this script
    }

    bool Compiler::import_all() {
        // importing the entry point:
        ast::Script* entry_point_script = import(m_entry_point_path, "pdm.script", "entry point");
        if (entry_point_script == nullptr) {
            return false;
        }
        m_all_scripts.push_back(entry_point_script);

        // todo: running until all dispatched dependencies are empty.
        // since each module's dd only runs on first import, this always halts for finite
        // number of imports.

        // all ok!
        return true;
    }
    bool Compiler::typecheck_all() {
        // todo: actually solve a typer here...
        return false;
    }

    std::string Compiler::abspath(std::string const& rel_path) const {
        return m_cwd / rel_path;
    }
}
