#ifndef INCLUDED_PDM_AST_PATTERN_VPATTERN_HH
#define INCLUDED_PDM_AST_PATTERN_VPATTERN_HH

#include <vector>

#include "pdm/ast/node.hh"
#include "pdm/ast/typespec/typespec.hh"
#include "pdm/core/intern.hh"
#include "pdm/ast/arg/varg.hh"

namespace pdm::ast {
    class Manager;
}

namespace pdm::ast {

    class VPattern: public Node {
        friend Manager;

      public:
        class Field {
            friend Manager;

          private:
            source::Loc    m_loc;
            intern::String m_lhs_name;
            Typespec*      m_typespec;
            VArgKind       m_accepted_varg_kind;

          protected:
            Field(source::Loc loc, intern::String name, Typespec* rhs_typespec, VArgKind accepted_varg_kind)
            : m_loc(loc),
              m_lhs_name(name),
              m_typespec(rhs_typespec),
              m_accepted_varg_kind(accepted_varg_kind) {}

          public:
            source::Loc const& loc() const {
                return m_loc;
            }
            intern::String lhs_name() const {
                return m_lhs_name;
            }
            Typespec* rhs_typespec() const {
                return m_typespec;
            }
            VArgKind accepted_varg_kind() const {
                return m_accepted_varg_kind;
            }
        };
      
      private:
        std::vector<VPattern::Field*> m_fields;

      protected:
        VPattern(source::Loc loc, std::vector<VPattern::Field*>&& fields)
        : Node(loc, Kind::VPattern),
          m_fields(std::move(fields)) {}

      public:
        std::vector<VPattern::Field*> const& fields() const {
            return m_fields;
        }
    };

}

#endif  // INCLUDED_PDM_AST_PATTERN_VPATTERN_HH
