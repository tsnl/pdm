#ifndef INCLUDED_PDM_AST_SCRIPT_SCRIPT_HH
#define INCLUDED_PDM_AST_SCRIPT_SCRIPT_HH

#include <pdm/ast/node.hh>
#include <pdm/source/source.hh>

namespace pdm::ast {
    class Manager;
}

namespace pdm::ast {

    class Script: public Node {
        friend Manager;

      private:
        source::Source* m_source;

      protected:
        Script(source::Source* source)
        : Node(source::Loc::none, Kind::Script),
          m_source(source) {}
    
        Script()
        : Script(nullptr) {}

      public:
        source::Source* source() const {
            return m_source;
        }
        void source(source::Source* source) {
            m_source = source;
        }
    };

}   // namespace pdm::ast

#endif  // INCLUDED_PDM_AST_SCRIPT_SCRIPT_HH