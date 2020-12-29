#include "scoper.hh"

#include <string>

#include "pdm/typer/typer.hh"

namespace pdm::scoper {

    // - pass 1: 'modconst'
    //   define frames, contexts, and symbols for all 
    //   modules & consts 
    //   with metavar TVs
    //   - each script is 1 frame with 1 Context containing all modules
    //   - each module is 1 frame with 1 Context
    // - pass 2: 'lookups'
    //   - resolve each ID's definition
    //   - set TV equality using a VIdLookupRule/TIdLookupRule
    
    // a typical Frame tree looks like... (`-` => separate defs, `*` => shared defs)
    // root
    // - script #1:
    //   * module #1:
    //     * module #1 defn #1
    //     * module #1 defn #2
    //     * ...
    //   * module #2:

    // scripts:
    bool ScoperVisitor::on_visit__script(ast::Script* script, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            scoper()->push_frame(FrameKind::Script);
        } else {
            scoper()->pop_frame();
        }
        return true;
    }

    // statements:
    bool ScoperVisitor::on_visit__mod_stmt(ast::ModStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            scoper()->push_frame(FrameKind::Module);
        } else {
            // popping the module frame:
            Frame* module_frame = scoper()->top_frame();
            scoper()->pop_frame();

            // creating a new TV:
            typer::TV* module_tv; {
                std::string tv_prefix = "module:";
                std::string tv_name = tv_prefix + node->module_name().content();
                module_tv = scoper()->typer()->new_monomorphic_var_tv(std::move(tv_name));
            }

            // defining the new module in the script:
            scoper()->top_frame()->define(new Defn(
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
            // todo: pass argument specifiers too, since `new_polymorphic_var_tv` only used to define 
            // statements with tpatterns
            std::string tv_prefix = "typeclass:";
            std::string tv_name = tv_prefix + node->typeclass_name().content();
            typer::TV* typeclass_tv = scoper()->typer()->new_polymorphic_var_tv(std::move(tv_name));
            scoper()->top_frame()->define(new Defn(
                DefnKind::Typeclass,
                node->typeclass_name(),
                node,
                typeclass_tv
            ));
        }
        return true;
    }
    bool ScoperVisitor::on_visit__type_stmt(ast::TypeStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_prefix = "type:";
            std::string tv_name = tv_prefix + node->lhs_name().content();
            
            typer::TV* type_tv;
            if (node->lhs_tpatterns().empty()) {
                type_tv = scoper()->typer()->new_monomorphic_var_tv(std::move(tv_name));
            } else {
                // todo: pass argument specifiers too, since `new_polymorphic_var_tv` only used to define 
                // statements with tpatterns
                type_tv = nullptr;
            }

            scoper()->top_frame()->define(new Defn(
                DefnKind::Type,
                node->lhs_name(),
                node,
                type_tv
            ));
        }
        return true;
    }
    bool ScoperVisitor::on_visit__enum_stmt(ast::EnumStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_prefix = "enum:";
            
        }
        return true;
    }
    bool ScoperVisitor::on_visit__fn_stmt(ast::FnStmt* node, VisitOrder visit_order) {
        return true;
    }
    bool ScoperVisitor::on_visit__const_stmt(ast::ConstStmt* node, VisitOrder visit_order) {
        return true;
    }
    bool ScoperVisitor::on_visit__val_stmt(ast::ValStmt* node, VisitOrder visit_order) {
        return true;
    }
    bool ScoperVisitor::on_visit__var_stmt(ast::VarStmt* node, VisitOrder visit_order) {
        return true;
    }
    bool ScoperVisitor::on_visit__extern_stmt(ast::ExternStmt* node, VisitOrder visit_order) {
        return true;
    }
    bool ScoperVisitor::on_visit__import_stmt(ast::ImportStmt* node, VisitOrder visit_order) {
        return true;
    }
    bool ScoperVisitor::on_visit__set_stmt(ast::SetStmt* node, VisitOrder visit_order) {
        return true;
    }
    bool ScoperVisitor::on_visit__discard_stmt(ast::DiscardStmt* node, VisitOrder visit_order) {
        return true;
    }
    bool ScoperVisitor::on_visit__using_stmt(ast::UsingStmt* node, VisitOrder visit_order) {
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
        return true;
    }
    bool ScoperVisitor::on_visit__lambda_exp(ast::LambdaExp* node, VisitOrder visit_order) {
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
        return true;
    }
    bool ScoperVisitor::on_visit__tpattern(ast::TPattern* node, VisitOrder visit_order) {
        return true;
    }
    bool ScoperVisitor::on_visit__lpattern(ast::LPattern* node, VisitOrder visit_order) {
        return true;
    }

    // typespecs:
    bool ScoperVisitor::on_visit__id_typespec(ast::IdTypespec* node, VisitOrder visit_order) {
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
