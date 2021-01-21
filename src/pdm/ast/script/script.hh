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
        source::Source*       m_source;
        std::vector<Stmt*>    m_head_stmts;
        std::vector<ModStmt*> m_body_mod_stmts;
        
        scoper::Frame* m_x_script_frame;

      protected:
        Script(source::Source* source, source::Loc loc, std::vector<Stmt*>&& head_stmts, std::vector<ModStmt*>&& body_mod_stmts)
        : Node(loc, Kind::Script),
          m_source(source),
          m_head_stmts(std::move(head_stmts)),
          m_body_mod_stmts(std::move(body_mod_stmts)),
          m_x_script_frame(nullptr) {}

      public:
        source::Source* source() const {
            return m_source;
        }
        std::vector<Stmt*> const& head_stmts() const {
            return m_head_stmts;
        }
        std::vector<ModStmt*> const& body_stmts() const {
            return m_body_mod_stmts;
        }

      public:
        scoper::Frame* x_script_frame() const {
            return m_x_script_frame;
        }
        void x_script_frame(scoper::Frame* frame) {
            m_x_script_frame = frame;
        }
    };

}   // namespace pdm::ast

#endif  // INCLUDED_PDM_AST_SCRIPT_SCRIPT_HH
