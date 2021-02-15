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
                for (ast::Stmt* head_stmt: script->head_stmts()) {
                    ok = visit(head_stmt) && ok;
                }
                for (ast::ModStmt* body_stmt: script->body_stmts()) {
                    ok = visit(body_stmt) && ok;
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
            case Kind::ModValStmt:
            {
                ModValStmt* mod_val_stmt = dynamic_cast<ModValStmt*>(node);
                for (TPattern* tpattern: mod_val_stmt->tpatterns()) {
                    ok = visit(tpattern) && ok;
                }
                if (mod_val_stmt->opt_rhs_exp()) {
                    ok = visit(mod_val_stmt->opt_rhs_exp()) && ok;
                }
                break;
            }
            case Kind::ModTypeStmt:
            {
                auto type_stmt = dynamic_cast<ModTypeStmt*>(node);
                ok = visit(type_stmt->opt_rhs_typespec()) && ok;
                break;
            }
            case Kind::ModEnumStmt:
            {
                auto enum_stmt = dynamic_cast<ModEnumStmt*>(node);
                for (ast::ModEnumStmt::Field* field: enum_stmt->fields()) {
                    if (field->opt_type_spec()) {
                        ok = visit(field->opt_type_spec()) && ok;
                    }
                }
                break;
            }
            case Kind::ModTypeclassStmt:
            {
                auto typeclass_stmt = dynamic_cast<ModTypeclassStmt*>(node);
                
                ok = visit(typeclass_stmt->candidate_class_spec()) && ok;
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
                auto module_stmt = dynamic_cast<ModStmt*>(node);
                for (Stmt* defn_stmt: module_stmt->defns()) {
                    ok = visit(defn_stmt) && ok;
                }
                break;
            }
            case Kind::ExternStmt:
            {
                auto extern_stmt = dynamic_cast<ExternStmt*>(node);
                ok = visit(extern_stmt->link_arg()) && ok;
                break;
            }
            case Kind::ImportStmt:
            {
                auto import_stmt = dynamic_cast<ImportStmt*>(node);
                break;
            }
            case Kind::UsingStmt:
            {
                auto using_stmt = dynamic_cast<UsingStmt*>(node);
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
                auto paren_exp = dynamic_cast<ParenExp*>(node);
                ok = visit(paren_exp->nested_exp()) && ok;
                break;
            }
            case Kind::ArrayExp:
            {
                auto array_exp = dynamic_cast<ArrayExp*>(node);
                for (auto const item_exp: array_exp->items()) {
                    ok = visit(item_exp) && ok;
                }
                break;
            }
            case Kind::TupleExp:
            {
                auto tuple_exp = dynamic_cast<TupleExp*>(node);
                for (Exp* tuple_item_exp: tuple_exp->items()) {
                    ok = visit(tuple_item_exp) && ok;
                }
                break;
            }
            case Kind::StructExp:
            {
                auto struct_exp = dynamic_cast<StructExp*>(node);
                for (StructExp::Field* field: struct_exp->fields()) {
                    ok = visit(field->value()) && ok;
                }
                break;
            }
            case Kind::ChainExp:
            {
                auto chain_exp = dynamic_cast<ChainExp*>(node);
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
                auto lambda_exp = dynamic_cast<LambdaExp*>(node);
                ok = visit(lambda_exp->lhs_vpattern()) && ok;
                if (lambda_exp->opt_ret_typespec()) {
                    ok = visit(lambda_exp->opt_ret_typespec()) && ok;
                }
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
                auto dot_index_exp = dynamic_cast<DotIndexExp*>(node);
                ok = visit(dot_index_exp->lhs()) && ok;
                break;
            }
            case Kind::DotNameExp:
            {
                auto dot_name_exp = dynamic_cast<DotNameExp*>(node);
                ok = visit(dot_name_exp->lhs()) && ok;
                break;
            }
            case Kind::ModuleDotExp:
            {
                break;
            }
            case Kind::UnaryExp:
            {
                auto unary_exp = dynamic_cast<UnaryExp*>(node);
                ok = visit(unary_exp->operand()) && ok;
                break;
            }
            case Kind::BinaryExp:
            {
                auto binary_exp = dynamic_cast<BinaryExp*>(node);
                ok = visit(binary_exp->lhs_operand()) && ok;
                ok = visit(binary_exp->rhs_operand()) && ok;
                break;
            }
            case Kind::VCallExp:
            {
                auto vcall_exp = dynamic_cast<VCallExp*>(node);
                ok = visit(vcall_exp->lhs_called()) && ok;
                for (VArg* arg: vcall_exp->args()) {
                    ok = visit(arg) && ok;
                }
                break;
            }
            case Kind::TCallExp:
            {
                auto tcall_exp = dynamic_cast<TCallExp*>(node);
                ok = visit(tcall_exp->lhs_called()) && ok;
                for (TArg* arg: tcall_exp->args()) {
                    ok = visit(arg) && ok;
                }
                break;
            }
            case Kind::TypeQueryExp:
            {
                auto type_query_exp = dynamic_cast<TypeQueryExp*>(node);
                ok = visit(type_query_exp->lhs_typespec()) && ok;
                ok = visit(type_query_exp->rhs_typespec()) && ok;
                break;
            }

            //
            // patterns:
            //

            case Kind::VPattern:
            {
                auto vpattern = dynamic_cast<VPattern*>(node);
                for (VPattern::Field* field: vpattern->fields()) {
                    ok = visit(field->rhs_typespec()) && ok;
                }
                break;
            }
            case Kind::TPattern:
            {
                auto tpattern = dynamic_cast<TPattern*>(node);
                for (TPattern::Field* field: tpattern->fields()) {
                    ok = visit(field->rhs_set_spec()) && ok;
                }
                break;
            }
            case Kind::LPattern:
            {
                auto lpattern = dynamic_cast<LPattern*>(node);
                for (LPattern::Field* field: lpattern->fields()) {
                    TypeSpec* opt_field_typespec = field->opt_rhs_typespec();
                    if (opt_field_typespec) {
                        ok = visit(opt_field_typespec) && ok;
                    }
                }
                break;
            }
            
            //
            // typespecs:
            //

            case Kind::IdTypeSpec:
            case Kind::IdClassSpec:
            case Kind::DotNameTypeSpec_ModPrefix:
            {
                break;
            }
            case Kind::FnTypeSpec:
            {
                auto fn_typespec = dynamic_cast<FnTypeSpec*>(node);
                ok = visit(fn_typespec->lhs_vpattern()) && ok;
                ok = visit(fn_typespec->opt_ret_typespec()) && ok;
                break;
            }
            case Kind::TCallTypeSpec:
            {
                auto tcall_typespec = dynamic_cast<TCallTypeSpec*>(node);
                ok = visit(tcall_typespec->lhs_called()) && ok;
                for (TArg* arg: tcall_typespec->args()) {
                    ok = visit(arg) && ok;
                }
                break;
            }
            case Kind::TCallClassSpec:
            {
                auto tcall_class_spec = dynamic_cast<TCallClassSpec*>(node);
                ok = visit(tcall_class_spec->lhs_called()) && ok;
                for (TArg* arg: tcall_class_spec->args()) {
                    ok = visit(arg) && ok;
                }
                break;
            }
            // case Kind::DotNameTypeSpec_TypePrefix:
            // {
            //     DotNameTypeSpec_TypePrefix* dot_name_typespec_w_type_prefix = dynamic_cast<DotNameTypeSpec_TypePrefix*>(node);
            //     ok = visit(dot_name_typespec_w_type_prefix->lhs_typespec());
            //     break;
            // }
            case Kind::StructTypeSpec:
            {
                StructTypeSpec* struct_typespec = dynamic_cast<StructTypeSpec*>(node);
                for (StructTypeSpec::Field* field: struct_typespec->fields()) {
                    ok = visit(field->rhs_typespec()) && ok;
                }
                break;
            }
            case Kind::TupleTypeSpec:
            {
                TupleTypeSpec* tuple_typespec = dynamic_cast<TupleTypeSpec*>(node);
                for (TypeSpec* item_typespec: tuple_typespec->items()) {
                    ok = visit(item_typespec) && ok;
                }
                break;
            }
            case Kind::ParenTypeSpec:
            {
                ParenTypeSpec* paren_typespec = dynamic_cast<ParenTypeSpec*>(node);
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

            case Kind::BuiltinStmt:
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
                return on_visit_script(dynamic_cast<Script *>(node), visit_order);
            }

            // statements:
            case Kind::DiscardStmt:
            {
                return on_visit_discard_stmt(dynamic_cast<DiscardStmt *>(node), visit_order);
            } 
            case Kind::ConstStmt:
            {
                return on_visit_const_stmt(dynamic_cast<ConstStmt *>(node), visit_order);
            }
            case Kind::ValStmt:
            {
                return on_visit_val_stmt(dynamic_cast<ValStmt *>(node), visit_order);
            }
            case Kind::VarStmt:
            {
                return on_visit_var_stmt(dynamic_cast<VarStmt *>(node), visit_order);
            }
            case Kind::SetStmt:
            {
                return on_visit_set_stmt(dynamic_cast<SetStmt *>(node), visit_order);
            }
            case Kind::ModValStmt:
            {
                return on_visit_mod_val_stmt(dynamic_cast<ModValStmt *>(node), visit_order);
            }
            case Kind::ModTypeStmt:
            {
                return on_visit_mod_type_stmt(dynamic_cast<ModTypeStmt *>(node), visit_order);
            }
            case Kind::ModEnumStmt:
            {
                return on_visit_mod_enum_stmt(dynamic_cast<ModEnumStmt *>(node), visit_order);
            }
            case Kind::ModTypeclassStmt:
            {
                return on_visit_mod_typeclass_stmt(dynamic_cast<ModTypeclassStmt *>(node), visit_order);
            }
            case Kind::ModStmt:
            {
                return on_visit_mod_stmt(dynamic_cast<ModStmt *>(node), visit_order);
            }
            case Kind::ExternStmt:
            {
                return on_visit_extern_stmt(dynamic_cast<ExternStmt *>(node), visit_order);
            }
            case Kind::ImportStmt:
            {
                return on_visit_import_stmt(dynamic_cast<ImportStmt *>(node), visit_order);
            }
            case Kind::UsingStmt:
            {
                return on_visit_using_stmt(dynamic_cast<UsingStmt *>(node), visit_order);
            }

            // expressions:
            case Kind::UnitExp:
            {
                return on_visit_unit_exp(dynamic_cast<UnitExp *>(node), visit_order);
            } 
            case Kind::IntExp:
            {
                return on_visit_int_exp(dynamic_cast<IntExp *>(node), visit_order);
            } 
            case Kind::FloatExp:
            {
                return on_visit_float_exp(dynamic_cast<FloatExp *>(node), visit_order);
            } 
            case Kind::StringExp:
            {
                return on_visit_string_exp(dynamic_cast<StringExp *>(node), visit_order);
            }
            case Kind::IdExp:
            {
                return on_visit_id_exp(dynamic_cast<IdExp *>(node), visit_order);
            }
            case Kind::ParenExp:
            {
                return on_visit_paren_exp(dynamic_cast<ParenExp *>(node), visit_order);
            }
            case Kind::ArrayExp:
            {
                return on_visit_array_exp(dynamic_cast<ArrayExp *>(node), visit_order);
            } 
            case Kind::TupleExp:
            {
                return on_visit_tuple_exp(dynamic_cast<TupleExp *>(node), visit_order);
            } 
            case Kind::StructExp:
            {
                return on_visit_struct_exp(dynamic_cast<StructExp *>(node), visit_order);
            } 
            case Kind::ChainExp:
            {
                return on_visit_chain_exp(dynamic_cast<ChainExp *>(node), visit_order);
            }
            case Kind::LambdaExp:
            {
                return on_visit_lambda_exp(dynamic_cast<LambdaExp *>(node), visit_order);
            }
            case Kind::IfExp:
            {
                return on_visit_if_exp(dynamic_cast<IfExp *>(node), visit_order);
            }
            case Kind::DotIndexExp:
            {
                return on_visit_dot_index_exp(dynamic_cast<DotIndexExp *>(node), visit_order);
            } 
            case Kind::DotNameExp:
            {
                return on_visit_dot_name_exp(dynamic_cast<DotNameExp *>(node), visit_order);
            }
            case Kind::ModuleDotExp:
            {
                return on_visit_module_dot_exp(dynamic_cast<ModuleDotExp *>(node), visit_order);
            }
            case Kind::UnaryExp:
            {
                return on_visit_unary_exp(dynamic_cast<UnaryExp *>(node), visit_order);
            } 
            case Kind::BinaryExp:
            {
                return on_visit_binary_exp(dynamic_cast<BinaryExp *>(node), visit_order);
            }
            case Kind::VCallExp:
            {
                return on_visit_v_call_exp(dynamic_cast<VCallExp *>(node), visit_order);
            } 
            case Kind::TCallExp:
            {
                return on_visit_t_call_exp(dynamic_cast<TCallExp *>(node), visit_order);
            }
            case Kind::TypeQueryExp:
            {
                return on_visit_type_query_exp(dynamic_cast<TypeQueryExp *>(node), visit_order);
            }

            // patterns:
            case Kind::VPattern:
            {
                return on_visit_v_pattern(dynamic_cast<VPattern *>(node), visit_order);
            }
            case Kind::TPattern:
            {
                return on_visit_t_pattern(dynamic_cast<TPattern *>(node), visit_order);
            }
            case Kind::LPattern:
            {
                return on_visit_l_pattern(dynamic_cast<LPattern *>(node), visit_order);
            }

            // typespecs:
            case Kind::IdClassSpec:
            {
                return on_visit_id_class_spec(dynamic_cast<IdClassSpec *>(node), visit_order);
            }
            case Kind::IdTypeSpec:
            {
                return on_visit_id_type_spec(dynamic_cast<IdTypeSpec *>(node), visit_order);
            }
            case Kind::FnTypeSpec:
            {
                return on_visit_fn_type_spec(dynamic_cast<FnTypeSpec *>(node), visit_order);
            }
            case Kind::TCallTypeSpec:
            {
                return on_visit_t_call_type_spec(dynamic_cast<TCallTypeSpec *>(node), visit_order);
            }
            case Kind::TCallClassSpec:
            {
                return on_visit_t_call_class_spec(dynamic_cast<TCallClassSpec *>(node), visit_order);
            }
            case Kind::TupleTypeSpec:
            {
                return on_visit_tuple_type_spec(dynamic_cast<TupleTypeSpec *>(node), visit_order);
            }
            // case Kind::DotNameTypeSpec_TypePrefix:
            // {
            //     return on_visit__dot_name_typespec_type_prefix(dynamic_cast<DotNameTypeSpec_TypePrefix*>(node), visit_order);
            // }
            case Kind::DotNameTypeSpec_ModPrefix:
            {
                return on_visit_dot_name_type_spec_mod_prefix(dynamic_cast<DotNameTypeSpec_ModPrefix *>(node),
                                                              visit_order);
            }
            case Kind::StructTypeSpec:
            {
                return on_visit_struct_type_spec(dynamic_cast<StructTypeSpec *>(node), visit_order);
            }
            case Kind::ParenTypeSpec:
            {
                return on_visit_paren_type_spec(dynamic_cast<ParenTypeSpec *>(node), visit_order);
            }

            // templates/shared:
            case Kind::TArg:
            {
                return on_visit_targ(dynamic_cast<TArg *>(node), visit_order);
            }
            case Kind::VArg:
            {
                return on_visit_varg(dynamic_cast<VArg *>(node), visit_order);
            }

            // non-syntactic elements:
            case Kind::BuiltinStmt:
            {
                return on_visit_builtin_type_stmt(dynamic_cast<BuiltinStmt *>(node), visit_order);
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
