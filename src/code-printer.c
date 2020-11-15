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
        // for (int tabIndex = 0; tabIndex < printer->indentCount; tabIndex++) {
        //     fputc('\t', printer->file);
        // }
        fputc('\t', printer->file);
    } else if (ch == '\n') {
        // printing tabs upto indent count:
        int spacesPerTab = 4;

        fputc('\n', printer->file);
        for (int tabIndex = 0; tabIndex < printer->indentCount; tabIndex++) {
            if (spacesPerTab > 0) {
                for (int spaceIndex = 0; spaceIndex < spacesPerTab; spaceIndex++) {
                    fputc(' ', printer->file);
                }
            } else {
                fputc('\t', printer->file);
            }
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
        case AST_SCRIPT:
        {
            int length = GetAstScriptLength(node);
            for (int index = 0; index < length; index++) {
                AstNode* module = GetAstScriptModuleAt(node, index);
                PrintNode(cp, module);
                PrintText(cp, ";\n");
            }
            break;
        }
        case AST_MODULE:
        {
            PrintText(cp, "mod ");
            PrintText(cp, GetSymbolText(GetAstModuleName(node)));
            PrintText(cp, " {");
            IndentPrinter(cp);
            PrintChar(cp, '\n');
            int length = GetAstModuleLength(node);
            for (int i = 0; i < length; i++) {
                PrintNode(cp, GetAstModuleStmtAt(node, i));
                if (i != length-1) {
                    PrintText(cp, ";\n");
                }
            }
            PrintChar(cp,';');
            DeIndentPrinter(cp);
            PrintChar(cp,'\n');
            PrintText(cp, "}");
            break;
        }
        case AST_UNIT:
        {
            PrintText(cp, "()");
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
            Utf8String string = GetAstStringLiteralValue(node);
            for (int index = 0; index < string.count; index++) {
                int ch = string.buf[index];
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
                } else if (ch == 0) {
                    PrintText(cp, "\\0");
                } else {
                    PrintChar(cp, (char)ch);
                }
            }
            PrintChar(cp, '"');
            break;
        }
        case AST_STMT_DISCARD:
        {
            PrintText(cp, "do ");
            PrintNode(cp, GetAstDiscardStmtDiscarded(node));
            break;
        }
        case AST_STMT_VDEF:
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
        case AST_STMT_TDEF:
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
        case AST_STMT_EXTERN:
        {
            SymbolID name = GetAstExternStmtName(node);
            AstNode* pattern = GetAstExternPattern(node);
            AstNode* typespec = GetAstExternTypespec(node);
            PrintText(cp, "extern ");
            PrintText(cp, GetSymbolText(name));
            PrintChar(cp, ' ');
            PrintNode(cp, pattern);
            PrintText(cp, " -> ");
            PrintNode(cp, typespec);
            break;
        }
        case AST_ORPHANED_FIELD:
        case AST_VPATTERN_FIELD:
        case AST_VTUPLE_FIELD:
        case AST_TPATTERN_FIELD:
        case AST_VSTRUCT_FIELD:
        case AST_VPATTERN_SINGLETON_FIELD:
        case AST_TPATTERN_SINGLETON_FIELD:
        {
            SymbolID lhs = GetAstFieldName(node);
            if (lhs != SYM_NULL) {
                PrintText(cp, GetSymbolText(lhs));
                PrintText(cp, " ");
            }
            AstNode* rhs = GetAstFieldRhs(node);
            if (rhs) {
                PrintNode(cp, rhs);
            }
            break;
        }
        case AST_VLAMBDA:
        {
            PrintText(cp,"fun ");
            int printCaptures = 0;
            if (printCaptures) {
                int captureCount = CountAstLambdaCaptures(node);
                PrintChar(cp, '{');
                for (int index = 0; index < captureCount; index++) {
                    DefnScope* captureDefn = GetAstVLambdaCaptureAt(node,index);
                    PrintText(cp,GetSymbolText(GetDefnName(captureDefn)));
                    if (index == captureCount-1) {
                        PrintChar(cp,',');
                    }
                }
                PrintChar(cp, '}');
                PrintChar(cp, ' ');
            }
            AstNode* pattern = GetAstVLambdaPattern(node);
            PrintNode(cp, pattern);
            PrintText(cp, " -> ");
            PrintNode(cp, GetAstVLambdaBody(node));
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
            AstNode* field = GetAstSingletonPatternField(node);
            PrintNode(cp,field);
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
                // PrintChar(cp, '\t');
                PrintNode(cp, stmt);
                PrintChar(cp, ';');
            }
            AstNode* result = GetAstChainResult(node);
            if (result) {
                PrintChar(cp, '\n');
                // PrintChar(cp, '\t');
                PrintNode(cp, result);
            }
            DeIndentPrinter(cp);
            PrintChar(cp, '\n');
            // PrintChar(cp, '\t');
            PrintChar(cp, '}');
            break;
        }
        case AST_STMT_VLET:
        {
            PrintText(cp, "let ");
            PrintNode(cp, GetAstLetStmtLhs(node));
            PrintText(cp, " = ");
            PrintNode(cp, GetAstLetStmtRhs(node));
            break;
        }
        case AST_STMT_ASSERT:
        {
            PrintText(cp, "assert (");
            PrintNode(cp, GetAstAssertStmtChecked(node));
            // todo: print the check message here.
            PrintText(cp, ", ...)");
            break;
        }
        case AST_TCALL:
        case AST_VCALL:
        {
            PrintNode(cp, GetAstCallLhs(node));
            int isTemplate = IsAstCallTemplate(node);
            char lpTk,rpTk;
            if (isTemplate) {
                lpTk = '['; rpTk = ']';
            } else {
                lpTk = '('; rpTk = ')';
            }
            PrintChar(cp,lpTk);
            int argCount = GetAstCallArgCount(node);
            for (int argIndex = 0; argIndex < argCount; argIndex++) {
                AstNode* arg = GetAstCallArgAt(node,argIndex);
                PrintNode(cp,arg);
                if (argIndex+1 != argCount) {
                    PrintChar(cp,',');
                }
            }
            PrintChar(cp,rpTk);
            break;
        }
        case AST_VCAST:
        {
            PrintNode(cp,GetAstVCastTypespec(node));
            PrintChar(cp,' ');
            PrintNode(cp,GetAstVCastRhs(node));
            break;
        }
        case AST_TYPE2VAL:
        {
            PrintNode(cp,GetAstType2ValTypespec(node));
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
            PrintNode(cp, GetAstDotNameLhs(node));
            PrintChar(cp, '.');
            PrintText(cp, GetSymbolText(GetAstDotNameRhs(node)));
            break;
        }
        case AST_COLON_NAME:
        {
            PrintNode(cp, GetAstColonNameLhs(node));
            PrintChar(cp, ':');
            PrintText(cp, GetSymbolText(GetAstColonNameRhs(node)));
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
        case AST_VPTR:
        {
            PrintText(cp, "^");
            PrintNode(cp, GetAstVPtrPointee(node));
            break;
        }
        case AST_TPTR:
        {
            PrintNode(cp, GetAstTPtrPointee(node));
            PrintText(cp, "^");
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