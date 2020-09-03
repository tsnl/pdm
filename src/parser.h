#ifndef INCLUDED_PARSER_H
#define INCLUDED_PARSER_H

#include "ast.h"
#include "source.h"

AstNode* ParseSource(Source* source);

#endif  // INCLUDED_PARSER_H
