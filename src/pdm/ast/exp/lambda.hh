#ifndef INCLUDED_PDM_AST_EXP_LAMBDA_HH
#define INCLUDED_PDM_AST_EXP_LAMBDA_HH

#include "pdm/ast/kind.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/exp/exp.hh"

namespace pdm::ast {
    class Manager;
    class LPattern;
}

namespace pdm::ast {

    class LambdaExp: public Exp {
        friend Manager;

      private:
        LPattern* m_lhs_lpattern;
        Exp*      m_body;
    
      protected:
        LambdaExp(source::Loc loc, LPattern* lhs_lpattern, Exp* body)
        : Exp(loc, Kind::LambdaExp),
          m_lhs_lpattern(lhs_lpattern),
          m_body(body) {}
      
      public:
        LPattern* lhs_lpattern() const {
            return m_lhs_lpattern;
        }
        Exp* body() const {
            return m_body;
        }
    };

}

#endif  // INCLUDED_PDM_AST_EXP_LAMBDA_HH