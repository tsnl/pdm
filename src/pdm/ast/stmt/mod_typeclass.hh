#ifndef INCLUDED_PDM_AST_STMT_TYPECLASS_HH
#define INCLUDED_PDM_AST_STMT_TYPECLASS_HH

#include "pdm/core/intern.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/stmt/stmt.hh"
#include "pdm/ast/setspec/type_spec.hh"
#include "pdm/ast/pattern/vpattern.hh"
#include "pdm/ast/pattern/tpattern.hh"
#include "mod_content.hh"

namespace pdm::ast {
    class Manager;
    class TPattern;
    class ClassSpec;
    class TypeQueryExp;
}

namespace pdm::ast {

    class ModTypeclassStmt: public ModContentStmt {
        friend Manager;

      private:
        intern::String              m_typeclass_name;
        intern::String              m_candidate_name;
        ClassSpec*                  m_candidate_class_spec;
        std::vector<TPattern*>      m_tpatterns;
        std::vector<TypeQueryExp*>  m_conditions;
        types::Var*                 m_x_defn_var;

      public:
        ModTypeclassStmt(
            source::Loc loc, 
            intern::String typeclass_name,
            intern::String candidate_name,
            ClassSpec* candidate_class_spec,
            std::vector<TPattern*>&& tpatterns,
            std::vector<TypeQueryExp*>&& conditions
        )
        :   ModContentStmt(loc, Kind::ModTypeclassStmt),
            m_typeclass_name(typeclass_name),
            m_candidate_name(candidate_name),
            m_candidate_class_spec(candidate_class_spec),
            m_tpatterns(std::move(tpatterns)),
            m_conditions(std::move(conditions)),
            m_x_defn_var(nullptr) 
        {}
      
      public:
        intern::String typeclass_name() const {
            return m_typeclass_name;
        }
        intern::String candidate_name() const {
            return m_candidate_name;
        }
        ClassSpec* candidate_class_spec() const {
            return m_candidate_class_spec;
        }
        std::vector<TPattern*> const& tpatterns() const {
            return m_tpatterns;
        }
        std::vector<TypeQueryExp*> const& conditions() const {
            return m_conditions;
        }

      public:
        types::Var* x_defn_var() const {
            return m_x_defn_var;
        }
        void x_defn_var(types::Var* defn_var) {
            m_x_defn_var = defn_var;
        }
    };

}

#endif  // INCLUDED_PDM_AST_STMT_TYPECLASS_HH
