#ifndef INCLUDED_PDM_AST_SCRIPT_SCRIPT_HH
#define INCLUDED_PDM_AST_SCRIPT_SCRIPT_HH

#include <vector>

#include "pdm/core/intern.hh"
#include "pdm/ast/node.hh"
#include "pdm/source/source.hh"
#include "pdm/source/loc.hh"

namespace pdm::ast {
    class Manager;
    class HeaderStmt;
    class ModExp;
}
namespace pdm::scoper {
    class Frame;
}

namespace pdm::ast {

    class Script: public Node {
        friend Manager;

      public:
        class Field: public Node {
          private:
            intern::String m_name;
            ModExp*        m_rhs_mod_exp;

          public:
            Field(source::Loc loc, intern::String name, ModExp* rhs_mod_exp);

          public:
            [[nodiscard]] intern::String name() const;
            [[nodiscard]] ModExp* rhs_mod_exp() const;
        };

      private:
        source::Source* m_source;
        std::vector<HeaderStmt*> m_header_stmts;
        std::vector<Script::Field*> m_body_fields;
        scoper::Frame* m_x_script_frame;

      protected:
        Script(
            source::Source* source,
            source::Loc loc,
            std::vector<HeaderStmt*>&& head_stmts,
            std::vector<Script::Field*>&& body_fields
        );

      public:
        [[nodiscard]] source::Source* source() const;
        [[nodiscard]] std::vector<HeaderStmt*> const& header_stmts() const;
        [[nodiscard]] std::vector<Script::Field*> const& body_fields() const;

      public:
        [[nodiscard]] scoper::Frame* x_script_frame() const;
        void x_script_frame(scoper::Frame* frame);
    };

    //
    // Inline implementations:
    //

    inline Script::Field::Field(source::Loc loc, intern::String name, ModExp *rhs_mod_exp)
    :   Node(loc, ast::Kind::ScriptField),
        m_name(name),
        m_rhs_mod_exp(rhs_mod_exp)
    {}

    inline intern::String Script::Field::name() const {
        return m_name;
    }

    inline ModExp* Script::Field::rhs_mod_exp() const {
        return m_rhs_mod_exp;
    }

    inline std::vector<HeaderStmt*> const& Script::header_stmts() const {
        return m_header_stmts;
    }

    inline std::vector<Script::Field*> const& Script::body_fields() const {
        return m_body_fields;
    }

    inline source::Source* Script::source() const {
        return m_source;
    }

    inline scoper::Frame* Script::x_script_frame() const {
        return m_x_script_frame;
    }

    inline void Script::x_script_frame(scoper::Frame* frame) {
        m_x_script_frame = frame;
    }


}   // namespace pdm::ast

#endif  // INCLUDED_PDM_AST_SCRIPT_SCRIPT_HH
