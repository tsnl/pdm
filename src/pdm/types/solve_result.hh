#ifndef INCLUDED__PDM__TYPES__SOLVING_HH
#define INCLUDED__PDM__TYPES__SOLVING_HH

#include <algorithm>

namespace pdm::types {

    // The Solver establishes 'subvar'/'supervar' as pipes for Invariants
    // to flow between.
    // Whenever an Invariant is assumed, it updates Common Constraints.
    // In SP1, we try to create Kind-Dependent Var Solvers (KDVSes) for each Var from Common Constraints.
    //      If there is insufficient Common info, we punt.
    // In SP2, we transfer Invariants from supervars to subvars.
    // -    When Invariants are added to a KDVS, new Relations are added by comparing
    //      existing KindDependentInvariant args to new args.
    // -    If a related Var doesn't have a KDVS yet, it is ignored.
    // -    If adding an Invariant to a KDVS produces an error,
    //      - an error message is posted
    //      - the KDVS is marked as poisoned, and is subsequently ignored.
    // After each SP2, we check if any of the Vars with KDVSes were updated.
    // -    If so, means new Relations were added. Repeat SP1.
    // -    Otherwise, means KDVSes are stable.
    // If KDVSes are stable,
    // -    If any Var lacks a KDVS or has a poisoned KDVS, generate an error.
    // -    Else, generate a Type from the KDVS (i.e. that satisfies global Invariants),
    //      called an algebraic type, and verify it is finite.
    
    // After the solver, we can typecheck each KDVS by attempting to generate 

    // KcResult = Kind-check result.
    // Kind checks are a coarser kind of type-check performed before more granular typechecking.
    enum class KcResult {
        InsufficientInfo,
        Error_MixedKind,
        Ok
    };

    inline bool kcr_is_error(KcResult kcr);

    inline bool kcr_is_error(KcResult kcr) {
        return (
            kcr == KcResult::Error_MixedKind
        );
    }

    // SolveResult = Kind-dependent result.
    // Represents results from post-kind-check territory.
    enum class SolveResult {
        CompilerError,
        TypingError,
        UpdatedOrFresh,
        NoChange,
    };

    inline SolveResult result_and(SolveResult r1, SolveResult r2);
    inline bool result_is_error(SolveResult kdr);

    inline SolveResult result_and(SolveResult r1, SolveResult r2) {
        return static_cast<SolveResult>(
            std::min(static_cast<int>(r1), static_cast<int>(r2))
        );
    }

    inline bool result_is_error(SolveResult kdr) {
        return (
            kdr == SolveResult::TypingError ||
            kdr == SolveResult::CompilerError
        );
    }

    // FinishResult: used after multiple solution iterations to get the final result
    enum class FinishResult {
        Plastic,
        Baking,
        Finished_Ok,
        Finished_Broken_Typing,
        Finished_Broken_Compiler
    };
}

#endif  // INCLUDED__PDM__TYPES__SOLVING_HH