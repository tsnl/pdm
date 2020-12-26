#ifndef INCLUDED_PDM_AST_TYPESPEC_PTR_HH
#define INCLUDED_PDM_AST_TYPESPEC_PTR_HH

#include <vector>

#include "pdm/core/intern.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/typespec/typespec.hh"

namespace pdm::ast {

    class Manager;

    class PtrTypespec: public Typespec {
        friend Manager;

      private:
        Typespec* m_pointee;

      protected:
        PtrTypespec(source::Loc loc, Typespec* pointee)
        : Typespec(loc, Kind::PtrTypespec),
          m_pointee(pointee) {}
      
      public:
        Typespec* pointee_typespec() const {
            return m_pointee;
        }
    };

}

#endif  // INCLUDED_PDM_AST_TYPESPEC_PTR_HH