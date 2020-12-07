#ifndef INCLUDED_PDM_AST_TYPESPEC_PTR_HH
#define INCLUDED_PDM_AST_TYPESPEC_PTR_HH

#include <vector>

#include "pdm/core/intern.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/typespec/typespec.hh"

namespace pdm::ast {

    class PtrTypespec: public Typespec {
      private:
        Typespec* m_pointee;
      public:
        PtrTypespec(source::Loc loc, Typespec* pointee)
        : Typespec(loc, Kind::PtrTypespec),
          m_pointee(pointee) {}
      
      public:
        Typespec* pointee() const {
            return m_pointee;
        }
    };

}

#endif  // INCLUDED_PDM_AST_TYPESPEC_PTR_HH