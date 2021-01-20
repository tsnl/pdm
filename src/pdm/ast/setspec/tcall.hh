#ifndef INCLUDED_PDM_AST_TYPESPEC_TCALL_HH
#define INCLUDED_PDM_AST_TYPESPEC_TCALL_HH

#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/setspec/typespec.hh"

namespace pdm::ast {
    class Manager;
    class TArg;
}

namespace pdm::ast {

    class TCallTypeSpec: public TypeSpec {
        friend Manager;

      private:
        TypeSpec*          m_lhs_called;
        std::vector<TArg*> m_args;

      protected:
        TCallTypeSpec(source::Loc loc, TypeSpec* lhs_called, std::vector<TArg*>&& args)
        : TypeSpec(loc, Kind::TCallTypeSpec),
          m_lhs_called(lhs_called),
          m_args(std::move(args)) {}
      
      public:
        TypeSpec* lhs_called() const {
            return m_lhs_called;
        }
        std::vector<TArg*> const& args() const {
            return m_args;
        }
    };

}

#endif  // INCLUDED_PDM_AST_TYPESPEC_TCALL_HH