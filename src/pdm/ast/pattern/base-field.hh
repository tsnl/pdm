#ifndef INCLUDED_PDM_AST_PATTERN_BASE_FIELD_HH
#define INCLUDED_PDM_AST_PATTERN_BASE_FIELD_HH

#include "pdm/source/loc.hh"
#include "pdm/core/intern.hh"

#include "pdm/ast/kind.hh"
#include "pdm/ast/node.hh"

namespace pdm::scoper {
    class Defn;
}

namespace pdm::ast {

    class BaseField: public Node {
      private:
        intern::String m_lhs_name;
        scoper::Defn* m_x_defn;
        
      // constructor:
      protected:
        BaseField(source::Loc loc, Kind kind, intern::String lhs_name);

      // getters:
      public:
        [[nodiscard]] intern::String lhs_name() const;

      public:
        void x_defn(scoper::Defn* x_defn);
        [[nodiscard]] inline scoper::Defn* x_defn() const;
    };

    inline BaseField::BaseField(source::Loc loc, Kind kind, intern::String lhs_name)
    :   Node(loc, kind),
        m_lhs_name(lhs_name),
        m_x_defn(nullptr)
    {}

    inline intern::String BaseField::lhs_name() const {
        return m_lhs_name;
    }

    inline void BaseField::x_defn(scoper::Defn* x_defn) {
        m_x_defn = x_defn;
    }

    inline scoper::Defn* BaseField::x_defn() const {
        return m_x_defn;
    }

}

#endif  // INCLUDED_PDM_AST_PATTERN_BASE_FIELD_HH
