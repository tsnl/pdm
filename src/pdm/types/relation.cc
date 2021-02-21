#include <iostream>

#include "relation.hh"
#include "var_invariant.hh"
#include "manager.hh"

#include "var.hh"

namespace pdm::types {

    //
    // constructors:
    //

    IsStructRelation::IsStructRelation(
        std::string&& why, ast::Node* node,
        TypeVar* struct_tv,
        std::map<intern::String, Var*> fields_tvs
    )
    : IsFieldCollectionRelation(
        IsFieldCollectionRelation::FieldCollectionKind::Struct,
        std::move(why),
        node, struct_tv, std::move(fields_tvs)
        )
    {}

    IsEnumRelation::IsEnumRelation(
        std::string&& why,
        ast::Node* node,
        TypeVar* enum_tv,
        std::map<intern::String, Var*> fields_tvs
    )
    : IsFieldCollectionRelation(
        IsFieldCollectionRelation::FieldCollectionKind::Enum,
        std::move(why),
        node,
        enum_tv, std::move(fields_tvs)
        )
    {}

    IsModuleRelation::IsModuleRelation(
        std::string&& why,
        ast::Node* node,
        TypeVar* module_tv,
        std::map<intern::String, Var*> fields_tvs
    )
    : IsFieldCollectionRelation(
        IsFieldCollectionRelation::FieldCollectionKind::Module,
        std::move(why),
        node,
        module_tv,
        std::move(fields_tvs)
        )
    {}

    //
    // on_assume:
    //

    void Relation::on_assume(types::Manager* manager) {
        if (m_apply_state == ApplyState::NotApplied) {
            if (on_assume_impl(manager)) {
                m_apply_state = ApplyState::Applied_OK;
            } else {
                m_apply_state = ApplyState::Applied_Fail;
            }
        }
    }

    bool SubtypeOfRelation::on_assume_impl(types::Manager* manager) {
        SolveResult assume_op_result = m_subtype_tv->assume_invariant_holds(
            new SubtypeOfInvariant(this, m_supertype_tv));
        return !result_is_error(assume_op_result);
    }
    bool SubclassOfRelation::on_assume_impl(types::Manager* manager) {
        SolveResult assume_op_result = m_subclass_cv->assume_invariant_holds(
            new SubclassOfInvariant(this, m_superclass_cv));
        return !result_is_error(assume_op_result);
    }
    bool ClassOfRelation::on_assume_impl(types::Manager* manager) {
        SolveResult assume_op_result = m_class_cv->assume_invariant_holds(new ClassOfInvariant(this, m_member_tv));
        return !result_is_error(assume_op_result);
    }
    
    bool TypeEqualsRelation::on_assume_impl(types::Manager* manager) {
        SolveResult assume_op_result1 = manager->assume_relation_holds(&m_lhs_subtype_of_rhs_relation);
        SolveResult assume_op_result2 = manager->assume_relation_holds(&m_rhs_subtype_of_lhs_relation);
        if (!result_is_error(result_and(assume_op_result1, assume_op_result2))) {
            return (
                m_lhs_subtype_of_rhs_relation.on_assume_impl(manager) &&
                m_rhs_subtype_of_lhs_relation.on_assume_impl(manager)
            );
        } else {
            return false;
        }
    }
    bool ClassEqualsRelation::on_assume_impl(types::Manager* manager) {
        SolveResult assume_op_result1 = manager->assume_relation_holds(&m_lhs_subclass_of_rhs_relation);
        SolveResult assume_op_result2 = manager->assume_relation_holds(&m_rhs_subclass_of_lhs_relation);
        if (!result_is_error(result_and(assume_op_result1, assume_op_result2))) {
            return (
                m_lhs_subclass_of_rhs_relation.on_assume_impl(manager) &&
                m_rhs_subclass_of_lhs_relation.on_assume_impl(manager)
            );
        } else {
            return false;
        }
    }

    bool LetValueRelation::on_assume_impl(types::Manager* manager) {
        SolveResult assume_op_result = m_typeof_lhs_tv->assume_invariant_holds(
            new SubtypeOfInvariant(this, m_typeof_rhs_tv));
        return !result_is_error(assume_op_result);
    }
    bool LetTypeRelation::on_assume_impl(types::Manager* manager) {
        SolveResult assume_op_result1 = m_lhs_tv->assume_invariant_holds(new SubtypeOfInvariant(this, m_rhs_tv));
        SolveResult assume_op_result2 = m_rhs_tv->assume_invariant_holds(new SubtypeOfInvariant(this, m_lhs_tv));
        return !result_is_error(result_and(assume_op_result1, assume_op_result2));
    }
    bool LetClassRelation::on_assume_impl(types::Manager* manager) {
        SolveResult assume_op_result1 = m_lhs_cv->assume_invariant_holds(new SubclassOfInvariant(this, m_rhs_cv));
        SolveResult assume_op_result2 = m_rhs_cv->assume_invariant_holds(new SubclassOfInvariant(this, m_lhs_cv));
        return !result_is_error(result_and(assume_op_result1, assume_op_result2));
    }

    bool DotNameRelation::on_assume_impl(types::Manager* manager) {
        VarInvariant* the_invariant = nullptr;
        
        std::cout << "NotImplemented: DotNameRelation::on_assume_impl" << std::endl;

        // todo: create appropriate invariants here.
        switch (m_dot_name_relation_kind)
        {
            case DotNameRelationKind::ModuleValueField:
            {
                // the_invariant = new ModuleWithValueFieldInvariant(this, VarKind::Type, m_rhs_name, m_eval_type);
                // the_invariant = new IsModuleInvariant(this, VarKind::Type, )
                break;
            }
            case DotNameRelationKind::ModuleTypeField:
            {
                // the_invariant = new ModuleWithTypeFieldInvariant(this, VarKind::Type, m_rhs_name, m_eval_type);
                break;
            }
            case DotNameRelationKind::StructValueField:
            case DotNameRelationKind::StructTypeField:
            {
                // the_invariant = new StructWithFieldInvariant(this, VarKind::Type, m_rhs_name, m_eval_type);
                break;
            }
            case DotNameRelationKind::EnumValueField:
            {
                EnumDotNameRelation* self = dynamic_cast<EnumDotNameRelation*>(this);
                // the_invariant = new EnumWithFieldInvariant(this, VarKind::Type, m_rhs_name, self->args(), EnumWithFieldInvariantStrength::Actual);
                break;
            }
        }
        return !result_is_error(m_lhs->assume_invariant_holds(the_invariant));
    }

    bool IsFieldCollectionRelation::on_assume_impl(types::Manager* manager) {
        switch (m_field_collection_kind)
        {
            case FieldCollectionKind::Struct:
            {
                auto invariant = new IsStructInvariant(
                    this,
                    VarArchetype::Type,
                    m_fields
                );
                return !result_is_error(m_collection_tv->assume_invariant_holds(invariant));
            }
            case FieldCollectionKind::Enum:
            {
                auto invariant = new IsEnumInvariant(
                    this,
                    VarArchetype::Type,
                    m_fields
                );
                return !result_is_error(m_collection_tv->assume_invariant_holds(invariant));
            }
            case FieldCollectionKind::Module:
            {
                auto invariant = new IsModuleInvariant(
                    this,
                    VarArchetype::Type,
                    m_fields
                );
                return !result_is_error(m_collection_tv->assume_invariant_holds(invariant));
            }
        }
        return true;
    }

    bool IsTupleRelation::on_assume_impl(types::Manager* types_mgr) {
        // todo: implement me!
        std::cout << "NotImplemented: TupleOfRelation::on_assume_impl" << std::endl;
        return true;
    }

    bool DotIndexRelation::on_assume_impl(types::Manager* manager) {
        VarInvariant* the_invariant = nullptr;
        // todo: require LHS is an array or a tuple.
        // todo: require index is an int.
        std::cout << "NotImplemented: TupleOfRelation::on_assume_impl" << std::endl;
        return false;
    }

    bool FormalVCallableRelation::on_assume_impl(types::Manager* manager) {
        std::vector<VCallArg> formal_args = args();
        auto invariant = new IsVCallableInvariant(
            VCallInvariantStrength::Formal,
            this, VarArchetype::Type,
            std::move(formal_args), ret_tv()
        );
        SolveResult kd_res = fn_tv()->assume_invariant_holds(invariant);
        return !result_is_error(kd_res);
    }

    bool ActualVCallableRelation::on_assume_impl(types::Manager* manager) {
        std::vector<VCallArg> actual_args = args();
        auto invariant = new IsVCallableInvariant(
            VCallInvariantStrength::Actual,
            this, VarArchetype::Type,
            std::move(actual_args), ret_tv()
        );
        SolveResult kd_res = fn_tv()->assume_invariant_holds(invariant);
        return !result_is_error(kd_res);
    }

    bool IfThenRelation::on_assume_impl(types::Manager* manager) {
        SolveResult kd_res = SolveResult::NoChange;

        // cond :< bool
        {
            auto cond_branch_invariant = new SubtypeOfInvariant(this, manager->get_u1_tv());
            kd_res = result_and(kd_res, m_cond->assume_invariant_holds(cond_branch_invariant));
        }

        // then :< output
        {
            auto then_branch_invariant = new SubtypeOfInvariant(this, m_then);
            kd_res = result_and(kd_res, m_output_tv->assume_invariant_holds(then_branch_invariant));
        }

        return !result_is_error(kd_res);
    }
    bool IfThenElseRelation::on_assume_impl(types::Manager* manager) {
        SolveResult kd_res = SolveResult::NoChange;

        // cond :< bool
        {
            auto cond_branch_invariant = new SubtypeOfInvariant(this, manager->get_u1_tv());
            kd_res = result_and(kd_res, m_cond->assume_invariant_holds(cond_branch_invariant));
        }

        // then :< output
        {
            auto then_branch_invariant = new SubtypeOfInvariant(this, m_then);
            kd_res = result_and(kd_res, m_output->assume_invariant_holds(then_branch_invariant));
        }

        // else :< output
        {
            auto else_branch_invariant = new SubtypeOfInvariant(this, m_else);
            kd_res = result_and(kd_res, m_output->assume_invariant_holds(else_branch_invariant));
        }

        return !result_is_error(kd_res);
    }

    bool BitcastableRelation::on_assume_impl(types::Manager* manager) {
        // todo: implement me!
        std::cout << "NotImplemented: BitcastableRelation::on_assume_impl" << std::endl;
        return true;
    }

    bool ConvertibleRelation::on_assume_impl(types::Manager* manager) {
        // todo: implement me!
        std::cout << "NotImplemented: ConvertableRelation::on_assume_impl" << std::endl;
        return true;
    }

    bool TemplateRelation::on_assume_impl(types::Manager* manager) {
        // todo: implement me!
        std::cout << "NotImplemented: TemplateRelation::on_assume_impl" << std::endl;
        return true;       
    }

    bool IsNumberRelation::on_assume_impl(types::Manager* manager) {
        SolveResult result = m_number_tv->assume_invariant_holds(new IsNumberVarInvariant(this));
        return !result_is_error(result);
    }

}
