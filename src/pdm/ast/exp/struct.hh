#ifndef INCLUDED_PDM_AST_EXP_STRUCT_HH
#define INCLUDED_PDM_AST_EXP_STRUCT_HH

#include <vector>

#include "pdm/ast/kind.hh"
#include "pdm/ast/exp/exp.hh"
#include "pdm/source/loc.hh"
#include "pdm/core/intern.hh"

namespace pdm::ast {

    class Manager;

    class StructExp: public Exp {
        friend Manager;

      public:
        class Field {
            friend Manager;

          private:
            intern::String m_name;
            Exp*           m_value;

          protected:
            Field(intern::String name, Exp* value)
            : m_name(name), m_value(value) {}
          
          public:
            intern::String name() const {
                return m_name;
            }
            Exp* value() const {
                return m_value;
            }
        };

      private:
        std::vector<StructExp::Field*> m_fields;
    
      protected:
        StructExp(source::Loc loc, std::vector<StructExp::Field*>&& fields)
        : Exp(loc, Kind::StructExp),
          m_fields(std::move(fields)) {}

      public:
        std::vector<StructExp::Field*> const& fields() const {
            return m_fields;
        }
    };

}

#endif  // INCLUDED_PDM_AST_EXP_STRUCT_HH