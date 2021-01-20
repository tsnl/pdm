#ifndef INCLUDED__PDM__AST__SETSPEC__SETSPEC_HH
#define INCLUDED__PDM__AST__SETSPEC__SETSPEC_HH

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
        types::Var* x_spectype_var() const;
        void        x_spectype_var(types::Var* spectype_var);
    };

    inline SetSpec::SetSpec(source::Loc loc, Kind kind)
    :   Node(loc, kind),
        m_x_spectype_var(nullptr)
    {}
    inline types::Var* SetSpec::x_spectype_var() const {
        return m_x_spectype_var;
    }
    inline void SetSpec::x_spectype_var(types::Var* spectype_var) {
        m_x_spectype_var = spectype_var;
    }


}

#endif  // INCLUDED__PDM__AST__SETSPEC__SETSPEC_HH