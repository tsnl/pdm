#ifndef INCLUDED_PDM_AST_PATTERN_VPATTERN_HH
#define INCLUDED_PDM_AST_PATTERN_VPATTERN_HH

#include <vector>

#include "pdm/ast/node.hh"
#include "pdm/ast/type_spec/type_spec.hh"
#include "pdm/core/intern.hh"
#include "pdm/ast/arg/varg.hh"

#include "base-field.hh"

namespace pdm::ast {
    class Manager;
}
namespace pdm::types {
    class TypeVar;
}

namespace pdm::ast {

    class VPattern: public Node {
        friend Manager;

      public:
        class Field: public BaseField {
            friend Manager;

          private:
            TypeSpec*       m_typespec;
            VArgAccessSpec  m_accepted_varg_kind;

          protected:
            Field(source::Loc loc, intern::String lhs_name, TypeSpec* rhs_typespec, VArgAccessSpec accepted_varg_kind);

          public:
            [[nodiscard]] TypeSpec* rhs_typespec() const;
            [[nodiscard]] VArgAccessSpec accepted_varg_kind() const;

          public:
            [[nodiscard]] types::TypeVar* x_defn_tv() const;
        };

      private:
        std::vector<VPattern::Field*> m_fields;

      protected:
        VPattern(source::Loc loc, std::vector<VPattern::Field*>&& fields);

      public:
        [[nodiscard]] std::vector<VPattern::Field*> const& fields() const;
    };

    inline std::vector<VPattern::Field*> const& VPattern::fields() const {
        return m_fields;
    }

    inline VPattern::VPattern(source::Loc loc, std::vector<VPattern::Field*>&& fields)
    :   Node(loc, Kind::VPattern),
        m_fields(std::move(fields)) {}

    inline VArgAccessSpec VPattern::Field::accepted_varg_kind() const {
        return m_accepted_varg_kind;
    }

    inline TypeSpec* VPattern::Field::rhs_typespec() const {
        return m_typespec;
    }

    inline VPattern::Field::Field(
        source::Loc loc,
        intern::String lhs_name,
        TypeSpec* rhs_typespec,
        VArgAccessSpec accepted_varg_kind
    )
    :   BaseField(loc, Kind::Aux_VPatternField, lhs_name),
        m_typespec(rhs_typespec),
        m_accepted_varg_kind(accepted_varg_kind)
    {}

}

#endif  // INCLUDED_PDM_AST_PATTERN_VPATTERN_HH
