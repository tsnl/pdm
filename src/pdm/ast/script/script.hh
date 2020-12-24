#ifndef INCLUDED_PDM_AST_SCRIPT_SCRIPT_HH
#define INCLUDED_PDM_AST_SCRIPT_SCRIPT_HH

#include <vector>

#include <pdm/ast/node.hh>
#include <pdm/source/source.hh>

namespace pdm::ast {
    class Manager;
    class Stmt;
}

namespace pdm::ast {

    class Script: public Node {
        friend Manager;

      private:
        source::Source*    m_source;
        std::vector<Stmt*> m_stmts;

      protected:
        Script(source::Source* source, source::Loc loc, std::vector<Stmt*> stmts)
        : Node(loc, Kind::Script),
          m_source(source),
          m_stmts(stmts) {}

      public:
        source::Source* source() const {
            return m_source;
        }
        std::vector<Stmt*> const& stmts() const {
            return m_stmts;
        }
    };

}   // namespace pdm::ast

#endif  // INCLUDED_PDM_AST_SCRIPT_SCRIPT_HH
