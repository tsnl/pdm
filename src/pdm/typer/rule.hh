#ifndef INCLUDED_PDM_TYPER_RULE_HH
#define INCLUDED_PDM_TYPER_RULE_HH

#include <string>

#include "pdm/source/source.hh"
#include "pdm/ast/ast.hh"

//
// forward declarations:
//

namespace pdm::typer {
    class Constraint;
}


//
// implementation:
//

namespace pdm::typer {
    
    class Rule {
      // private data members:
      private:
        ast::Node* m_who;
        source::Span m_where;
        std::string m_why;

      // protected constructor => pure abstract
      protected:
        Rule(ast::Node* who, source::Span&& where, std::string&& why);
    };

    // todo: implement various rules to handle each typing case in the language.
    //       each typing should add one or more rules to the typer

}

#endif  // INCLUDED_PDM_TYPER_RULE_HH