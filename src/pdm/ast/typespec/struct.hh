#ifndef INCLUDED_PDM_AST_TYPESPEC_STRUCT_HH
#define INCLUDED_PDM_AST_TYPESPEC_STRUCT_HH

#include <vector>

#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/typespec/typespec.hh"

namespace pdm::ast {

    class StructTypespec: public Typespec {
      public:
        class Field {
          private:
            intern::String m_lhs_name;
            Typespec*      m_rhs_typespec;
          public:
            Field(intern::String name, Typespec* typespec)
            : m_lhs_name(name), m_rhs_typespec(typespec) {}
          public:
            intern::String lhs_name() const {
                return m_lhs_name;
            }
            Typespec* rhs_typespec() const {
                return m_rhs_typespec;
            }
        };

      private:
        std::vector<StructTypespec::Field> m_fields;
        
      public:
        StructTypespec(source::Loc loc, std::vector<StructTypespec::Field>&& fields)
        : Typespec(loc, Kind::StructTypespec),
          m_fields(std::move(fields)) {}

      public:
        std::vector<StructTypespec::Field> const& fields() const {
            return m_fields;
        }
    };

}

#endif  // INCLUDED_PDM_AST_TYPESPEC_STRUCT_HH