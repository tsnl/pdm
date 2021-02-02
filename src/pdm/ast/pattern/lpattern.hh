#ifndef INCLUDED_PDM_AST_PATTERN_LPATTERN_HH
#define INCLUDED_PDM_AST_PATTERN_LPATTERN_HH

#include <vector>
#include <cassert>

#include "pdm/core/intern.hh"
#include "pdm/ast/node.hh"
#include "pdm/ast/setspec/type_spec.hh"

#include "base_field.hh"

namespace pdm::scoper {
    class Defn;
}
namespace pdm::types {
    class TypeVar;
}
namespace pdm::ast {
    class Manager;
}

namespace pdm::ast {

    class LPattern: public Node {
        friend Manager;

      public:
        enum class FieldKind {
            IdSingleton,
            IdTypeSpecPair
        };
        class Field: public BaseField {
            friend Manager;
          
          private:
            FieldKind       m_field_kind;
            TypeSpec*       m_opt_rhs_typespec;
            types::TypeVar* m_x_defn_tv;
            
          protected:
            Field(source::Loc loc, FieldKind field_kind, intern::String name, TypeSpec* opt_rhs_typespec = nullptr)
            :   BaseField(loc, Kind::Aux_LPatternField, name),
                m_field_kind(field_kind),
                m_opt_rhs_typespec(opt_rhs_typespec)
            {
                if (opt_rhs_typespec) {
                    assert(
                        (field_kind == LPattern::FieldKind::IdTypeSpecPair) &&
                        ("LPattern: cannot pass rhs_typespec for singleton field.")
                    );
                }
            }
          
          public:
            [[nodiscard]] FieldKind field_kind() const;
            [[nodiscard]] TypeSpec* opt_rhs_typespec() const;

          public:
            [[nodiscard]] types::TypeVar* x_defn_tv() const;
            void x_defn_tv(types::TypeVar* defn_tv);
        };
      
      private:
        std::vector<LPattern::Field*> m_fields;
        bool                          m_destructure;
      
      protected:
        LPattern(source::Loc loc, std::vector<LPattern::Field*>&& fields, bool destructure);
      
      public:
        [[nodiscard]] bool destructure() const;
        [[nodiscard]] std::vector<LPattern::Field*> const& fields() const;
    };

    inline bool LPattern::destructure() const {
        return m_destructure;
    }

    inline std::vector<LPattern::Field *> const &LPattern::fields() const {
        return m_fields;
    }

    inline LPattern::LPattern(source::Loc loc, std::vector<LPattern::Field *> &&fields, bool destructure)
    :   Node(loc, Kind::LPattern),
        m_fields(std::move(fields)),
        m_destructure(destructure) {}

    inline LPattern::FieldKind LPattern::Field::field_kind() const {
        return m_field_kind;
    }

    inline TypeSpec* LPattern::Field::opt_rhs_typespec() const {
        return m_opt_rhs_typespec;
    }

    inline types::TypeVar* LPattern::Field::x_defn_tv() const {
        return m_x_defn_tv;
    }

    inline void LPattern::Field::x_defn_tv(types::TypeVar* defn_tv) {
        m_x_defn_tv = defn_tv;
    }

}

#endif  // INCLUDED_PDM_AST_PATTERN_LPATTERN_HH
