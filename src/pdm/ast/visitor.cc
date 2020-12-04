#include "visitor.hh"

#include "node.hh"
#include "kind.hh"

namespace pdm::ast {

    bool BaseVisitor_Factored::on_visit(Node* node, bool preNotPost) {
        switch (node->kind()) {
            // script:
            case ast::Kind::Script: 
            {
                return on_visit__script(node, preNotPost);
            }
            // statements:
            // todo: add delegates for other kinds.
            default: 
            {
                // todo: generate a debug compiler error?
                return false;
            }
        }
    }

}   // namespace pdm::ast
