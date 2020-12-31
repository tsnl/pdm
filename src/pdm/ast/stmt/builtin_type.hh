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
        typer::TypeVar* m_x_tv;

      public:
        BuiltinTypeStmt(std::string&& desc);

      public:
        std::string const& desc() const {
            return m_desc;
        }
        
      public:
        void x_tv(typer::TypeVar* tv);
        typer::TypeVar* x_tv() const;
    };

}

#endif  // INCLUDED_PDM_AST_STMT_BUILTIN_TYPE_HH