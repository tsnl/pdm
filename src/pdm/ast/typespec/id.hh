#ifndef INCLUDED_PDM_AST_TYPESPEC_ID_HH
#define INCLUDED_PDM_AST_TYPESPEC_ID_HH

#include <vector>

#include "pdm/core/intern.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "typespec.hh"

namespace pdm::scoper {
    class Manager;
    class Defn;
}

namespace pdm::ast {

    class IdTypespec: public Typespec {
        friend Manager;

      private:
        intern::String m_name;
        scoper::Defn const* m_x_defn;

      protected:
        IdTypespec(source::Loc loc, intern::String name)
        : Typespec(loc, Kind::IdTypespec),
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

#endif  // INCLUDED_PDM_AST_TYPESPEC_ID_HH