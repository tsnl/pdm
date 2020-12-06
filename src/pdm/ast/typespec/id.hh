#ifndef INCLUDED_PDM_AST_TYPESPEC_ID_HH
#define INCLUDED_PDM_AST_TYPESPEC_ID_HH

#include <vector>

#include "pdm/core/intern.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/typespec/typespec.hh"

namespace pdm::ast {

    class IdTypespec: public Typespec {
      private:
        intern::String m_name;
      public:
        IdTypespec(source::Loc loc, intern::String name)
        : Typespec(loc, Kind::IdTypespec),
          m_name(name) {}
    };

}

#endif  // INCLUDED_PDM_AST_TYPESPEC_ID_HH