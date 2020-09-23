#include "code-printer.h"

#include <assert.h>
#include <stdio.h>
#include <stdarg.h>

#include "stb/stretchy_buffer.h"

size_t const BUFFER_SIZE = 1024;
char buffer[BUFFER_SIZE] = {0};

CodePrinter CreateCodePrinter(FILE* file, int flags) {
    CodePrinter printer;
    printer.file = file;
    printer.indentCount = 0;
    printer.flags = flags;
    return printer;
}
void PrintChar(CodePrinter* printer, char ch) {
    if (ch == '\t') {
        // extending tabs
        for (int tabIndex = 0; tabIndex < printer->indentCount; tabIndex++) {
            fputc('\t', printer->file);
        }
    } else {
        fputc(ch, printer->file);
    }
}
void PrintText(CodePrinter* printer, char const* text) {
    for (; *text; text++) {
        PrintChar(printer, *text);
    }
}
void PrintFormattedText(CodePrinter* printer, char const* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, BUFFER_SIZE, fmt, args);
    va_end(args);

    PrintText(printer, buffer);
}
void PrintNode(CodePrinter* cp, AstNode* node) {
    AstKind kind = GetAstNodeKind(node);
    switch (kind)
    {
        case AST_UNIT:
        {
            PrintText(cp, "()");
            break;
        }
        case AST_MODULE:
        {
            int length = GetAstModuleLength(node);
            PrintFormattedText(cp, "MODULE... (%d)\n", length);
            for (int i = 0; i < length; i++) {
                PrintNode(cp, GetAstModuleFieldAt(node, i));
                PrintText(cp, ";\n");
            }
            break;
        }
        case AST_ID:
        {
            PrintText(cp, GetSymbolText(GetAstIdName(node)));
            break;
        }
        case AST_LITERAL_INT:
        {
            int base = GetAstIntLiteralBase(node);
            if (base == 10) {
                PrintFormattedText(cp, "%zu", GetAstIntLiteralValue(node));
            } else if (base == 16) {
                PrintFormattedText(cp, "0x%zx", GetAstIntLiteralValue(node));
            } else if (DEBUG) {
                printf("!!- invalid base %d while printing literal int", base);
            } else {
                assert(0 && "invalid 'base' while printing literal int.");
            }
            break;
        }
        case AST_LITERAL_FLOAT:
        {
            PrintFormattedText(cp, "%Lf", GetAstFloatLiteralValue(node));
            break;
        }
        case AST_LITERAL_STRING:
        {
            PrintChar(cp, '"');
            int const* stringSb = GetAstStringLiteralValue(node);
            int length = sb_count(stringSb);
            for (int index = 0; index < length; index++) {
                int ch = stringSb[index];
                if (ch == '\\') {
                    PrintText(cp, "\\\\");
                } else if (ch == '\n') {
                    PrintText(cp, "\\n");
                } else if (ch == '\r') {
                    PrintText(cp, "\\r");
                } else if (ch == '\a') {
                    PrintText(cp, "\\a");
                } else if (ch == '"') {
                    PrintText(cp, "\\\"");
                } else {
                    PrintChar(cp, (char)ch);
                }
            }
            PrintChar(cp, '"');
            break;
        }
        case AST_FIELD__MODULE_ITEM:
        case AST_FIELD__PATTERN_ITEM:
        case AST_FIELD__STRUCT_ITEM:
        case AST_FIELD__TEMPLATE_ITEM:
        case AST_FIELD__TUPLE_ITEM:
        {
            SymbolID lhs = GetAstFieldName(node);
            if (lhs != SYM_NULL) {
                PrintText(cp, GetSymbolText(lhs));
                if (GetAstNodeKind(node) == AST_FIELD__MODULE_ITEM) {
                    AstNode* pattern = GetAstModuleFieldPattern(node);
                    if (pattern) {
                        PrintChar(cp, '[');
                        int patternCount = GetAstPatternLength(pattern);
                        for (int patternIndex = 0; patternIndex < patternCount; patternIndex++) {
                            AstNode* patternFieldAtIndex = GetAstPatternFieldAt(pattern, patternIndex);
                            SymbolID patternNameAtIndex = GetAstFieldName(patternFieldAtIndex);
                            PrintText(cp, GetSymbolText(patternNameAtIndex));
                            if (patternIndex+1 != patternCount) {
                                PrintChar(cp, ',');
                            }
                        }
                        PrintChar(cp, ']');
                    }
                }
                if (kind == AST_FIELD__MODULE_ITEM) {
                    PrintText(cp, " :: ");
                } else {
                    PrintText(cp, ": ");
                }
            }
            PrintNode(cp, GetAstFieldRhs(node));
            break;
        }
        case AST_LAMBDA:
        {
            PrintNode(cp, GetAstLambdaPattern(node));
            PrintText(cp, " -> ");
            PrintNode(cp, GetAstLambdaBody(node));
            break;
        }
        case AST_PATTERN:
        {
            PrintText(cp, "[");
            int patternLength = GetAstPatternLength(node);
            for (int index = 0; index < patternLength; index++) {
                PrintNode(cp, GetAstPatternFieldAt(node, index));
                if (index != patternLength-1) {
                    PrintText(cp, ", ");
                }
            }
            PrintText(cp, "]");
            break;
        }
        case AST_PAREN:
        {
            PrintText(cp, "(");
            PrintNode(cp, GetAstParenItem(node));
            PrintText(cp, ")");
            break;
        }
        case AST_TUPLE:
        {
            PrintChar(cp, '(');
            int tupleCount = GetAstTupleLength(node);
            for (int index = 0; index < tupleCount; index++) {
                AstNode* field = GetAstTupleItemAt(node, index);
                PrintNode(cp, field);
                if (index != tupleCount-1) {
                    PrintChar(cp, ',');
                }
            }
            PrintChar(cp, ')');
            break;
        }
        case AST_STRUCT:
        {
            PrintChar(cp, '{');
            IndentPrinter(cp);
            PrintChar(cp, '\n');

            int structCount = GetAstStructLength(node);
            for (int index = 0; index < structCount; index++) {
                AstNode* field = GetAstStructFieldAt(node, index);
                PrintChar(cp, '\t');
                PrintNode(cp, field);
                if (index != structCount-1) {
                    PrintText(cp, ",\n");
                }
            }
            DeIndentPrinter(cp);
            PrintChar(cp, '\n');
            PrintChar(cp, '\t');
            PrintChar(cp, '}');
            break;
        }
        case AST_CHAIN:
        {
            PrintChar(cp, '{');
            IndentPrinter(cp);

            int prefixLength = GetAstChainPrefixLength(node);
            for (int index = 0; index < prefixLength; index++) {
                AstNode* stmt = GetAstChainPrefixStmtAt(node, index);
                PrintChar(cp, '\n');
                PrintChar(cp, '\t');
                PrintNode(cp, stmt);
                PrintChar(cp, ';');
            }
            AstNode* result = GetAstChainResult(node);
            if (result) {
                PrintChar(cp, '\n');
                PrintChar(cp, '\t');
                PrintNode(cp, result);
            }
            DeIndentPrinter(cp);
            PrintChar(cp, '\n');
            PrintChar(cp, '\t');
            PrintChar(cp, '}');
            break;
        }
        case AST_STMT_BIND:
        {
            PrintText(cp, GetSymbolText(GetAstBindStmtLhs(node)));
            PrintText(cp, " = ");
            PrintNode(cp, GetAstBindStmtRhs(node));
            break;
        }
        case AST_STMT_CHECK:
        {
            PrintText(cp, "check(");
            PrintNode(cp, GetAstCheckStmtChecked(node));
            // todo: print the check message here.
            PrintText(cp, ", ...)");
            break;
        }
        case AST_CALL:
        {
            PrintNode(cp, GetAstCallLhs(node));
            PrintChar(cp, ' ');
            PrintNode(cp, GetAstCallRhs(node));
            break;
        }
        case AST_UNARY:
        {
            PrintText(cp, GetUnaryOperatorText(GetAstUnaryOperator(node)));
            PrintChar(cp, ' ');
            PrintNode(cp, GetAstUnaryOperand(node));
            break;
        }
        case AST_BINARY:
        {
            PrintNode(cp, GetAstBinaryLtOperand(node));
            PrintText(cp, GetBinaryOperatorText(GetAstBinaryOperator(node)));
            PrintNode(cp, GetAstBinaryRtOperand(node));
            break;
        }
        case AST_DOT_INDEX:
        {
            PrintNode(cp, GetAstDotIndexLhs(node));
            PrintChar(cp, '.');
            PrintFormattedText(cp, "%zu", GetAstDotIndexRhs(node));
            break;
        }
        case AST_DOT_NAME:
        {
            PrintNode(cp, GetAstDotIndexLhs(node));
            PrintChar(cp, '.');
            PrintText(cp, GetSymbolText(GetAstDotNameRhs(node)));
            break;
        }
        default:
        {
            PrintText(cp, "?");
            break;
        }
    }
}
void IndentPrinter(CodePrinter* printer) {
    printer->indentCount++;
}
void DeIndentPrinter(CodePrinter* printer) {
    printer->indentCount--;
}