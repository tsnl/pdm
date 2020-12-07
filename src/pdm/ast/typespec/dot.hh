#ifndef INCLUDED_PDM_AST_TYPESPEC_DOT_HH
#define INCLUDED_PDM_AST_TYPESPEC_DOT_HH

#include <vector>

#include "pdm/core/intern.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/typespec/typespec.hh"

namespace pdm::ast {

    class DotNameTypespec_TypePrefix: public Typespec {
      private:
        Typespec*      m_lhs_typespec;
        intern::String m_rhs_name;

      public:
        DotNameTypespec_TypePrefix(source::Loc loc, Typespec* lhs_typespec, intern::String rhs_name)
        : Typespec(loc, Kind::DotNameTypespec_TypePrefix),
          m_lhs_typespec(lhs_typespec),
          m_rhs_name(rhs_name) {}
      
      public:
        Typespec* lhs_typespec() const {
            return m_lhs_typespec;
        }
        intern::String rhs_name() const {
            return m_rhs_name;
        }
    };

    class DotNameTypespec_ModPrefix: public Typespec {
      private:
        std::vector<intern::String> m_lhs_prefixes;
        intern::String              m_rhs_name;

      public:
        DotNameTypespec_ModPrefix(source::Loc loc, std::vector<intern::String>&& lhs_prefixes, intern::String rhs_name)
        : Typespec(loc, Kind::DotNameTypespec_ModPrefix),
          m_lhs_prefixes(std::move(lhs_prefixes)),
          m_rhs_name(rhs_name) {}
      
      public:
        std::vector<intern::String> const& lhs_prefixes() const {
            return m_lhs_prefixes;
        }
        intern::String rhs_name() const {
            return m_rhs_name;
        }
    };

}

#endif  // INCLUDED_PDM_AST_TYPESPEC_DOT_HH