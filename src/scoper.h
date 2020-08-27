#pragma once

#include "ast.h"

typedef struct Scoper Scoper;

Scoper* CreateScoper(void);
int ScopeModule(Scoper* scoper, AstNode* node);
