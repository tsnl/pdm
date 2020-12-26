#ifndef INCLUDED_PDM_AST_STMT_EXTERN_HH
#define INCLUDED_PDM_AST_STMT_EXTERN_HH

#include "stmt.hh"
#include "pdm/core/intern.hh"

namespace pdm::ast {
    class Manager;
    class Exp;
}

namespace pdm::ast {

    class ExternStmt: public Stmt {
        friend Manager;

      private:
        intern::String m_ext_mod_name;
        Exp*           m_link_arg;
    
      protected:
        ExternStmt(source::Loc loc, intern::String ext_mod_name, Exp* link_arg)
        : Stmt(loc, Kind::ExternStmt),
          m_ext_mod_name(ext_mod_name),
          m_link_arg(link_arg) {}
    
      public:
        intern::String ext_mod_name() const {
            return m_ext_mod_name;
        }
        Exp* link_arg() const {
            return m_link_arg;
        }
    };

}

#endif // INCLUDED_PDM_AST_STMT_EXTERN_HH