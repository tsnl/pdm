#include "code-printer.h"

#include <assert.h>
#include <stdio.h>
#include <stdarg.h>

#include "stb/stretchy_buffer.h"

#include "primer.h"

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
                PrintNode(cp, GetAstModuleStmtAt(node, i));
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
        case AST_DEF:
        {
            int desugared = 1;
            PrintText(cp, "def ");
            PrintText(cp, GetSymbolText(GetAstDefStmtLhs(node)));

            if (desugared) {
                PrintText(cp, " = ");
                PrintNode(cp, GetAstDefStmtDesugaredRhs(node));
            } else {
                int patternCount = GetAstDefStmtPatternCount(node);
                for (int index = 0; index < patternCount; index++) {
                    AstNode* pattern = GetAstDefStmtPatternAt(node,index);
                    PrintChar(cp,' ');
                    PrintNode(cp,pattern);
                }
                PrintText(cp, " = ");
                PrintNode(cp,GetAstDefStmtRhs(node));
            }
            break;
        }
        case AST_TYPEDEF:
        {
            SymbolID name = GetAstTypedefStmtName(node);
            AstNode* pattern = GetAstTypedefStmtOptPattern(node);
            AstNode* rhs = GetAstTypedefStmtOptRhs(node);
            PrintText(cp,"typedef ");
            PrintText(cp,GetSymbolText(name));
            if (pattern) {
                PrintNode(cp,pattern);
            }
            if (rhs) {
                PrintText(cp," = ");
                PrintNode(cp,rhs);
            }
            break;
        }
        case AST_EXTERN:
        {
            SymbolID name = GetAstExternStmtName(node);
            AstNode* typespec = GetAstExternTypespec(node);
            PrintText(cp, "extern ");
            PrintText(cp, GetSymbolText(name));
            PrintText(cp, ": ");
            PrintNode(cp, typespec);
            break;
        }
        case AST_FIELD__PATTERN_ITEM:
        case AST_FIELD__STRUCT_ITEM:
        case AST_FIELD__TEMPLATE_ITEM:
        case AST_FIELD__TUPLE_ITEM:
        {
            SymbolID lhs = GetAstFieldName(node);
            if (lhs != SYM_NULL) {
                PrintText(cp, GetSymbolText(lhs));
                PrintText(cp, ": ");
            }
            AstNode* rhs = GetAstFieldRhs(node);
            if (rhs) {
                PrintNode(cp, rhs);
            }
            break;
        }
        case AST_LAMBDA:
        {
            int captureCount = CountAstLambdaCaptures(node);
            PrintChar(cp, '{');
            for (int index = 0; index < captureCount; index++) {
                Defn* captureDefn = GetAstLambdaCaptureAt(node,index);
                PrintText(cp,GetSymbolText(captureDefn->defnID));
                if (index == captureCount-1) {
                    PrintChar(cp,',');
                }
            }
            PrintChar(cp, '}');

            PrintNode(cp, GetAstLambdaPattern(node));
            PrintText(cp, " ");
            PrintNode(cp, GetAstLambdaBody(node));
            break;
        }
        case AST_T_PATTERN:
        case AST_V_PATTERN:
        {
            char ltChar = (kind == AST_T_PATTERN ? '[':'(');
            char rtChar = (kind == AST_T_PATTERN ? ']':')');
            PrintChar(cp,ltChar);
            int patternLength = GetAstPatternLength(node);
            for (int index = 0; index < patternLength; index++) {
                PrintNode(cp, GetAstPatternFieldAt(node, index));
                if (index != patternLength-1) {
                    PrintText(cp, ", ");
                }
            }
            PrintChar(cp,rtChar);
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
        case AST_LET:
        {
            PrintText(cp, "let ");
            PrintText(cp, GetSymbolText(GetAstLetStmtLhs(node)));
            PrintText(cp, " = ");
            PrintNode(cp, GetAstLetStmtRhs(node));
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
            int isTemplate = IsAstCallTemplate(node);
            if (isTemplate) {
                PrintChar(cp,'[');
            } else {
                PrintChar(cp,'(');
            }
            PrintNode(cp, GetAstCallRhs(node));
            if (isTemplate) {
                PrintChar(cp,']');
            } else {
                PrintChar(cp,')');
            }
            break;
        }
        case AST_UNARY:
        {
            PrintText(cp, AstUnaryOperatorAsText(GetAstUnaryOperator(node)));
            PrintChar(cp, ' ');
            PrintNode(cp, GetAstUnaryOperand(node));
            break;
        }
        case AST_BINARY:
        {
            PrintNode(cp, GetAstBinaryLtOperand(node));
            PrintText(cp, AstBinaryOperatorAsText(GetAstBinaryOperator(node)));
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
        case AST_ITE:
        {
            PrintText(cp, "if ");
            PrintNode(cp, GetAstIteCond(node));
            PrintText(cp, " then ");
            PrintNode(cp, GetAstIteIfTrue(node));
            AstNode* ifFalse = GetAstIteIfFalse(node);
            if (ifFalse) {
                PrintText(cp, " else ");
                PrintNode(cp, ifFalse);
            }
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