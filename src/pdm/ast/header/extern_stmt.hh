#ifndef INCLUDED__PDM__AST__HEADER__EXTERN_STMT_HH
#define INCLUDED__PDM__AST__HEADER__EXTERN_STMT_HH

#include "header_stmt.hh"
#include "pdm/source/loc.hh"
#include "pdm/core/intern.hh"

namespace pdm::ast {
    class Manager;
    class Exp;
}

namespace pdm::ast {

    class ExternStmt: public HeaderStmt {
        friend Manager;

      private:
        intern::String m_ext_mod_name;
        Exp*           m_link_arg;
    
      protected:
        ExternStmt(source::Loc loc, intern::String ext_mod_name, Exp* link_arg);
    
      public:
        [[nodiscard]] intern::String ext_mod_name() const;
        [[nodiscard]] Exp* link_arg() const;
    };

    inline ExternStmt::ExternStmt(source::Loc loc, intern::String ext_mod_name, Exp* link_arg)
    :   HeaderStmt(loc, Kind::ExternStmt),
        m_ext_mod_name(ext_mod_name),
        m_link_arg(link_arg) {}

    inline intern::String ExternStmt::ext_mod_name() const {
        return m_ext_mod_name;
    }

    inline Exp* ExternStmt::link_arg() const {
        return m_link_arg;
    }

}

#endif // INCLUDED__PDM__AST__HEADER__EXTERN_STMT_HH