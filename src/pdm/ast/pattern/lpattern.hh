#ifndef INCLUDED_PDM_AST_PATTERN_LPATTERN_HH
#define INCLUDED_PDM_AST_PATTERN_LPATTERN_HH

#include <vector>
#include <cassert>

#include "pdm/core/intern.hh"
#include "pdm/ast/node.hh"
#include "pdm/ast/setspec/type_spec.hh"

#include "base_field.hh"

namespace pdm::scoper {
    class Defn;
}
namespace pdm::types {
    class TypeVar;
}
namespace pdm::ast {
    class Manager;
}

namespace pdm::ast {

    class LPattern: public Node {
        friend Manager;

      public:
        enum class FieldKind {
            IdSingleton,
            IdTypeSpecPair
        };
        class Field: public BaseField {
            friend Manager;
          
          private:
            FieldKind       m_kind;
            TypeSpec*       m_opt_rhs_typespec;
            types::TypeVar* m_x_defn_tv;
            
          protected:
            Field(source::Loc loc, FieldKind kind, intern::String name, TypeSpec* opt_rhs_typespec = nullptr)
            :   BaseField(loc, Kind::Aux_LPatternField, name),
                m_kind(kind),
                m_opt_rhs_typespec(opt_rhs_typespec)
            {
                if (opt_rhs_typespec) {
                    assert(
                        (kind == LPattern::FieldKind::IdTypeSpecPair) && 
                        ("LPattern: cannot pass rhs_typespec for singleton field.")
                    );
                }
            }
          
          public:
            FieldKind kind() const { 
                return m_kind; 
            }
            TypeSpec* opt_rhs_typespec() const { 
                return m_opt_rhs_typespec; 
            }

          public:
            types::TypeVar* x_defn_tv() const {
                return m_x_defn_tv;
            }
            void x_defn_tv(types::TypeVar* defn_tv) {
                m_x_defn_tv = defn_tv;
            }
        };
      
      private:
        std::vector<LPattern::Field*> m_fields;
        bool                          m_destructure;
      
      protected:
        LPattern(source::Loc loc, std::vector<LPattern::Field*>&& fields, bool destructure)
        : Node(loc, Kind::LPattern),
          m_fields(std::move(fields)),
          m_destructure(destructure) {}
      
      public:
        bool destructure() const {
            return m_destructure;
        }
        std::vector<LPattern::Field*> const& fields() const {
            return m_fields;
        }
    };

}

#endif  // INCLUDED_PDM_AST_PATTERN_LPATTERN_HH
