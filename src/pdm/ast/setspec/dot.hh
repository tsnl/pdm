#ifndef INCLUDED_PDM_AST_TYPESPEC_DOT_HH
#define INCLUDED_PDM_AST_TYPESPEC_DOT_HH

#include <vector>

#include "pdm/core/intern.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/setspec/type_spec.hh"

namespace pdm::ast {

    class Manager;

    class DotNameTypeSpec_ModPrefix: public TypeSpec {
        friend Manager;

      private:
        std::vector<intern::String> m_lhs_prefixes;
        intern::String              m_rhs_name;

      protected:
        DotNameTypeSpec_ModPrefix(source::Loc loc, std::vector<intern::String>&& lhs_prefixes, intern::String rhs_name)
        : TypeSpec(loc, Kind::DotNameTypeSpec_ModPrefix),
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

    //
    // Removed:
    //

    // class DotNameTypeSpec_TypePrefix: public TypeSpec {
    //     friend Manager;

    //   private:
    //     TypeSpec*      m_lhs_typespec;
    //     intern::String m_rhs_name;

    //   protected:
    //     DotNameTypeSpec_TypePrefix(source::Loc loc, TypeSpec* lhs_typespec, intern::String rhs_name)
    //     : TypeSpec(loc, Kind::DotNameTypeSpec_TypePrefix),
    //       m_lhs_typespec(lhs_typespec),
    //       m_rhs_name(rhs_name) {}
      
    //   public:
    //     TypeSpec* lhs_typespec() const {
    //         return m_lhs_typespec;
    //     }
    //     intern::String rhs_name() const {
    //         return m_rhs_name;
    //     }
    // };
}

#endif  // INCLUDED_PDM_AST_TYPESPEC_DOT_HH