#ifndef INCLUDED_PDM_AST_PATTERN_TPATTERN_HH
#define INCLUDED_PDM_AST_PATTERN_TPATTERN_HH

#include <vector>

#include "pdm/core/intern.hh"
#include "pdm/ast/node.hh"
#include "pdm/ast/setspec/type_spec.hh"

#include "base_field.hh"

namespace pdm::ast {
    class Manager;
    class SetSpec;
}
namespace pdm::types {
    class Var;
}

namespace pdm::ast {

    class TPattern: public Node {
        friend Manager;

      public:
        enum class FieldKind {
            Value,
            Type
        };
        class Field: public BaseField {
            friend Manager;

          private:
            FieldKind m_field_kind;
            SetSpec* m_set_spec;
            types::Var* m_x_defn_var;

          protected:
            Field(source::Loc loc, FieldKind kind, intern::String name, SetSpec* rhs_set_spec);
          
          public:
            [[nodiscard]] FieldKind field_kind() const;
            [[nodiscard]] SetSpec* rhs_set_spec() const;
          
          public:
            [[nodiscard]] types::Var* x_defn_var() const;
            void x_defn_var(types::Var* defn_var);
        };

      private:
        std::vector<TPattern::Field*> m_fields;
        bool                          m_is_only_captured;

      protected:
        TPattern(source::Loc loc, std::vector<TPattern::Field*>&& fields, bool is_only_captured)
        : Node(loc, Kind::TPattern),
          m_fields(std::move(fields)),
          m_is_only_captured(is_only_captured) {}

      public:
        [[nodiscard]] std::vector<TPattern::Field*> const& fields() const;
        [[nodiscard]] bool is_only_captured() const;
    };

    inline bool TPattern::is_only_captured() const {
        return m_is_only_captured;
    }

    inline std::vector<TPattern::Field *> const &TPattern::fields() const {
        return m_fields;
    }

    inline TPattern::Field::Field(source::Loc loc, TPattern::FieldKind field_kind, intern::String name, SetSpec *rhs_set_spec)
    :   BaseField(loc, Kind::Aux_TPatternField, name),
        m_field_kind(field_kind),
        m_set_spec(rhs_set_spec),
        m_x_defn_var(nullptr)
    {}

    inline TPattern::FieldKind TPattern::Field::field_kind() const {
        return m_field_kind;
    }

    inline SetSpec* TPattern::Field::rhs_set_spec() const {
        return m_set_spec;
    }

    inline types::Var* TPattern::Field::x_defn_var() const {
        return m_x_defn_var;
    }

    inline void TPattern::Field::x_defn_var(types::Var* defn_var) {
        m_x_defn_var = defn_var;
    }
}

#endif  // INCLUDED_PDM_AST_PATTERN_TPATTERN_HH
