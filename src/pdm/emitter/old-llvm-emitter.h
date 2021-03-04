#ifndef INCLUDED_LLVM_EMITTER_H
#define INCLUDED_LLVM_EMITTER_H

#include "source.h"
#include "ast.h"
#include "typer.h"

int EmitLlvmModule(Manager* typer, AstNode* module);

#endif  // INCLUDED_LLVM_EMITTER_H
