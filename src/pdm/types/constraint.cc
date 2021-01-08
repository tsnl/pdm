#include "constraint.hh"

#include "relation.hh"

namespace pdm::types {

    KindConstraint::KindConstraint(typer::Rule* parent_rule, VarKind domain_var_kind, pdm::u64 allowed_kinds_bitset)
    :   Constraint(parent_rule, domain_var_kind),
        m_allowed_type_kinds_bitset(allowed_kinds_bitset)
    {}

    bool Constraint::test(TypeVar const* arg) {
        // todo: make this method pure virtual once ready.
        return false;
    }
    bool Constraint::apply(TypeVar* arg) {
        // todo: make this method pure virtual once ready.
        return false;
    }

    SubtypeOfConstraint::SubtypeOfConstraint(typer::Rule* parent_rule, TypeVar* supertype_tv)
    :   Constraint(parent_rule, VarKind::Type),
        m_supertype_tv(supertype_tv)
    {}

    SubclassOfConstraint::SubclassOfConstraint(typer::Rule* parent_rule, ClassVar* superclass_cv)
    :   Constraint(parent_rule, VarKind::Class),
        m_superclass_cv(superclass_cv)
    {}

    KindDependentConstraint::KindDependentConstraint(typer::Rule* parent_rule, VarKind domain_var_kind, TypeKind required_type_kind)
    :   Constraint(parent_rule, domain_var_kind),
        m_required_type_kind(required_type_kind)
    {}

}
