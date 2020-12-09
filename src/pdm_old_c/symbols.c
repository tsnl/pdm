#include "symbols.h"

#include "config.h"

#include "intern/strings.h"

static struct strings* stringsRepository = NULL;

void InitSymbols(void) {
    if (!stringsRepository) {
        stringsRepository = strings_new();
    }
}

void DeInitSymbols(void) {
    if (stringsRepository) {
        strings_free(stringsRepository);
        stringsRepository = NULL;
    }
}

SymbolID Symbol(char const* text) {
    return strings_intern(stringsRepository, text);
}

char const* GetSymbolText(SymbolID symbolID) {
    return strings_lookup_id(stringsRepository, symbolID);
}
