#ifndef INCLUDED_PDM_AST_STMT_BUILTIN_TYPE_HH
#define INCLUDED_PDM_AST_STMT_BUILTIN_TYPE_HH

#include <string>

#include "pdm/ast/stmt/stmt.hh"

namespace pdm::types {
    class TypeVar;
}

namespace pdm::ast {

    class Manager;

    class BuiltinStmt: public Stmt {
        friend Manager;

      private:
        std::string     m_desc;
        types::TypeVar* m_x_tv;

      public:
        explicit BuiltinStmt(std::string&& desc);

      public:
        [[nodiscard]] std::string const& desc() const;
        
      public:
        void x_tv(types::TypeVar* tv);
        [[nodiscard]] types::TypeVar* x_tv() const;
    };

    inline BuiltinStmt::BuiltinStmt(std::string&& desc)
    :   Stmt(source::Loc::none, Kind::BuiltinStmt),
        m_desc(std::move(desc)),
        m_x_tv(nullptr) {}

    inline types::TypeVar* BuiltinStmt::x_tv() const {
        return m_x_tv;
    }

    inline std::string const &BuiltinStmt::desc() const {
        return m_desc;
    }

}

#endif  // INCLUDED_PDM_AST_STMT_BUILTIN_TYPE_HH