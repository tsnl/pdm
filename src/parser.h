#ifndef INCLUDED_PARSER_H
#define INCLUDED_PARSER_H

#include "ast.h"
#include "source.h"

RawAstNode* ParseSource(Source* source);

#endif  // INCLUDED_PARSER_H
