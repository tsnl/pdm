#ifndef INCLUDED_PDM_AST_TYPESPEC_PAREN_HH
#define INCLUDED_PDM_AST_TYPESPEC_PAREN_HH

#include "typespec.hh"

namespace pdm::ast {
    class Manager;
}

namespace pdm::ast {
    class ParenTypespec: public Typespec {
        friend Manager;

      private:
        Typespec* m_nested_typespec;
    
      protected:
        ParenTypespec(source::Loc loc, Typespec* nested_typespec)
        : Typespec(loc, Kind::ParenTypespec),
          m_nested_typespec(nested_typespec) {}

      public:
        Typespec* nested_typespec() const {
            return m_nested_typespec;
        }
    };
}

#endif  // INCLUDED_PDM_AST_TYPESPEC_PAREN_HH