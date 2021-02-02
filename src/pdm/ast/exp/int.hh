#ifndef INCLUDED_PDM_AST_EXP_INT_HH
#define INCLUDED_PDM_AST_EXP_INT_HH

#include "pdm/core/integer.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/exp/exp.hh"

namespace pdm::ast {

    class Manager;

    class IntExp: public Exp {
        friend Manager;
      
      public:
        enum class Base {
            Dec,
            Hex
        };

      private:
        u64          m_value;
        IntExp::Base m_base;
        bool         m_force_unsigned;

      protected:
        IntExp(source::Loc loc, u64 value, IntExp::Base base, bool force_unsigned);
      
      public:
        [[nodiscard]] u64 value() const;
        [[nodiscard]] IntExp::Base base() const;
        [[nodiscard]] bool force_unsigned() const;
    };

    inline IntExp::IntExp(source::Loc loc, u64 value, IntExp::Base base, bool force_unsigned)
    :   Exp(loc, Kind::IntExp),
        m_value(value),
        m_base(base),
        m_force_unsigned(force_unsigned) {}

    inline u64 IntExp::value() const {
        return m_value;
    }

    inline IntExp::Base IntExp::base() const {
        return m_base;
    }

    inline bool IntExp::force_unsigned() const {
        return m_force_unsigned;
    }

}

#endif  // INCLUDED_PDM_AST_EXP_INT_HH