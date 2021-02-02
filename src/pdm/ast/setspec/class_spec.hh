#ifndef INCLUDED__PDM__AST__SETSPEC__CLASSSPEC_HH
#define INCLUDED__PDM__AST__SETSPEC__CLASSSPEC_HH

#include "setspec.hh"

namespace pdm::ast {

    class ClassSpec: public SetSpec {
      public:
        inline ClassSpec(source::Loc loc, Kind node_kind);

      protected:
        bool check_x_spec_var(types::Var* var) const override;
    };

    inline ClassSpec::ClassSpec(source::Loc loc, Kind node_kind) 
    :   SetSpec(loc, node_kind)
    {}

}

#endif  // INCLUDED__PDM__AST__SETSPEC__CLASSSPEC_HH