#ifndef INCLUDED_PDM_AST_EXP_STRUCT_HH
#define INCLUDED_PDM_AST_EXP_STRUCT_HH

#include <vector>

#include "pdm/ast/kind.hh"
#include "pdm/ast/exp/exp.hh"
#include "pdm/source/loc.hh"
#include "pdm/core/intern.hh"

namespace pdm::ast {

    class StructExp: public Exp {
      public:
        class Field {
            intern::String m_name;
            Exp*           m_value;

          public:
            Field(intern::String name, Exp* value)
            : m_name(name), m_value(value) {}
        };

      private:
        std::vector<StructExp::Field> m_fields;
    
      public:
        StructExp(source::Loc loc, std::vector<StructExp::Field>&& fields)
        : Exp(loc, Kind::StructExp),
          m_fields(std::move(fields)) {}
    };

}

#endif  // INCLUDED_PDM_AST_EXP_STRUCT_HH