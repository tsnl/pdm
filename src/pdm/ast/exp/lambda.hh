#ifndef INCLUDED_PDM_AST_EXP_LAMBDA_HH
#define INCLUDED_PDM_AST_EXP_LAMBDA_HH

#include "pdm/ast/kind.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/exp/exp.hh"
#include "pdm/ast/pattern/vpattern.hh"

namespace pdm::ast {

    class LambdaExp: public Exp {
      private:
        VPattern* m_lhs_vpattern;
        Exp*      m_body;
    
      public:
        LambdaExp(source::Loc loc, VPattern* lhs_vpattern, Exp* body)
        : Exp(loc, Kind::LambdaExp),
          m_lhs_vpattern(lhs_vpattern),
          m_body(body) {}
      
      public:
        VPattern* lhs_vpattern() const {
            return m_lhs_vpattern;
        }
        Exp* body() const {
            return m_body;
        }
    };

}

#endif  // INCLUDED_PDM_AST_EXP_LAMBDA_HH