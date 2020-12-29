#ifndef INCLUDED_PDM_SCOPER_DEFN_HH
#define INCLUDED_PDM_SCOPER_DEFN_HH

#include "pdm/core/intern.hh"
#include "pdm/ast/stmt/stmt.hh"
#include "pdm/typer/typer.hh"

namespace pdm::scoper {

    class Context;

    enum class DefnKind {
        BuiltinType,
        Module,
        Def,
        Const,
        Let,
        Type,
        Typeclass,
        Using,
        Import
    };

    class Defn {
      private:
        DefnKind       m_kind;
        intern::String m_name;
        ast::Stmt*     m_stmt;
        typer::TV*     m_tv;
        Context*       m_container_context;

      public:
        Defn(DefnKind kind, intern::String name, ast::Stmt* stmt, typer::TV* tv)
        : m_kind(kind), m_name(name), m_stmt(stmt), m_tv(tv),
          m_container_context(nullptr) {}

      public:
        DefnKind kind() const {
            return m_kind;
        }
        intern::String name() const {
            return m_name;
        }
        ast::Stmt* stmt() const {
            return m_stmt;
        }
        typer::TV* tv() const {
            return m_tv;
        }
        Context* container_context() const {
            return m_container_context;
        }

      public:
        Context* container_context(Context* context) {
            return m_container_context = context;
        }
    };

}

#endif  // INCLUDED_PDM_SCOPER_DEFN_HH