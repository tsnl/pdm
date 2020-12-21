#ifndef INCLUDED_PDM_AST_STMT_BUILTIN_TYPE_HH
#define INCLUDED_PDM_AST_STMT_BUILTIN_TYPE_HH

#include <string>

#include "pdm/ast/stmt/stmt.hh"

namespace pdm::typer {
    class TV;
}

namespace pdm::ast {

    class Manager;

    class BuiltinTypeStmt: public Stmt {
        friend Manager;

      private:
        std::string m_desc;
        typer::TV*  m_tv;

      public:
        BuiltinTypeStmt(std::string&& desc, typer::TV* tv);
    };

}

#endif  // INCLUDED_PDM_AST_STMT_BUILTIN_TYPE_HH