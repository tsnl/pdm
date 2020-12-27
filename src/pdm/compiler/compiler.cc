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

    ast::Script* Compiler::import(std::string&& from_path, std::string&& type) {
        aux::Key key {
            abspath(std::move(from_path)), 
            std::move(type)
        };

        aux::ImportMap::iterator script_it = m_cached_imports.find(key);
        if (script_it != m_cached_imports.end()) {
            return script_it->second;
        }

        if (type == "pdm.script") {
            std::string abs_from_path = key.import_from_path.native();
            source::Source* source = new source::Source(std::move(abs_from_path));
            ast::Script* script = parser::parse_script(&m_manager, source);

            // todo: load, scan, parse, ...
            // - run reader + lexer + parser, module_dispatcher, and type_initializer.
            //   - halt if any fail
            //   - note that 'module' IDs are lookup-ed by scoper, so...
            //      1. imported modules need to be in-memory first (cf dependency_dispatcher)
            //      2. all analysis post-import (i.e., from 'typecheck') is global
            
            return m_cached_imports[key] = script;
        } else {
            // posting feedback: invalid 'type'
            feedback::post(new feedback::Letter(
                feedback::Severity::Error, 
                "Invalid type: <?>", 
                "abspath: " + key.import_from_path.native()
            ));
            return nullptr;
        }
    }

    bool Compiler::import_all() {
        // importing the entry point:
        std::string entry_point_path = m_entry_point_path;
        std::string import_type = "pdm.script";
        if (!import(std::move(entry_point_path), std::move(import_type))) {
            return false;
        }

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

    std::string Compiler::abspath(std::string&& rel_path) const {
        return m_cwd / rel_path;
    }
}
