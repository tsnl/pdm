#ifndef INCLUDED_PDM_AST_EXP_CHAIN_HH
#define INCLUDED_PDM_AST_EXP_CHAIN_HH

#include <vector>

#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/stmt/stmt.hh"
#include "pdm/ast/exp/exp.hh"

namespace pdm::ast {

    class Manager;

    class ChainExp: public Exp {
        friend Manager;

      private:
        std::vector<Stmt*> m_prefix;
        Exp*               m_suffix;
      
      protected:
        ChainExp(source::Loc loc, std::vector<Stmt*>&& prefix, Exp* suffix = nullptr);
      
      public:
        [[nodiscard]] std::vector<Stmt*> const& prefix() const;
        [[nodiscard]] Exp* suffix() const;
    };

    inline ChainExp::ChainExp(source::Loc loc, std::vector<Stmt*>&& prefix, Exp* suffix)
    :   Exp(loc, Kind::ChainExp),
        m_prefix(std::move(prefix)),
        m_suffix(suffix) {}

    inline std::vector<Stmt*> const& ChainExp::prefix() const {
        return m_prefix;
    }

    inline Exp* ChainExp::suffix() const {
        return m_suffix;
    }

}

#endif  // INCLUDED_PDM_AST_EXP_CHAIN_HH