// this pass' sole job is to generate a minimal set of instantiations (keyed by evaluated type/value)
// stored on the origin template.

// the emitter can generate a monomorph for each instantiation, while each usage can use a stored key to access the
// monomorph.

// Three steps:
// 1. assemble a list of all TCall usages
// 2. generate keys for each usage in the TCall list, and store the key in the TCall
//    - evaluation requires querying the AST for symbols
//    - interpreting the result of values (potentially calling functions in the AST if static-call with '!')
//    - and ensuring the '==' operator is respected on keys so we can uniquely hash
// 3. store each unique key for substitution in the emitter on the template (i.e. BaseModExp)

#ifndef INCLUDED_PDM_EXPANSION_EXPANSION_HH
#define INCLUDED_PDM_EXPANSION_EXPANSION_HH

#include "pdm/ast/source-node/script.hh"
#include "pdm/ast/module/base-mod-exp.hh"

namespace pdm::expansion {

    void expand_usages_in_script(ast::Script* script);

}

#endif  // INCLUDED_PDM_EXPANSION_EXPANSION_HH