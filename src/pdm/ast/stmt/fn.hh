#ifndef INCLUDED_PDM_AST_STMT_FN_HH
#define INCLUDED_PDM_AST_STMT_FN_HH

#include <variant>

#include "stmt.hh"
#include "pdm/ast/kind.hh"
#include "pdm/core/intern.hh"
#include "pdm/source/loc.hh"

namespace pdm::ast {   
    class Manager;
    class Exp;
    class Typespec;
    class VPattern;
    class TPattern;
}


namespace pdm::ast {
    class FnStmt: public Stmt {
        friend Manager;

      private:
        struct ExpRhs {
            Exp* exp;
        };
        struct ExternRhs {
            intern::String ext_mod_name;
            utf8::String   ext_fn_name;
        };

      private:
        intern::String                  m_name;
        std::vector<TPattern*>          m_tpatterns;
        VPattern*                       m_vpattern;
        Typespec*                       m_return_ts;
        std::variant<ExpRhs, ExternRhs> m_rhs;

      protected:
        FnStmt(source::Loc loc, intern::String name, std::vector<TPattern*> tpatterns, VPattern* vpattern, Typespec* opt_return_ts, Exp* rhs)
        : Stmt(loc, Kind::FnStmt),
          m_name(name),
          m_tpatterns(std::move(tpatterns)),
          m_vpattern(vpattern),
          m_return_ts(opt_return_ts),
          m_rhs(ExpRhs{rhs}) {}

        FnStmt(source::Loc loc, intern::String name, std::vector<TPattern*> tpatterns, VPattern* vpattern, Typespec* opt_return_ts, intern::String ext_mod_name, utf8::String ext_fn_name)
        : Stmt(loc, Kind::FnStmt),
          m_name(name),
          m_tpatterns(std::move(tpatterns)),
          m_vpattern(vpattern),
          m_return_ts(opt_return_ts),
          m_rhs(ExternRhs{ext_mod_name, ext_fn_name}) {}

      public:
        intern::String name() const {
            return m_name;
        }
        std::vector<TPattern*> const& tpatterns() const {
            return m_tpatterns;
        }
        VPattern* vpattern() const {
            return m_vpattern;
        }
        Typespec* opt_return_ts() const {
            return m_return_ts;
        }
      public:
        enum class RhsKind {
            Exp,
            Extern
        };
        RhsKind rhs_kind() const {
            if (std::holds_alternative<ExpRhs>(m_rhs)) {
                return RhsKind::Exp;
            } else {
                return RhsKind::Extern;
            }
        }
        Exp* opt_rhs_exp() const {
            if (std::holds_alternative<ExpRhs>(m_rhs)) {
                return std::get<ExpRhs>(m_rhs).exp;
            } else {
                return nullptr;
            }
        }
        intern::String opt_rhs_ext_mod_name() const {
            if (std::holds_alternative<ExpRhs>(m_rhs)) {
                return std::get<ExternRhs>(m_rhs).ext_mod_name;
            } else {
                return {};
            }
        }
        utf8::String opt_rhs_ext_fn_name() const {
            if (std::holds_alternative<ExpRhs>(m_rhs)) {
                return std::get<ExternRhs>(m_rhs).ext_fn_name;
            } else {
                return {};
            }
        }
    };

}

#endif  // INCLUDED_PDM_AST_STMT_FN_HH
