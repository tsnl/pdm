#include "compiler.hh"

#include <string>
#include <unordered_map>
#include <algorithm>

#include "pdm/core/intern.hh"
#include "pdm/ast/script/script.hh"
#include "pdm/feedback/feedback.hh"
#include "pdm/feedback/letter.hh"

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

        if (type == "fs/file") {
            std::string abs_from_path = key.import_from_path.native();
            source::Source* source = new source::Source(std::move(abs_from_path));
            ast::Script* script = nullptr;

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
    bool Compiler::typecheck() {
        // todo: actually solve a typer here...
        return false;
    }

    std::string Compiler::abspath(std::string&& rel_path) const {
        return m_cwd / rel_path;
    }
}
