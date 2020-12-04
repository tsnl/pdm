#ifndef INCLUDED_PDM_TYPER_CONSTRAINT_HH
#define INCLUDED_PDM_TYPER_CONSTRAINT_HH

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

    enum class ConstraintKind {
        // todo: populate with different constraint kinds
    };

    class Constraint {
      // private data members:
      private:
        ConstraintKind m_kind;
        Rule* m_rule;
    };

    // todo: create the few necessary Constraints for a typer as subtypes of this constraint.
    //       constraint set should remain stable, add new rules to compose constraints.

}   // pdm::typer

#endif  // INCLUDED_PDM_TYPER_CONSTRAINT_HH

