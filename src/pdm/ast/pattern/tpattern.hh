#ifndef INCLUDED_PDM_AST_PATTERN_TPATTERN_HH
#define INCLUDED_PDM_AST_PATTERN_TPATTERN_HH

#include <vector>

#include "pdm/core/intern.hh"
#include "pdm/ast/node.hh"
#include "pdm/ast/typespec/typespec.hh"

namespace pdm::ast {
    class TPattern: public Node {
      public:
        enum class FieldKind {
            Value,
            Type
        };
        class Field {
          private:
            FieldKind m_kind;
            intern::String m_name;
            Typespec* m_typespec;
          public:
            Field(FieldKind kind, intern::String name, Typespec* typespec)
            : m_kind(kind),
              m_name(name),
              m_typespec(typespec) {}
        };

      private:
        std::vector<TPattern::Field> m_fields;

      public:
        TPattern(source::Loc loc, std::vector<Field>&& fields)
        : Node(loc, Kind::TPattern),
          m_fields(std::move(fields)) {}
    };
}

#endif  // INCLUDED_PDM_AST_PATTERN_TPATTERN_HH
