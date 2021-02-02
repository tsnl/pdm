#ifndef INCLUDED__PDM__AST__SETSPEC__ID_CLASS_SPEC_HH
#define INCLUDED__PDM__AST__SETSPEC__ID_CLASS_SPEC_HH

#include "class_spec.hh"

namespace pdm::ast {

    class IdClassSpec: public ClassSpec {
      private:
        intern::String      m_name;
        scoper::Defn const* m_x_defn;

      public:
        inline IdClassSpec(source::Loc loc, intern::String name);
      
      public:
        [[nodiscard]] inline intern::String name() const;

      public:
        [[nodiscard]] inline scoper::Defn const* x_defn() const;
        inline void x_defn(scoper::Defn const* defn);
    };

    inline IdClassSpec::IdClassSpec(source::Loc loc, intern::String name)
    :   ClassSpec(loc, Kind::IdClassSpec),
        m_name(name),
        m_x_defn(nullptr)
    {}

    inline intern::String IdClassSpec::name() const {
        return m_name;
    }
    inline scoper::Defn const* IdClassSpec::x_defn() const {
        return m_x_defn;
    }
    inline void IdClassSpec::x_defn(scoper::Defn const* defn) {
        m_x_defn = defn;
    }

}

#endif  // INCLUDED__PDM__AST__SETSPEC__ID_CLASS_SPEC_HH