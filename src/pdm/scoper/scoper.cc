#include "scoper.hh"

#include <string>
#include <cassert>

#include "pdm/compiler/compiler.hh"
#include "pdm/types/manager.hh"
#include "pdm/types/var.hh"

#include "pdm/feedback/feedback.hh"
#include "pdm/feedback/letter.hh"
#include "pdm/feedback/severity.hh"
#include "pdm/feedback/note.hh"

#include "pdm/ast/module/pkg-bundle-mod-exp.hh"

#include "defn.hh"

// helpers:
namespace pdm::scoper {
    static ast::BaseModExp* original_mod_exp_of_import(Defn const* module_defn);
}

namespace pdm::scoper {

    //
    //
    // Scoper:
    //
    //

    Scoper::Scoper(Compiler* compiler_ptr)
    :   m_compiler_ptr(compiler_ptr),
        m_id_exp_orders(),
        m_id_type_spec_orders(),
        m_id_class_spec_orders(),
        m_import_orders(),
        m_using_orders(),
        m_finished(false)
    {
        m_root_frame = new RootFrame(compiler()->types_mgr());
    }

    types::Manager* Scoper::types_mgr() const {
        return m_compiler_ptr->types_mgr();
    }

    bool Scoper::scope_script(ast::Script* script) {
        if (finished()) {
            if (DEBUG) {
                assert(0 && "ScoperError: cannot call `scope_script` after 'finish'.");
            }
            return false;
        }

        ScriptScoperVisitor visitor{this};
        return visitor.visit(script);
    }

    bool Scoper::scope_package(ast::Package* package) {
        if (finished()) {
            if (DEBUG) {
                assert(0 && "ScoperError: cannot call `scope_package` after 'finish'.");
            }
            return false;
        }

        // defining the symbols found in this package into an exported package_root_frame:

        auto package_root_frame = new Frame(FrameKind::Package, root_frame());
        package->x_export_frame(package_root_frame);
        for (auto base_export_field: package->exports_fields()) {
            DefnKind defn_kind;
            types::TypeVar* tv;
            scoper::Frame* field_module_frame = nullptr;
            {
                auto export_field_kind = base_export_field->kind();
                switch (export_field_kind)
                {
                    case ast::Kind::PackageExportField_ImportAllModulesFrom: {
                        defn_kind = DefnKind::Package_ImportBundleModule;
                        auto field = dynamic_cast<ast::Package::ExportField_ImportAllModulesFrom*>(base_export_field);
                        std::string tv_name = ast::kind_as_text(export_field_kind);
                        tv = types_mgr()->new_unknown_type_var(std::move(tv_name), base_export_field);

                        // creating a new frame nested within the exported frame:
                        // - can access all definitions
                        // - any new definitions in this frame do not influence the old one
                        auto from_source_node = field->x_origin_source_node();
                        assert(from_source_node && "Expected an export source node from DD.");

                        auto from_source_frame = from_source_node->x_export_frame();
                        assert(from_source_node && "Expected an export frame on source node from DD.");

                        field_module_frame = new scoper::Frame(FrameKind::Package, from_source_frame);

                        break;
                    }
                    case ast::Kind::PackageExportField_ExternModuleInC: {
                        defn_kind = DefnKind::Package_ExternModule;
                        auto field = dynamic_cast<ast::Package::ExportField_ExternModuleInC*>(base_export_field);
                        std::string tv_name = "PackageExportField_ImportAllModulesFrom";
                        tv = types_mgr()->new_unknown_type_var(std::move(tv_name), base_export_field);

                        field_module_frame = new scoper::Frame(FrameKind::Package, package_root_frame);
                        // todo: define symbols in `field_module_frame` for 'extern' module.

                        break;
                    }
                    default: {
                        assert(0 && "NotImplemented: unknown ast::Kind::PackageExportField_?");
                    }
                }
            }
            auto defn = new Defn {
                defn_kind,
                base_export_field->name(),
                base_export_field,
                tv
            };
            base_export_field->mod_exp()->x_module_var(tv);
            base_export_field->mod_exp()->x_module_frame(field_module_frame);
            bool defn_ok = package_root_frame->define(defn);
            if (!defn_ok) {
                assert(0 && "NotImplemented: report multiple package export fields have same name.");
            }
        }
        return true;
    }

    bool Scoper::finish() {
        m_finished = true;

        bool ok = true;

        // IdExp
        for (IdExpLookupOrder id_exp_order: m_id_exp_orders) {
            ast::IdExp* id_exp = id_exp_order.id_exp;
            intern::String id_name = id_exp->name();
            Defn const* opt_defn = id_exp_order.lookup_context->lookup(id_name);
            if (opt_defn != nullptr) {
                id_exp->x_defn(opt_defn);
            } else {
                // post feedback about a value ID that was used but not defined.
                std::string headline = "Value ID '" + std::string(id_name.content()) + "' used but not defined";
                std::string desc = "";
                std::vector<feedback::Note*> notes(1); {
                    source::Loc defn_loc = id_exp->loc();
                    std::string defn_desc = "see here...";
                    notes[0] = new feedback::SourceLocNote(std::move(defn_desc), defn_loc);
                }
                feedback::post(new feedback::Letter(
                    feedback::Severity::Error,
                    std::move(headline),
                    std::move(desc),
                    std::move(notes)
                ));
                ok = false;
            }
        }

        // IdTypeSpec
        for (IdTypeSpecLookupOrder id_type_spec_order: m_id_type_spec_orders) {
            ast::IdTypeSpec* id_type_spec = id_type_spec_order.type_spec;
            intern::String id_name = id_type_spec_order.type_spec->name();
            Defn const* defn = id_type_spec_order.lookup_context->lookup(id_name);
            if (defn != nullptr) {
                id_type_spec_order.type_spec->x_defn(defn);
            } else {
                // post feedback about a type ID that was used but not defined.
                std::string headline = "Type ID '" + std::string(id_name.content()) + "' used but not defined";
                std::string desc = "";
                std::vector<feedback::Note*> notes(1); {
                    source::Loc defn_loc = id_type_spec->loc();
                    std::string defn_desc = "see here...";
                    notes[0] = new feedback::SourceLocNote(std::move(defn_desc), defn_loc);
                }
                feedback::post(new feedback::Letter(
                    feedback::Severity::Error,
                    std::move(headline),
                    std::move(desc),
                    std::move(notes)
                ));
                ok = false;
            }
        }

        // IdClassSpec:
        for (IdClassSpecLookupOrder id_class_spec_order: m_id_class_spec_orders) {
            ast::IdClassSpec* id_class_spec = id_class_spec_order.class_spec;
            intern::String id_name = id_class_spec_order.class_spec->name();
            Defn const* defn = id_class_spec_order.lookup_context->lookup(id_name);
            if (defn != nullptr) {
                id_class_spec_order.class_spec->x_defn(defn);
            } else {
                // post feedback about a class ID that was used but not defined:
                std::string headline = "Class ID '" + std::string(id_name.content()) + "' used but not defined";
                std::string desc = "";
                std::vector<feedback::Note*> notes(1); {
                    source::Loc defn_loc = id_class_spec->loc();
                    std::string defn_desc = "see here...";
                    notes[0] = new feedback::SourceLocNote(std::move(defn_desc), defn_loc);
                }
                feedback::post(new feedback::Letter(
                    feedback::Severity::Error,
                    std::move(headline),
                    std::move(desc),
                    std::move(notes)
                ));
                ok = false;
            }
        }

        // Import
        // - important to traverse in reverse-order, assuming scripts scoped in DD order.
        // - this allows leaves to set pointers for intermediate nodes to use.
        for (auto it = m_import_orders.rbegin(); it != m_import_orders.rend(); it++) {
            ImportLookupOrder import_order = *it;

            // fetching the exported frame:
            ast::ImportStmt::Field* import_field = import_order.import_field;
            ast::ISourceNode* origin_source_node = import_field->x_origin_source_node();
            if (origin_source_node == nullptr) {
                // posting feedback about an import failure:
                std::string headline = "Import '" + import_field->import_name().cpp_str() + "' could not be resolved.";
                std::string desc = "From '" + import_field->parent_group()->from_path().string() + "'";
                std::vector<feedback::Note*> notes{1}; {
                    std::string note_desc0 = "at import statement here...";
                    notes[0] = new feedback::SourceLocNote(std::move(note_desc0), import_field->loc());
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

            // looking up the exported symbol in the exported frame:
            Frame* exported_frame = origin_source_node->x_export_frame();
            if (exported_frame == nullptr) {
                assert(0 && "Successfully retrieved an origin source node, but no frame was exported.");
                continue;
            }
            Context* first_ctx = exported_frame->first_context();
            Context* last_ctx = exported_frame->last_context();
            Defn const* module_defn = last_ctx->lookup_until(import_field->import_name(), first_ctx);
            if (module_defn == nullptr) {
                // posting feedback about importing an undefined symbol
                std::string headline = "Module '" + import_field->import_name().cpp_str() + "' could not be found in the origin script.";
                std::string desc = "From '" + import_field->parent_group()->from_path().string() + "'";
                std::vector<feedback::Note*> notes{1}; {
                    std::string note_desc0 = "at import statement here...";
                    notes[0] = new feedback::SourceLocNote(std::move(note_desc0), import_field->loc());
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

            // checking the exported symbol's kind:
            if (!module_defn_kind(module_defn->kind())) {
                // posting feedback about importing an undefined symbol
                std::string headline = "Symbol '" + import_field->import_name().cpp_str() + "' is not importable.";
                std::string desc = "From '" + import_field->parent_group()->from_path().string() + "'";
                std::vector<feedback::Note*> notes{2}; {
                    std::string note_desc0 = "at import statement here...";
                    notes[0] = new feedback::SourceLocNote(std::move(note_desc0), import_field->loc());

                    std::string note_desc1 = "non-importable node here (expected module or imported module)...";
                    notes[1] = new feedback::SourceLocNote(std::move(note_desc1), module_defn->defn_node()->loc());
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

            // setting the exported 'defn' tv so the typer can equate both Vars:
            ast::BaseModExp* original_mod_exp = original_mod_exp_of_import(module_defn);
            assert(original_mod_exp && "Failed to locate original mod exp of import.");
            import_field->x_origin_mod_exp(original_mod_exp);
        }

        // Using
        // todo: rename to 'extend' such that a module may extend another
        for (UsingLookupOrder using_order: m_using_orders) {
            ast::UsingStmt* using_stmt = using_order.using_stmt;

            // lookup 'module_name' in specified context.
            Defn const* module_defn = using_order.lookup_context->lookup(using_stmt->module_name());

            // check that 'using' not applied to an 'package-content' module, only 'importable' ones
            if (!module_defn_kind(module_defn->kind())) {
                // todo: post feedback about using a non-module.
                assert(0 && "NotImplemented: error reporting on 'using/extend'-ing a non-module");
                ok = false;
                continue;
            }

            // linking to an appropriate frame:
            ast::BaseModExp* original_mod_exp = original_mod_exp_of_import(module_defn);
            Frame* module_frame = original_mod_exp->x_module_frame();
            using_order.lookup_context->link(module_frame, using_stmt->suffix());
        }

        // ModAddressLookupOrders:
        // Each 'ModAddress' (i.e. a::b::c::, multiple 'residents' can share a module) requires a sequence of successive
        // queries.
        // - using grammar, recursive queries encoded as nested nodes
        // - so, important to traverse in reverse order such that we go from last-visited (original parent) to
        //   first-visited
        // - provides module targets to type ModAddressId{TypeSpec|ClassSpec} using `x_defn_var`
        // - if no opt_parent_module is provided, equivalent to an ID lookup.
        // NOTE: ModAddress-X gets resolved in Typer module.
        for (auto order_it = m_mod_address_orders.begin(); order_it != m_mod_address_orders.end(); order_it++) {
            ModAddressLookupOrder order = *order_it;
            ast::ModAddress* mod_address = order.mod_address;
            assert(mod_address->template_args().empty() && "NotImplemented: template calls in mod addresses");

            Defn const* module_defn = nullptr;
            if (mod_address->opt_parent_address()) {
                // parent address provided: lookup in lhs module
                auto lhs_origin_mod_exp = mod_address->opt_parent_address()->x_origin_mod_exp();
                assert(lhs_origin_mod_exp && "Expected non-nullptr lhs_origin_mod_exp when scoping ModAddress");

                // if the parent origin is unknown, an error has already been reported. ignore and move on.
                if (!lhs_origin_mod_exp) {
                    continue;
                }

                // if traversing in reverse order and visit-order correct, LHS' origin should already be known:
                if (lhs_origin_mod_exp) {
                    // looking up in LHS:
                    module_defn = lhs_origin_mod_exp->x_module_frame()->last_context()->lookup(mod_address->rhs_name());
                } else {
                    assert(lhs_origin_mod_exp && "Iterating/appending 'ModAddressLookupOrder's incorrectly-- order error.");
                }
            } else {
                // parent address not provided: lookup in the context where this address was used:
                module_defn = order.lookup_context->lookup(mod_address->rhs_name());
            }
            if (module_defn) {
                // lookup succeeded!
                ast::BaseModExp* origin_mod_exp = original_mod_exp_of_import(module_defn);
                assert(origin_mod_exp && "error in Scoper::finish: could not find origin mod_exp of import");
                mod_address->x_origin_mod_exp(origin_mod_exp);
            } else {
                // lookup failed... fail & post feedback.
                ok = false;
                std::string headline; {
                    if (mod_address->opt_parent_address()) {
                        headline = "Field '<...>::" + mod_address->rhs_name().cpp_str() + "' used, but not defined.";
                    } else {
                        headline = "Symbol '" + mod_address->rhs_name().cpp_str() + "' used, but not defined.";
                    }
                }
                std::string desc = "Are you sure the module and its field is imported/defined?";
                std::vector<feedback::Note*> notes{1}; {
                    std::string desc0 = "see usage here...";
                    notes[0] = new feedback::AstNodeNote(std::move(desc0), mod_address);
                }
                feedback::post(new feedback::Letter(
                    feedback::Severity::Error,
                    std::move(headline), std::move(desc), std::move(notes)
                ));
            }
        }

        return ok;
    }

    // debug:
    void Scoper::print(printer::Printer* printer) {
        printer::print_c_str(printer, "Scoper dump");
        printer::print_newline_indent(printer);
        m_root_frame->print(printer);
        printer::print_newline_exdent(printer);
    }

    //
    //
    // ScriptScoperVisitor:
    //
    //

    //
    // helpers:
    //

    ScriptScoperVisitor::ScriptScoperVisitor(Scoper* scoper_ref)
    : m_scoper_ref(scoper_ref),
      m_overhead_chain_exp_count(0) 
    {
        m_frame_stack.push(scoper_ref->root_frame());
    }

    void ScriptScoperVisitor::push_frame(FrameKind frame_kind) {
        m_frame_stack.push(new Frame(frame_kind, top_frame()));

        if (DEBUG) {
            // std::cout << "Push (" << m_frame_stack.size() << ")" << std::endl;
        }
    }
    void ScriptScoperVisitor::pop_frame() {
        m_frame_stack.pop();
        
        if (DEBUG) {
            assert(!m_frame_stack.empty() && "Cannot pop root frame in scoper.");
            // std::cout << "Pop (" << m_frame_stack.size() << ")" << std::endl;
        }
    }

    void ScriptScoperVisitor::place_id_exp_lookup_order(ast::IdExp* exp) {
        Scoper::IdExpLookupOrder order {exp, top_frame()->last_context()};
        scoper()->m_id_exp_orders.push_back(order);
    }
    void ScriptScoperVisitor::place_id_type_spec_lookup_order(ast::IdTypeSpec* id_type_spec) {
        Scoper::IdTypeSpecLookupOrder order {id_type_spec, top_frame()->last_context()};
        scoper()->m_id_type_spec_orders.push_back(order);
    }
    void ScriptScoperVisitor::place_id_class_spec_lookup_order(ast::IdClassSpec* id_class_spec) {
        Scoper::IdClassSpecLookupOrder order {id_class_spec, top_frame()->last_context()};
        scoper()->m_id_class_spec_orders.push_back(order);
    }
    void ScriptScoperVisitor::place_import_lookup_order(ast::ImportStmt::Field* import_field) {
        Scoper::ImportLookupOrder order {import_field, top_frame()->last_context()};
        scoper()->m_import_orders.push_back(order);
    }
    void ScriptScoperVisitor::place_using_lookup_order(ast::UsingStmt* using_stmt) {
        Scoper::UsingLookupOrder order {using_stmt, top_frame()->last_context()};
        scoper()->m_using_orders.push_back(order);
    }
    void ScriptScoperVisitor::place_mod_address_lookup_order(ast::ModAddress* mod_address) {
        assert(mod_address && "Cannot place lookup order with nullptr mod address.");
        Scoper::ModAddressLookupOrder order {mod_address, top_frame()->last_context()};
        scoper()->m_mod_address_orders.push_back(order);
    }

    void ScriptScoperVisitor::post_overlapping_defn_error(std::string defn_kind, Defn const* new_defn) {
        Context* tried_context = top_frame()->last_context();
        post_overlapping_defn_error(std::move(defn_kind), new_defn, tried_context);
    }
    void ScriptScoperVisitor::post_overlapping_defn_error(std::string defn_kind, Defn const* new_defn, Context* tried_context) {
        Defn const* old_defn = tried_context->lookup_until(new_defn->name(), tried_context);
        help_post_defn_failure(std::move(defn_kind), new_defn, old_defn);
    }
    void ScriptScoperVisitor::help_post_defn_failure(std::string defn_kind, Defn const* new_defn, Defn const* old_defn) {
        std::string headline = "Symbol '" + std::string(new_defn->name().content()) + "' conflicts with an existing definition in the same context.";
        std::string more = (
            "Note that symbols in the same " + defn_kind + " cannot shadow."
        );
        std::vector<feedback::Note*> notes{2}; {
            std::string old_desc = "Symbol was first defined here...";
            notes[0] = new feedback::SourceLocNote(std::move(old_desc), old_defn->defn_node()->loc());
            std::string new_desc = "Overlapping symbol defined here...";
            notes[1] = new feedback::SourceLocNote(std::move(new_desc), new_defn->defn_node()->loc());
        }
        feedback::post(new feedback::Letter(
            feedback::Severity::Error,
            std::move(headline),
            std::move(more),
            std::move(notes)
        ));
    }

    ast::BaseModExp* original_mod_exp_of_import(Defn const* module_defn) {
        ast::BaseModExp* original_mod_exp = nullptr;
        {
            switch (module_defn->kind())
            {
                case DefnKind::Module:
                {
                    auto node = dynamic_cast<ast::Node*>(module_defn->defn_node());

                    auto script_field = dynamic_cast<ast::Script::Field*>(node);
                    if (script_field) {
                        original_mod_exp = script_field->rhs_mod_exp();
                    }
                    auto mod_field = dynamic_cast<ast::NativeModExp::ModuleField*>(node);
                    if (mod_field) {
                        original_mod_exp = mod_field->rhs_mod_exp();
                    }
                    break;
                }
                case DefnKind::ImportModule:
                {
                    auto imported_field = dynamic_cast<ast::ImportStmt::Field*>(module_defn->defn_node());
                    assert(imported_field != nullptr);
                    // from dependency dispatcher:
                    original_mod_exp = imported_field->x_origin_mod_exp();
                    break;
                }
                case DefnKind::Package_ExternModule:
                case DefnKind::Package_ImportBundleModule:
                {
                    auto package_export_field = dynamic_cast<ast::Package::ExportField*>(module_defn->defn_node());
                    original_mod_exp = package_export_field->mod_exp();
                    break;
                }
                default:
                {
                    // std::cout << "Unknown DefnKind: " << defn_kind_as_text(module_defn->kind()) << std::endl;
                    assert(original_mod_exp && "Mod expression lookup failed: unknown DefnKind");
                }
            }
        }
        return original_mod_exp;
    }

    //
    // visitor methods:
    //

    // scripts:
    bool ScriptScoperVisitor::on_visit_script(ast::Script* script, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            push_frame(FrameKind::Script);
        } else {
            // popping the script frame:
            Frame* script_frame = top_frame();
            pop_frame();

            // storing the frame on the script node for later (for imports):
            assert(script_frame && "Cannot export a NULL frame for a script.");
            script->x_export_frame(script_frame);
        }
        return true;
    }
    bool ScriptScoperVisitor::on_visit_script_field(ast::Script::Field* field, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            // defining the script field symbol for a module:
            types::TypeVar* script_field_tv = nullptr; {
                std::string tv_name = "ScriptField(akaMod)";
                script_field_tv = scoper()->types_mgr()->new_unknown_type_var(std::move(tv_name));
            }
            auto new_defn = new Defn {
                DefnKind::Module,
                field->name(),
                field,
                script_field_tv
            };
            bool defn_ok = top_frame()->define(new_defn);
            if (!defn_ok) {
                post_overlapping_defn_error("module field in a script", new_defn);
                return false;
            }

            // storing result on the node:
            field->x_defn_var(script_field_tv);

            // pushing a frame for RHS content:
            push_frame(FrameKind::ScriptFieldRhs);
        } else {
            // popping the script RHS frame:
            // Frame* script_field_frame = top_frame();
            pop_frame();
        }
        return true;
    }

    //
    // Modules:
    //

    bool ScriptScoperVisitor::on_visit_native_mod_exp(ast::NativeModExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            // storing the Frame and TV on the module for later:
            // node->x_module_frame(module_frame);
            // node->x_module_tv(module_tv);

            types::TypeVar* module_tv = nullptr; {
                std::string tv_name = "AnonymousModuleExp";
                module_tv = scoper()->types_mgr()->new_unknown_type_var(std::move(tv_name), node);
            }
            node->x_module_var(module_tv);

            push_frame(FrameKind::ModuleBody);
        } else {
            node->x_module_frame(top_frame());
            pop_frame();
        }
        return true;
    }
    bool ScriptScoperVisitor::on_visit_mod_mod_field(ast::NativeModExp::ModuleField* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            // creating a 'var':
            types::Var* mod_val_var = nullptr; {
                std::string tv_prefix = "NativeModExp_ModField:";
                std::string tv_name = tv_prefix + node->name().content();
                mod_val_var = scoper()->types_mgr()->new_unknown_type_var(std::move(tv_name), node);
            }

            // adding the new defn:
            auto new_defn = new Defn {
                DefnKind::Module,
                node->name(),
                node,
                mod_val_var
            };
            bool defn_ok = top_frame()->define(new_defn);
            if (!defn_ok) {
                post_overlapping_defn_error("module field in a module", new_defn);
                return false;
            }

            // storing result on the node:
            node->x_defn(new_defn);

            push_frame(FrameKind::ValueModFieldRhs);
        } else {
            pop_frame();
        }
        return true;
    }
    bool ScriptScoperVisitor::on_visit_value_mod_field(ast::NativeModExp::ValueField* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            // creating the var:
            types::Var* type_var = nullptr;

            // single type
            std::string tv_prefix = "NativeModExp_ValueField:";
            std::string tv_name = tv_prefix + node->name().content();
            type_var = scoper()->types_mgr()->new_unknown_type_var(std::move(tv_name), node);

            // defining the var in the current context:
            auto new_defn = new Defn {
                DefnKind::Val,
                node->name(),
                node,
                type_var
            };
            bool defn_ok = top_frame()->define(new_defn);
            if (!defn_ok) {
                post_overlapping_defn_error("value field in a module", new_defn);
                return false;
            }

            // storing the var on the node:
            node->x_defn(new_defn);

            // pushing attribs/frames for nested defns:
            push_frame(FrameKind::TypeModFieldRhs);
        } else {
            pop_frame();
        }
        return true;
    }
    bool ScriptScoperVisitor::on_visit_type_mod_field(ast::NativeModExp::TypeField *node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            // creating the var:
            types::Var* type_var = nullptr;

            // single type
            std::string tv_prefix = "NativeModExp_TypeField:";
            std::string tv_name = tv_prefix + node->name().content();
            type_var = scoper()->types_mgr()->new_unknown_type_var(std::move(tv_name));

            // defining the var in the current context:
            auto new_defn = new Defn {
                DefnKind::Type,
                node->name(),
                node,
                type_var
            };
            bool defn_ok = top_frame()->define(new_defn);
            if (!defn_ok) {
                post_overlapping_defn_error("type field in a module", new_defn);
                return false;
            }

            // storing the var on the node:
            node->x_defn(new_defn);

            // pushing attribs/frames for nested defns:
            push_frame(FrameKind::TypeModFieldRhs);
        } else {
            pop_frame();
        }
        return true;
    }
    bool ScriptScoperVisitor::on_visit_class_mod_field(ast::NativeModExp::ClassField *node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            // creating the typeclass var:
            types::Var* typeclass_var; {
                std::string cv_prefix = "NativeModExp_ClassField:";
                std::string cv_name = cv_prefix + node->name().content();
                typeclass_var = scoper()->types_mgr()->new_unknown_class_var(std::move(cv_name), node);
            }

            // defining the defn var in the current context:
            auto new_defn = new Defn {
                DefnKind::Typeclass,
                node->name(),
                node,
                typeclass_var
            };
            bool defn_ok = top_frame()->define(new_defn);
            if (!defn_ok) {
                post_overlapping_defn_error("typeclass statement", new_defn);
                return false;
            }

            // storing the defn var on the node:
            node->x_defn(new_defn);

            // pushing attribs/frames for nested defns:
            push_frame(FrameKind::ClassModFieldRhs);
            {
                // defining the candidate explicitly:
                std::string candidate_var_name = "TypeclassCandidate:" + std::string(node->name().content());
                types::TypeVar* candidate_var = scoper()->types_mgr()->new_unknown_type_var(
                    std::move(candidate_var_name), node
                );
                assert(candidate_var != nullptr);

                auto candidate_defn = new Defn {
                    DefnKind::TypeclassCandidate,
                    node->name(),
                    node,
                    candidate_var
                };
                bool candidate_defn_ok = top_frame()->define(candidate_defn);
                if (!defn_ok) {
                    post_overlapping_defn_error("typeclass candidate", new_defn);
                    return false;
                }
            }
        } else {
            pop_frame();
        }
        return true;
    }
    bool ScriptScoperVisitor::on_visit_mod_address(ast::ModAddress* node, VisitOrder visit_order) {
        // important to perform in 'post' order, such that most nested are processed first.
        if (visit_order == VisitOrder::Post) {
            place_mod_address_lookup_order(node);
        }
        return true;
    }

    // statements:

    // type and enum stmts create TVs, not CVs, that are typed as returns from a polymorphic
    // function.
    // This function is implicitly defined within the system.
    // Thus, use TV, not CV, even if targs present.
    bool ScriptScoperVisitor::on_visit_enum_type_spec(ast::EnumTypeSpec *node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            // pushing frames/attribs for nested defns:
            push_frame(FrameKind::EnumTypeSpecBody);
        } else {
            pop_frame();
        }
        return true;
    }

    bool ScriptScoperVisitor::on_visit_const_stmt(ast::ConstStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            if (in_chain_exp()) {
                top_frame()->shadow(ContextKind::ChainLink);
            }

            // in order to specify what kind of definition this lpattern performs, push to stack:
            m_lpattern_defn_kind_stack.push(DefnKind::Const);
        } else {
            m_lpattern_defn_kind_stack.pop();
        }
        return true;
    }
    bool ScriptScoperVisitor::on_visit_val_stmt(ast::ValStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            if (in_chain_exp()) {
                top_frame()->shadow(ContextKind::ChainLink);
            }

            // in order to specify what kind of definition this lpattern performs, push to stack:
            m_lpattern_defn_kind_stack.push(DefnKind::Val);
        } else {
            m_lpattern_defn_kind_stack.pop();
        }
        return true;
    }
    bool ScriptScoperVisitor::on_visit_var_stmt(ast::VarStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            if (in_chain_exp()) {
                top_frame()->shadow(ContextKind::ChainLink);
            }

            // in order to specify what kind of definition this lpattern performs, push to stack:
            m_lpattern_defn_kind_stack.push(DefnKind::Var);
        } else {
            m_lpattern_defn_kind_stack.pop();
        }
        return true;
    }

    bool ScriptScoperVisitor::on_visit_extern_stmt(ast::ExternStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            types::TypeVar* ext_mod_tv = nullptr; {
                std::string tv_prefix = "Defn(ExternModule):";
                std::string tv_name = std::move(tv_prefix) + node->ext_mod_name().content();
                ext_mod_tv = scoper()->types_mgr()->new_unknown_type_var(std::move(tv_name), node);
            }
            auto new_defn = new Defn(
                DefnKind::Package_ExternModule,
                node->ext_mod_name(),
                node,
                ext_mod_tv
            );
            assert(0 && "DISABLED: 'extern_stmt'");
            bool defn_ok = top_frame()->define(new_defn);
            if (!defn_ok) {
                // post feedback here
            }
        }
        return true;
    }
    bool ScriptScoperVisitor::on_visit_import_stmt(ast::ImportStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            for (ast::ImportStmt::FieldGroup* group: node->field_groups()) {
                for (ast::ImportStmt::Field* field: group->fields()) {
                    // defining the new symbol with a new, exported TV:
                    types::TypeVar* mod_tv = nullptr; {
                        std::string tv_prefix = "ExportedProxy:";
                        std::string tv_name = std::move(tv_prefix) + field->import_name().content();
                        mod_tv = scoper()->types_mgr()->new_unknown_type_var(std::move(tv_name), node);
                    }
                    auto new_defn = new Defn {
                        DefnKind::ImportModule,
                        field->import_name(),
                        field,
                        mod_tv
                    };
                    bool defn_ok = top_frame()->define(new_defn);
                    if (!defn_ok) {
                        post_overlapping_defn_error("import", new_defn);
                        return false;
                    }
                    field->x_defn(new_defn);

                    // storing the exported TV to link against later, placing an order to link:
                    // field->x_exported_tv(mod_tv);
                    place_import_lookup_order(field);
                }
            }
        }
        return true;
    }
    bool ScriptScoperVisitor::on_visit_set_stmt(ast::SetStmt* node, VisitOrder visit_order) {
        // do nothing
        return true;
    }
    bool ScriptScoperVisitor::on_visit_discard_stmt(ast::DiscardStmt* node, VisitOrder visit_order) {
        // do nothing
        return true;
    }
    bool ScriptScoperVisitor::on_visit_using_stmt(ast::UsingStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            // just placing an order; with 'link' there:
            place_using_lookup_order(node);
        }
        return true;
    }

    // expressions:
    bool ScriptScoperVisitor::on_visit_unit_exp(ast::UnitExp* node, VisitOrder visit_order) {
        return true;
    }
    bool ScriptScoperVisitor::on_visit_int_exp(ast::IntExp* node, VisitOrder visit_order) {
        return true;
    }
    bool ScriptScoperVisitor::on_visit_float_exp(ast::FloatExp* node, VisitOrder visit_order) {
        return true;
    }
    bool ScriptScoperVisitor::on_visit_string_exp(ast::StringExp* node, VisitOrder visit_order) {
        return true;
    }
    bool ScriptScoperVisitor::on_visit_id_exp(ast::IdExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            place_id_exp_lookup_order(node);
        }
        return true;
    }
    bool ScriptScoperVisitor::on_visit_paren_exp(ast::ParenExp* node, VisitOrder visit_order) {
        return true;
    }
    bool ScriptScoperVisitor::on_visit_tuple_exp(ast::TupleExp* node, VisitOrder visit_order) {
        return true;
    }
    bool ScriptScoperVisitor::on_visit_array_exp(ast::ArrayExp* node, VisitOrder visit_order) {
        return true;
    }
    bool ScriptScoperVisitor::on_visit_struct_exp(ast::StructExp* node, VisitOrder visit_order) {
        return true;
    }
    bool ScriptScoperVisitor::on_visit_type_query_exp(ast::TypeQueryExp* node, VisitOrder visit_order) {
        return true;
    }
    bool ScriptScoperVisitor::on_visit_chain_exp(ast::ChainExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            inc_overhead_chain_exp_count();
            push_frame(FrameKind::Chain);
        } else {
            pop_frame();
            dec_overhead_chain_exp_count();
        }
        return true;
    }
    bool ScriptScoperVisitor::on_visit_lambda_exp(ast::LambdaExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            // all below vpatterns must be defined
            m_vpattern_defn_kind_stack.push(DefnKind::FormalVArg);
        } else {
            m_vpattern_defn_kind_stack.pop();
        }
        return true;
    }
    bool ScriptScoperVisitor::on_visit_if_exp(ast::IfExp* node, VisitOrder visit_order) {
        return true;
    }
    bool ScriptScoperVisitor::on_visit_dot_index_exp(ast::DotIndexExp* node, VisitOrder visit_order) {
        return true;
    }
    bool ScriptScoperVisitor::on_visit_dot_name_exp(ast::DotNameExp* node, VisitOrder visit_order) {
        return true;
    }
    bool ScriptScoperVisitor::on_visit_module_dot_exp(ast::ModuleDotExp* node, VisitOrder visit_order) {
        return true;
    }
    bool ScriptScoperVisitor::on_visit_unary_exp(ast::UnaryExp* node, VisitOrder visit_order) {
        return true;
    }
    bool ScriptScoperVisitor::on_visit_binary_exp(ast::BinaryExp* node, VisitOrder visit_order) {
        return true;
    }
    bool ScriptScoperVisitor::on_visit_v_call_exp(ast::VCallExp* node, VisitOrder visit_order) {
        return true;
    }
    bool ScriptScoperVisitor::on_visit_t_call_exp(ast::TCallExp* node, VisitOrder visit_order) {
        return true;
    }
    
    // patterns:
    bool ScriptScoperVisitor::on_visit_v_pattern(ast::VPattern* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            for (ast::VPattern::Field* field: node->fields()) {
                std::string field_prefix = defn_kind_as_text(m_vpattern_defn_kind_stack.top());
                std::string field_name = field->lhs_name().content();
                std::string tv_name = "VPattern(" + field_prefix + "):" + field_name;
                types::TypeVar* field_tv = scoper()->types_mgr()->new_unknown_type_var(std::move(tv_name), node);
                auto new_defn = new Defn {
                    m_vpattern_defn_kind_stack.top(),
                    field->lhs_name(),
                    field,
                    field_tv
                };

                // when vpatterns are used in Fn typespecs, we do not define the symbols in the top frame.
                // in all other cases, we do.
                if (m_vpattern_defn_kind_stack.top() != DefnKind::NO_DEF_FnTypeSpecFormalVArg) {
                    bool defn_ok = top_frame()->define(new_defn);
                    if (!defn_ok) {
                        post_overlapping_defn_error(field_prefix, new_defn);
                        return false;
                    }
                    field->x_defn(new_defn);
                }
            }
        }
        return true;
    }
    bool ScriptScoperVisitor::on_visit_t_pattern(ast::TPattern* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            for (ast::TPattern::Field* field: node->fields()) {
                types::Var* field_var = nullptr;
                std::string field_prefix = defn_kind_as_text(DefnKind::FormalTArg);
                std::string field_name = field->lhs_name().content();
                std::string tv_name = "TPattern(" + field_prefix + "):" + field_name;
                if (field->field_kind() == ast::TPattern::FieldKind::Value) {
                    // storing typeof arg:
                    field_var = scoper()->types_mgr()->new_unknown_type_var(std::move(tv_name), node);
                } else if (field->field_kind() == ast::TPattern::FieldKind::Type) {
                    // storing PROXY arg:
                    // doesn't need a unique soln, typechecked like a class, but has 'typevar' interface for
                    // typing formal arguments in place of (as a proxy of) actual arguments.
                    field_var = scoper()->types_mgr()->new_unknown_type_var(std::move(tv_name), node);
                }
                
                assert(field_var != nullptr && "Unknown TPattern Field Kind or bad var.");

                auto new_defn = new Defn {
                    DefnKind::FormalTArg,
                    field->lhs_name(),
                    field,
                    field_var
                };

                bool defn_ok = top_frame()->define(new_defn);
                if (!defn_ok) {
                    post_overlapping_defn_error(field_prefix, new_defn);
                    return false;
                }
                field->x_defn(new_defn);
            }
        }
        return true;
    }
    bool ScriptScoperVisitor::on_visit_l_pattern(ast::LPattern* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            for (ast::LPattern::Field* field: node->fields()) {
                std::string field_prefix = defn_kind_as_text(m_lpattern_defn_kind_stack.top());
                std::string field_name = field->lhs_name().content();
                std::string tv_name = "LPattern(" + field_prefix + "):" + field_name;
                types::TypeVar* field_tv = scoper()->types_mgr()->new_unknown_type_var(std::move(tv_name), node);
                auto new_defn = new Defn {
                    m_lpattern_defn_kind_stack.top(),
                    field->lhs_name(),
                    field,
                    field_tv
                };
                bool defn_ok = top_frame()->define(new_defn);
                if (!defn_ok) {
                    post_overlapping_defn_error("let-pattern", new_defn);
                    return false;
                }
                field->x_defn(new_defn);
                // field->x_defn_tv(field_tv);
            }
        }
        return true;
    }

    // typespecs:
    bool ScriptScoperVisitor::on_visit_id_type_spec(ast::IdTypeSpec* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            // placing an order:
            place_id_type_spec_lookup_order(node);
        }
        return true;
    }
    bool ScriptScoperVisitor::on_visit_id_class_spec(ast::IdClassSpec* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            // placing an order:
            place_id_class_spec_lookup_order(node);
        }
        return true;
    }
    bool ScriptScoperVisitor::on_visit_ma_class_spec(ast::ModAddressIdClassSpec* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            assert(0 && "NotImplemented: module-prefix-ed class_spec (DotClassSpec)");
        }
        return true;
    }
    bool ScriptScoperVisitor::on_visit_fn_type_spec(ast::FnTypeSpec* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            m_vpattern_defn_kind_stack.push(DefnKind::NO_DEF_FnTypeSpecFormalVArg);
        } else {
            assert(visit_order == VisitOrder::Post);
            m_vpattern_defn_kind_stack.pop();
        }
        return true;
    }
    bool ScriptScoperVisitor::on_visit_tuple_type_spec(ast::TupleTypeSpec* node, VisitOrder visit_order) {
        return true;
    }
    bool ScriptScoperVisitor::on_visit_struct_type_spec(ast::StructTypeSpec* node, VisitOrder visit_order) {
        return true;
    }
    bool ScriptScoperVisitor::on_visit_ma_type_spec(ast::ModAddressIdTypeSpec* node, VisitOrder visit_order) {
        return true;
    }

    // class specs:
    bool ScriptScoperVisitor::on_visit_class_exp_class_spec(ast::ClassExpClassSpec* node, VisitOrder visit_order) {
        assert(0 && "NotImplemented: on_visit_class_exp_class_spec");
        return true;
    }

    // args:
    bool ScriptScoperVisitor::on_visit_t_arg(ast::TArg* t_arg, VisitOrder visit_order) {
        return true;
    }
    bool ScriptScoperVisitor::on_visit_v_arg(ast::VArg* v_arg, VisitOrder visit_order) {
        return true;
    }

    // non-syntax
    bool ScriptScoperVisitor::on_visit_builtin_type_stmt(ast::BuiltinStmt* node, VisitOrder visit_order) {
        return true;
    }

}
