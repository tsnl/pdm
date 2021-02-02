#ifndef INCLUDED__PDM__AST__SETSPEC__SETSPEC_HH
#define INCLUDED__PDM__AST__SETSPEC__SETSPEC_HH

#include "pdm/ast/node.hh"

namespace pdm::types {
    class Var;
}

namespace pdm::ast {

    class SetSpec: public Node {
      private:
        types::Var* m_x_spectype_var;
      
      protected:
        inline SetSpec(source::Loc loc, Kind kind);

      public:
        [[nodiscard]] inline types::Var* x_spec_var() const;
        inline void x_spec_var(types::Var* spec_var);
        
      protected:
        virtual bool check_x_spec_var(types::Var* var) const = 0;
    };

    inline SetSpec::SetSpec(source::Loc loc, Kind kind)
    :   Node(loc, kind),
        m_x_spectype_var(nullptr)
    {}
    inline types::Var* SetSpec::x_spec_var() const {
        return m_x_spectype_var;
    }
    inline void SetSpec::x_spec_var(types::Var* spec_var) {
        assert(check_x_spec_var(spec_var));
        m_x_spectype_var = spec_var;
    }

}

#endif  // INCLUDED__PDM__AST__SETSPEC__SETSPEC_HH