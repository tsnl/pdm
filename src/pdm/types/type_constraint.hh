#ifndef INCLUDED_PDM_TYPES_TYPE_CONSTRAINT_HH
#define INCLUDED_PDM_TYPES_TYPE_CONSTRAINT_HH

//
// Forward Declarations:
//

namespace pdm::types {

    class Rule;

}   // namespace pdm::typer


//
// Implementation:
//

namespace pdm::types {
    
    class TypeConstraint {
      private:
        Rule* m_parent_rule;

      protected:
        TypeConstraint(Rule* parent_rule)
        : m_parent_rule(parent_rule) {}
    };

    class TC_OfKind: public TypeConstraint {
      
    };
}

#endif  // INCLUDED_PDM_TYPES_TYPE_CONSTRAINT_HH

