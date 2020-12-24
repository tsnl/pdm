#ifndef INCLUDED_PDM_AST_TYPESPEC_TCALL_HH
#define INCLUDED_PDM_AST_TYPESPEC_TCALL_HH

#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/typespec/typespec.hh"

namespace pdm::ast {
    class Manager;
    class TArg;
}

namespace pdm::ast {

    class TCallTypespec: public Typespec {
        friend Manager;

      private:
        Typespec*          m_lhs_called;
        std::vector<TArg*> m_args;

      protected:
        TCallTypespec(source::Loc loc, Typespec* lhs_called, std::vector<TArg*>&& args)
        : Typespec(loc, Kind::TCallTypespec),
          m_lhs_called(lhs_called),
          m_args(std::move(args)) {}
      
      public:
        Typespec* lhs_called() const {
            return m_lhs_called;
        }
        std::vector<TArg*> const& args() const {
            return m_args;
        }
    };

}

#endif  // INCLUDED_PDM_AST_TYPESPEC_TCALL_HH