#ifndef INCLUDED_PDM_AST_PATTERN_VPATTERN_HH
#define INCLUDED_PDM_AST_PATTERN_VPATTERN_HH

#include <vector>

#include "pdm/ast/node.hh"
#include "pdm/ast/typespec/typespec.hh"
#include "pdm/core/intern.hh"

namespace pdm::ast {

    class VPattern: public Node {
      public:
        class Field {
          private:
            intern::String m_name;
            Typespec*      m_typespec;
          public:
            Field(intern::String name, Typespec* typespec)
            : m_name(name),
              m_typespec(typespec) {}
        };
      
      private:
        std::vector<VPattern::Field> m_fields;

      public:
        VPattern(source::Loc loc, std::vector<VPattern::Field>&& fields)
        : Node(loc, Kind::VPattern),
          m_fields(std::move(fields)) {}
    };

}

#endif  // INCLUDED_PDM_AST_PATTERN_VPATTERN_HH
