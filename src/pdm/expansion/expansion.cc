#include "expansion.hh"

#include <variant>
#include <vector>

#include "pdm/ast/visitor.hh"
#include "pdm/types/type.hh"

#include "simval.hh"

// debug:
#include <iostream>

namespace pdm::expansion {

    // all template instantiations are already linked to the instantiated template in the scoper.
    // the goal is to evaluate the arguments of each instantiation into constants.

    using ConstTArg = std::variant<types::Type*, Val*>;
    using ConstTArgPack = std::vector<ConstTArg>;

    class ExpandScriptVisitor: public ast::TinyVisitor {
      private:


      public:
        ExpandScriptVisitor();

      protected:
        bool on_visit_mod_address(ast::ModAddress* node, VisitOrder visit_order) override;
    };

    inline ExpandScriptVisitor::ExpandScriptVisitor() = default;

    bool ExpandScriptVisitor::on_visit_mod_address(ast::ModAddress* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            if (!node->template_args().empty()) {
                std::cout << "Template args detected to be expanded." << std::endl;
            }
        }
        return true;
    }

}

namespace pdm::expansion {

    void expand_usages_in_script(ast::Script* script) {
        ExpandScriptVisitor expand_script_visitor{};
        expand_script_visitor.visit(script);
    }

}