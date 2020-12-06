#ifndef INCLUDED_PDM_AST_TYPESPEC_TCALL_HH
#define INCLUDED_PDM_AST_TYPESPEC_TCALL_HH

#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/typespec/typespec.hh"

namespace pdm::ast {

    class TCallTypespec: public Typespec {
      private:
        Typespec*          m_lhs_called;
        std::vector<Node*> m_args;
      public:
        TCallTypespec(source::Loc loc, Typespec* lhs_called, std::vector<Node*>&& args)
        : Typespec(loc, Kind::TCallTypespec),
          m_lhs_called(lhs_called),
          m_args(std::move(args)) {}
    };

}

#endif  // INCLUDED_PDM_AST_TYPESPEC_TCALL_HH