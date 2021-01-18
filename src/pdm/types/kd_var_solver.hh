#ifndef INCLUDED__PDM__TYPES__KD_VAR_SOLVER_HH
#define INCLUDED__PDM__TYPES__KD_VAR_SOLVER_HH

#include <vector>
#include <set>

#include "pdm/core/integer.hh"
#include "solving.hh"
#include "var_kind.hh"
#include "invariant.hh"

namespace pdm::types {

    class KindDependentVarSolver {
      private:
        std::set<KindDependentInvariant*> m_added_invariants;
        VarKind m_var_kind;
        TypeKind m_required_type_kind;
        
      protected:
        bool check_if_new_then_add_invariant(KindDependentInvariant* invariant);

      protected:
        inline KindDependentVarSolver(VarKind var_kind, TypeKind type_kind);
        virtual ~KindDependentVarSolver() = default;

      private:
        SolvePhase2_Result try_add_invariant(KindDependentInvariant* invariant);
        virtual SolvePhase2_Result lazy_try_add_invariant_impl(KindDependentInvariant* invariant) = 0;

      public:
        inline VarKind var_kind() const;
        inline TypeKind required_type_kind() const;
    };
    inline KindDependentVarSolver::KindDependentVarSolver(VarKind var_kind, TypeKind required_type_kind)
    :   m_var_kind(var_kind),
        m_required_type_kind(required_type_kind)
    {}
    inline VarKind KindDependentVarSolver::var_kind() const {
        return m_var_kind;
    }
    inline TypeKind KindDependentVarSolver::required_type_kind() const {
        return m_required_type_kind;
    }

    struct NewKDVS {
        SolvePhase1_Result result;
        KindDependentVarSolver* kdvs;
    };
    NewKDVS try_new_kdvs_for(VarKind var_kind, u64 allowed_type_kinds_bitset);

}

#endif  // INCLUDED__PDM__TYPES__KD_VAR_SOLVER_HH
