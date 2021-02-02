#ifndef INCLUDED_PDM_AST_SCRIPT_SCRIPT_HH
#define INCLUDED_PDM_AST_SCRIPT_SCRIPT_HH

#include <vector>

#include <pdm/ast/node.hh>
#include <pdm/source/source.hh>

namespace pdm::ast {
    class Manager;
    class Stmt;
    class ModStmt;
}
namespace pdm::scoper {
    class Frame;
}

namespace pdm::ast {

    class Script: public Node {
        friend Manager;

      private:
        source::Source* m_source;
        std::vector<Stmt*> m_head_stmts;
        std::vector<ModStmt*> m_body_mod_stmts;
        scoper::Frame* m_x_script_frame;

      protected:
        Script(
            source::Source* source,
            source::Loc loc,
            std::vector<Stmt*>&& head_stmts,
            std::vector<ModStmt*>&& body_mod_stmts
        );

      public:
        [[nodiscard]] source::Source* source() const;
        [[nodiscard]] std::vector<Stmt*> const& head_stmts() const;
        [[nodiscard]] std::vector<ModStmt*> const& body_stmts() const;

      public:
        [[nodiscard]] scoper::Frame* x_script_frame() const;
        void x_script_frame(scoper::Frame* frame);
    };

    inline std::vector<ModStmt*> const& Script::body_stmts() const {
        return m_body_mod_stmts;
    }

    inline std::vector<Stmt*> const& Script::head_stmts() const {
        return m_head_stmts;
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
