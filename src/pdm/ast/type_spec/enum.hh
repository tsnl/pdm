#ifndef INCLUDED__PDM__AST__TYPE_SPEC__ENUM_HH
#define INCLUDED__PDM__AST__TYPE_SPEC__ENUM_HH

#include "type_spec.hh"

#include "pdm/source/loc.hh"
#include "pdm/core/intern.hh"
#include "pdm/ast/kind.hh"

namespace pdm::ast {
    class Manager;
}

namespace pdm::ast {

    class EnumTypeSpec: public TypeSpec {
        friend Manager;

      public:
        class Field {
            friend Manager;

          private:
            source::Loc    m_loc;
            intern::String m_name;
            ast::TypeSpec* m_opt_type_spec;

          protected:
            Field(source::Loc loc, intern::String name);
            Field(source::Loc loc, intern::String name, ast::TypeSpec* opt_type_spec);

          public:
            [[nodiscard]] source::Loc loc() const;
            [[nodiscard]] intern::String name() const;
            [[nodiscard]] ast::TypeSpec* opt_type_spec() const;
        };

      private:
        std::vector<Field*> m_fields;

      protected:
        EnumTypeSpec(source::Loc loc, std::vector<Field*>&& fields);

      public:
        [[nodiscard]] std::vector<Field*> const& fields() const;
    };

    //
    // Inline implementations:
    //

    inline EnumTypeSpec::EnumTypeSpec(source::Loc loc, std::vector<Field*>&& fields)
    :   TypeSpec(loc, Kind::EnumTypeSpec),
        m_fields(std::move(fields))
    {}

    inline EnumTypeSpec::Field::Field(source::Loc loc, intern::String name)
    :   m_loc(loc),
        m_name(name),
        m_opt_type_spec(nullptr)
    {}

    inline EnumTypeSpec::Field::Field(
        source::Loc loc,
        intern::String name,
        ast::TypeSpec* opt_type_spec
    )
    :   m_loc(loc),
        m_name(name),
        m_opt_type_spec(opt_type_spec)
    {
        assert(!m_name.is_nil() && "Invalid Enum Field name");
    }

    inline source::Loc EnumTypeSpec::Field::loc() const {
        return m_loc;
    }

    inline intern::String EnumTypeSpec::Field::name() const {
        return m_name;
    }

    inline ast::TypeSpec* EnumTypeSpec::Field::opt_type_spec() const {
        return m_opt_type_spec;
    }

    inline std::vector<EnumTypeSpec::Field*> const& EnumTypeSpec::fields() const {
        return m_fields;
    }
}

#endif  // INCLUDED__PDM__AST__TYPE_SPEC__ENUM_HH