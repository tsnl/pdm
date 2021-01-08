#ifndef INCLUDED_PDM_AST_EXP_EXP_HH
#define INCLUDED_PDM_AST_EXP_EXP_HH

#include "pdm/ast/node.hh"

namespace pdm::types {
    class Manager;
    class TypeVar;
}

namespace pdm::ast {

    class Exp: public Node {
      private:
        types::TypeVar* m_x_evaltype_tv;

      protected:
        Exp(source::Loc loc, Kind kind)
        : Node(loc, kind) {}

      protected:
        // todo: implement 'is_const_evaluable' for all 'exp's
        // virtual bool is_const_evaluable() const;

      public:
        types::TypeVar* x_evaltype_tv() const {
            return m_x_evaltype_tv;
        }
        void x_evaltype_tv(types::TypeVar* evaltype_tv) {
            m_x_evaltype_tv = evaltype_tv;
        }
    };

}

#endif  // INCLUDED_PDM_AST_EXP_EXP_HH
