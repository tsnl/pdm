#ifndef INCLUDED_PDM_DEPENDENCY_DISPATCHER_DEPENDENCY_DISPATCHER_HH
#define INCLUDED_PDM_DEPENDENCY_DISPATCHER_DEPENDENCY_DISPATCHER_HH

#include "pdm/ast/visitor.hh"

namespace pdm::compiler {
    class Compiler;
}
namespace pdm::ast {
    class Script;
}

namespace pdm::dependency_dispatcher {

    class DDVisitor: public ast::Visitor {
      private:
        compiler::Compiler* m_compiler_ref;
        ast::Script*        m_this_script;

      public:
        DDVisitor(compiler::Compiler* compiler_ref, ast::Script* this_script)
        : m_compiler_ref(compiler_ref),
          m_this_script(this_script) {}
      
      protected:
        virtual bool on_visit__import_stmt(ast::ImportStmt* node, VisitOrder visit_order) override;
    };

    class DependencyDispatcher {
        compiler::Compiler* m_compiler_ref;

      public:
        DependencyDispatcher(compiler::Compiler* compiler_ref)
        : m_compiler_ref(compiler_ref) {}

      public:
        void dispatch_imports_for(ast::Script* script);
    };

}

#endif  // INCLUDED_PDM_DEPENDENCY_DISPATCHER_DEPENDENCY_DISPATCHER_HH