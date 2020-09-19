#include "primer.h"


AstNode* PrimeAst(RawAstNode* rawModuleNode) {
    if (rawModuleNode == NULL) {
        return NULL;
    }

    // TODO: validate the AST here before passing to modules.

    return rawModuleNode;
}
