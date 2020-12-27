#ifndef INCLUDED_PDM_AST_PATTERN_TPATTERN_HH
#define INCLUDED_PDM_AST_PATTERN_TPATTERN_HH

#include <vector>

#include "pdm/core/intern.hh"
#include "pdm/ast/node.hh"
#include "pdm/ast/typespec/typespec.hh"

namespace pdm::ast {

    class Manager;

    class TPattern: public Node {
        friend Manager;

      public:
        enum class FieldKind {
            Value,
            Type
        };
        class Field {
            friend Manager;

          private:
            source::Loc m_loc;
            FieldKind m_kind;
            intern::String m_lhs_name;
            Typespec* m_typespec;

          protected:
            Field(source::Loc loc, FieldKind kind, intern::String name, Typespec* rhs_typespec)
            : m_loc(loc),
              m_kind(kind),
              m_lhs_name(name),
              m_typespec(rhs_typespec) {}
          
          public:
            source::Loc const& loc() const {
                return m_loc;
            }
            FieldKind kind() const { 
                return m_kind; 
            }
            intern::String name() const {
                return m_lhs_name; 
            }
            Typespec* rhs_typespec() const {
                return m_typespec; 
            }
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
        std::vector<TPattern::Field*> const& fields() const {
            return m_fields;
        }
        bool is_only_captured() const {
            return m_is_only_captured;
        }
    };
}

#endif  // INCLUDED_PDM_AST_PATTERN_TPATTERN_HH
