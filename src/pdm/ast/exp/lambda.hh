#ifndef INCLUDED_PDM_AST_EXP_LAMBDA_HH
#define INCLUDED_PDM_AST_EXP_LAMBDA_HH

#include "pdm/ast/kind.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/exp/exp.hh"
#include "pdm/ast/type_spec/fn.hh"

namespace pdm::ast {
    class Manager;
    class VPattern;
    class TypeSpec;
}

namespace pdm::ast {

    class LambdaExp: public Exp {
        friend Manager;

      private:
        FnTypeSpec* m_fn_type_spec;
        Exp* m_body;
    
      protected:
        LambdaExp(source::Loc loc, FnTypeSpec* fn_type_spec, Exp* body)
        :   Exp(loc, Kind::LambdaExp),
            m_fn_type_spec(fn_type_spec),
            m_body(body) {}
      
      public:
        [[nodiscard]] FnTypeSpec* fn_type_spec() const;
        [[nodiscard]] VPattern* lhs_vpattern() const;
        [[nodiscard]] TypeSpec* opt_ret_typespec() const;
        [[nodiscard]] Exp* rhs_body() const;
    };

    inline FnTypeSpec* LambdaExp::fn_type_spec() const {
        return m_fn_type_spec;
    }

    inline VPattern* LambdaExp::lhs_vpattern() const {
        return fn_type_spec()->lhs_vpattern();
    }

    inline TypeSpec* LambdaExp::opt_ret_typespec() const {
        return fn_type_spec()->opt_ret_type_spec();
    }

    inline Exp* LambdaExp::rhs_body() const {
        return m_body;
    }

}

#endif  // INCLUDED_PDM_AST_EXP_LAMBDA_HH