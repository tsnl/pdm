#ifndef INCLUDED_PDM_AST_STMT_DEF_HH
#define INCLUDED_PDM_AST_STMT_DEF_HH

#include "pdm/core/intern.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/stmt/stmt.hh"
#include "pdm/ast/exp/exp.hh"
#include "pdm/ast/typespec/typespec.hh"
#include "pdm/ast/pattern/tpattern.hh"
#include "pdm/ast/pattern/vpattern.hh"


namespace pdm::ast {

    class DefStmt: public Stmt {
      private:
        intern::String m_name;
        std::vector<TPattern*> m_tpatterns;
        VPattern* m_vpattern;
        Typespec* m_return_ts;
        Exp* m_body;
      public:
        DefStmt(source::Loc loc, intern::String name, std::vector<TPattern*> tpatterns, VPattern* vpattern, Typespec* return_ts, Exp* body)
        : Stmt(loc, Kind::DefStmt),
          m_name(name),
          m_tpatterns(std::move(tpatterns)),
          m_vpattern(vpattern),
          m_return_ts(return_ts),
          m_body(body) {}
    };

}

#endif  // INCLUDED_PDM_AST_STMT_DEF_HH