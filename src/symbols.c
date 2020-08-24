#include "symbols.h"

#include "config.h"

#include "intern/strings.h"

static struct strings* stringsRepository;

void InitSymbols(void) {
    stringsRepository = strings_new();
}

void DeInitSymbols(void) {
    strings_free(stringsRepository);
}

SymbolID Symbol(char const* text) {
    return strings_intern(stringsRepository, text);
}

char const* GetSymbolText(SymbolID symbolID) {
    return strings_lookup_id(stringsRepository, symbolID);
}
