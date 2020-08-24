#pragma once

#include <stddef.h>
#include <stdint.h>

typedef uint32_t SymbolID;

#define SYM_NULL ((SymbolID)0)

void InitSymbols(void);
void DeInitSymbols(void);

SymbolID Symbol(char const* text);
char const* GetSymbolText(SymbolID symbolID);
