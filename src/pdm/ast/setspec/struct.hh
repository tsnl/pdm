#ifndef INCLUDED_PDM_AST_TYPESPEC_STRUCT_HH
#define INCLUDED_PDM_AST_TYPESPEC_STRUCT_HH

#include <vector>

#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/setspec/typespec.hh"

namespace pdm::ast {

    class Manager;

    class StructTypeSpec: public TypeSpec {
        friend Manager;

      public:
        class Field {
          private:
            source::Loc    m_loc;
            intern::String m_lhs_name;
            TypeSpec*      m_rhs_typespec;
          
          public:
            Field(source::Loc loc, intern::String name, TypeSpec* typespec)
            : m_loc(loc),
              m_lhs_name(name), m_rhs_typespec(typespec) {}
          
          public:
            source::Loc const& loc() const {
                return m_loc;
            }
            intern::String lhs_name() const {
                return m_lhs_name;
            }
            TypeSpec* rhs_typespec() const {
                return m_rhs_typespec;
            }
        };

      private:
        std::vector<StructTypeSpec::Field*> m_fields;
        
      protected:
        StructTypeSpec(source::Loc loc, std::vector<StructTypeSpec::Field*>&& fields)
        : TypeSpec(loc, Kind::StructTypeSpec),
          m_fields(std::move(fields)) {}

      public:
        std::vector<StructTypeSpec::Field*> const& fields() const {
            return m_fields;
        }
    };

}

#endif  // INCLUDED_PDM_AST_TYPESPEC_STRUCT_HH