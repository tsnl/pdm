#ifndef INCLUDED__PDM__AST__TYPE_SPEC__ID_HH
#define INCLUDED__PDM__AST__TYPE_SPEC__ID_HH

#include <vector>

#include "type_spec.hh"

#include "pdm/core/intern.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"

namespace pdm::scoper {
    class Manager;
    class Defn;
}

namespace pdm::ast {

    class IdTypeSpec: public TypeSpec {
        friend Manager;

      private:
        intern::String m_name;
        scoper::Defn const* m_x_defn;

      public:
        IdTypeSpec(source::Loc loc, intern::String name);
      
      public:
        [[nodiscard]] intern::String name() const;

      public:
        [[nodiscard]] scoper::Defn const* x_defn() const;
        void x_defn(scoper::Defn const* defn);
    };

    inline scoper::Defn const *IdTypeSpec::x_defn() const {
        return m_x_defn;
    }

    inline void IdTypeSpec::x_defn(const scoper::Defn *defn) {
        m_x_defn = defn;
    }

    inline intern::String IdTypeSpec::name() const {
        return m_name;
    }

    inline IdTypeSpec::IdTypeSpec(source::Loc loc, intern::String name)
    :   TypeSpec(loc, Kind::IdTypeSpec),
        m_name(name),
        m_x_defn(nullptr) {}

}

#endif  // INCLUDED__PDM__AST__TYPE_SPEC__ID_HH
