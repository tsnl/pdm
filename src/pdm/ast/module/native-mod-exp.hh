#ifndef INCLUDED__PDM__AST__MODULE__MOD_EXP_HH
#define INCLUDED__PDM__AST__MODULE__MOD_EXP_HH

#include <vector>

#include "base-mod-exp.hh"
#include "pdm/source/loc.hh"
#include "pdm/core/intern.hh"

namespace pdm::ast {
    class TPattern;
    class Exp;
    class TypeSpec;
    class ClassSpec;
}
namespace pdm::types {
    class Var;
    class TypeVar;
}
namespace pdm::scoper {
    class Frame;
}

namespace pdm::ast {

    class NativeModExp: public BaseModExp {
      private:
        ast::TPattern* m_opt_template_pattern;

      public:
        NativeModExp(source::Loc loc, std::vector<NativeModExp::Field*>&& fields, ast::TPattern* opt_template_pattern);
        
      public:
        [[nodiscard]] ast::TPattern* opt_template_pattern() const;
    };

    //
    // Inline implementations:
    //

    inline NativeModExp::NativeModExp(source::Loc loc, std::vector<NativeModExp::Field*>&& fields, ast::TPattern* opt_template_pattern)
    :   BaseModExp(loc, ast::Kind::NativeModExp, std::move(fields)),
        m_opt_template_pattern(opt_template_pattern)
    {}

    inline ast::TPattern* NativeModExp::opt_template_pattern() const {
        return m_opt_template_pattern;
    }

    inline BaseModExp* NativeModExp::ModuleField::rhs_mod_exp() const {
        return m_rhs_mod_exp;
    }
}

#endif  // INCLUDED__PDM__AST__MODULE__MOD_EXP_HH