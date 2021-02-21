#ifndef INCLUDED_PDM_AST_PATTERN_VPATTERN_HH
#define INCLUDED_PDM_AST_PATTERN_VPATTERN_HH

#include <vector>

#include "pdm/ast/node.hh"
#include "pdm/ast/type_spec/type_spec.hh"
#include "pdm/core/intern.hh"
#include "pdm/ast/arg/varg.hh"

#include "base_field.hh"

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
            types::TypeVar* m_x_defn_tv;

          protected:
            Field(source::Loc loc, intern::String lhs_name, TypeSpec* rhs_typespec, VArgAccessSpec accepted_varg_kind);

          public:
            [[nodiscard]] TypeSpec* rhs_typespec() const;
            [[nodiscard]] VArgAccessSpec accepted_varg_kind() const;

          public:
            [[nodiscard]] types::TypeVar* x_defn_tv() const;
            void x_defn_tv(types::TypeVar* defn_tv);
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

    inline void VPattern::Field::x_defn_tv(types::TypeVar* defn_tv) {
        m_x_defn_tv = defn_tv;
    }

    inline types::TypeVar* VPattern::Field::x_defn_tv() const {
        return m_x_defn_tv;
    }

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
        m_accepted_varg_kind(accepted_varg_kind),
        m_x_defn_tv(nullptr)
    {}

}

#endif  // INCLUDED_PDM_AST_PATTERN_VPATTERN_HH
