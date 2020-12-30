#ifndef INCLUDED_PDM_AST_STMT_BUILTIN_TYPE_HH
#define INCLUDED_PDM_AST_STMT_BUILTIN_TYPE_HH

#include <string>

#include "pdm/ast/stmt/stmt.hh"

namespace pdm::typer {
    class TypeVar;
}

namespace pdm::ast {

    class Manager;

    class BuiltinTypeStmt: public Stmt {
        friend Manager;

      private:
        std::string     m_desc;
        typer::TypeVar* m_tv;

      public:
        BuiltinTypeStmt(std::string&& desc, typer::TypeVar* tv);

      public:
        std::string const& desc() const {
            return m_desc;
        }
        typer::TypeVar* tv() const {
            return m_tv;
        }
    };

}

#endif  // INCLUDED_PDM_AST_STMT_BUILTIN_TYPE_HH