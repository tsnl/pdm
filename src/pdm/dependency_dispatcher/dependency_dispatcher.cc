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

    class ScriptDDVisitor: public ast::TinyVisitor {
      private:
        Compiler* m_compiler_ref;
        ast::Script*        m_this_script;

      public:
        ScriptDDVisitor(Compiler* compiler_ref, ast::Script* this_script)
            : m_compiler_ref(compiler_ref),
              m_this_script(this_script) {}

      public:
        virtual bool on_visit(ast::Node* node, VisitOrder visit_order) override;

      protected:
        virtual bool on_visit_import_stmt(ast::ImportStmt* node, VisitOrder visit_order) override;
    };

    bool ScriptDDVisitor::on_visit(ast::Node* node, VisitOrder visit_order) {
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

    bool ScriptDDVisitor::on_visit_import_stmt(ast::ImportStmt* node, VisitOrder visit_order) {
        assert(m_this_script != nullptr);

        if (!ast::TinyVisitor::on_visit_import_stmt(node, visit_order)) {
            return false;
        }

        if (visit_order == VisitOrder::Pre) {
            bool ok = true;
            for (auto field_group: node->field_groups()) {
                std::filesystem::path this_script_path = field_group->from_path().string();

                std::string reason = "import statement";
                std::filesystem::path import_from = field_group->from_path().string();

                // acquiring the absolute path of the 'from':
                std::filesystem::path absolute_import_from;
                if (import_from.is_relative()) {
                    std::filesystem::path base_dir_path = m_this_script->source()->abs_path();
                    base_dir_path.remove_filename();
                    absolute_import_from = base_dir_path / import_from;
                } else {
                    std::string headline = "Cannot import from absolute path.";
                    std::string desc = (
                        "Only relative paths can be used in import statements, see: '" +
                        import_from.string() +
                        "'"
                    );
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
                    ok = false;
                    continue;
                }

                // importing from the given path:
                ast::ISourceNode* imported_source_node = m_compiler_ref->import(absolute_import_from.string(), reason);

                // assigning the imported source node to each field group:
                for (auto field: field_group->fields()) {
                    field->x_origin_source_node(imported_source_node);
                }
            }
            return ok;
        }

        return true;
    }

}

namespace pdm::dependency_dispatcher {

    void dispatch_extern_module_in_c(Compiler* compiler, ast::Package::ExportField_ExternModuleInC* field) {
        std::cout << "TODO: Compiling C module with Clang:" << std::endl;

        intern::String compiler_target_name = compiler->target_name();
        ast::Package::ExportField_ExternModuleInC::CoreCompilerArgs const&
        core_args_ref = field->core_compiler_args();

        ast::Package::ExportField_ExternModuleInC::PlatformCompilerArgs const&
        platform_args_ref = field->platform_compiler_args();

        std::cout << "include:" << std::endl;
        for (auto const& it: core_args_ref.include) {
            std::cout << "- " << it << std::endl;
        }
        if (platform_args_ref.contains(compiler_target_name)) {
            for (auto const& it: platform_args_ref.find(compiler_target_name)->second.include) {
                std::cout << "- " << it << std::endl;
            }
        }

        std::cout << "lib:" << std::endl;
        for (auto const& it: core_args_ref.lib) {
            std::cout << "- " << it << std::endl;
        }
        if (platform_args_ref.contains(compiler_target_name)) {
            for (auto const& it: platform_args_ref.find(compiler_target_name)->second.lib) {
                std::cout << "- " << it << std::endl;
            }
        }

        std::cout << "src:" << std::endl;
        for (auto const& it: core_args_ref.src) {
            std::cout << "- " << it << std::endl;
        }
        if (platform_args_ref.contains(compiler_target_name)) {
            for (auto const& it: platform_args_ref.find(compiler_target_name)->second.src) {
                std::cout << "- " << it << std::endl;
            }
        }

        // LLVM dispatches C dependencies from here.
    }

    void dispatch_import_all_modules_from(Compiler* compiler, ast::Package::ExportField_ImportAllModulesFrom* field) {
        assert(0 && "NotImplemented: dependency dispatch for IMPORT_ALL_MODULES_FROM.");
    }

}

namespace pdm::dependency_dispatcher {

    void dispatch_script_dependencies(Compiler* compiler, ast::Script* script) {
        dependency_dispatcher::ScriptDDVisitor dd_visitor{compiler, script};
        dd_visitor.visit(script);
    }

    void dispatch_package_dependencies(Compiler* compiler, ast::Package* package) {
        for (ast::Package::ExportField* base_export_field: package->exports_fields()) {
            switch (base_export_field->kind()) {
                case ast::Kind::PackageExportField_ExternModuleInC:
                {
                    auto field = dynamic_cast<ast::Package::ExportField_ExternModuleInC*>(base_export_field);
                    dispatch_extern_module_in_c(compiler, field);
                    break;
                }
                case ast::Kind::PackageExportField_ImportAllModulesFrom:
                {
                    auto field = dynamic_cast<ast::Package::ExportField_ImportAllModulesFrom*>(base_export_field);
                    dispatch_import_all_modules_from(compiler, field);
                    break;
                }
                default:
                {
                    assert(0 && "NotImplemented: Unknown Ast Kind: PackageExportField_?");
                    break;
                }
            }
        }
    }

}
