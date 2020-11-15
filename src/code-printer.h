#ifndef INCLUDED_CODE_PRINTER_H
#define INCLUDED_CODE_PRINTER_H

#include <stdio.h>

#include "ast.h"

typedef enum CodePrinterFlags CodePrinterFlags;
enum CodePrinterFlags {
    PRINT_NONE = (0x0),
    PRINT_INDENT = (0x1),
};

typedef struct CodePrinter CodePrinter;
struct CodePrinter {
    FILE* file;
    int indentCount;
    int flags;
};

CodePrinter CreateCodePrinter(FILE* file, int flags);
void PrintChar(CodePrinter* printer, char text);
void PrintText(CodePrinter* printer, char const* text);
void PrintFormattedText(CodePrinter* printer, char const* fmt, ...);
void PrintNode(CodePrinter* cp, AstNode* node);
void IndentPrinter(CodePrinter* printer);
void DeIndentPrinter(CodePrinter* printer);

#endif  // INCLUDED_CODE_PRINTER_H
