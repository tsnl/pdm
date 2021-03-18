#ifndef INCLUDED_PDM_DEPENDENCY_DISPATCHER_DEPENDENCY_DISPATCHER_HH
#define INCLUDED_PDM_DEPENDENCY_DISPATCHER_DEPENDENCY_DISPATCHER_HH

#include <string>

#include "pdm/ast/visitor.hh"

namespace pdm {
    class Compiler;
}
namespace pdm::ast {
    class Script;
}

namespace pdm::dependency_dispatcher {

    class DDVisitor: public ast::TinyVisitor {
      private:
        Compiler* m_compiler_ref;
        ast::Script*        m_this_script;

      public:
        DDVisitor(Compiler* compiler_ref, ast::Script* this_script)
        : m_compiler_ref(compiler_ref),
          m_this_script(this_script) {}
      
      public:
        virtual bool on_visit(ast::Node* node, VisitOrder visit_order) override;

      protected:
        virtual bool on_visit_import_stmt(ast::ImportStmt* node, VisitOrder visit_order) override;
    };

}

#endif  // INCLUDED_PDM_DEPENDENCY_DISPATCHER_DEPENDENCY_DISPATCHER_HH
