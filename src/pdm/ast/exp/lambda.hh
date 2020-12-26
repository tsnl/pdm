#ifndef INCLUDED_PDM_AST_EXP_LAMBDA_HH
#define INCLUDED_PDM_AST_EXP_LAMBDA_HH

#include "pdm/ast/kind.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/exp/exp.hh"

namespace pdm::ast {
    class Manager;
    class VPattern;
}

namespace pdm::ast {

    class LambdaExp: public Exp {
        friend Manager;

      private:
        VPattern* m_lhs_vpattern;
        Exp*      m_body;
    
      protected:
        LambdaExp(source::Loc loc, VPattern* lhs_vpattern, Exp* body)
        : Exp(loc, Kind::LambdaExp),
          m_lhs_vpattern(lhs_vpattern),
          m_body(body) {}
      
      public:
        VPattern* lhs_vpattern() const {
            return m_lhs_vpattern;
        }
        Exp* rhs_body() const {
            return m_body;
        }
    };

}

#endif  // INCLUDED_PDM_AST_EXP_LAMBDA_HH