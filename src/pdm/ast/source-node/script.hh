#ifndef INCLUDED_PDM_AST_SCRIPT_SCRIPT_HH
#define INCLUDED_PDM_AST_SCRIPT_SCRIPT_HH

#include <vector>

#include "./i-source-node.hh"
#include "pdm/core/intern.hh"
#include "pdm/source/i-source.hh"
#include "pdm/source/loc.hh"

namespace pdm::ast {
    class Manager;
    class HeaderStmt;
    class BaseModExp;
}
namespace pdm::scoper {
    class Frame;
}
namespace pdm::types {
    class TypeVar;
}

namespace pdm::ast {

    // A Script is a source node that is a collection of native modules.
    class Script: public ISourceNode {
        friend Manager;

      public:
        class Field: public Node {
          private:
            intern::String  m_name;
            BaseModExp*     m_rhs_mod_exp;
            types::TypeVar* m_x_defn_var;

          public:
            Field(source::Loc loc, intern::String name, BaseModExp* rhs_mod_exp);

          public:
            [[nodiscard]] intern::String name() const;
            [[nodiscard]] BaseModExp* rhs_mod_exp() const;
          
          public:
            [[nodiscard]] types::TypeVar* x_defn_var() const;
            void x_defn_var(types::TypeVar* defn_tv);
        };

      private:
        std::vector<HeaderStmt*> m_header_stmts;
        std::vector<Script::Field*> m_body_fields;

      protected:
        Script(
            source::ISource* source,
            source::Loc loc,
            std::vector<HeaderStmt*>&& header_stmts,
            std::vector<Script::Field*>&& body_fields
        );

      public:
        [[nodiscard]] std::vector<HeaderStmt*> const& header_stmts() const;
        [[nodiscard]] std::vector<Script::Field*> const& body_fields() const;
    };

    //
    // Inline implementations:
    //

    inline
    Script::Script(
        source::ISource* source,
        source::Loc loc,
        std::vector<HeaderStmt*>&& header_stmts,
        std::vector<Script::Field*>&& body_fields
    )
    :   ISourceNode(source, loc, Kind::Script),
        m_header_stmts(std::move(header_stmts)),
        m_body_fields(std::move(body_fields))
    {}

    inline Script::Field::Field(source::Loc loc, intern::String name, BaseModExp *rhs_mod_exp)
    :   Node(loc, ast::Kind::ScriptField),
        m_name(name),
        m_rhs_mod_exp(rhs_mod_exp),
        m_x_defn_var(nullptr)
    {}

    inline intern::String Script::Field::name() const {
        return m_name;
    }

    inline BaseModExp* Script::Field::rhs_mod_exp() const {
        return m_rhs_mod_exp;
    }

    inline types::TypeVar* Script::Field::x_defn_var() const {
        return m_x_defn_var;
    }

    inline void Script::Field::x_defn_var(types::TypeVar* defn_tv) {
        m_x_defn_var = defn_tv;
    }

    inline std::vector<HeaderStmt*> const& Script::header_stmts() const {
        return m_header_stmts;
    }

    inline std::vector<Script::Field*> const& Script::body_fields() const {
        return m_body_fields;
    }

}   // namespace pdm::ast

#endif  // INCLUDED_PDM_AST_SCRIPT_SCRIPT_HH
