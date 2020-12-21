#ifndef INCLUDED_PDM_AST_STMT_FN_HH
#define INCLUDED_PDM_AST_STMT_FN_HH

#include "pdm/core/intern.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/stmt/stmt.hh"
#include "pdm/ast/exp/exp.hh"
#include "pdm/ast/typespec/typespec.hh"
#include "pdm/ast/pattern/tpattern.hh"
#include "pdm/ast/pattern/vpattern.hh"

namespace pdm::ast {
    
    class Manager;

    class FnStmt: public Stmt {
        friend Manager;

      private:
        intern::String m_name;
        std::vector<TPattern*> m_tpatterns;
        VPattern* m_vpattern;
        Typespec* m_return_ts;
        Exp* m_body;

      protected:
        FnStmt(source::Loc loc, intern::String name, std::vector<TPattern*> tpatterns, VPattern* vpattern, Typespec* opt_return_ts, Exp* body)
        : Stmt(loc, Kind::FnStmt),
          m_name(name),
          m_tpatterns(std::move(tpatterns)),
          m_vpattern(vpattern),
          m_return_ts(opt_return_ts),
          m_body(body) {}

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
        Exp* body() const {
            return m_body;
        }
    };

}

#endif  // INCLUDED_PDM_AST_STMT_FN_HH
