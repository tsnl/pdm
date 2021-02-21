#ifndef INCLUDED__PDM__AST__TYPE_SPEC__TYPE_SPEC_HH
#define INCLUDED__PDM__AST__TYPE_SPEC__TYPE_SPEC_HH

#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/node.hh"

namespace pdm::types {
    class TypeVar;
}
namespace pdm::ast {

    class TypeSpec: public Node {
      private:
        types::TypeVar* m_x_spec_var;

      public:
        inline TypeSpec(source::Loc loc, Kind node_kind);

      public:
        [[nodiscard]] types::TypeVar* x_spec_var() const;
        void x_spec_var(types::TypeVar* spec_var);
    };

    //
    // Inline definitions:
    //

    inline TypeSpec::TypeSpec(source::Loc loc, Kind node_kind)
    :   Node(loc, node_kind),
        m_x_spec_var(nullptr)
    {}

    inline types::TypeVar* TypeSpec::x_spec_var() const {
        return m_x_spec_var;
    }

    inline void TypeSpec::x_spec_var(types::TypeVar* spec_var) {
        m_x_spec_var = spec_var;
    }

}

#endif  // INCLUDED__PDM__AST__TYPE_SPEC__TYPE_SPEC_HH