#include "visitor.hh"

#include "node.hh"
#include "kind.hh"

namespace pdm::ast {

    bool Visitor::visit(Node* node) {
        bool ok = true;
        
        ok = on_visit(node, VisitOrder::Pre) && ok;

        switch (node->kind()) 
        {
            //
            // scripts:
            //

            case Kind::Script:
            {
                break;
            }

            //
            // statements:
            //

            case Kind::LetStmt:
            {
                LetStmt* let_stmt = dynamic_cast<LetStmt*>(node);
                ok = visit(let_stmt->lhs_lpattern()) && ok;
                ok = visit(let_stmt->rhs_exp()) && ok;
                break;
            }
            case Kind::ConstStmt:
            {
                ConstStmt* const_stmt = dynamic_cast<ConstStmt*>(node);
                ok = visit(const_stmt->lhs_lpattern()) && ok;
                ok = visit(const_stmt->rhs_exp()) && ok;
                break;
            }
            case Kind::DefStmt:
            {
                DefStmt* def_stmt = dynamic_cast<DefStmt*>(node);
                for (TPattern* tpattern: def_stmt->tpatterns()) {
                    ok = visit(tpattern) && ok;
                }
                ok = visit(def_stmt->vpattern()) && ok;
                break;
            }
            case Kind::TypeStmt:
            {
                TypeStmt* type_stmt = dynamic_cast<TypeStmt*>(node);
                ok = visit(type_stmt->rhs_typespec()) && ok;
                break;
            }
            case Kind::EnumStmt:
            {
                // notably, enum doesn't emit anything.
                break;
            }
            case Kind::TypeclassStmt:
            {
                TypeclassStmt* typeclass_stmt = dynamic_cast<TypeclassStmt*>(node);
                for (TPattern* tpattern: typeclass_stmt->tpatterns()) {
                    ok = visit(tpattern) && ok;
                }
                for (TypeclassStmt::Field* field: typeclass_stmt->fields()) {
                    switch (field->kind()) {
                        case TypeclassStmt::FieldKind::Exp:
                        {
                            TypeclassStmt::ExpField* exp_field = dynamic_cast<TypeclassStmt::ExpField*>(field);
                            ok = visit(exp_field->const_exp()) && ok;
                            break;
                        }
                        case TypeclassStmt::FieldKind::Fun:
                        {
                            TypeclassStmt::FunField* fun_field = dynamic_cast<TypeclassStmt::FunField*>(field);
                            ok = visit(fun_field->lhs_pattern()) && ok;
                            ok = visit(fun_field->rhs_body()) && ok;
                            break;
                        }
                    }
                }
                break;
            }
            case Kind::ModuleStmt:
            {
                ModuleStmt* module_stmt = dynamic_cast<ModuleStmt*>(node);
                for (Stmt* defn_stmt: module_stmt->defns()) {
                    ok = visit(defn_stmt) && ok;
                }
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
                ok = visit(paren_exp->nested()) && ok;
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
                for (StructExp::Field const& field: struct_exp->fields()) {
                    ok = visit(field.value()) && ok;
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
                ok = visit(lambda_exp->body()) && ok;
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
                for (Exp* arg: vcall_exp->args()) {
                    ok = visit(arg) && ok;
                }
                break;
            }
            case Kind::TCallExp:
            {
                TCallExp* tcall_exp = dynamic_cast<TCallExp*>(node);
                ok = visit(tcall_exp->lhs_called()) && ok;
                for (TCallExp::Arg const& arg: tcall_exp->args()) {
                    ok = visit(arg.node()) && ok;
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
                for (VPattern::Field const& field: vpattern->fields()) {
                    ok = visit(field.rhs_typespec()) && ok;
                }
                break;
            }
            case Kind::TPattern:
            {
                TPattern* tpattern = dynamic_cast<TPattern*>(node);
                for (TPattern::Field const& field: tpattern->fields()) {
                    ok = visit(field.rhs_typespec()) && ok;
                }
                break;
            }
            case Kind::LPattern:
            {
                LPattern* lpattern = dynamic_cast<LPattern*>(node);
                for (LPattern::Field const& field: lpattern->fields()) {
                    Typespec* opt_field_typespec = field.opt_rhs_typespec();
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
            case Kind::MutTypespec:
            {
                MutTypespec* mut_typespec = dynamic_cast<MutTypespec*>(node);
                ok = visit(mut_typespec->mutatee()) && ok;
                break;
            }
            case Kind::PtrTypespec:
            {
                PtrTypespec* ptr_typespec = dynamic_cast<PtrTypespec*>(node);
                ok = visit(ptr_typespec->pointee()) && ok;
                break;
            }
            case Kind::FuncTypespec:
            {
                FuncTypespec* func_typespec = dynamic_cast<FuncTypespec*>(node);
                ok = visit(func_typespec->lhs_vpattern()) && ok;
                ok = visit(func_typespec->rhs_typespec()) && ok;
                break;
            }
            case Kind::TCallTypespec:
            {
                TCallTypespec* tcall_typespec = dynamic_cast<TCallTypespec*>(node);
                ok = visit(tcall_typespec->lhs_called()) && ok;
                for (TCallTypespec::Arg const& arg: tcall_typespec->args()) {
                    ok = visit(arg.node()) && ok;
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
                for (StructTypespec::Field const& field: struct_typespec->fields()) {
                    ok = visit(field.rhs_typespec()) && ok;
                }
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
            case Kind::LetStmt:
            {
                return on_visit__let_stmt(dynamic_cast<LetStmt*>(node), visit_order);
            }
            case Kind::ConstStmt:
            {
                return on_visit__const_stmt(dynamic_cast<ConstStmt*>(node), visit_order);
            }
            case Kind::DefStmt:
            {
                return on_visit__def_stmt(dynamic_cast<DefStmt*>(node), visit_order);
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
            case Kind::ModuleStmt:
            {
                return on_visit__module_stmt(dynamic_cast<ModuleStmt*>(node), visit_order);
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
                return on_visit__v_call_exp(dynamic_cast<VCallExp*>(node), visit_order);
            } 
            case Kind::TCallExp:
            {
                return on_visit__t_call_exp(dynamic_cast<TCallExp*>(node), visit_order);
            }
            case Kind::TypeQueryExp:
            {
                return on_visit__type_query_exp(dynamic_cast<TypeQueryExp*>(node), visit_order);
            }

            // patterns:
            case Kind::VPattern:
            {
                return on_visit__v_pattern(dynamic_cast<VPattern*>(node), visit_order);
            }
            case Kind::TPattern:
            {
                return on_visit__t_pattern(dynamic_cast<TPattern*>(node), visit_order);
            }
            case Kind::LPattern:
            {
                return on_visit__l_pattern(dynamic_cast<LPattern*>(node), visit_order);
            }

            // typespecs:
            case Kind::IdTypespec:
            {
                return on_visit__id_typespec(dynamic_cast<IdTypespec*>(node), visit_order);
            }
            case Kind::MutTypespec:
            {
                return on_visit__mut_typespec(dynamic_cast<MutTypespec*>(node), visit_order);
            }
            case Kind::PtrTypespec:
            {
                return on_visit__ptr_typespec(dynamic_cast<PtrTypespec*>(node), visit_order);
            }
            case Kind::FuncTypespec:
            {
                return on_visit__func_typespec(dynamic_cast<FuncTypespec*>(node), visit_order);
            }
            case Kind::TCallTypespec:
            {
                return on_visit__t_call_typespec(dynamic_cast<TCallTypespec*>(node), visit_order);
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
        }
    }

}   // namespace pdm::ast
