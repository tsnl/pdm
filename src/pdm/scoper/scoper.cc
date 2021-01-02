#include "scoper.hh"

#include <iostream>

#include <string>
#include <cassert>

#include "pdm/types/manager.hh"
#include "pdm/types/var.hh"

#include "pdm/feedback/feedback.hh"
#include "pdm/feedback/letter.hh"
#include "pdm/feedback/severity.hh"
#include "pdm/feedback/note.hh"

// helpers:
namespace pdm::scoper {
    static ast::ModStmt* original_stmt_of_module_defn(Defn const* module_defn);
}

namespace pdm::scoper {

    //
    //
    // Scoper:
    //
    //

    Scoper::Scoper(types::Manager* typer)
    : m_typer(typer),
      m_id_exp_orders(),
      m_id_typespec_orders(),
      m_import_orders(),
      m_using_orders(),
      m_finished(false)
    {
        m_root_frame = new RootFrame(m_typer);
    }

    bool Scoper::scope(ast::Script* script) {
        if (finished()) {
            if (DEBUG) {
                assert(0 && "Scoper: cannot call `scope` after 'finish'.");
            }
            return false;
        }

        ScoperVisitor visitor{this};
        return visitor.visit(script);
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
                std::string headline = "ID '" + std::string(id_name.content()) + "' used but not defined";
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

        // IdTypespec
        for (IdTypespecLookupOrder id_typespec_order: m_id_typespec_orders) {
            ast::IdTypespec* id_typespec = id_typespec_order.id_typespec;
            intern::String id_name = id_typespec_order.id_typespec->name();
            Defn const* defn = id_typespec_order.lookup_context->lookup(id_name);
            if (defn != nullptr) {
                id_typespec_order.id_typespec->x_defn(defn);
            } else {
                // post feedback about a type ID that was used but not defined.
                std::string headline = "ID '" + std::string(id_name.content()) + "' used but not defined";
                std::string desc = "";
                std::vector<feedback::Note*> notes(1); {
                    source::Loc defn_loc = id_typespec->loc();
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
        // important to traverse in reverse-order, assuming scripts scoped in DD order.
        for (auto it = m_import_orders.rbegin(); it != m_import_orders.rend(); it++) {
            ImportLookupOrder import_order = *it;
            
            // fetching the exported frame:
            ast::ImportStmt* import_stmt = import_order.import_stmt;
            Frame* origin_script_frame = import_stmt->x_origin_script()->x_script_frame();
            if (origin_script_frame == nullptr) {
                // posting feedback about an import failure:
                std::string headline = "Import '" + std::string(import_stmt->import_name().content()) + "' could not be resolved.";
                std::string desc = "From '" + import_stmt->import_from_str().string() + "'";
                std::vector<feedback::Note*> notes{1}; {
                    std::string desc = "at import statement here...";
                    notes[0] = new feedback::SourceLocNote(std::move(desc), import_stmt->loc());
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
            Context* first_ctx = origin_script_frame->first_context();
            Context* last_ctx = origin_script_frame->last_context();
            Defn const* module_defn = last_ctx->lookup_until(import_stmt->import_name(), first_ctx);
            if (module_defn == nullptr) {
                // posting feedback about importing an undefined symbol
                std::string headline = "Module '" + std::string(import_stmt->import_name().content()) + "' could not be found in the origin script.";
                std::string desc = "From '" + import_stmt->import_from_str().string() + "'";
                std::vector<feedback::Note*> notes{1}; {
                    std::string desc = "at import statement here...";
                    notes[0] = new feedback::SourceLocNote(std::move(desc), import_stmt->loc());
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
                std::string headline = "Symbol '" + std::string(import_stmt->import_name().content()) + "' is not importable.";
                std::string desc = "From '" + import_stmt->import_from_str().string() + "'";
                std::vector<feedback::Note*> notes{2}; {
                    std::string desc0 = "at import statement here...";
                    notes[0] = new feedback::SourceLocNote(std::move(desc0), import_stmt->loc());
                    
                    std::string desc1 = "non-importable node here (expected module or imported module)...";
                    notes[1] = new feedback::SourceLocNote(std::move(desc1), module_defn->defn_node()->loc());
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
            
            // setting the exported 'defn' and 'stmt' so the typer can equate both Vars:
            ast::ModStmt* original_mod_stmt = original_stmt_of_module_defn(module_defn);
            import_stmt->x_origin_mod_stmt(original_mod_stmt);
        }

        // Using
        for (UsingLookupOrder using_order: m_using_orders) {
            ast::UsingStmt* using_stmt = using_order.using_stmt;

            // lookup 'module_name' in specified context.            
            Defn const* module_defn = using_order.lookup_context->lookup(using_stmt->module_name());

            // check that 'using' not applied to an 'extern' module, only 'importable' ones
            if (!module_defn_kind(module_defn->kind())) {
                // todo: post feedback about using a non-module.
                ok = false;
                continue;
            }

            // linking to an appropriate frame:
            ast::ModStmt* original_mod_stmt = original_stmt_of_module_defn(module_defn);
            Frame* module_frame = original_mod_stmt->x_module_frame();
            using_order.lookup_context->link(module_frame, using_stmt->suffix());
        }

        return ok;
    }

    // debug:
    void Scoper::print(printer::Printer& printer) {
        printer.print_cstr("Scoper dump");
        printer.print_newline_indent();
        m_root_frame->print(printer);
        printer.print_newline_deindent();
    }

    //
    //
    // ScoperVisitor:
    //
    //

    //
    // helpers:
    //

    ScoperVisitor::ScoperVisitor(Scoper* scoper_ref)
    : m_scoper_ref(scoper_ref),
      m_overhead_chain_exp_count(0) 
    {
        m_frame_stack.push(scoper_ref->root_frame());
    }

    void ScoperVisitor::push_frame(FrameKind frame_kind) {
        m_frame_stack.push(new Frame(frame_kind, top_frame()));

        if (DEBUG) {
            // std::cout << "Push (" << m_frame_stack.size() << ")" << std::endl;
        }
    }
    void ScoperVisitor::pop_frame() {
        m_frame_stack.pop();
        
        if (DEBUG) {
            assert(!m_frame_stack.empty() && "Cannot pop root frame in scoper.");
            // std::cout << "Pop (" << m_frame_stack.size() << ")" << std::endl;
        }
    }

    void ScoperVisitor::place_id_exp_lookup_order(ast::IdExp* exp) {
        Scoper::IdExpLookupOrder order {exp, top_frame()->last_context()};
        scoper()->m_id_exp_orders.push_back(order);
    }
    void ScoperVisitor::place_id_typespec_lookup_order(ast::IdTypespec* typespec) {
        Scoper::IdTypespecLookupOrder order {typespec, top_frame()->last_context()};
        scoper()->m_id_typespec_orders.push_back(order);
    }
    void ScoperVisitor::place_import_lookup_order(ast::ImportStmt* import_stmt) {
        Scoper::ImportLookupOrder order {import_stmt, top_frame()->last_context()};
        scoper()->m_import_orders.push_back(order);
    }
    void ScoperVisitor::place_using_lookup_order(ast::UsingStmt* using_stmt) {
        Scoper::UsingLookupOrder order {using_stmt, top_frame()->last_context()};
        scoper()->m_using_orders.push_back(order);
    }

    ast::ModStmt* original_stmt_of_module_defn(Defn const* module_defn) {
        ast::ModStmt* original_mod_stmt = nullptr;
        
        if (module_defn->kind() == DefnKind::Module) {
            original_mod_stmt = dynamic_cast<ast::ModStmt*>(module_defn->defn_node());
        }
        else if (module_defn->kind() == DefnKind::ImportModule) {
            ast::ImportStmt* imported_stmt = dynamic_cast<ast::ImportStmt*>(module_defn->defn_node());
            assert(imported_stmt != nullptr);
            // from dependency dispatcher:
            original_mod_stmt = imported_stmt->x_origin_mod_stmt();
        }
        assert(original_mod_stmt != nullptr);
        return original_mod_stmt;
    }
    
    //
    // visitor methods:
    //

    // scripts:
    bool ScoperVisitor::on_visit__script(ast::Script* script, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            push_frame(FrameKind::Script);
        } else {
            // popping the script frame:
            Frame* script_frame = top_frame();
            pop_frame();

            // storing the frame on the script node for later (for imports):
            script->x_script_frame(script_frame);
        }
        return true;
    }

    // statements:
    bool ScoperVisitor::on_visit__mod_stmt(ast::ModStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            push_frame(FrameKind::Module);
        } else {
            // popping the module frame:
            Frame* module_frame = top_frame();
            pop_frame();

            // creating a new TV:
            types::TypeVar* module_tv; {
                std::string tv_prefix = "Defn(Module):";
                std::string tv_name = tv_prefix + node->module_name().content();
                module_tv = scoper()->typer()->new_tv(std::move(tv_name), nullptr, node);
            }

            // defining the new module in the script:
            top_frame()->define(Defn(
                DefnKind::Module,
                node->module_name(),
                node,
                module_tv
            ));

            // storing the Frame and TV on the module for later:
            node->x_module_frame(module_frame);
            node->x_module_tv(module_tv);
        }
        return true;
    }
    bool ScoperVisitor::on_visit__typeclass_stmt(ast::TypeclassStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            types::ClassVar* typeclass_cv = nullptr; {
                std::string cv_prefix = "Defn(Typeclass):";
                std::string cv_name = cv_prefix + node->typeclass_name().content();
                typeclass_cv = scoper()->typer()->new_cv(std::move(cv_name), node);
            }
            top_frame()->define(Defn(
                DefnKind::Typeclass,
                node->typeclass_name(),
                node,
                typeclass_cv
            ));

            push_frame(FrameKind::TypeclassRhs);
        } else {
            pop_frame();
        }
        return true;
    }

    // type and enum stmts create TVs, not CVs, that are typed as returns from a polymorphic
    // function.
    // This function is implicitly defined within the system.
    // Thus, use TV, not CV, even if targs present.
    bool ScoperVisitor::on_visit__type_stmt(ast::TypeStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            types::TypeVar* type_tv = nullptr; {
                std::string tv_prefix = "Defn(Type):";
                std::string tv_name = tv_prefix + node->lhs_name().content();
                type_tv = scoper()->typer()->new_tv(std::move(tv_name));
            }
            top_frame()->define(Defn(
                DefnKind::Type,
                node->lhs_name(),
                node,
                type_tv
            ));

            push_frame(FrameKind::TypeRhs);
        } else {
            pop_frame();
        }
        return true;
    }
    bool ScoperVisitor::on_visit__enum_stmt(ast::EnumStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            types::TypeVar* type_tv = nullptr; {
                std::string tv_prefix = "Defn(Enum):";
                std::string tv_name = tv_prefix + node->name().content();
                type_tv = scoper()->typer()->new_tv(std::move(tv_name), nullptr, node);
            }
            top_frame()->define(Defn(
                DefnKind::Enum,
                node->name(),
                node,
                type_tv
            ));

            push_frame(FrameKind::EnumRhs);
        } else {
            pop_frame();
        }
        return true;
    }

    bool ScoperVisitor::on_visit__fn_stmt(ast::FnStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            types::TypeVar* type_tv = nullptr; {
                std::string tv_prefix = "Defn(Fn):";
                std::string tv_name = tv_prefix + node->name().content();
                type_tv = scoper()->typer()->new_tv(std::move(tv_name), nullptr, node);
            }
            top_frame()->define(Defn(
                DefnKind::Fn,
                node->name(),
                node,
                type_tv
            ));
            push_frame(FrameKind::FnRhs);

            m_vpattern_defn_kind_stack.push(DefnKind::FormalVArg);
        } else {
            m_vpattern_defn_kind_stack.pop();
            pop_frame();
        }
        return true;
    }

    bool ScoperVisitor::on_visit__const_stmt(ast::ConstStmt* node, VisitOrder visit_order) {
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
    bool ScoperVisitor::on_visit__val_stmt(ast::ValStmt* node, VisitOrder visit_order) {
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
    bool ScoperVisitor::on_visit__var_stmt(ast::VarStmt* node, VisitOrder visit_order) {
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

    bool ScoperVisitor::on_visit__extern_stmt(ast::ExternStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            types::TypeVar* ext_mod_tv = nullptr; {
                std::string tv_prefix = "Defn(ExternModule):";
                std::string tv_name = std::move(tv_prefix) + node->ext_mod_name().content();
                ext_mod_tv = scoper()->typer()->new_tv(std::move(tv_name), nullptr, node);
            }
            top_frame()->define(Defn(
                DefnKind::ExternObject,
                node->ext_mod_name(),
                node,
                ext_mod_tv
            ));
        }
        return true;
    }
    bool ScoperVisitor::on_visit__import_stmt(ast::ImportStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            // defining the new symbol with a new, exported TV:
            types::TypeVar* mod_tv = nullptr; {
                std::string tv_prefix = "Defn(ImportModule):";
                std::string tv_name = std::move(tv_prefix) + node->import_name().content();
                mod_tv = scoper()->typer()->new_tv(std::move(tv_name), nullptr, node);
            }
            top_frame()->define(Defn(
                DefnKind::ImportModule,
                node->import_name(),
                node,
                mod_tv
            ));

            // storing the exported TV to link against later, placing an order to link:
            node->x_exported_tv(mod_tv);
            place_import_lookup_order(node);
        }
        return true;
    }
    bool ScoperVisitor::on_visit__set_stmt(ast::SetStmt* node, VisitOrder visit_order) {
        // do nothing
        return true;
    }
    bool ScoperVisitor::on_visit__discard_stmt(ast::DiscardStmt* node, VisitOrder visit_order) {
        // do nothing
        return true;
    }
    bool ScoperVisitor::on_visit__using_stmt(ast::UsingStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            // just placing an order; with 'link' there:
            place_using_lookup_order(node);
        }
        return true;
    }

    // expressions:
    bool ScoperVisitor::on_visit__unit_exp(ast::UnitExp* node, VisitOrder visit_order) {
        return true;
    }
    bool ScoperVisitor::on_visit__int_exp(ast::IntExp* node, VisitOrder visit_order) {
        return true;
    }
    bool ScoperVisitor::on_visit__float_exp(ast::FloatExp* node, VisitOrder visit_order) {
        return true;
    }
    bool ScoperVisitor::on_visit__string_exp(ast::StringExp* node, VisitOrder visit_order) {
        return true;
    }
    bool ScoperVisitor::on_visit__id_exp(ast::IdExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            place_id_exp_lookup_order(node);
        }
        return true;
    }
    bool ScoperVisitor::on_visit__paren_exp(ast::ParenExp* node, VisitOrder visit_order) {
        return true;
    }
    bool ScoperVisitor::on_visit__tuple_exp(ast::TupleExp* node, VisitOrder visit_order) {
        return true;
    }
    bool ScoperVisitor::on_visit__array_exp(ast::ArrayExp* node, VisitOrder visit_order) {
        return true;
    }
    bool ScoperVisitor::on_visit__struct_exp(ast::StructExp* node, VisitOrder visit_order) {
        return true;
    }
    bool ScoperVisitor::on_visit__type_query_exp(ast::TypeQueryExp* node, VisitOrder visit_order) {
        return true;
    }
    bool ScoperVisitor::on_visit__chain_exp(ast::ChainExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            inc_overhead_chain_exp_count();
            push_frame(FrameKind::Chain);
        } else {
            pop_frame();
            dec_overhead_chain_exp_count();
        }
        return true;
    }
    bool ScoperVisitor::on_visit__lambda_exp(ast::LambdaExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            m_vpattern_defn_kind_stack.push(DefnKind::FormalVArg);
        } else {
            m_vpattern_defn_kind_stack.pop();
        }
        return true;
    }
    bool ScoperVisitor::on_visit__if_exp(ast::IfExp* node, VisitOrder visit_order) {
        return true;
    }
    bool ScoperVisitor::on_visit__dot_index_exp(ast::DotIndexExp* node, VisitOrder visit_order) {
        return true;
    }
    bool ScoperVisitor::on_visit__dot_name_exp(ast::DotNameExp* node, VisitOrder visit_order) {
        return true;
    }
    bool ScoperVisitor::on_visit__unary_exp(ast::UnaryExp* node, VisitOrder visit_order) {
        return true;
    }
    bool ScoperVisitor::on_visit__binary_exp(ast::BinaryExp* node, VisitOrder visit_order) {
        return true;
    }
    bool ScoperVisitor::on_visit__vcall_exp(ast::VCallExp* node, VisitOrder visit_order) {
        return true;
    }
    bool ScoperVisitor::on_visit__tcall_exp(ast::TCallExp* node, VisitOrder visit_order) {
        return true;
    }
    
    // patterns:
    bool ScoperVisitor::on_visit__vpattern(ast::VPattern* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            for (ast::VPattern::Field* field: node->fields()) {
                types::TypeVar* field_tv; {
                    std::string field_prefix = defn_kind_as_text(m_vpattern_defn_kind_stack.top());
                    std::string field_name = field->lhs_name().content();
                    std::string tv_name = "VPattern(" + field_prefix + "):" + field_name;
                    field_tv = scoper()->typer()->new_tv(std::move(tv_name), nullptr, node);
                }
                top_frame()->define(Defn(
                    m_vpattern_defn_kind_stack.top(),
                    field->lhs_name(),
                    node,
                    field_tv
                ));
            }
        }
        return true;
    }
    bool ScoperVisitor::on_visit__tpattern(ast::TPattern* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            for (ast::TPattern::Field* field: node->fields()) {
                types::TypeVar* field_tv; {
                    std::string field_prefix = defn_kind_as_text(DefnKind::FormalTArg);
                    std::string field_name = field->lhs_name().content();
                    std::string tv_name = "TPattern(" + field_prefix + "):" + field_name;
                    field_tv = scoper()->typer()->new_tv(std::move(tv_name), nullptr, node);
                }
                top_frame()->define(Defn(
                    DefnKind::FormalTArg,
                    field->lhs_name(),
                    node,
                    field_tv
                ));
            }
        }
        return true;
    }
    bool ScoperVisitor::on_visit__lpattern(ast::LPattern* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            for (ast::LPattern::Field* field: node->fields()) {
                types::TypeVar* field_tv; {
                    std::string field_prefix = defn_kind_as_text(m_lpattern_defn_kind_stack.top());
                    std::string field_name = field->lhs_name().content();
                    std::string tv_name = "LPattern(" + field_prefix + "):" + field_name;
                    field_tv = scoper()->typer()->new_tv(std::move(tv_name), nullptr, node);
                }
                top_frame()->define(Defn(
                    m_lpattern_defn_kind_stack.top(),
                    field->lhs_name(),
                    node,
                    field_tv
                ));
            }
        }
        return true;
    }

    // typespecs:
    bool ScoperVisitor::on_visit__id_typespec(ast::IdTypespec* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            // placing an order:
            place_id_typespec_lookup_order(node);
        }
        return true;
    }
    bool ScoperVisitor::on_visit__fn_typespec(ast::FnTypespec* node, VisitOrder visit_order) {
        return true;
    }
    bool ScoperVisitor::on_visit__tcall_typespec(ast::TCallTypespec* node, VisitOrder visit_order) {
        return true;
    }
    bool ScoperVisitor::on_visit__tuple_typespec(ast::TupleTypespec* node, VisitOrder visit_order) {
        return true;
    }
    bool ScoperVisitor::on_visit__dot_name_typespec_type_prefix(ast::DotNameTypespec_TypePrefix* node, VisitOrder visit_order) {
        return true;
    }
    bool ScoperVisitor::on_visit__dot_name_typespec_mod_prefix(ast::DotNameTypespec_ModPrefix* node, VisitOrder visit_order) {
        return true;
    }
    bool ScoperVisitor::on_visit__struct_typespec(ast::StructTypespec* node, VisitOrder visit_order) {
        return true;
    }
    bool ScoperVisitor::on_visit__paren_typespec(ast::ParenTypespec* node, VisitOrder visit_order) {
        return true;
    }

    // args:
    bool ScoperVisitor::on_visit__targ(ast::TArg* targ, VisitOrder visit_order) {
        return true;
    }
    bool ScoperVisitor::on_visit__varg(ast::VArg* varg, VisitOrder visit_order) {
        return true;
    }

    // non-syntax
    bool ScoperVisitor::on_visit__builtin_type_stmt(ast::BuiltinTypeStmt* node, VisitOrder visit_order) {
        return true;
    }

}
