#ifndef INCLUDED_PDM_AST_EXP_ID_HH
#define INCLUDED_PDM_AST_EXP_ID_HH

#include "pdm/core/intern.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "exp.hh"

namespace pdm::scoper {
    class Manager;
    class Defn;
}

namespace pdm::ast {

    class IdExp: public Exp {
        friend Manager;
      
      private:
        intern::String      m_name;
        scoper::Defn const* m_x_defn;

      protected:
        IdExp(source::Loc loc, intern::String name)
        : Exp(loc, Kind::IdExp),
          m_name(name) {}

      public:
        intern::String name() const {
            return m_name;
        }

      public:
        scoper::Defn const* x_defn() const {
            return m_x_defn;
        }
        void x_defn(scoper::Defn const* defn) {
            m_x_defn = defn;
        }
    };

}

#endif  // INCLUDED_PDM_AST_EXP_ID_HH