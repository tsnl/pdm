#ifndef INCLUDED_PDM_AST_PATTERN_LPATTERN_HH
#define INCLUDED_PDM_AST_PATTERN_LPATTERN_HH

#include <vector>

#include "pdm/core/intern.hh"
#include "pdm/ast/node.hh"
#include "pdm/ast/typespec/typespec.hh"

namespace pdm::ast {

    class LPattern: public Node {
      public:
        enum class FieldKind {
            IdSingleton,
            MutIdSingleton,
            IdTypespecPair
        };
        class Field {
          private:
            FieldKind       m_kind;
            intern::String  m_name;
            Typespec*       m_rhs_typespec;
          public:
            Field(FieldKind kind, intern::String name, Typespec* rhs_typespec)
            : m_kind(kind), m_name(name), m_rhs_typespec(rhs_typespec) {}
        };
      private:
        std::vector<LPattern::Field> m_fields;
      public:
        LPattern(source::Loc loc, std::vector<LPattern::Field>&& fields)
        : Node(loc, Kind::LPattern),
          m_fields(std::move(fields)) {}
    };

}

#endif  // INCLUDED_PDM_AST_PATTERN_LPATTERN_HH
