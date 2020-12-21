#ifndef INCLUDED_PDM_AST_TYPESPEC_MUT_HH
#define INCLUDED_PDM_AST_TYPESPEC_MUT_HH

#include <vector>

#include "pdm/core/intern.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/typespec/typespec.hh"

namespace pdm::ast {
  
    class Manager;

    class MutTypespec: public Typespec {
        friend Manager;

      private:
        Typespec* m_mutatee;

      protected:
        MutTypespec(source::Loc loc, Typespec* mutatee)
        : Typespec(loc, Kind::MutTypespec),
          m_mutatee(mutatee) {}
      
      public:
        Typespec* mutatee() const {
            return m_mutatee;
        }
    };

}

#endif  // INCLUDED_PDM_AST_TYPESPEC_MUT_HH