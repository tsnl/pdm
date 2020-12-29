#include "dependency_dispatcher.hh"

#include <iostream>
#include <string>
#include <filesystem>
#include <cassert>

#include "pdm/compiler/compiler.hh"
#include "pdm/ast/manager.hh"

#include "pdm/feedback/feedback.hh"
#include "pdm/feedback/letter.hh"
#include "pdm/feedback/note.hh"
#include "pdm/feedback/severity.hh"

namespace pdm::dependency_dispatcher {

    inline bool is_relfile_import_type(std::string const& import_type) {
        return import_type == "pdm.script";
    }

    bool DDVisitor::on_visit__import_stmt(ast::ImportStmt* node, VisitOrder visit_order) {
        assert(m_this_script != nullptr);

        if (!ast::Visitor::on_visit__import_stmt(node, visit_order)) {
            return false;
        }

        if (visit_order == VisitOrder::Pre) {
            std::filesystem::path this_script_path = node->imported_from_str().string();
            std::string reason = "import " + std::string(node->imported_name().content());
            std::filesystem::path import_from = node->imported_from_str().string();
            std::string import_type = node->imported_type_str().string();
            
            std::filesystem::path absolute_import_from;
            if (is_relfile_import_type(import_type)) {
                if (import_from.is_relative()) {
                    std::filesystem::path base_dir_path = m_this_script->source()->abs_path();
                    base_dir_path.remove_filename();
                    absolute_import_from = base_dir_path / import_from;
                } else  {
                    // todo: post feedback; cannot have absolute path in import.
                    std::string headline = "Cannot import '" + import_type + "' ";
                    std::string desc = "";
                    std::vector<feedback::Note*> notes{1}; {
                        std::string desc0 = "See import statement here...";
                        notes[0] = new feedback::SourceLocNote(std::move(desc0), node->loc());
                    }
                    feedback::post(new feedback::Letter(
                        feedback::Severity::Error,
                        std::move(headline),
                        std::move(desc),
                        std::move(notes)
                    ));
                    return false;
                }
            } else {
                // *shrugs*; wait for 'import' to catch errors.
                absolute_import_from = import_from;
            }

            ast::Script* imported_script = m_compiler_ref->import(absolute_import_from.string(), import_type, reason);
            node->x_imported_script(imported_script);
        }

        return true;
    }

    void DependencyDispatcher::dispatch_imports_for(ast::Script* script) {
        DDVisitor visitor{m_compiler_ref, script};
        visitor.visit(script);
    }

}