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
            intern::String m_name;
            Typespec*      m_typespec;
          public:
            Field(intern::String name, Typespec* typespec)
            : m_name(name), m_typespec(typespec) {}
        };

      private:
        std::vector<StructTypespec::Field> m_fields;
        
      public:
        StructTypespec(source::Loc loc, std::vector<StructTypespec::Field>&& fields)
        : Typespec(loc, Kind::StructTypespec),
          m_fields(std::move(fields)) {}
    };

}

#endif  // INCLUDED_PDM_AST_TYPESPEC_STRUCT_HH