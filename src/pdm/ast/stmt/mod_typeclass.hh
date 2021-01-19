#ifndef INCLUDED_PDM_AST_STMT_TYPECLASS_HH
#define INCLUDED_PDM_AST_STMT_TYPECLASS_HH

#include "pdm/core/intern.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/stmt/stmt.hh"
#include "pdm/ast/typespec/typespec.hh"
#include "pdm/ast/pattern/vpattern.hh"
#include "pdm/ast/pattern/tpattern.hh"
#include "mod_content.hh"

namespace pdm::ast {
    class Manager;
    class TPattern;
    class Typespec;
    class TypeQueryExp;
}

namespace pdm::ast {

    class ModTypeclassStmt: public ModContentStmt {
        friend Manager;

      private:
        intern::String              m_typeclass_name;
        intern::String              m_candidate_name;
        Typespec*                   m_candidate_typespec;
        std::vector<TPattern*>      m_tpatterns;
        std::vector<TypeQueryExp*>  m_conditions;
        types::Var*                 m_x_defn_var;

      public:
        ModTypeclassStmt(
            source::Loc loc, 
            intern::String typeclass_name,
            intern::String candidate_name,
            Typespec* candidate_typespec,
            std::vector<TPattern*>&& tpatterns,
            std::vector<TypeQueryExp*>&& conditions
        )
        :   ModContentStmt(loc, Kind::ModTypeclassStmt),
            m_typeclass_name(typeclass_name),
            m_candidate_name(candidate_name),
            m_candidate_typespec(candidate_typespec),
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
        Typespec* candidate_typespec() const {
            return m_candidate_typespec;
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
