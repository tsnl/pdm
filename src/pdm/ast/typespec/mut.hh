#ifndef INCLUDED_PDM_AST_TYPESPEC_MUT_HH
#define INCLUDED_PDM_AST_TYPESPEC_MUT_HH

#include <vector>

#include "pdm/core/intern.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/typespec/typespec.hh"

namespace pdm::ast {

    class MutTypespec: public Typespec {
      private:
        Typespec* m_mutatee;
      public:
        MutTypespec(source::Loc loc, Typespec* mutatee)
        : Typespec(loc, Kind::MutTypespec),
          m_mutatee(mutatee) {}
    };

}

#endif  // INCLUDED_PDM_AST_TYPESPEC_MUT_HH