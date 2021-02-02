#ifndef INCLUDED_PDM_AST_TYPESPEC_PAREN_HH
#define INCLUDED_PDM_AST_TYPESPEC_PAREN_HH

#include "type_spec.hh"

namespace pdm::ast {
    class Manager;
}

namespace pdm::ast {
    class ParenTypeSpec: public TypeSpec {
        friend Manager;

      private:
        TypeSpec* m_nested_typespec;
    
      protected:
        ParenTypeSpec(source::Loc loc, TypeSpec* nested_typespec);

      public:
        [[nodiscard]] TypeSpec* nested_typespec() const;
    };

    inline ParenTypeSpec::ParenTypeSpec(source::Loc loc, TypeSpec* nested_typespec)
    :   TypeSpec(loc, Kind::ParenTypeSpec),
        m_nested_typespec(nested_typespec) {}

    inline TypeSpec* ParenTypeSpec::nested_typespec() const {
        return m_nested_typespec;
    }
}

#endif  // INCLUDED_PDM_AST_TYPESPEC_PAREN_HH