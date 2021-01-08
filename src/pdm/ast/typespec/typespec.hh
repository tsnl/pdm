#ifndef INCLUDED_PDM_AST_TYPESPEC_TYPESPEC_HH
#define INCLUDED_PDM_AST_TYPESPEC_TYPESPEC_HH

#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/node.hh"

namespace pdm::types {
    class Var;
}

namespace pdm::ast {

    class Typespec: public Node {
      private:
        types::Var* m_x_spectype_var;
      
      protected:
        Typespec(source::Loc loc, Kind kind);

      public:
        types::Var* x_spectype_var() const;
        void        x_spectype_var(types::Var* spectype_var);
    };

}

#endif  // INCLUDED_PDM_AST_TYPESPEC_TYPESPEC_HH