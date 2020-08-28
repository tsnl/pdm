#pragma once

#include "ast.h"

typedef struct Scoper Scoper;

Scoper* CreateScoper(void);

int RunScoper(Scoper* scoper, AstNode* node);
