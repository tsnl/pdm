#ifndef INCLUDED__PDM__TYPES__KD_VAR_SOLVER_HH
#define INCLUDED__PDM__TYPES__KD_VAR_SOLVER_HH

#include <string>
#include <vector>
#include <set>

#include "pdm/core/integer.hh"
#include "pdm/printer/printer.hh"

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
        inline KindDependentVarSolver(VarKind var_kind, TypeKind type_kind);
        virtual ~KindDependentVarSolver() = default;

      // use 'try_add_invariant' to transfer invariants from Vars (plural, incl. sub- and sup-)
      // to solution set.
      public:
        KdResult try_add_invariant(KindDependentInvariant* invariant);
      private:
        virtual KdResult lazy_try_add_invariant_impl(KindDependentInvariant* invariant) = 0;

      public:
        inline VarKind var_kind() const;
        inline TypeKind required_type_kind() const;

      public:
        virtual void print(printer::Printer& printer) const = 0;
      protected:
        void help_print_common_and_start_indented_block(printer::Printer& printer, std::string const& name) const;
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
        KcResult result;
        KindDependentVarSolver* kdvs;
    };
    NewKDVS try_new_kdvs_for(VarKind var_kind, u64 allowed_type_kinds_bitset);

}

#endif  // INCLUDED__PDM__TYPES__KD_VAR_SOLVER_HH
