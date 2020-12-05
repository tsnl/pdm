#ifndef INCLUDED_PDM_TYPER_CONSTRAINT_HH
#define INCLUDED_PDM_TYPER_CONSTRAINT_HH

#include "rough_class.hh"
#include "tv_kind.hh"

//
// Forward Declarations:
//

namespace pdm::typer {

    class Rule;

}   // namespace pdm::typer


//
// Implementation:
//

namespace pdm::typer {

    // ApplyConstraintResult feedsback whether a constraint is Confirmed, Disproved, Or Deferred
    // - Applied_Confirmed: (1) no new info gained, (2) no irregularities
    // - Applied: **new info gained** propagating to other types without issue
    // - Rejected: (2) irregularities detected, no changes applied (strong guarantee)
    enum class ApplyConstraintResult {
        Applied_Confirmed,
        Applied,
        Rejected
    };
    
    class Constraint {
      // private data members:
      private:
        Rule* m_parent_rule;
      // public methods:
      public:
        virtual RoughClass formal_rough_class() const = 0;
    };

    // todo: create the few necessary Constraints for a typer as subtypes of this constraint.
    //       constraint set should remain stable, add new rules to compose constraints.

}   // pdm::typer

#endif  // INCLUDED_PDM_TYPER_CONSTRAINT_HH

