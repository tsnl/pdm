#ifndef INCLUDED_PDM_AST_PATTERN_LPATTERN_HH
#define INCLUDED_PDM_AST_PATTERN_LPATTERN_HH

#include <vector>
#include <cassert>

#include "pdm/core/intern.hh"
#include "pdm/ast/node.hh"
#include "pdm/ast/typespec/typespec.hh"

namespace pdm::ast {

    class Manager;

    class LPattern: public Node {
        friend Manager;

      public:
        enum class FieldKind {
            IdSingleton,
            IdTypespecPair
        };
        class Field {
            friend Manager;
          
          private:
            source::Loc     m_loc;
            FieldKind       m_kind;
            intern::String  m_lhs_name;
            Typespec*       m_opt_rhs_typespec;
          
          protected:
            Field(source::Loc loc, FieldKind kind, intern::String name, Typespec* opt_rhs_typespec = nullptr)
            : m_loc(loc),
              m_kind(kind), 
              m_lhs_name(name), 
              m_opt_rhs_typespec(opt_rhs_typespec) {
                if (opt_rhs_typespec) {
                    assert(
                        (kind == LPattern::FieldKind::IdTypespecPair) && 
                        ("LPattern: cannot pass rhs_typespec for singleton field.")
                    );
                }
            }
          
          public:
            source::Loc const& loc() const { 
                return m_loc; 
            }
            FieldKind kind() const { 
                return m_kind; 
            }
            intern::String lhs_name() const { 
                return m_lhs_name; 
            }
            Typespec* opt_rhs_typespec() const { 
                return m_opt_rhs_typespec; 
            }
        };
      
      private:
        std::vector<LPattern::Field*> m_fields;
      
      protected:
        LPattern(source::Loc loc, std::vector<LPattern::Field*>&& fields)
        : Node(loc, Kind::LPattern),
          m_fields(std::move(fields)) {}
      
      public:
        bool is_singleton_pattern() const {
            return m_fields.size() == 1;
        }

        std::vector<LPattern::Field*> const& fields() const {
            return m_fields;
        }
    };

}

#endif  // INCLUDED_PDM_AST_PATTERN_LPATTERN_HH
