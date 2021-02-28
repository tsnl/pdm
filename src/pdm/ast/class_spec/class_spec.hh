#ifndef INCLUDED__PDM__AST__CLASS_SPEC__CLASS_SPEC_HH
#define INCLUDED__PDM__AST__CLASS_SPEC__CLASS_SPEC_HH

#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/node.hh"

namespace pdm::types {
    class ClassVar;
}

namespace pdm::ast {

    class ClassSpec: public ast::Node {
      private:
        types::ClassVar* m_x_spec_var;

      public:
        inline ClassSpec(source::Loc loc, Kind node_kind);

      public:
        [[nodiscard]] types::ClassVar* x_spec_var() const;
        void x_spec_var(types::ClassVar* spec_var);
    };

    //
    // Inline definitions:
    //

    inline ClassSpec::ClassSpec(source::Loc loc, Kind node_kind) 
    :   Node(loc, node_kind),
        m_x_spec_var(nullptr)
    {}

    inline types::ClassVar* ClassSpec::x_spec_var() const {
        return m_x_spec_var;
    }

    inline void ClassSpec::x_spec_var(types::ClassVar* spec_var) {
        m_x_spec_var = spec_var;
    }

}

#endif  // INCLUDED__PDM__AST__CLASS_SPEC__CLASS_SPEC_HH