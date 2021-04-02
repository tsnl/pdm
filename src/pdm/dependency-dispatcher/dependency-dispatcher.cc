#include "dependency-dispatcher.hh"

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
#include "pdm/ast/module/pkg-bundle-mod-exp.hh"

#include "pdm/feedback/feedback.hh"
#include "pdm/feedback/letter.hh"
#include "pdm/feedback/note.hh"
#include "pdm/feedback/severity.hh"

namespace pdm::dependency_dispatcher {

    class ScriptDDVisitor: public ast::TinyVisitor {
      private:
        Compiler*    m_compiler_ref;
        ast::Script* m_this_script;

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
                    std::filesystem::path base_dir_path = m_this_script->source()->abs_path_string();
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
                    assert(imported_source_node->x_container_mod_exp() && "Expected x_container_mod_exp.");
                    field->x_origin_mod_exp(imported_source_node->x_container_mod_exp());
                }
            }
            return ok;
        }

        return true;
    }

}

//
// The primary role of DD for packages is setting
// - the 'mod_exp' property for 'Package::ExportField'
// - and the 'x_bundle_mod_exp' property for 'Package'
//
// This cannot be done earlier since we need to dispatch
// referenced scripts and packages before exporting their
// fields.
//

namespace pdm::dependency_dispatcher {

    void dispatch_extern_module_in_c(
        Compiler* compiler,
        ast::Package* package,
        ast::Package::ExportField_ExternModuleInC* field
    ) {
        ast::Package::ExportField_ExternModuleInC::CoreCompilerArgs const&
        core_args_ref = field->core_compiler_args();

        ast::Package::ExportField_ExternModuleInC::CompilerArgs const* opt_platform_args;
        {
            intern::String compiler_target_name = compiler->target_name();

            auto const& platform_args_ref = field->platform_compiler_args();

            auto active_platform_args_it = platform_args_ref.find(compiler_target_name);
            if (active_platform_args_it != platform_args_ref.end()) {
                opt_platform_args = &active_platform_args_it->second;
            }
        }

        auto const print_extern = false;
        if (print_extern) {
            std::cout << "TODO: Compiling C module with Clang: see Dependency Dispatcher" << std::endl;

            std::cout << "* include:" << std::endl;
            for (auto const& it: core_args_ref.include) {
                std::cout << "  - " << it << std::endl;
            }
            if (opt_platform_args) {
                for (auto const& it: opt_platform_args->include) {
                    std::cout << "  - " << it << std::endl;
                }
            }

            std::cout << "* lib:" << std::endl;
            for (auto const& it: core_args_ref.lib) {
                std::cout << "  - " << it << std::endl;
            }
            if (opt_platform_args) {
                for (auto const& it: opt_platform_args->lib) {
                    std::cout << "  - " << it << std::endl;
                }
            }

            std::cout << "* src:" << std::endl;
            for (auto const& it: core_args_ref.src) {
                std::cout << "  - " << it << std::endl;
            }
            if (opt_platform_args) {
                for (auto const& it: opt_platform_args->src) {
                    std::cout << "  - " << it << std::endl;
                }
            }
        }

        // LLVM dispatches C dependencies from here.

        // todo: initialize interface_fields from C source code here!
        std::vector<ast::BaseModExp::Field*> interface_fields;
        auto extern_c_mod_exp = compiler->ast_mgr()->new_extern_c_mod_exp(field->loc(), std::move(interface_fields));
        field->mod_exp(extern_c_mod_exp);
    }

    void dispatch_import_all_modules_from(
        Compiler* compiler,
        ast::Package* package,
        ast::Package::ExportField_ImportAllModulesFrom* field
    ) {
        std::string reason = "packaged import field: '" + field->name().cpp_str() + "'";

        std::filesystem::path package_dir_path {package->source()->abs_path_string()};
        std::filesystem::path target_path = std::filesystem::canonical(package_dir_path / field->path());
        auto imported_source_node = compiler->import(target_path, reason);
        if (!imported_source_node) {
            assert(0 && "NotImplemented: report failed import.");
        }

        // todo: assert that imported sources are dependency-dispatched already, i.e. no cycles.

        // Importing the source-node's 'container' module:
        std::vector<ast::BaseModExp::Field*> imported_fields;
        field->mod_exp(imported_source_node->x_container_mod_exp());
        field->x_origin_source_node(imported_source_node);
    }

}

namespace pdm::dependency_dispatcher {

    void dispatch_script_dependencies(Compiler* compiler, ast::Script* script) {
        dependency_dispatcher::ScriptDDVisitor dd_visitor{compiler, script};

        // creating and storing the module expression & the origin source node:
        std::vector<ast::BaseModExp::Field*> container_mod_fields;
        container_mod_fields.reserve(script->body_fields().size());
        for (ast::Script::Field* script_field: script->body_fields()) {
            container_mod_fields.push_back(
                compiler->ast_mgr()->new_mod_field_for_mod_exp(
                    script_field->loc(),
                    script_field->name(),
                    script_field->rhs_mod_exp()
                )
            );
        }
        auto container_mod_exp = compiler->ast_mgr()->new_pkg_bundle_mod_exp(
            script->loc(),
            std::move(container_mod_fields)
        );
        script->x_container_mod_exp(container_mod_exp);
        dd_visitor.visit(script);
    }

    void dispatch_package_dependencies(Compiler* compiler, ast::Package* package) {

        // iterating through package export fields, dispatching, and collating exported module fields.
        size_t export_fields_count = package->exports_fields().size();
        std::vector<ast::BaseModExp::Field*> package_container_fields;
        package_container_fields.reserve(export_fields_count);
        for (ast::Package::ExportField* base_export_field: package->exports_fields()) {
            switch (base_export_field->kind()) {
                case ast::Kind::PackageExportField_ExternModuleInC:
                {
                    auto field = dynamic_cast<ast::Package::ExportField_ExternModuleInC*>(base_export_field);
                    dispatch_extern_module_in_c(compiler, package, field);
                    break;
                }
                case ast::Kind::PackageExportField_ImportAllModulesFrom:
                {
                    auto field = dynamic_cast<ast::Package::ExportField_ImportAllModulesFrom*>(base_export_field);
                    dispatch_import_all_modules_from(compiler, package, field);
                    break;
                }
                default:
                {
                    assert(0 && "NotImplemented: Unknown Ast Kind: PackageExportField_?");
                    break;
                }
            }
            assert(
                base_export_field->mod_exp() &&
                "Expected `field->mod_exp()` after dispatching from IMPORT_ALL field."
            );
            package_container_fields.push_back(
                compiler->ast_mgr()->new_mod_field_for_mod_exp(
                    base_export_field->loc(),
                    base_export_field->name(),
                    base_export_field->mod_exp()
                )
            );
        }

        // setting the container module expression:
        auto bundle_mod_exp = compiler->ast_mgr()->new_pkg_bundle_mod_exp(
            package->loc(),
            std::move(package_container_fields)
        );
        package->x_container_mod_exp(bundle_mod_exp);
    }

}
