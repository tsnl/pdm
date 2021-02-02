#ifndef INCLUDED_PDM_AST_TYPESPEC_TCALL_HH
#define INCLUDED_PDM_AST_TYPESPEC_TCALL_HH

#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/setspec/type_spec.hh"
#include "pdm/ast/setspec/class_spec.hh"

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
        inline TCallTypeSpec(source::Loc loc, TypeSpec* lhs_called, std::vector<TArg*>&& args);
        
      public:
        [[nodiscard]] inline TypeSpec* lhs_called() const;
        [[nodiscard]] inline std::vector<TArg*> const& args() const;
    };

    inline TCallTypeSpec::TCallTypeSpec(source::Loc loc, TypeSpec* lhs_called, std::vector<TArg*>&& args)
    : TypeSpec(loc, Kind::TCallTypeSpec),
        m_lhs_called(lhs_called),
        m_args(std::move(args)) 
    {}
    inline TypeSpec* TCallTypeSpec::lhs_called() const {
        return m_lhs_called;
    }
    inline std::vector<TArg*> const& TCallTypeSpec::args() const {
        return m_args;
    }

    class TCallClassSpec: public ClassSpec {
        friend Manager;

      private:
        ClassSpec*         m_lhs_called;
        std::vector<TArg*> m_args;

      public:
        inline TCallClassSpec(source::Loc loc, ClassSpec* lhs_called, std::vector<TArg*>&& args);

      public:
        [[nodiscard]] inline ClassSpec* lhs_called() const;
        [[nodiscard]] inline std::vector<TArg*> const& args() const;
    };

    inline TCallClassSpec::TCallClassSpec(source::Loc loc, ClassSpec* lhs_called, std::vector<TArg*>&& args)
    :   ClassSpec(loc, Kind::TCallClassSpec),
        m_lhs_called(lhs_called)
    {}
    inline ClassSpec* TCallClassSpec::lhs_called() const {
        return m_lhs_called;
    }
    inline std::vector<TArg*> const& TCallClassSpec::args() const {
        return m_args;
    }

}

#endif  // INCLUDED_PDM_AST_TYPESPEC_TCALL_HH