#include "dependency_dispatcher.hh"

#include <iostream>
#include <iomanip>

#include <string>
#include <filesystem>
#include <cassert>

#include "pdm/compiler/compiler.hh"
#include "pdm/ast/manager.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/pattern/vpattern.hh"
#include "pdm/ast/pattern/lpattern.hh"
#include "pdm/ast/pattern/tpattern.hh"

#include "pdm/feedback/feedback.hh"
#include "pdm/feedback/letter.hh"
#include "pdm/feedback/note.hh"
#include "pdm/feedback/severity.hh"

namespace pdm::dependency_dispatcher {

    std::string const PD_SCRIPT_IMPORT_TYPE_STRING = "pd/script";

    inline bool is_relfile_import_type(std::string const& import_type) {
        return import_type == PD_SCRIPT_IMPORT_TYPE_STRING;
    }

    bool DDVisitor::on_visit(ast::Node* node, VisitOrder visit_order) {
        // setting 'source' for each node 'loc':
        node->mut_loc().source(m_this_script->source());

        // (inelegant but efficient) additionally setting for fields if pattern:
        // - inelegant because DependencyDispatcher is growing into a 'parser cleanup' module too.
        // - need better names... ;-;
        if (ast::is_pattern_kind(node->kind())) {
            if (node->kind() == ast::Kind::VPattern) {
                for (ast::VPattern::Field* field: dynamic_cast<ast::VPattern*>(node)->fields()) {
                    field->mut_loc().source(m_this_script->source());
                }
            } else if (node->kind() == ast::Kind::LPattern) {
                for (ast::LPattern::Field* field: dynamic_cast<ast::LPattern*>(node)->fields()) {
                    field->mut_loc().source(m_this_script->source());
                }
            } else if (node->kind() == ast::Kind::TPattern) {
                for (ast::TPattern::Field* field: dynamic_cast<ast::TPattern*>(node)->fields()) {
                    field->mut_loc().source(m_this_script->source());
                }
            }
        }

        return TinyVisitor::on_visit(node, visit_order);
    }

    bool DDVisitor::on_visit_import_stmt(ast::ImportStmt* node, VisitOrder visit_order) {
        assert(m_this_script != nullptr);

        if (!ast::TinyVisitor::on_visit_import_stmt(node, visit_order)) {
            return false;
        }

        if (visit_order == VisitOrder::Pre) {
            std::filesystem::path this_script_path = node->import_from_str().string();
            std::string reason = "import " + std::string(node->import_name().content());
            std::filesystem::path import_from = node->import_from_str().string();
            std::string import_type = node->import_type_str().string();
            
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
            node->x_origin_script(imported_script);
        }

        return true;
    }

}
