#include "visitor.hh"

#include "node.hh"
#include "kind.hh"

namespace pdm::ast {

    bool Visitor::visit(Node* node) {
        bool ok = true;
        
        // early return if a helper node:
        if (is_aux_kind(node->kind())) {
            return ok;
        }

        ok = on_visit(node, VisitOrder::Pre) && ok;

        switch (node->kind()) 
        {
            //
            // scripts:
            //

            case Kind::Script:
            {
                Script* script = dynamic_cast<Script*>(node);
                for (ast::Stmt* stmt: script->stmts()) {
                    ok = visit(stmt) && ok;
                }
                break;
            }

            //
            // statements:
            //

            case Kind::DiscardStmt:
            {
                DiscardStmt* discard_stmt = dynamic_cast<DiscardStmt*>(node);
                ok = visit(discard_stmt->discarded_exp()) && ok;
                break;
            }
            case Kind::ConstStmt:
            {
                ConstStmt* const_stmt = dynamic_cast<ConstStmt*>(node);
                ok = visit(const_stmt->lhs_lpattern()) && ok;
                ok = visit(const_stmt->rhs_exp()) && ok;
                break;
            } 
            case Kind::ValStmt:
            {
                ValStmt* val_stmt = dynamic_cast<ValStmt*>(node);
                ok = visit(val_stmt->lhs_lpattern()) && ok;
                ok = visit(val_stmt->rhs_exp()) && ok;
                break;
            }
            case Kind::VarStmt:
            {
                VarStmt* var_stmt = dynamic_cast<VarStmt*>(node);
                ok = visit(var_stmt->lhs_lpattern()) && ok;
                ok = visit(var_stmt->rhs_exp()) && ok;
                break;
            }
            case Kind::SetStmt:
            {
                SetStmt* set_stmt = dynamic_cast<SetStmt*>(node);
                ok = visit(set_stmt->lhs_exp()) && ok;
                ok = visit(set_stmt->rhs_exp()) && ok;
                break;
            }
            case Kind::FnStmt:
            {
                FnStmt* fn_stmt = dynamic_cast<FnStmt*>(node);
                for (TPattern* tpattern: fn_stmt->tpatterns()) {
                    ok = visit(tpattern) && ok;
                }
                ok = visit(fn_stmt->vpattern()) && ok;
                if (fn_stmt->opt_return_ts()) {
                    ok = visit(fn_stmt->opt_return_ts()) && ok;
                }
                if (fn_stmt->opt_rhs_exp()) {
                    ok = visit(fn_stmt->opt_rhs_exp()) && ok;
                }
                break;
            }
            case Kind::TypeStmt:
            {
                TypeStmt* type_stmt = dynamic_cast<TypeStmt*>(node);
                ok = visit(type_stmt->opt_rhs_typespec()) && ok;
                break;
            }
            case Kind::EnumStmt:
            {
                // notably, enum doesn't need any visits; all fields should be processed in this node's pre or post visit handler.
                break;
            }
            case Kind::TypeclassStmt:
            {
                TypeclassStmt* typeclass_stmt = dynamic_cast<TypeclassStmt*>(node);
                
                ok = visit(typeclass_stmt->candidate_typespec()) && ok;
                for (TPattern* tpattern: typeclass_stmt->tpatterns()) {
                    ok = visit(tpattern) && ok;
                }
                for (Exp* condition: typeclass_stmt->conditions()) {
                    ok = visit(condition) && ok;
                }
                break;
            }
            case Kind::ModStmt:
            {
                ModStmt* module_stmt = dynamic_cast<ModStmt*>(node);
                for (Stmt* defn_stmt: module_stmt->defns()) {
                    ok = visit(defn_stmt) && ok;
                }
                break;
            }
            case Kind::ExternStmt:
            {
                ExternStmt* extern_stmt = dynamic_cast<ExternStmt*>(node);
                ok = visit(extern_stmt->link_arg()) && ok;
                break;
            }
            case Kind::ImportStmt:
            {
                ImportStmt* import_stmt = dynamic_cast<ImportStmt*>(node);
                break;
            }
            case Kind::UsingStmt:
            {
                UsingStmt* using_stmt = dynamic_cast<UsingStmt*>(node);
                break;
            }

            //
            // expressions:
            //

            case Kind::UnitExp:
            case Kind::IntExp:
            case Kind::FloatExp:
            case Kind::StringExp:
            case Kind::IdExp:
            {
                break;
            }
            case Kind::ParenExp:
            {
                ParenExp* paren_exp = dynamic_cast<ParenExp*>(node);
                ok = visit(paren_exp->nested_exp()) && ok;
                break;
            }
            case Kind::ArrayExp:
            {
                ArrayExp* array_exp = dynamic_cast<ArrayExp*>(node);
                for (auto const item_exp: array_exp->items()) {
                    ok = visit(item_exp) && ok;
                }
                break;
            }
            case Kind::TupleExp:
            {
                TupleExp* tuple_exp = dynamic_cast<TupleExp*>(node);
                for (Exp* tuple_item_exp: tuple_exp->items()) {
                    ok = visit(tuple_item_exp) && ok;
                }
                break;
            }
            case Kind::StructExp:
            {
                StructExp* struct_exp = dynamic_cast<StructExp*>(node);
                for (StructExp::Field* field: struct_exp->fields()) {
                    ok = visit(field->value()) && ok;
                }
                break;
            }
            case Kind::ChainExp:
            {
                ChainExp* chain_exp = dynamic_cast<ChainExp*>(node);
                for (auto const prefix_stmt: chain_exp->prefix()) {
                    ok = visit(prefix_stmt) && ok;
                }
                if (chain_exp->suffix()) {
                    ok = visit(chain_exp->suffix()) && ok;
                }
                break;
            }
            case Kind::LambdaExp:
            {
                LambdaExp* lambda_exp = dynamic_cast<LambdaExp*>(node);
                ok = visit(lambda_exp->lhs_vpattern()) && ok;
                ok = visit(lambda_exp->rhs_body()) && ok;
                break;
            }
            case Kind::IfExp:
            {
                IfExp* if_exp = dynamic_cast<IfExp*>(node);
                ok = visit(if_exp->cond_exp()) && ok;
                ok = visit(if_exp->then_exp()) && ok;
                if (if_exp->else_exp()) {
                    ok = visit(if_exp->else_exp()) && ok;
                }
                break;
            }
            case Kind::DotIndexExp:
            {
                DotIndexExp* dot_index_exp = dynamic_cast<DotIndexExp*>(node);
                ok = visit(dot_index_exp->lhs()) && ok;
                break;
            }
            case Kind::DotNameExp:
            {
                DotNameExp* dot_name_exp = dynamic_cast<DotNameExp*>(node);
                ok = visit(dot_name_exp->lhs()) && ok;
                break;
            }
            case Kind::UnaryExp:
            {
                UnaryExp* unary_exp = dynamic_cast<UnaryExp*>(node);
                ok = visit(unary_exp->operand()) && ok;
                break;
            }
            case Kind::BinaryExp:
            {
                BinaryExp* binary_exp = dynamic_cast<BinaryExp*>(node);
                ok = visit(binary_exp->lhs_operand()) && ok;
                ok = visit(binary_exp->rhs_operand()) && ok;
                break;
            }
            case Kind::VCallExp:
            {
                VCallExp* vcall_exp = dynamic_cast<VCallExp*>(node);
                ok = visit(vcall_exp->lhs_called()) && ok;
                for (VArg* arg: vcall_exp->args()) {
                    ok = visit(arg) && ok;
                }
                break;
            }
            case Kind::TCallExp:
            {
                TCallExp* tcall_exp = dynamic_cast<TCallExp*>(node);
                ok = visit(tcall_exp->lhs_called()) && ok;
                for (TArg* arg: tcall_exp->args()) {
                    ok = visit(arg) && ok;
                }
                break;
            }
            case Kind::TypeQueryExp:
            {
                TypeQueryExp* type_query_exp = dynamic_cast<TypeQueryExp*>(node);
                ok = visit(type_query_exp->lhs_typespec()) && ok;
                ok = visit(type_query_exp->rhs_typespec()) && ok;
                break;
            }

            //
            // patterns:
            //

            case Kind::VPattern:
            {
                VPattern* vpattern = dynamic_cast<VPattern*>(node);
                for (VPattern::Field* field: vpattern->fields()) {
                    ok = visit(field->rhs_typespec()) && ok;
                }
                break;
            }
            case Kind::TPattern:
            {
                TPattern* tpattern = dynamic_cast<TPattern*>(node);
                for (TPattern::Field* field: tpattern->fields()) {
                    ok = visit(field->rhs_typespec()) && ok;
                }
                break;
            }
            case Kind::LPattern:
            {
                LPattern* lpattern = dynamic_cast<LPattern*>(node);
                for (LPattern::Field* field: lpattern->fields()) {
                    Typespec* opt_field_typespec = field->opt_rhs_typespec();
                    if (opt_field_typespec) {
                        ok = visit(opt_field_typespec) && ok;
                    }
                }
                break;
            }
            
            //
            // typespecs:
            //

            case Kind::IdTypespec:
            case Kind::DotNameTypespec_ModPrefix:
            {
                break;
            }
            case Kind::FnTypespec:
            {
                FnTypespec* fn_typespec = dynamic_cast<FnTypespec*>(node);
                ok = visit(fn_typespec->lhs_vpattern()) && ok;
                ok = visit(fn_typespec->rhs_typespec()) && ok;
                break;
            }
            case Kind::TCallTypespec:
            {
                TCallTypespec* tcall_typespec = dynamic_cast<TCallTypespec*>(node);
                ok = visit(tcall_typespec->lhs_called()) && ok;
                for (TArg* arg: tcall_typespec->args()) {
                    ok = visit(arg) && ok;
                }
                break;
            }
            case Kind::DotNameTypespec_TypePrefix:
            {
                DotNameTypespec_TypePrefix* dot_name_typespec_w_type_prefix = dynamic_cast<DotNameTypespec_TypePrefix*>(node);
                ok = visit(dot_name_typespec_w_type_prefix->lhs_typespec());
                break;
            }
            case Kind::StructTypespec:
            {
                StructTypespec* struct_typespec = dynamic_cast<StructTypespec*>(node);
                for (StructTypespec::Field* field: struct_typespec->fields()) {
                    ok = visit(field->rhs_typespec()) && ok;
                }
                break;
            }
            case Kind::TupleTypespec:
            {
                TupleTypespec* tuple_typespec = dynamic_cast<TupleTypespec*>(node);
                for (Typespec* item_typespec: tuple_typespec->items()) {
                    ok = visit(item_typespec) && ok;
                }
                break;
            }
            case Kind::ParenTypespec:
            {
                ParenTypespec* paren_typespec = dynamic_cast<ParenTypespec*>(node);
                ok = visit(paren_typespec->nested_typespec()) && ok;
                break;
            }

            //
            // shared/templates:
            //

            case Kind::TArg:
            {
                TArg* targ = dynamic_cast<TArg*>(node);
                ok = visit(targ->arg_node()) && ok;
                break;
            }
            case Kind::VArg:
            {
                VArg* varg = dynamic_cast<VArg*>(node);
                ok = visit(varg->arg_exp()) && ok;
                break;
            }

            //
            // non-syntactic elements:
            // (never parsed, only compiler-created)
            //

            case Kind::BuiltinTypeStmt:
            {
                break;
            }

            //
            // invalid enum entries:
            //
            case Kind::__Count:
            {
                ok = false;
                break;
            }

            // ignoring 'Aux_':
            case Kind::Aux_LPatternField:
            case Kind::Aux_TPatternField:
            case Kind::Aux_VPatternField:
            {
                break;
            }
        }

        ok = on_visit(node, VisitOrder::Post) && ok;

        return ok;
    }

    bool Visitor::on_visit(Node* node, VisitOrder visit_order) {
        switch (node->kind()) {
            
            // script:
            case Kind::Script: 
            {
                return on_visit__script(dynamic_cast<Script*>(node), visit_order);
            }

            // statements:
            case Kind::DiscardStmt:
            {
                return on_visit__discard_stmt(dynamic_cast<DiscardStmt*>(node), visit_order);
            } 
            case Kind::ConstStmt:
            {
                return on_visit__const_stmt(dynamic_cast<ConstStmt*>(node), visit_order);
            }
            case Kind::ValStmt:
            {
                return on_visit__val_stmt(dynamic_cast<ValStmt*>(node), visit_order);
            }
            case Kind::VarStmt:
            {
                return on_visit__var_stmt(dynamic_cast<VarStmt*>(node), visit_order);
            }
            case Kind::SetStmt:
            {
                return on_visit__set_stmt(dynamic_cast<SetStmt*>(node), visit_order);
            }
            case Kind::FnStmt:
            {
                return on_visit__fn_stmt(dynamic_cast<FnStmt*>(node), visit_order);
            }
            case Kind::TypeStmt:
            {
                return on_visit__type_stmt(dynamic_cast<TypeStmt*>(node), visit_order);
            }
            case Kind::EnumStmt:
            {
                return on_visit__enum_stmt(dynamic_cast<EnumStmt*>(node), visit_order);
            }
            case Kind::TypeclassStmt:
            {
                return on_visit__typeclass_stmt(dynamic_cast<TypeclassStmt*>(node), visit_order);
            }
            case Kind::ModStmt:
            {
                return on_visit__mod_stmt(dynamic_cast<ModStmt*>(node), visit_order);
            }
            case Kind::ExternStmt:
            {
                return on_visit__extern_stmt(dynamic_cast<ExternStmt*>(node), visit_order);
            }
            case Kind::ImportStmt:
            {
                return on_visit__import_stmt(dynamic_cast<ImportStmt*>(node), visit_order);
            }
            case Kind::UsingStmt:
            {
                return on_visit__using_stmt(dynamic_cast<UsingStmt*>(node), visit_order);
            }

            // expressions:
            case Kind::UnitExp:
            {
                return on_visit__unit_exp(dynamic_cast<UnitExp*>(node), visit_order);
            } 
            case Kind::IntExp:
            {
                return on_visit__int_exp(dynamic_cast<IntExp*>(node), visit_order);
            } 
            case Kind::FloatExp:
            {
                return on_visit__float_exp(dynamic_cast<FloatExp*>(node), visit_order);
            } 
            case Kind::StringExp:
            {
                return on_visit__string_exp(dynamic_cast<StringExp*>(node), visit_order);
            }
            case Kind::IdExp:
            {
                return on_visit__id_exp(dynamic_cast<IdExp*>(node), visit_order);
            }
            case Kind::ParenExp:
            {
                return on_visit__paren_exp(dynamic_cast<ParenExp*>(node), visit_order);
            }
            case Kind::ArrayExp:
            {
                return on_visit__array_exp(dynamic_cast<ArrayExp*>(node), visit_order);
            } 
            case Kind::TupleExp:
            {
                return on_visit__tuple_exp(dynamic_cast<TupleExp*>(node), visit_order);
            } 
            case Kind::StructExp:
            {
                return on_visit__struct_exp(dynamic_cast<StructExp*>(node), visit_order);
            } 
            case Kind::ChainExp:
            {
                return on_visit__chain_exp(dynamic_cast<ChainExp*>(node), visit_order);
            }
            case Kind::LambdaExp:
            {
                return on_visit__lambda_exp(dynamic_cast<LambdaExp*>(node), visit_order);
            }
            case Kind::IfExp:
            {
                return on_visit__if_exp(dynamic_cast<IfExp*>(node), visit_order);
            }
            case Kind::DotIndexExp:
            {
                return on_visit__dot_index_exp(dynamic_cast<DotIndexExp*>(node), visit_order);
            } 
            case Kind::DotNameExp:
            {
                return on_visit__dot_name_exp(dynamic_cast<DotNameExp*>(node), visit_order);
            }
            case Kind::UnaryExp:
            {
                return on_visit__unary_exp(dynamic_cast<UnaryExp*>(node), visit_order);
            } 
            case Kind::BinaryExp:
            {
                return on_visit__binary_exp(dynamic_cast<BinaryExp*>(node), visit_order);
            }
            case Kind::VCallExp:
            {
                return on_visit__vcall_exp(dynamic_cast<VCallExp*>(node), visit_order);
            } 
            case Kind::TCallExp:
            {
                return on_visit__tcall_exp(dynamic_cast<TCallExp*>(node), visit_order);
            }
            case Kind::TypeQueryExp:
            {
                return on_visit__type_query_exp(dynamic_cast<TypeQueryExp*>(node), visit_order);
            }

            // patterns:
            case Kind::VPattern:
            {
                return on_visit__vpattern(dynamic_cast<VPattern*>(node), visit_order);
            }
            case Kind::TPattern:
            {
                return on_visit__tpattern(dynamic_cast<TPattern*>(node), visit_order);
            }
            case Kind::LPattern:
            {
                return on_visit__lpattern(dynamic_cast<LPattern*>(node), visit_order);
            }

            // typespecs:
            case Kind::IdTypespec:
            {
                return on_visit__id_typespec(dynamic_cast<IdTypespec*>(node), visit_order);
            }
            case Kind::FnTypespec:
            {
                return on_visit__fn_typespec(dynamic_cast<FnTypespec*>(node), visit_order);
            }
            case Kind::TCallTypespec:
            {
                return on_visit__tcall_typespec(dynamic_cast<TCallTypespec*>(node), visit_order);
            }
            case Kind::TupleTypespec:
            {
                return on_visit__tuple_typespec(dynamic_cast<TupleTypespec*>(node), visit_order);
            }
            case Kind::DotNameTypespec_TypePrefix:
            {
                return on_visit__dot_name_typespec_type_prefix(dynamic_cast<DotNameTypespec_TypePrefix*>(node), visit_order);
            }
            case Kind::DotNameTypespec_ModPrefix:
            {
                return on_visit__dot_name_typespec_mod_prefix(dynamic_cast<DotNameTypespec_ModPrefix*>(node), visit_order);
            }
            case Kind::StructTypespec:
            {
                return on_visit__struct_typespec(dynamic_cast<StructTypespec*>(node), visit_order);
            }
            case Kind::ParenTypespec:
            {
                return on_visit__paren_typespec(dynamic_cast<ParenTypespec*>(node), visit_order);
            }

            // templates/shared:
            case Kind::TArg:
            {
                return on_visit__targ(dynamic_cast<TArg*>(node), visit_order);
            }
            case Kind::VArg:
            {
                return on_visit__varg(dynamic_cast<VArg*>(node), visit_order);
            }

            // non-syntactic elements:
            case Kind::BuiltinTypeStmt:
            {
                return on_visit__builtin_type_stmt(dynamic_cast<BuiltinTypeStmt*>(node), visit_order);
            }

            // meta elements:
            case Kind::__Count:
            {
                return false;
            }

            // ignore:
            case Kind::Aux_LPatternField:
            case Kind::Aux_TPatternField:
            case Kind::Aux_VPatternField:
            {
                return true;
            }
        }
    }

}   // namespace pdm::ast
