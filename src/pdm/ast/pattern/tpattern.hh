#ifndef INCLUDED_PDM_AST_PATTERN_TPATTERN_HH
#define INCLUDED_PDM_AST_PATTERN_TPATTERN_HH

#include <vector>

#include "pdm/core/intern.hh"
#include "pdm/ast/node.hh"
#include "pdm/ast/type_spec/type_spec.hh"

#include "base-field.hh"

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
            Node* m_set_spec;

          protected:
            Field(source::Loc loc, FieldKind kind, intern::String name, Node* rhs_set_spec);
          
          public:
            [[nodiscard]] FieldKind field_kind() const;
            [[nodiscard]] Node* rhs_set_spec() const;
          
          public:
            [[nodiscard]] types::Var* x_defn_var() const;
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

    inline TPattern::Field::Field(
        source::Loc loc,
        TPattern::FieldKind field_kind,
        intern::String name,
        Node *rhs_set_spec
    )
    :   BaseField(loc, Kind::Aux_TPatternField, name),
        m_field_kind(field_kind),
        m_set_spec(rhs_set_spec)
    {}

    inline TPattern::FieldKind TPattern::Field::field_kind() const {
        return m_field_kind;
    }

    inline Node* TPattern::Field::rhs_set_spec() const {
        return m_set_spec;
    }

}

#endif  // INCLUDED_PDM_AST_PATTERN_TPATTERN_HH
