#ifndef INCLUDED_PDM_AST_EXP_EXP_HH
#define INCLUDED_PDM_AST_EXP_EXP_HH

#include "pdm/ast/node.hh"

namespace pdm::types {
    class Manager;
    class Var;
}

namespace pdm::ast {

    class Exp: public Node {
      private:
        types::Var* m_x_typeof_var;

      protected:
        Exp(source::Loc loc, Kind kind);

      protected:
        // todo: implement 'is_const_evaluable' for all 'exp's
        // virtual bool is_const_evaluable() const;

      public:
        [[nodiscard]] types::Var* x_type_of_var() const;
        void x_type_of_var(types::Var* typeof_var);
    };

    inline Exp::Exp(source::Loc loc, Kind kind)
    :   Node(loc, kind),
        m_x_typeof_var(nullptr)
    {}

    inline types::Var *Exp::x_type_of_var() const {
        return m_x_typeof_var;
    }

    inline void Exp::x_type_of_var(types::Var* typeof_var) {
        m_x_typeof_var = typeof_var;
    }

}

#endif  // INCLUDED_PDM_AST_EXP_EXP_HH
