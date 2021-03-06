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

            case Kind::Script: {
                auto script = dynamic_cast<Script*>(node);
                for (ast::HeaderStmt* head_stmt: script->header_stmts()) {
                    ok = visit(head_stmt) && ok;
                }
                for (ast::Script::Field* body_field: script->body_fields()) {
                    ok = visit(body_field) && ok; 
                }
                break;
            }
            case Kind::ScriptField: {
                auto field = dynamic_cast<Script::Field*>(node);
                ok = visit(field->rhs_mod_exp()) && ok;
                break;
            }

            //
            // Modules:
            //

            case Kind::ModExp: {
                auto exp = dynamic_cast<ModExp*>(node);
                for (ast::ModExp::Field* field: exp->fields()) {
                    ok = visit(field) && ok;
                }
                break;
            }
            case Kind::ModModField: {
                auto field = dynamic_cast<ModExp::ModuleField*>(node);
                ok = visit(field->rhs_mod_exp()) && ok;
                break;
            }
            case Kind::ValueModField: {
                auto field = dynamic_cast<ModExp::ValueField*>(node);
                ok = visit(field->rhs_exp()) && ok;
                break;
            }
            case Kind::TypeModField: {
                auto field = dynamic_cast<ModExp::TypeField*>(node);
                ok = visit(field->rhs_type_spec()) && ok;
                break;
            }
            case Kind::ClassModField: {
                auto field = dynamic_cast<ModExp::ClassField*>(node);
                ok = visit(field->rhs_class_spec()) && ok;
                break;
            }

            case Kind::ModAddress: {
                auto address = dynamic_cast<ModAddress*>(node);
                for (ast::TArg* template_arg: address->template_args()) {
                    ok = visit(template_arg) && ok;
                }
                break;
            }

            //
            // statements:
            //

            case Kind::DiscardStmt: {
                auto discard_stmt = dynamic_cast<DiscardStmt*>(node);
                ok = visit(discard_stmt->discarded_exp()) && ok;
                break;
            }
            case Kind::ConstStmt: {
                auto const_stmt = dynamic_cast<ConstStmt*>(node);
                ok = visit(const_stmt->lhs_lpattern()) && ok;
                ok = visit(const_stmt->rhs_exp()) && ok;
                break;
            } 
            case Kind::ValStmt: {
                auto val_stmt = dynamic_cast<ValStmt*>(node);
                ok = visit(val_stmt->lhs_lpattern()) && ok;
                ok = visit(val_stmt->rhs_exp()) && ok;
                break;
            }
            case Kind::VarStmt: {
                auto var_stmt = dynamic_cast<VarStmt*>(node);
                ok = visit(var_stmt->lhs_lpattern()) && ok;
                ok = visit(var_stmt->rhs_exp()) && ok;
                break;
            }
            case Kind::SetStmt: {
                auto set_stmt = dynamic_cast<SetStmt*>(node);
                ok = visit(set_stmt->lhs_exp()) && ok;
                ok = visit(set_stmt->rhs_exp()) && ok;
                break;
            }
            case Kind::ExternStmt: {
                auto extern_stmt = dynamic_cast<ExternStmt*>(node);
                ok = visit(extern_stmt->link_arg()) && ok;
                break;
            }
            case Kind::ImportStmt:
            case Kind::UsingStmt:
            {
                // no children
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
            case Kind::ParenExp: {
                auto paren_exp = dynamic_cast<ParenExp*>(node);
                ok = visit(paren_exp->nested_exp()) && ok;
                break;
            }
            case Kind::ArrayExp: {
                auto array_exp = dynamic_cast<ArrayExp*>(node);
                for (auto const item_exp: array_exp->items()) {
                    ok = visit(item_exp) && ok;
                }
                break;
            }
            case Kind::TupleExp: {
                auto tuple_exp = dynamic_cast<TupleExp*>(node);
                for (Exp* tuple_item_exp: tuple_exp->items()) {
                    ok = visit(tuple_item_exp) && ok;
                }
                break;
            }
            case Kind::StructExp: {
                auto struct_exp = dynamic_cast<StructExp*>(node);
                for (StructExp::Field* field: struct_exp->fields()) {
                    ok = visit(field->value()) && ok;
                }
                break;
            }
            case Kind::ChainExp: {
                auto chain_exp = dynamic_cast<ChainExp*>(node);
                for (auto const prefix_stmt: chain_exp->prefix()) {
                    ok = visit(prefix_stmt) && ok;
                }
                if (chain_exp->suffix()) {
                    ok = visit(chain_exp->suffix()) && ok;
                }
                break;
            }
            case Kind::LambdaExp: {
                auto lambda_exp = dynamic_cast<LambdaExp*>(node);
                ok = visit(lambda_exp->lhs_vpattern()) && ok;
                if (lambda_exp->opt_ret_typespec()) {
                    ok = visit(lambda_exp->opt_ret_typespec()) && ok;
                }
                ok = visit(lambda_exp->rhs_body()) && ok;
                break;
            }
            case Kind::IfExp: {
                auto if_exp = dynamic_cast<IfExp*>(node);
                ok = visit(if_exp->cond_exp()) && ok;
                ok = visit(if_exp->then_exp()) && ok;
                if (if_exp->else_exp()) {
                    ok = visit(if_exp->else_exp()) && ok;
                }
                break;
            }
            case Kind::DotIndexExp: {
                auto dot_index_exp = dynamic_cast<DotIndexExp*>(node);
                ok = visit(dot_index_exp->lhs()) && ok;
                break;
            }
            case Kind::DotNameExp: {
                auto dot_name_exp = dynamic_cast<DotNameExp*>(node);
                ok = visit(dot_name_exp->lhs()) && ok;
                break;
            }
            case Kind::ModuleDotExp: {
                auto mod_dot_exp = dynamic_cast<ModuleDotExp*>(node);
                ok = visit(mod_dot_exp->lhs_mod_address()) && ok;
                break;
            }
            case Kind::UnaryExp: {
                auto unary_exp = dynamic_cast<UnaryExp*>(node);
                ok = visit(unary_exp->operand()) && ok;
                break;
            }
            case Kind::BinaryExp: {
                auto binary_exp = dynamic_cast<BinaryExp*>(node);
                ok = visit(binary_exp->lhs_operand()) && ok;
                ok = visit(binary_exp->rhs_operand()) && ok;
                break;
            }
            case Kind::VCallExp: {
                auto vcall_exp = dynamic_cast<VCallExp*>(node);
                ok = visit(vcall_exp->lhs_called()) && ok;
                for (VArg* arg: vcall_exp->args()) {
                    ok = visit(arg) && ok;
                }
                break;
            }
            case Kind::TCallExp: {
                auto tcall_exp = dynamic_cast<TCallExp*>(node);
                ok = visit(tcall_exp->lhs_called()) && ok;
                for (TArg* arg: tcall_exp->args()) {
                    ok = visit(arg) && ok;
                }
                break;
            }
            case Kind::TypeQueryExp: {
                auto type_query_exp = dynamic_cast<TypeQueryExp*>(node);
                ok = visit(type_query_exp->lhs_typespec()) && ok;
                ok = visit(type_query_exp->rhs_typespec()) && ok;
                break;
            }

            //
            // patterns:
            //

            case Kind::VPattern: {
                auto v_pattern = dynamic_cast<VPattern*>(node);
                for (VPattern::Field* field: v_pattern->fields()) {
                    ok = visit(field->rhs_typespec()) && ok;
                }
                break;
            }
            case Kind::TPattern: {
                auto t_pattern = dynamic_cast<TPattern*>(node);
                for (TPattern::Field* field: t_pattern->fields()) {
                    ok = visit(field->rhs_set_spec()) && ok;
                }
                break;
            }
            case Kind::LPattern: {
                auto l_pattern = dynamic_cast<LPattern*>(node);
                for (LPattern::Field* field: l_pattern->fields()) {
                    TypeSpec* opt_field_typespec = field->opt_rhs_typespec();
                    if (opt_field_typespec) {
                        ok = visit(opt_field_typespec) && ok;
                    }
                }
                break;
            }

            //
            // type specs:
            //

            case Kind::IdTypeSpec:
            {
                break;
            }
            case Kind::FnTypeSpec: {
                auto fn_type_spec = dynamic_cast<FnTypeSpec*>(node);
                ok = visit(fn_type_spec->lhs_vpattern()) && ok;
                ok = visit(fn_type_spec->opt_ret_type_spec()) && ok;
                break;
            }
            case Kind::ModAddressIdTypeSpec: {
                auto mai_type_spec = dynamic_cast<ModAddressIdTypeSpec*>(node);
                ok = visit(mai_type_spec->lhs_mod_address());
                break;
            }
            case Kind::StructTypeSpec: {
                auto struct_type_spec = dynamic_cast<StructTypeSpec*>(node);
                for (StructTypeSpec::Field* field: struct_type_spec->fields()) {
                    ok = visit(field->rhs_typespec()) && ok;
                }
                break;
            }
            case Kind::TupleTypeSpec: {
                auto tuple_type_spec = dynamic_cast<TupleTypeSpec*>(node);
                for (TypeSpec* item_type_spec: tuple_type_spec->items()) {
                    ok = visit(item_type_spec) && ok;
                }
                break;
            }
            case Kind::EnumTypeSpec: {
                auto enum_type_spec = dynamic_cast<EnumTypeSpec*>(node);
                for (EnumTypeSpec::Field* field: enum_type_spec->fields()) {
                    if (field->opt_type_spec()) {
                        ok = visit(field->opt_type_spec()) && ok;
                    }
                }
                break;
            }

            //
            // class specs:
            //

            case Kind::IdClassSpec: {
                auto mai_class_spec = dynamic_cast<IdClassSpec*>(node);
                break;
            }
            case Kind::ClassExpClassSpec: {
                auto class_exp_class_spec = dynamic_cast<ClassExpClassSpec*>(node);

                ok = visit(class_exp_class_spec->candidate_class_spec()) && ok;

                for (ast::TypeQueryExp* type_query_exp: class_exp_class_spec->conditions()) {
                    ok = visit(type_query_exp) && ok;
                }

                break;
            }
            case Kind::ModAddressIdClassSpec: {
                auto id_class_spec = dynamic_cast<ModAddressIdClassSpec*>(node);
                ok = visit(id_class_spec->lhs_mod_address());
                break;
            }

            //
            // shared/templates:
            //

            case Kind::TArg: {
                auto t_arg = dynamic_cast<TArg*>(node);
                ok = visit(t_arg->arg_node()) && ok;
                break;
            }
            case Kind::VArg: {
                auto v_arg = dynamic_cast<VArg*>(node);
                ok = visit(v_arg->arg_exp()) && ok;
                break;
            }

            //
            // non-syntactic elements:
            // (never parsed, only compiler-created)
            //

            case Kind::BuiltinStmt: {
                break;
            }

            //
            // invalid enum entries:
            //
            case Kind::META_Count: {
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
            case Kind::Script: return on_visit_script(
                dynamic_cast<Script*>(node),
                visit_order
            );
            case Kind::ScriptField: return on_visit_script_field(
                dynamic_cast<Script::Field*>(node),
                visit_order
            );

            // modules:
            case Kind::ModExp: return on_visit_mod_exp(
                dynamic_cast<ModExp*>(node),
                visit_order
            );
            case Kind::ModModField: return on_visit_mod_mod_field(
                dynamic_cast<ModExp::ModuleField*>(node),
                visit_order
            );
            case Kind::ClassModField: return on_visit_class_mod_field(
                dynamic_cast<ModExp::ClassField*>(node),
                visit_order
            );
            case Kind::TypeModField: return on_visit_type_mod_field(
                dynamic_cast<ModExp::TypeField*>(node),
                visit_order
            );
            case Kind::ValueModField: return on_visit_value_mod_field(
                dynamic_cast<ModExp::ValueField*>(node),
                visit_order
            );
            case Kind::ModAddress: return on_visit_mod_address(
                dynamic_cast<ModAddress*>(node),
                visit_order
            );

            // statements:
            case Kind::DiscardStmt: return on_visit_discard_stmt(
                dynamic_cast<DiscardStmt*>(node),
                visit_order
            );
            case Kind::ConstStmt: return on_visit_const_stmt(
                dynamic_cast<ConstStmt*>(node),
                visit_order
            );
            case Kind::ValStmt: return on_visit_val_stmt(
                dynamic_cast<ValStmt*>(node),
                visit_order
            );
            case Kind::VarStmt: return on_visit_var_stmt(
                dynamic_cast<VarStmt*>(node),
                visit_order
            );
            case Kind::SetStmt: return on_visit_set_stmt(
                dynamic_cast<SetStmt*>(node),
                visit_order
            );
            case Kind::ExternStmt: return on_visit_extern_stmt(
                dynamic_cast<ExternStmt*>(node),
                visit_order
            );
            case Kind::ImportStmt: return on_visit_import_stmt(
                dynamic_cast<ImportStmt*>(node),
                visit_order
            );
            case Kind::UsingStmt: return on_visit_using_stmt(
                dynamic_cast<UsingStmt*>(node),
                visit_order
            );

            // expressions:
            case Kind::UnitExp: return on_visit_unit_exp(
                dynamic_cast<UnitExp*>(node),
                visit_order
            );
            case Kind::IntExp: return on_visit_int_exp(
                dynamic_cast<IntExp*>(node),
                visit_order
            );
            case Kind::FloatExp: return on_visit_float_exp(
                dynamic_cast<FloatExp*>(node),
                visit_order
            );
            case Kind::StringExp: return on_visit_string_exp(
                dynamic_cast<StringExp*>(node),
                visit_order
            );
            case Kind::IdExp: return on_visit_id_exp(
                dynamic_cast<IdExp*>(node),
                visit_order
            );
            case Kind::ParenExp: return on_visit_paren_exp(
                dynamic_cast<ParenExp*>(node),
                visit_order
            );
            case Kind::ArrayExp: return on_visit_array_exp(
                dynamic_cast<ArrayExp*>(node),
                visit_order
            );
            case Kind::TupleExp: return on_visit_tuple_exp(
                dynamic_cast<TupleExp*>(node),
                visit_order
            );
            case Kind::StructExp: return on_visit_struct_exp(
                dynamic_cast<StructExp*>(node),
                visit_order
            );
            case Kind::ChainExp: return on_visit_chain_exp(
                dynamic_cast<ChainExp*>(node),
                visit_order
            );
            case Kind::LambdaExp: return on_visit_lambda_exp(
                dynamic_cast<LambdaExp*>(node),
                visit_order
            );
            case Kind::IfExp: return on_visit_if_exp(
                dynamic_cast<IfExp*>(node),
                visit_order
            );
            case Kind::DotIndexExp: return on_visit_dot_index_exp(
                dynamic_cast<DotIndexExp*>(node),
                visit_order
            );
            case Kind::DotNameExp: return on_visit_dot_name_exp(
                dynamic_cast<DotNameExp*>(node),
                visit_order
            );
            case Kind::ModuleDotExp: return on_visit_module_dot_exp(
                dynamic_cast<ModuleDotExp*>(node),
                visit_order
            );
            case Kind::UnaryExp: return on_visit_unary_exp(
                dynamic_cast<UnaryExp*>(node),
                visit_order
            );
            case Kind::BinaryExp: return on_visit_binary_exp(
                dynamic_cast<BinaryExp*>(node),
                visit_order
            );
            case Kind::VCallExp: return on_visit_v_call_exp(
                dynamic_cast<VCallExp*>(node),
                visit_order
            );
            case Kind::TCallExp: return on_visit_t_call_exp(
                dynamic_cast<TCallExp*>(node),
                visit_order
            );
            case Kind::TypeQueryExp: return on_visit_type_query_exp(
                dynamic_cast<TypeQueryExp*>(node),
                visit_order
            );

            // patterns:
            case Kind::VPattern: return on_visit_v_pattern(
                dynamic_cast<VPattern *>(node),
                visit_order
            );
            case Kind::TPattern: return on_visit_t_pattern(
                dynamic_cast<TPattern *>(node),
                visit_order
            );
            case Kind::LPattern: return on_visit_l_pattern(
                dynamic_cast<LPattern *>(node),
                visit_order
            );

            // type specs:
            case Kind::IdTypeSpec: return on_visit_id_type_spec(
                dynamic_cast<IdTypeSpec*>(node),
                visit_order
            );
            case Kind::FnTypeSpec: return on_visit_fn_type_spec(
                dynamic_cast<FnTypeSpec*>(node),
                visit_order
            );
            case Kind::StructTypeSpec: return on_visit_struct_type_spec(
                dynamic_cast<StructTypeSpec*>(node),
                visit_order
            );
            case Kind::TupleTypeSpec: return on_visit_tuple_type_spec(
                dynamic_cast<TupleTypeSpec*>(node),
                visit_order
            );
            case Kind::ModAddressIdTypeSpec: return on_visit_ma_type_spec(
                dynamic_cast<ModAddressIdTypeSpec*>(node),
                visit_order
            );
            case Kind::EnumTypeSpec: return on_visit_enum_type_spec(
                dynamic_cast<EnumTypeSpec*>(node),
                visit_order
            );

            // class specs:
            case Kind::IdClassSpec: return on_visit_id_class_spec(
                dynamic_cast<IdClassSpec*>(node),
                visit_order
            );
            case Kind::ClassExpClassSpec: return on_visit_class_exp_class_spec(
                dynamic_cast<ClassExpClassSpec*>(node),
                visit_order
            );
            case Kind::ModAddressIdClassSpec: return on_visit_ma_class_spec(
                dynamic_cast<ModAddressIdClassSpec*>(node),
                visit_order
            );

            // templates/shared:
            case Kind::TArg: return on_visit_t_arg(dynamic_cast<TArg*>(node), visit_order);
            case Kind::VArg: return on_visit_v_arg(dynamic_cast<VArg*>(node), visit_order);

            // non-syntactic elements:
            case Kind::BuiltinStmt: return on_visit_builtin_type_stmt(dynamic_cast<BuiltinStmt *>(node), visit_order);

            // meta elements:
            case Kind::META_Count: return false;

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
