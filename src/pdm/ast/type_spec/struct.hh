#ifndef INCLUDED__PDM__AST__TYPE_SPEC__STRUCT_HH
#define INCLUDED__PDM__AST__TYPE_SPEC__STRUCT_HH

#include <vector>

#include "type_spec.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/core/intern.hh"

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
            Field(source::Loc loc, intern::String name, TypeSpec* typespec);
          
          public:
            [[nodiscard]] source::Loc const& loc() const;
            [[nodiscard]] intern::String lhs_name() const;
            [[nodiscard]] TypeSpec* rhs_typespec() const;
        };

      private:
        std::vector<StructTypeSpec::Field*> m_fields;
        
      protected:
        StructTypeSpec(source::Loc loc, std::vector<StructTypeSpec::Field*>&& fields);

      public:
        [[nodiscard]] std::vector<StructTypeSpec::Field*> const& fields() const;
    };

    inline std::vector<StructTypeSpec::Field*> const& StructTypeSpec::fields() const {
        return m_fields;
    }

    inline StructTypeSpec::StructTypeSpec(source::Loc loc, std::vector<StructTypeSpec::Field*>&& fields)
    :   TypeSpec(loc, Kind::StructTypeSpec),
        m_fields(std::move(fields)) {}

    inline StructTypeSpec::Field::Field(source::Loc loc, intern::String name, TypeSpec* typespec)
    :   m_loc(loc),
        m_lhs_name(name), m_rhs_typespec(typespec) {}

    inline TypeSpec* StructTypeSpec::Field::rhs_typespec() const {
        return m_rhs_typespec;
    }

    inline intern::String StructTypeSpec::Field::lhs_name() const {
        return m_lhs_name;
    }

    inline source::Loc const& StructTypeSpec::Field::loc() const {
        return m_loc;
    }

}

#endif  // INCLUDED__PDM__AST__TYPE_SPEC__STRUCT_HH
