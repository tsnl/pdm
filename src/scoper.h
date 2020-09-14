#ifndef INCLUDED_SCOPER_H
#define INCLUDED_SCOPER_H

#include "ast.h"

typedef struct Scoper Scoper;

Scoper* CreateScoper(void);

int ScopeModule(Scoper* scoper, AstNode* node);

#endif  // INCLUDED_SCOPER_H