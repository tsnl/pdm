#ifndef INCLUDED_PDM_AST_EXP_ID_HH
#define INCLUDED_PDM_AST_EXP_ID_HH

#include "pdm/core/intern.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "exp.hh"

namespace pdm::ast {
    class Manager;
}
namespace pdm::scoper {
    class Defn;
}

namespace pdm::ast {

    class IdExp: public Exp {
        friend Manager;
      
      private:
        intern::String      m_name;
        scoper::Defn const* m_x_defn;

      protected:
        IdExp(source::Loc loc, intern::String name);

      public:
        [[nodiscard]] intern::String name() const;

      public:
        [[nodiscard]] scoper::Defn const* x_defn() const;
        void x_defn(scoper::Defn const* defn);
    };

    inline IdExp::IdExp(source::Loc loc, intern::String name)
    :   Exp(loc, Kind::IdExp),
        m_name(name),
        m_x_defn{} {}

    inline intern::String IdExp::name() const {
        return m_name;
    }

    inline scoper::Defn const* IdExp::x_defn() const {
        return m_x_defn;
    }

    inline void IdExp::x_defn(const scoper::Defn* defn) {
        m_x_defn = defn;
    }

}

#endif  // INCLUDED_PDM_AST_EXP_ID_HH