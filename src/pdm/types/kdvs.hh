#ifndef INCLUDED__PDM__TYPES__KD_VAR_SOLVER_HH
#define INCLUDED__PDM__TYPES__KD_VAR_SOLVER_HH

#include <string>
#include <vector>
#include <set>

#include "pdm/core/integer.hh"
#include "pdm/printer/printer.hh"

#include "solve_result.hh"
#include "var-archetype.hh"
#include "var-invariant.hh"
#include "type.hh"

namespace pdm::types {
    class Var;
}

namespace pdm::types {

    class KindDependentVarSolver {
      private:
        std::set<KindDependentInvariant*> m_added_invariants;
        VarArchetype m_var_kind;
        Kind m_required_type_kind;
        Type* m_reified_soln;

      protected:
        inline KindDependentVarSolver(VarArchetype var_kind, Kind type_kind);
        virtual ~KindDependentVarSolver() = default;

      // use 'try_add_invariant' to transfer invariants from Vars (plural, incl. sub- and sup-)
      // to solution set.
      public:
        SolveResult try_add_invariant(KindDependentInvariant* invariant);
        Type* reify(Var* parent_var);
      protected:
        virtual SolveResult lazy_try_add_invariant_impl(KindDependentInvariant* invariant) = 0;
        virtual Type* reify_impl(Var* parent_var) = 0;

      public:
        [[nodiscard]] inline VarArchetype var_kind() const;
        [[nodiscard]] inline Kind required_type_kind() const;

      public:
        virtual void print(printer::Printer& printer) const = 0;
      protected:
        void help_print_common_and_start_indented_block(printer::Printer& printer, std::string const& name) const;
    };
    inline KindDependentVarSolver::KindDependentVarSolver(VarArchetype var_kind, Kind required_type_kind)
    :   m_var_kind(var_kind),
        m_required_type_kind(required_type_kind)
    {}
    inline VarArchetype KindDependentVarSolver::var_kind() const {
        return m_var_kind;
    }
    inline Kind KindDependentVarSolver::required_type_kind() const {
        return m_required_type_kind;
    }

    struct NewKDVS {
        KcResult result;
        KindDependentVarSolver* kdvs;
    };
    NewKDVS try_new_kdvs_for(VarArchetype var_kind, Kind type_kind);

}

#endif  // INCLUDED__PDM__TYPES__KD_VAR_SOLVER_HH
