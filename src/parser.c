#include "parser.h"

#include <assert.h>
#include <stdio.h>

#include "config.h"
#include "lexer.h"

int const PARSER_LOOKAHEAD_COUNT = 2;
typedef struct Parser Parser;
typedef struct ParserLookahead ParserLookahead;
typedef int(*TokenKindPredicate)(TokenKind tokenKind);
struct ParserLookahead {
    TokenKind peekKind;
    TokenInfo peekInfo;
};
struct Parser {
    Source* source;
    ParserLookahead lookaheadBuffer[PARSER_LOOKAHEAD_COUNT];
};
static TokenKind lookaheadKind(Parser* p, int index);
static TokenInfo* lookaheadInfo(Parser* p, int index);
static void advance(Parser* p);
static int match(Parser* p, TokenKind tokenKind);
static int matchIf(Parser* p, TokenKindPredicate tokenKindPredicate);
static int expect(Parser* p, TokenKind tokenKind, char const* expectedDesc);
static int expectIf(Parser* p, TokenKindPredicate tokenKindPredicate, char const* expectedDesc);

typedef struct BinaryOpPrecedenceNode BinaryOpPrecedenceNode;
typedef struct BinaryOpPrecedenceNode BinaryOpPrecedenceList;
struct BinaryOpPrecedenceNode {
    BinaryOpPrecedenceNode* nextHighest;
    TokenKind tokenKind;
    AstBinaryOperator bop;
};
BinaryOpPrecedenceNode mulBinaryOpPrecedenceNode = {NULL, BOP_MUL};
BinaryOpPrecedenceNode divBinaryOpPrecedenceNode = {&mulBinaryOpPrecedenceNode, BOP_DIV};
BinaryOpPrecedenceNode remBinaryOpPrecedenceNode = {&divBinaryOpPrecedenceNode, BOP_REM};
BinaryOpPrecedenceNode addBinaryOpPrecedenceNode = {&remBinaryOpPrecedenceNode, BOP_ADD};
BinaryOpPrecedenceNode subBinaryOpPrecedenceNode = {&addBinaryOpPrecedenceNode, BOP_SUB};
BinaryOpPrecedenceNode lThanBinaryOpPrecedenceNode = {&subBinaryOpPrecedenceNode, BOP_LTHAN};
BinaryOpPrecedenceNode gThanBinaryOpPrecedenceNode = {&lThanBinaryOpPrecedenceNode, BOP_GTHAN};
BinaryOpPrecedenceNode leThanBinaryOpPrecedenceNode = {&gThanBinaryOpPrecedenceNode, BOP_LETHAN};
BinaryOpPrecedenceNode geThanBinaryOpPrecedenceNode = {&leThanBinaryOpPrecedenceNode, BOP_GETHAN};
BinaryOpPrecedenceNode andBinaryOpPrecedenceNode = {&geThanBinaryOpPrecedenceNode, BOP_AND};
BinaryOpPrecedenceNode xorBinaryOpPrecedenceNode = {&andBinaryOpPrecedenceNode, BOP_XOR};
BinaryOpPrecedenceNode orBinaryOpPrecedenceNode = {&xorBinaryOpPrecedenceNode, BOP_OR};
BinaryOpPrecedenceNode* binaryOpPrecedenceListHead = &orBinaryOpPrecedenceNode;

static AstNode* parseStmt(Parser* p);
static AstNode* parseBindStmt(Parser* p);
static AstNode* parseCheckStmt(Parser* p);

static AstNode* parseExpr(Parser* p);
static AstNode* tryParsePrimaryExpr(Parser* p);
static AstNode* tryParsePostfixExpr(Parser* p);
static AstNode* tryParsePostfixExprSuffix(Parser* p, AstNode* lhs, int* stopP);
static AstNode* tryParseUnaryExpr(Parser* p);
static AstNode* tryParseBinaryExprAtPrecedence(Parser* p, BinaryOpPrecedenceNode* highestPrecedenceNode);
static AstNode* tryParseBinaryExpr(Parser* p);
static AstNode* tryParseCallExpr(Parser* p);

static AstNode* parsePattern(Parser* p);
static void parsePatternElement(Parser* p, AstNode* pattern, int* okP);

//
// Implementation:
//

static TokenKind lookaheadKind(Parser* p, int index) {
    return p->lookaheadBuffer[index].peekKind;
}
static TokenInfo* lookaheadInfo(Parser* p, int index) {
    return &p->lookaheadBuffer[index].peekInfo;
}
static void advance(Parser* p) {
    // copying look-aheads backward:
    for (int index = 0; index < PARSER_LOOKAHEAD_COUNT - 1; index++) {
        p->lookaheadBuffer[index] = p->lookaheadBuffer[index+1];
    }
    // lexing the last token:
    ParserLookahead* lookaheadP = &p->lookaheadBuffer[PARSER_LOOKAHEAD_COUNT-1];
    lookaheadP->peekKind = LexOneToken(p->source, &lookaheadP->peekInfo);
}
static int match(Parser* p, TokenKind tokenKind) {
    if (lookaheadKind(p,0) == tokenKind) {
        advance(p);
        return 1;
    } else {
        return 0;
    }
}
static int matchIf(Parser* p, TokenKindPredicate tokenKindPredicate) {
    if (tokenKindPredicate(lookaheadKind(p,0))) {
        advance(p);
        return 1;
    } else {
        return 0;
    }
}
inline static void expectError(Parser* p, char const* expectedDesc) {
    // todo: send feedback here
    printf("... Before <?>, expected %s.\n", expectedDesc);
}
static int expect(Parser* p, TokenKind tokenKind, char const* expectedDesc) {
    if (match(p, tokenKind)) {
        return 1;
    } else {
        expectError(p, expectedDesc);
        return 0;
    }
}
static int expectIf(Parser* p, TokenKindPredicate tokenKindPredicate, char const* expectedDesc) {
    if (matchIf(p, tokenKindPredicate)) {
        return 1;
    } else {
        expectError(p, expectedDesc);
        return 0;
    }
}

static AstNode* parseStmt(Parser* p) {
    if (lookaheadKind(p,0) == TK_KW_CHECK) {
        parseCheckStmt(p);
    }
    if (lookaheadKind(p,0) == TK_ID && lookaheadKind(p,1) == TK_BIND) {
        parseBindStmt(p);
    }
    return NULL;
}

static AstNode* parseBindStmt(Parser* p) {
    Loc loc = lookaheadInfo(p, 0)->loc;
    
    TokenInfo* idTokenInfo = lookaheadInfo(p, 0);
    SymbolID lhs = SYM_NULL;
    AstNode* templatePattern = NULL;
    AstNode* rhs = NULL;

    if (expect(p, TK_ID, "the defined (lhs) identifier")) {
        lhs = idTokenInfo->as.ID;
    } else {
        return NULL;
    }
    if (lookaheadKind(p,0) == TK_LSQBRK) {
        templatePattern = parsePattern(p);
        if (!templatePattern) {
            // bad pattern
            return NULL;
        }
    }
    if (!expect(p, TK_BIND, "the '=' (bind) operator")) {
        return NULL;
    }
    rhs = parseExpr(p);
    if (!rhs) {
        // bad rhs
        return NULL;
    }

    return CreateAstBindStmt(loc, lhs, templatePattern, rhs);
}

static AstNode* parseCheckStmt(Parser* p) {
    Loc loc = lookaheadInfo(p,0)->loc;
    AstNode* checked;
    AstNode* message;
    if (!expect(p, TK_KW_CHECK, "the keyword 'check'")) {
        return NULL;
    }
    if (!expect(p, TK_LPAREN, "an opening '('")) {
        return NULL;
    }
    checked = parseExpr(p);
    if (!checked) {
        return NULL;
    }
    if (!expect(p, TK_COMMA, "',' then message")) {
        return NULL;
    }
    message = parseString(p);
    if (!message) {
        return NULL;
    }
    if (!expect(p, TK_RPAREN, "a closing ')'")) {
        return NULL;
    }
    return CreateAstCheckStmt(loc, checked, message);
}

static AstNode* parseExpr(Parser* p) {
    return tryParseCallExpr(p);
}
static AstNode* tryParsePrimaryExpr(Parser* p) {
    Loc loc; GetSourceReaderHeadLoc(p->source, &loc);
    switch (lookaheadKind(p,0)) {
        case TK_ID: 
        { 
            TokenInfo* idTokenInfo = lookaheadInfo(p, 0);
            if (expect(p, TK_ID, "a bound identifier")) {
                return CreateAstId(idTokenInfo->loc, idTokenInfo->as.ID);
            } else {
                return NULL;
            }
        }
        case TK_DINT_LIT: 
        case TK_XINT_LIT: 
        { 
            TokenInfo* intTokenInfo = lookaheadInfo(p, 0);
            if (match(p, TK_DINT_LIT) || match(p, TK_XINT_LIT)) {
                return CreateAstIntLiteral(intTokenInfo->loc, intTokenInfo->as.Int);
            } else {
                expectError(p, "an integer literal");
                return NULL;
            }
        }
        case TK_FLOAT_LIT: 
        { 
            TokenInfo* floatTokenInfo = lookaheadInfo(p, 0);
            if (expect(p, TK_FLOAT_LIT, "a float literal")) {
                return CreateAstFloatLiteral(floatTokenInfo->loc, floatTokenInfo->as.Float);
            } else {
                return NULL;
            }
        }
        case TK_DQSTRING_LIT:
        case TK_SQSTRING_LIT:
        { 
            TokenInfo* stringTokenInfo = lookaheadInfo(p, 0);
            if (match(p, TK_SQSTRING_LIT) || match(p, TK_DQSTRING_LIT)) {
                return CreateAstStringLiteral(stringTokenInfo->loc, stringTokenInfo->as.Utf8String);
            } else {
                expectError(p, "a string literal");
                return NULL;
            }
        }
        case TK_LPAREN:
        {
            // if one expr, then parenthesized.
            // if multiple comma-separated exprs, then tuple
            // todo: implement tuples and parenthesized exprs
        }
        case TK_LSQBRK: 
        { 
            AstNode* pattern = parsePattern(p);
            AstNode* body = parseExpr(p);
            return CreateAstLambda(GetAstNodeLoc(pattern), pattern, body);
        }
        case TK_LCYBRK: 
        {
            advance(p);

            // if label, then struct (aka namedtuple), else chain.
            if (lookaheadKind(p,0) == TK_ID && lookaheadKind(p,1) == TK_COLON) {
                // struct/namedtuple
                AstNode* structNode = CreateAstStruct(loc);
                for (;;) {
                    TokenInfo* labelInfo = lookaheadInfo(p,0);
                    if (expect(p, TK_ID, "a label")) {
                        if (expect(p, TK_COLON, "a label, followed by a colon")) {
                            AstNode* rhs = parseExpr(p);
                            PushFieldToAstStruct(loc, structNode, labelInfo->as.ID, rhs);
                        }
                    } else {
                        return NULL;
                    }
                    if (!match(p, TK_COMMA)) {
                        break;
                    }
                }
            } else {
                // chain
                AstNode* chainNode = CreateAstStruct(loc);
                
                // fixme: this is all wrong, need to handle result tails
                
                for (;;) {
                    AstNode* stmt = parseStmt(p);
                    if (stmt) {
                        PushStmtToAstChain(chainNode, stmt);
                    } else {
                        return NULL;
                    }
                    if (!match(p, TK_SEMICOLON)) {
                        break;
                    }
                }
                return chainNode;
            }

            if (!expect(p, TK_RCYBRK, "a closing '}'")) {
                return NULL;
            }
        }
        default: { return NULL; }
    }
}
static AstNode* tryParsePostfixExpr(Parser* p) {
    AstNode* lhs = tryParsePrimaryExpr(p);
    int stop = 0;
    while (lhs && !stop) {
        lhs = tryParsePostfixExprSuffix(p, lhs, &stop);
    }
    return lhs;
}
static AstNode* tryParsePostfixExprSuffix(Parser* p, AstNode* lhs, int* stopP) {
    *stopP = 0;
    if (match(p, TK_DOT)) {
        TokenInfo* dotSuffix = lookaheadInfo(p,0);
        if (match(p, TK_ID)) {
            return CreateAstDotName(GetAstNodeLoc(lhs), lhs, dotSuffix->as.ID);
        }
        if (match(p, TK_DINT_LIT) || match(p, TK_XINT_LIT)) {
            return CreateAstDotIndex(GetAstNodeLoc(lhs), lhs, dotSuffix->as.Int);
        }
    }
    *stopP = 1;
    return NULL;
}
static AstNode* tryParseUnaryExpr(Parser* p) {
    Loc loc; GetSourceReaderHeadLoc(p->source, &loc);
    AstUnaryOperator operator;
    if (match(p, TK_NOT)) {
        operator = UOP_NOT;
    } else if (match(p, TK_CARET)) {
        operator = UOP_GETREF;
    } else if (match(p, TK_ASTERISK)) {
        operator = UOP_DEREF;
    }
    AstNode* operand = tryParseUnaryExpr(p);
    return CreateAstUnary(loc, operator, operand);
}
static AstNode* tryParseBinaryExpr(Parser* p) {
    return tryParseBinaryExprAtPrecedence(p, binaryOpPrecedenceListHead);
}
static AstNode* tryParseBinaryExprAtPrecedence(Parser* p, BinaryOpPrecedenceNode* highestPrecedenceNode) {
    AstNode* lhs;
    if (highestPrecedenceNode->nextHighest) {
        lhs = tryParseBinaryExprAtPrecedence(p, highestPrecedenceNode->nextHighest);
    } else {
        lhs = tryParseUnaryExpr(p);
    }

    if (match(p, highestPrecedenceNode->tokenKind)) {
        AstNode* rhs = tryParseBinaryExprAtPrecedence(p, highestPrecedenceNode);
        return CreateAstBinary(GetAstNodeLoc(lhs), highestPrecedenceNode->bop, lhs, rhs);
    } else {
        return lhs;
    }
}
static AstNode* tryParseCallExpr(Parser* p) {
    AstNode* lhs = tryParseBinaryExpr(p);
    for (;;) {
        AstNode* rhs = tryParseBinaryExpr(p);
        if (rhs) {
            lhs = CreateAstCall(
                GetAstNodeLoc(lhs),
                lhs, rhs
            );
        } else {
            break;
        }
    }
    return lhs;
}

static AstNode* parsePattern(Parser* p) {
    Loc loc; GetSourceReaderHeadLoc(p->source, &loc);
    
    if (!expect(p, TK_LSQBRK, "an opening '[' (for a pattern)")) {
        return NULL;
    }
    
    int ok = 1;
    AstNode* pattern = CreateAstPattern(loc);
    for (;;) {
        parsePatternElement(p, pattern, &ok);
        if (!ok) {
            // bad pattern element
            return NULL;
        }
        if (!match(p, TK_COMMA)) {
            // end of comma-separated element sequence
            break;
        }
    }

    if (!expect(p, TK_RSQBRK, "a closing ']' (for a pattern)")) {
        return NULL;
    }
}
static void parsePatternElement(Parser* p, AstNode* pattern, int* okP) {
    Loc loc; GetSourceReaderHeadLoc(p, &loc);
    SymbolID bankedSymbols[MAX_IDS_PER_SHARED_FIELD];
    int bankedSymbolsCount;
    do {
        if (expect(p, TK_ID, "a pattern label")) {
            // bank this label
            TokenInfo* firstTokenInfo = lookaheadInfo(p,0);
            bankedSymbols[bankedSymbolsCount++] = firstTokenInfo->as.ID;
            if (DEBUG) {
                assert(bankedSymbolsCount < MAX_IDS_PER_SHARED_FIELD);
            }

            // push all banked fields we have if we have a ':' next
            if (match(p, TK_COLON)) {
                AstNode* rhs = parseExpr(p);
                for (int i = 0; i < bankedSymbolsCount; i++) {
                    PushFieldToAstPattern(loc, pattern, firstTokenInfo->as.ID, rhs);
                }
                return 1;
            }
        } else {
            // todo: feedback + error here.
            // eof before pattern ID.
            *okP = 0;
            return 0;
        }
    } while (match(p, TK_COMMA));
}

//
// API:
//

AstNode* ParseSource(Source* source) {
    // TODO: implement a source parser, delegating to the above.
    return NULL;
}
