#ifndef INCLUDED_PDM_AST_EXP_CHAIN_HH
#define INCLUDED_PDM_AST_EXP_CHAIN_HH

#include <vector>

#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/stmt/stmt.hh"
#include "pdm/ast/exp/exp.hh"

namespace pdm::ast {

    class ChainExp: public Exp {
        std::vector<Stmt*> m_prefix;
        Exp* m_suffix;
      
      public:
        ChainExp(source::Loc loc, std::vector<Stmt*>&& prefix, Exp* suffix = nullptr)
        : Exp(loc, Kind::ChainExp),
          m_prefix(std::move(prefix)),
          m_suffix(suffix) {}
    };

}

#endif  // INCLUDED_PDM_AST_EXP_CHAIN_HH