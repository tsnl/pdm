#include <stdio.h>

#include "useful.h"
#include "symbols.h"
#include "interp.h"

int main(int argc, char* argv[]) {
    char const* defaultSourcePath = "test/test1.hub";
    char const* sourcePath = NULL;
    if (argc == 1) {
        sourcePath = defaultSourcePath;
    } else if (argc == 2) {
        sourcePath = argv[1];
    } else {
        COMPILER_ERROR_VA(
            "Invalid #args=%d; either leave empty for default path '%s' or provide 1 arg path", 
            argc - 1, defaultSourcePath
        );
    }

    Interp* interp = CreateInterp();
    Source* scriptSource = CreateSource(sourcePath);
    if (!scriptSource) {
        printf("File not found: '%s'\n\n\n",sourcePath);
        return 1;
    }

    int result;
    
    result = InterpLoadModuleSource(interp, scriptSource);
    if (!result) {
        printf("Loading failed.\n\n\n");
        return 1;
    }
    printf("Loading succeeded.\n\n");
    
    result = InterpTypecheckModules(interp);
    if (!result) {
        printf("Linking failed.\n\n\n");
        return 1;
    }

    result = InterpCompile(interp);
    if (!result) {
        printf("LLVM emission failed.\n\n\n");
        return 1;
    }

    // TODO: execute, emit an executable, or just exit after reporting the program's validity.
    DestroyInterp(interp);

    printf("Exiting normally.\n\n\n");
    return 0;
}

