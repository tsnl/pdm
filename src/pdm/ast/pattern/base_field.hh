#ifndef INCLUDED_PDM_AST_PATTERN_BASE_FIELD_HH
#define INCLUDED_PDM_AST_PATTERN_BASE_FIELD_HH

#include "pdm/source/loc.hh"
#include "pdm/core/intern.hh"

#include "pdm/ast/kind.hh"
#include "pdm/ast/node.hh"

namespace pdm::ast {

    class BaseField: public Node {
      private:
        intern::String m_lhs_name;
        
      // constructor:
      protected:
        BaseField(source::Loc loc, Kind kind, intern::String lhs_name);

      // getters:
      public:
        [[nodiscard]] intern::String lhs_name() const;
    };

    inline BaseField::BaseField(source::Loc loc, Kind kind, intern::String lhs_name)
    :   Node(loc, kind),
        m_lhs_name(lhs_name)
    {}

    inline intern::String BaseField::lhs_name() const {
        return m_lhs_name;
    }

}

#endif  // INCLUDED_PDM_AST_PATTERN_BASE_FIELD_HH
