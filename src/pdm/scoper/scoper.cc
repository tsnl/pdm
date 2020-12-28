#include "scoper.hh"

namespace pdm::scoper {

    // todo: implement all these scoper overloads ;-;
    // - pass 1: 'modconst'
    //   define frames, contexts, and symbols for all 
    //   modules & consts 
    //   with metavar TVs
    // - pass 2: 'lookups'
    //   - resolve each ID's definition
    //   - set TV equality using a VIdLookupRule/TIdLookupRule
    

    // scripts:
    bool Scoper::on_visit__script(ast::Script* script, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__script(script, visit_order);
        // todo: implement Scoper::on_visit__script. e.g....
        //   Defn* defn_ptr = nullptr;
        //   top_frame()->append_new_context(defn_ptr);
        return ok;
    }

    // statements:
    bool Scoper::on_visit__mod_stmt(ast::ModStmt* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__mod_stmt(node, visit_order);
        // todo: implement Scoper::on_visit__module_stmt
        return ok;
    }
    bool Scoper::on_visit__typeclass_stmt(ast::TypeclassStmt* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__typeclass_stmt(node, visit_order);
        // todo: implement Scoper::on_visit__typeclass_stmt
        return ok;
    }
    bool Scoper::on_visit__type_stmt(ast::TypeStmt* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__type_stmt(node, visit_order);
        // todo: implement Scoper::on_visit__type_stmt
        return ok;
    }
    bool Scoper::on_visit__enum_stmt(ast::EnumStmt* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__enum_stmt(node, visit_order);
        // todo: implement Scoper::on_visit__enum_stmt
        return ok;
    }
    bool Scoper::on_visit__fn_stmt(ast::FnStmt* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__fn_stmt(node, visit_order);
        // todo: implement Scoper::on_visit__fn_stmt
        return ok;
    }
    bool Scoper::on_visit__val_stmt(ast::ValStmt* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__val_stmt(node, visit_order);
        // todo: implement Scoper::on_visit__let_stmt
        return ok;
    }
    bool Scoper::on_visit__const_stmt(ast::ConstStmt* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__const_stmt(node, visit_order);
        // todo: implement Scoper::on_visit__const_stmt
        return ok;
    }
    bool Scoper::on_visit__extern_stmt(ast::ExternStmt* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__extern_stmt(node, visit_order);
        // todo: implement Scoper::on_visit__link_stmt
        return ok;
    }
    bool Scoper::on_visit__import_stmt(ast::ImportStmt* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__import_stmt(node, visit_order);
        // todo: implement Scoper::on_visit__import_stmt
        return ok;
    }

    // expressions:
    bool Scoper::on_visit__unit_exp(ast::UnitExp* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__unit_exp(node, visit_order);
        // todo: implement Scoper::on_visit__unit_exp
        return ok;
    }
    bool Scoper::on_visit__int_exp(ast::IntExp* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__int_exp(node, visit_order);
        // todo: implement Scoper::on_visit__int_exp
        return ok;
    }
    bool Scoper::on_visit__float_exp(ast::FloatExp* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__float_exp(node, visit_order);
        // todo: implement Scoper::on_visit__float_exp
        return ok;
    }
    bool Scoper::on_visit__string_exp(ast::StringExp* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__string_exp(node, visit_order);
        // todo: implement Scoper::on_visit__string_exp
        return ok;
    }
    bool Scoper::on_visit__id_exp(ast::IdExp* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__id_exp(node, visit_order);
        // todo: implement Scoper::on_visit__id_exp
        return ok;
    }
    bool Scoper::on_visit__paren_exp(ast::ParenExp* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__paren_exp(node, visit_order);
        // todo: implement Scoper::on_visit__paren_exp
        return ok;
    }
    bool Scoper::on_visit__tuple_exp(ast::TupleExp* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__tuple_exp(node, visit_order);
        // todo: implement Scoper::on_visit__tuple_exp
        return ok;
    }
    bool Scoper::on_visit__array_exp(ast::ArrayExp* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__array_exp(node, visit_order);
        // todo: implement Scoper::on_visit__array_exp
        return ok;
    }
    bool Scoper::on_visit__struct_exp(ast::StructExp* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__struct_exp(node, visit_order);
        // todo: implement Scoper::on_visit__struct_exp
        return ok;
    }
    bool Scoper::on_visit__type_query_exp(ast::TypeQueryExp* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__type_query_exp(node, visit_order);
        // todo: implement Scoper::on_visit__type_query_exp
        return ok;
    }
    bool Scoper::on_visit__chain_exp(ast::ChainExp* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__chain_exp(node, visit_order);
        // todo: implement Scoper::on_visit__chain_exp
        return ok;
    }
    bool Scoper::on_visit__lambda_exp(ast::LambdaExp* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__lambda_exp(node, visit_order);
        // todo: implement Scoper::on_visit__lambda_exp
        return ok;
    }
    bool Scoper::on_visit__if_exp(ast::IfExp* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__if_exp(node, visit_order);
        // todo: implement Scoper::on_visit__if_exp
        return ok;
    }
    bool Scoper::on_visit__dot_index_exp(ast::DotIndexExp* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__dot_index_exp(node, visit_order);
        // todo: implement Scoper::on_visit__dot_index_exp
        return ok;
    }
    bool Scoper::on_visit__dot_name_exp(ast::DotNameExp* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__dot_name_exp(node, visit_order);
        // todo: implement Scoper::on_visit__dot_name_exp
        return ok;
    }
    bool Scoper::on_visit__unary_exp(ast::UnaryExp* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__unary_exp(node, visit_order);
        // todo: implement Scoper::on_visit__unary_exp
        return ok;
    }
    bool Scoper::on_visit__binary_exp(ast::BinaryExp* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__binary_exp(node, visit_order);
        // todo: implement Scoper::on_visit__binary_exp
        return ok;
    }
    bool Scoper::on_visit__vcall_exp(ast::VCallExp* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__vcall_exp(node, visit_order);
        // todo: implement Scoper::on_visit__v_call_exp
        return ok;
    }
    bool Scoper::on_visit__tcall_exp(ast::TCallExp* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__tcall_exp(node, visit_order);
        // todo: implement Scoper::on_visit__t_call_exp
        return ok;
    }
    
    // patterns:
    bool Scoper::on_visit__vpattern(ast::VPattern* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__vpattern(node, visit_order);
        // todo: implement Scoper::on_visit__v_pattern
        return ok;
    }
    bool Scoper::on_visit__tpattern(ast::TPattern* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__tpattern(node, visit_order);
        // todo: implement Scoper::on_visit__t_pattern
        return ok;
    }
    bool Scoper::on_visit__lpattern(ast::LPattern* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__lpattern(node, visit_order);
        // todo: implement Scoper::on_visit__l_pattern
        return ok;
    }

    // typespecs:
    bool Scoper::on_visit__id_typespec(ast::IdTypespec* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__id_typespec(node, visit_order);
        // todo: implement Scoper::on_visit__id_typespec
        return ok;
    }
    bool Scoper::on_visit__fn_typespec(ast::FnTypespec* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__fn_typespec(node, visit_order);
        // todo: implement Scoper::on_visit__func_typespec
        return ok;
    }
    bool Scoper::on_visit__tcall_typespec(ast::TCallTypespec* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__tcall_typespec(node, visit_order);
        // todo: implement Scoper::on_visit__t_call_typespec
        return ok;
    }
    bool Scoper::on_visit__tuple_typespec(ast::TupleTypespec* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__tuple_typespec(node, visit_order);
        // todo: implement Scoper::on_visit__tuple_typespec
        return ok;
    }
    bool Scoper::on_visit__dot_name_typespec_type_prefix(ast::DotNameTypespec_TypePrefix* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__dot_name_typespec_type_prefix(node, visit_order);
        // todo: implement Scoper::on_visit__dot_name_typespec_type_prefix
        return ok;
    }
    bool Scoper::on_visit__dot_name_typespec_mod_prefix(ast::DotNameTypespec_ModPrefix* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__dot_name_typespec_mod_prefix(node, visit_order);
        // todo: implement Scoper::on_visit__dot_name_typespec_mod_prefix
        return ok;
    }
    bool Scoper::on_visit__struct_typespec(ast::StructTypespec* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__struct_typespec(node, visit_order);
        // todo: implement Scoper::on_visit__struct_typespec
        return ok;
    }

    // args:
    bool Scoper::on_visit__targ(ast::TArg* targ, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__targ(targ, visit_order);
        // todo: implement Scoper::on_visit__targ
        return ok;
    }
    bool Scoper::on_visit__varg(ast::VArg* varg, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__varg(varg, visit_order);
        // todo: implement Scoper::on_visit__varg
        return ok;
    }


    // non-syntax
    bool Scoper::on_visit__builtin_type_stmt(ast::BuiltinTypeStmt* node, VisitOrder visit_order) {
        bool ok = ast::Visitor::on_visit__builtin_type_stmt(node, visit_order);
        return ok;
    }
}
