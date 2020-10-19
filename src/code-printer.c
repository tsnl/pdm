#include "code-printer.h"

#include <assert.h>
#include <stdio.h>
#include <stdarg.h>

#include "stb/stretchy_buffer.h"

#include "useful.h"
#include "primer.h"

#define BUFFER_SIZE (1024)

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
        case AST_VID:
        case AST_TID:
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
            } else {
                COMPILER_ERROR_VA("Invalid base '%d' while printing literal int",base);
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
        case AST_VDEF:
        {
            PrintText(cp, "def ");
            PrintText(cp, GetSymbolText(GetAstDefValueStmtLhs(node)));
            AstNode* optTemplatePattern = GetAstDefValueStmtOptTemplatePattern(node);
            if (optTemplatePattern) {
                PrintNode(cp,optTemplatePattern);
            }
            PrintText(cp, " = ");
            PrintNode(cp, GetAstDefValueStmtRhs(node));
            break;
        }
        case AST_TDEF:
        {
            PrintText(cp, "define ");
            SymbolID name = GetAstTypedefStmtName(node);
            AstNode* pattern = GetAstTypedefStmtOptPattern(node);
            AstNode* rhs = GetAstTypedefStmtOptRhs(node);
            PrintText(cp,"type ");
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
        case AST_VPATTERN_FIELD:
        case AST_VTUPLE_FIELD:
        case AST_TPATTERN_FIELD:
        case AST_VSTRUCT_FIELD:
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
            PrintText(cp,"fun ");
            int printCaptures = 0;
            if (printCaptures) {
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
                PrintChar(cp, ' ');
            }
            int patternCount = CountAstLambdaPatterns(node);
            for (int patternIndex = 0; patternIndex < patternCount; patternIndex++) {
                AstNode* pattern = GetAstLambdaPatternAt(node,patternIndex);
                PrintNode(cp,pattern);
                PrintChar(cp,' ');
            }
            PrintText(cp, "-> ");
            PrintNode(cp, GetAstLambdaBody(node));
            break;
        }
        case AST_TPATTERN:
        case AST_VPATTERN:
        {
            char ltChar = (kind == AST_TPATTERN ? '[':'(');
            char rtChar = (kind == AST_TPATTERN ? ']':')');
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
        case AST_TPATTERN_SINGLETON:
        case AST_VPATTERN_SINGLETON:
        {
            PrintText(cp,GetSymbolText(GetAstSingletonPatternName(node)));
            PrintChar(cp,':');
            PrintNode(cp,GetAstSingletonPatternRhs(node));
            // PrintText(cp,GetSymbolText())
            break;
        }
        case AST_VPAREN:
        case AST_TPAREN:
        {
            PrintText(cp, "(");
            PrintNode(cp, GetAstParenItem(node));
            PrintText(cp, ")");
            break;
        }
        case AST_VTUPLE:
        case AST_TTUPLE:
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
        case AST_VSTRUCT:
        {
            PrintChar(cp, '{');
            IndentPrinter(cp);
            PrintChar(cp, '\n');

            int structCount = CountAstStructFields(node);
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
        case AST_VLET:
        {
            PrintText(cp, "let ");
            PrintNode(cp, GetAstLetStmtLhs(node));
            PrintText(cp, " = ");
            PrintNode(cp, GetAstLetStmtRhs(node));
            break;
        }
        case AST_STMT_WITH:
        {
            PrintText(cp, "check(");
            PrintNode(cp, GetAstWithStmtChecked(node));
            // todo: print the check message here.
            PrintText(cp, ", ...)");
            break;
        }
        case AST_TCALL:
        case AST_VCALL:
        {
            PrintNode(cp, GetAstCallLhs(node));
            int isTemplate = IsAstCallTemplate(node);
            if (isTemplate) {
                PrintChar(cp,'[');
                int argCount = GetAstCallArgCount(node);
                for (int argIndex = 0; argIndex < argCount; argIndex++) {
                    AstNode* arg = GetAstCallArgAt(node,argIndex);
                    PrintNode(cp,arg);
                    if (argIndex+1 != argCount) {
                        PrintChar(cp,',');
                    }
                }
                PrintChar(cp,']');
            } else {
                int argCount = GetAstCallArgCount(node);
                for (int argIndex = 0; argIndex < argCount; argIndex++) {
                    AstNode* arg = GetAstCallArgAt(node,argIndex);
                    PrintChar(cp,' ');
                    PrintNode(cp,arg);
                }
            }
            break;
        }
        case AST_VCAST:
        {
            PrintNode(cp,GetAstVCastTypespec(node));
            PrintChar(cp,' ');
            PrintNode(cp,GetAstVCastRhs(node));
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