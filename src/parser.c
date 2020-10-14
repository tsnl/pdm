#include "parser.h"

#include <assert.h>
#include <stdio.h>

#include "stb/stretchy_buffer.h"

#include "config.h"
#include "useful.h"
#include "lexer.h"

#define PARSER_LOOKAHEAD_COUNT (2)

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
static Parser createParser(Source* source);
static TokenKind lookaheadKind(Parser* p, int index);
static TokenInfo lookaheadInfo(Parser* p, int index);
static Loc lookaheadLoc(Parser* p, int index);
static void advance(Parser* p);
static int match(Parser* p, TokenKind tokenKind);
// static int matchIf(Parser* p, TokenKindPredicate tokenKindPredicate);
static int expect(Parser* p, TokenKind tokenKind, char const* expectedDesc);
// static int expectIf(Parser* p, TokenKindPredicate tokenKindPredicate, char const* expectedDesc);

// binary operator data-structures:
typedef struct BinaryOpPrecedenceNode BinaryOpPrecedenceNode;
typedef struct BinaryOpPrecedenceNode BinaryOpPrecedenceList;
struct BinaryOpPrecedenceNode {
    BinaryOpPrecedenceNode* nextHighest;
    TokenKind tokenKind;
    AstBinaryOperator bop;
};
static BinaryOpPrecedenceNode mulBinaryOpPrecedenceNode = {NULL, TK_ASTERISK, BOP_MUL};
static BinaryOpPrecedenceNode divBinaryOpPrecedenceNode = {&mulBinaryOpPrecedenceNode, TK_FSLASH, BOP_DIV};
static BinaryOpPrecedenceNode remBinaryOpPrecedenceNode = {&divBinaryOpPrecedenceNode, TK_PERCENT, BOP_REM};
static BinaryOpPrecedenceNode addBinaryOpPrecedenceNode = {&remBinaryOpPrecedenceNode, TK_PLUS, BOP_ADD};
static BinaryOpPrecedenceNode subBinaryOpPrecedenceNode = {&addBinaryOpPrecedenceNode, TK_MINUS, BOP_SUB};
static BinaryOpPrecedenceNode lThanBinaryOpPrecedenceNode = {&subBinaryOpPrecedenceNode, TK_LTHAN, BOP_LTHAN};
static BinaryOpPrecedenceNode gThanBinaryOpPrecedenceNode = {&lThanBinaryOpPrecedenceNode, TK_GTHAN, BOP_GTHAN};
static BinaryOpPrecedenceNode leThanBinaryOpPrecedenceNode = {&gThanBinaryOpPrecedenceNode, TK_LETHAN, BOP_LETHAN};
static BinaryOpPrecedenceNode geThanBinaryOpPrecedenceNode = {&leThanBinaryOpPrecedenceNode, TK_GETHAN, BOP_GETHAN};
static BinaryOpPrecedenceNode equalsBinaryOpPrecedenceNode = {&geThanBinaryOpPrecedenceNode, TK_EQUALS, BOP_EQUALS};
static BinaryOpPrecedenceNode notEqualsBinaryOpPrecedenceNode = {&equalsBinaryOpPrecedenceNode, TK_NEQUALS, BOP_NEQUALS};
static BinaryOpPrecedenceNode andBinaryOpPrecedenceNode = {&notEqualsBinaryOpPrecedenceNode, TK_KW_AND, BOP_AND};
static BinaryOpPrecedenceNode xorBinaryOpPrecedenceNode = {&andBinaryOpPrecedenceNode, TK_CARET, BOP_XOR};
static BinaryOpPrecedenceNode orBinaryOpPrecedenceNode = {&xorBinaryOpPrecedenceNode, TK_KW_OR, BOP_OR};
static BinaryOpPrecedenceNode* binaryOpPrecedenceListHead = &orBinaryOpPrecedenceNode;

// stmts:
// static RawAstNode* parseStmt(Parser* p);
static RawAstNode* tryParseStmt(Parser* p);
static RawAstNode* parseLetStmt(Parser* p);
static RawAstNode* parseReturnStmt(Parser* p);
static RawAstNode* parseYieldStmt(Parser* p);
static RawAstNode* parseDefValueStmt(Parser* p);
static RawAstNode* parseExternStmt(Parser* p);
static RawAstNode* parseDefTypeStmt(Parser* p);
static RawAstNode* parseWithStmt(Parser* p);
// static RawAstNode* parseValStmt(Parser* p);

// exprs:
static int isFirstExprTokenKind(TokenKind kind);
static RawAstNode* parseExpr(Parser* p);
static RawAstNode* tryParseExpr(Parser* p);
static RawAstNode* tryParsePrimaryExpr(Parser* p);
static RawAstNode* tryParsePostfixExpr(Parser* p);
static RawAstNode* tryParsePostfixExprSuffix(Parser* p, RawAstNode* lhs, int* stopP);
static RawAstNode* tryParseUnaryExpr(Parser* p);
static RawAstNode* tryParseBinaryExprAtPrecedence(Parser* p, BinaryOpPrecedenceNode* highestPrecedenceNode);
static RawAstNode* tryParseBinaryExpr(Parser* p);
static RawAstNode* tryParseCallExpr(Parser* p);

// patterns:
static int isFirstValuePatternTokenKind(TokenKind kind);
static int isFirstTemplatePatternTokenKind(TokenKind kind);
static RawAstNode* helpParsePattern(Parser* p, int notTemplatePattern);
static RawAstNode* parseValuePattern(Parser* p);
static RawAstNode* parseTemplatePattern(Parser* p);
static void parsePatternElement(Parser* p, RawAstNode* pattern, int* okP, int hasTail, TokenKind idTokenKind);
static void parsePatternElementWithTail(Parser* p, RawAstNode* pattern, int* okP, TokenKind idTokenKind);
static void parsePatternElementWithoutTail(Parser* p, RawAstNode* pattern, int* okP, TokenKind idTokenKind);

// typespecs:
static int isFirstTypespecTokenKind(TokenKind kind);
static RawAstNode* parseTypespec(Parser* p);
static RawAstNode* tryParseTypespec(Parser* p);
static RawAstNode* tryParsePrimaryTypespec(Parser* p);
static RawAstNode* tryParsePostfixTypespec(Parser* p);

// shared string helpers:
static RawAstNode* parseString(Parser* p);


//
//
// Implementation:
//
//

static Parser createParser(Source* source) {
    Parser p;
    p.source = source;
    for (int i = 0; i < PARSER_LOOKAHEAD_COUNT; i++) {
        TokenKind kind = LexOneToken(source, &p.lookaheadBuffer[i].peekInfo);
        p.lookaheadBuffer[i].peekKind = kind;
        if (kind == TK_EOS || kind == TK_NULL) {
            break;
        }
    }
    return p;
}
static TokenKind lookaheadKind(Parser* p, int index) {
    return p->lookaheadBuffer[index].peekKind;
}
static TokenInfo lookaheadInfo(Parser* p, int index) {
    return p->lookaheadBuffer[index].peekInfo;
}
static Loc lookaheadLoc(Parser* p, int index) {
    return lookaheadInfo(p,index).loc;
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
// static int matchIf(Parser* p, TokenKindPredicate tokenKindPredicate) {
//     if (tokenKindPredicate(lookaheadKind(p,0))) {
//         advance(p);
//         return 1;
//     } else {
//         return 0;
//     }
// }
inline static void expectError(Parser* p, char const* expectedDesc) {
    char errorText[512];
    TokenKind kind = lookaheadKind(p,0);
    TokenInfo info = lookaheadInfo(p,0);
    TokenToText(kind, &info, errorText, 512);
    
    FeedbackNote* note = CreateFeedbackNote("here...", info.loc, NULL);
    PostFeedback(FBK_ERROR, note, "Before '%s' expected %s.", errorText, expectedDesc);
}
int expect(Parser* p, TokenKind tokenKind, char const* expectedDesc) {
    if (match(p, tokenKind)) {
        return 1;
    } else {
        expectError(p, expectedDesc);
        return 0;
    }
}
// int expectIf(Parser* p, TokenKindPredicate tokenKindPredicate, char const* expectedDesc) {
//     if (matchIf(p, tokenKindPredicate)) {
//         return 1;
//     } else {
//         expectError(p, expectedDesc);
//         return 0;
//     }
// }

// RawAstNode* parseStmt(Parser* p) {
//     Loc loc = lookaheadLoc(p,0);

//     RawAstNode* stmt = tryParseStmt(p);
//     if (stmt) {
//         return stmt;
//     }

//     FeedbackNote note = {
//         .message = "here...",
//         .loc = loc,
//         .nextP = NULL
//     };
//     PostFeedback(FBK_ERROR, &note, "Expected a statement");
//     return NULL;
// }
RawAstNode* tryParseStmt(Parser* p) {
    TokenKind tokenKind = lookaheadKind(p,0);
    switch (tokenKind) {
        case TK_KW_WITH:
        {
            return parseWithStmt(p);
        }
        case TK_VID:
        {
            return parseLetStmt(p);
        }
        case TK_KW_RETURN:
        {
            return parseReturnStmt(p);
        }
        case TK_KW_YIELD:
        {
            return parseYieldStmt(p);
        }
        default:
        {
            return NULL;
        }
    }
}
RawAstNode* parseLetStmt(Parser* p) {
    Loc loc = lookaheadLoc(p,0);

    SymbolID lhs = SYM_NULL; {
        TokenInfo idTokenInfo = lookaheadInfo(p,0);
        if (expect(p, TK_VID, "the defined (lhs) identifier")) {
            lhs = idTokenInfo.as.ID_symbolID;
        } else {
            return NULL;
        }
    }
    AstNode* typespec = NULL; {
        if (match(p,TK_COLON)) {
            typespec = parseTypespec(p);
            if (!typespec) {
                FeedbackNote* note = CreateFeedbackNote("here...",loc,NULL);
                PostFeedback(
                    FBK_ERROR, note,
                    "Invalid let-typespec"
                );
                return NULL;
            }
        }
    }
    RawAstNode* rhs = NULL; {
        if (!expect(p, TK_BIND, "the '=' (bind) operator")) {
            return NULL;
        }
        rhs = parseExpr(p);
        if (!rhs) {
            return NULL;
        }
    }
    return CreateAstLetStmt(loc,lhs,typespec,rhs);
}
RawAstNode* parseReturnStmt(Parser* p) {
    // todo: implement `parseReturnStmt`
    if (DEBUG) {
        printf("!!- NotImplemented: parseReturnStmt\n");
    } else {
        assert(0 && "NotImplemented: parseReturnStmt");
    }
    return NULL;
}
RawAstNode* parseYieldStmt(Parser* p) {
    // todo: implement `parseReturnStmt`
    if (DEBUG) {
        printf("!!- NotImplemented: parseYieldStmt\n");
    } else {
        assert(0 && "NotImplemented: parseYieldStmt");
    }
    return NULL;
}
RawAstNode* parseDefValueStmt(Parser* p) {
    Loc loc = lookaheadLoc(p,0);

    // parsing an ID
    SymbolID lhs = SYM_NULL; {
        TokenInfo idTokenInfo = lookaheadInfo(p,0);
        if (expect(p, TK_VID, "the defined (lhs) identifier")) {
            lhs = idTokenInfo.as.ID_symbolID;
        } else {
            return NULL;
        }
    }

    // parsing an optional template pattern
    AstNode* optTemplatePattern = NULL;
    if (isFirstTemplatePatternTokenKind(lookaheadKind(p,0))) {
        optTemplatePattern = parseTemplatePattern(p);
    }
    
    RawAstNode** patternsSB = NULL;
    while (lookaheadKind(p,0) != TK_BIND) {
        RawAstNode* pattern = NULL;
        if (isFirstValuePatternTokenKind(lookaheadKind(p,0))) {
            pattern = parseValuePattern(p);
            if (pattern) {
                // PushPatternToAstDefStmt(defStmt,pattern);
                sb_push(patternsSB, pattern);
            } else {
                if (DEBUG) {
                    printf("!!- Skipping pattern addition (index=%d)", sb_count(patternsSB));
                } else {
                    assert(0 && "Skipping pattern addition");
                }
            }
        } else {
            FeedbackNote* note = CreateFeedbackNote("see definition here...",loc,NULL);
            PostFeedback(FBK_ERROR,note,"Unexpected/invalid pattern in definition: '%s'", GetSymbolText(lhs));
            return NULL;
        }
    }
    
    RawAstNode* rhs = NULL; {
        if (!expect(p, TK_BIND, "the '=' (bind) operator")) {
            return NULL;
        }
        rhs = parseExpr(p);
        if (!rhs) {
            return NULL;
        }
    }
    RawAstNode** patterns = patternsSB;
    int patternsCount = sb_count(patterns);
    RawAstNode* defStmt = CreateAstDefValueStmt(loc,lhs,optTemplatePattern,patterns,patternsCount,rhs);
    sb_free(patternsSB);
    return defStmt;
}
RawAstNode* parseExternStmt(Parser* p) {
    Loc loc = lookaheadLoc(p,0);
    if (!expect(p,TK_KW_EXTERN,"'extern'")) { return NULL; }
    
    TokenInfo idTokenInfo = lookaheadInfo(p,0);
    if (!expect(p,TK_VID,"an extern ID")) { return NULL; }
    SymbolID name = idTokenInfo.as.ID_symbolID;

    if (!expect(p,TK_COLON,"':' followed by a type specifier")) { return NULL; }
    RawAstNode* typespec = parseExpr(p);
    
    RawAstNode* externNode = CreateAstExternStmt(loc,name,typespec);
    return externNode;
}
RawAstNode* parseDefTypeStmt(Parser* p) {
    Loc loc = lookaheadLoc(p,0);
    
    TokenInfo idTokenInfo = lookaheadInfo(p,0);
    if (!expect(p,TK_TID,"a typedef ID")) { return NULL; }
    SymbolID name = idTokenInfo.as.ID_symbolID;

    AstNode* optPattern = NULL;
    if (isFirstTemplatePatternTokenKind(lookaheadKind(p,0))) {
        optPattern = parseTemplatePattern(p);
    }

    if (!expect(p,TK_BIND,"'='")) { return NULL; }

    AstNode* optRhs = NULL;
    if (match(p,TK_BIND)) {
        optRhs = parseExpr(p);
    }

    return CreateAstDefTypeStmt(loc,name,optPattern,optRhs);
}
RawAstNode* parseWithStmt(Parser* p) {
    Loc loc = lookaheadLoc(p,0);
    RawAstNode* checked;
    if (!expect(p, TK_KW_WITH, "'with'")) {
        return NULL;
    }
    checked = parseExpr(p);
    if (!checked) {
        return NULL;
    }
    return CreateAstWithStmt(loc, checked);
}

int isFirstExprTokenKind(TokenKind kind) {
    return (
        kind == TK_VID ||
        kind == TK_SQSTRING_LIT ||
        kind == TK_DQSTRING_LIT ||
        kind == TK_DINT_LIT ||
        kind == TK_XINT_LIT ||
        kind == TK_FLOAT_LIT ||
        kind == TK_PLUS ||
        kind == TK_MINUS ||
        kind == TK_NOT ||
        kind == TK_CARET ||
        kind == TK_ASTERISK ||
        kind == TK_KW_FUN ||
        kind == TK_KW_IF ||
        kind == TK_KW_MATCH ||
        kind == TK_LPAREN ||
        kind == TK_LCYBRK ||
        0
    );
}
RawAstNode* parseExpr(Parser* p) {
    Loc loc = lookaheadLoc(p,0);

    if (isFirstExprTokenKind(lookaheadKind(p,0))) {
        RawAstNode* expr = tryParseExpr(p);
        return expr;
    } else {    
        FeedbackNote note = {
            .message = "here...",
            .loc = loc,
            .nextP = NULL
        };
        PostFeedback(FBK_ERROR, &note, "Expected an expression");
        return NULL;
    }
}
RawAstNode* tryParseExpr(Parser* p) {
    return tryParseCallExpr(p);
}
RawAstNode* tryParsePrimaryExpr(Parser* p) {
    Loc loc = lookaheadLoc(p,0); 

    switch (lookaheadKind(p,0)) {
        case TK_VID:
        { 
            TokenInfo idTokenInfo = lookaheadInfo(p, 0);
            if (expect(p, TK_VID, "a bound value identifier")) {
                return CreateAstVID(idTokenInfo.loc, idTokenInfo.as.ID_symbolID);
            } else {
                return NULL;
            }
        }
        case TK_DINT_LIT: 
        case TK_XINT_LIT: 
        { 
            TokenInfo intTokenInfo = lookaheadInfo(p, 0);
            if (match(p, TK_DINT_LIT)) {
                return CreateAstIntLiteral(intTokenInfo.loc, intTokenInfo.as.Int, 10);
            } else if (match(p, TK_XINT_LIT)) {
                return CreateAstIntLiteral(intTokenInfo.loc, intTokenInfo.as.Int, 16);
            } else {
                expectError(p, "an integer literal");
                return NULL;
            }
        }
        case TK_FLOAT_LIT: 
        { 
            TokenInfo floatTokenInfo = lookaheadInfo(p, 0);
            if (expect(p, TK_FLOAT_LIT, "a float literal")) {
                return CreateAstFloatLiteral(floatTokenInfo.loc, floatTokenInfo.as.Float);
            } else {
                return NULL;
            }
        }
        case TK_DQSTRING_LIT:
        case TK_SQSTRING_LIT:
        { 
            return parseString(p);
        }
        case TK_LPAREN:
        {
            if (!expect(p, TK_LPAREN, "an opening '('")) {
                return NULL;
            }

            if (match(p, TK_RPAREN)) {
                return CreateAstUnit(loc);
            }

            RawAstNode* expr = parseExpr(p);
            if (!expr) {
                return NULL;
            }

            if (match(p, TK_COMMA)) {
                // tuple
                RawAstNode* firstExpr = expr;
                expr = CreateAstVTuple(loc);

                PushFieldToAstTuple(GetAstNodeLoc(firstExpr), expr, firstExpr);
                do {
                    RawAstNode* nextExpr = parseExpr(p);
                    if (!nextExpr) {
                        return NULL;
                    }
                    PushFieldToAstTuple(GetAstNodeLoc(nextExpr), expr, nextExpr);
                } while (match(p, TK_COMMA));
            } else {
                // paren
                expr = CreateAstVParen(loc, expr);
            }

            if (!expect(p, TK_RPAREN, "a closing ')'")) {
                return NULL;
            }

            return expr;
        }
        case TK_LCYBRK: 
        {
            if (!expect(p, TK_LCYBRK, "an opening '{'")) {
                return NULL;
            }

            RawAstNode* result;
            if (lookaheadKind(p,0) == TK_VID && lookaheadKind(p,1) == TK_COLON) {
                // struct/namedtuple
                RawAstNode* structNode = CreateAstStruct(loc);
                for (;;) {
                    TokenInfo labelInfo = lookaheadInfo(p,0);
                    if (expect(p, TK_VID, "a label")) {
                        if (expect(p, TK_COLON, "a label's colon")) {
                            RawAstNode* rhs = parseExpr(p);
                            if (!rhs) {
                                return NULL;
                            }
                            PushFieldToAstStruct(loc, structNode, labelInfo.as.ID_symbolID, rhs);
                        }
                    } else {
                        return NULL;
                    }
                    if (!match(p, TK_COMMA)) {
                        break;
                    }
                }
                result = structNode;
            } else {
                // chain
                RawAstNode* chainNode = CreateAstChain(loc);
                RawAstNode* elementNode;

                for (;;) {
                    // if <statement> ';', continue
                    elementNode = tryParseStmt(p);
                    if (elementNode) {
                        PushStmtToAstChain(chainNode, elementNode);
                        if (!expect(p, TK_SEMICOLON, "a ';' separator")) {
                            goto fatal_error;
                        }
                        continue;
                    }

                    // else optional <expr>, break
                    elementNode = tryParseExpr(p);
                    if (elementNode) {
                        SetAstChainResult(chainNode, elementNode);
                    } else {
                        SetAstChainResult(chainNode, NULL);
                    }
                    break;

                    // error
                    fatal_error: {
                        FeedbackNote note = {
                            .message = "chain here...",
                            .loc = loc,
                            .nextP = NULL
                        };
                        PostFeedback(FBK_ERROR, &note, "invalid chain");
                        break;
                    }
                }
                result = chainNode;
            }

            if (!expect(p, TK_RCYBRK, "a closing '}'")) {
                return NULL;
            }

            return result;
        }
        case TK_KW_FUN: 
        {
            if (!expect(p,TK_KW_FUN,"'fun'")) {
                return NULL;
            }
            RawAstNode* pattern = parseValuePattern(p);
            if (!expect(p, TK_ARROW, "'->'")) {
                return NULL;
            }
            RawAstNode* body = parseExpr(p);
            if (!body) {
                return NULL;
            }
            return CreateAstLambda(GetAstNodeLoc(pattern), pattern, body);
        }
        case TK_KW_IF:
        {
            if (!expect(p, TK_KW_IF, "'if'")) {
                return NULL;
            }

            RawAstNode* cond = parseExpr(p);
            
            if (!expect(p,TK_KW_THEN,"'then'")) {
                return NULL;
            }
            RawAstNode* ifTrue = parseExpr(p);
            
            RawAstNode* ifFalse = NULL;
            if (match(p,TK_KW_ELSE)) {
                ifFalse = parseExpr(p);
            }
            
            return CreateAstIte(loc,cond,ifTrue,ifFalse);
        }
    
        //
        // Checking for a cast expression:
        //

        case TK_TID:
        {
            COMPILER_ERROR("NotImplemented: cast expressions");
            return NULL;
        }

        default: 
        { 
            return NULL; 
        }
    }
}
RawAstNode* tryParsePostfixExpr(Parser* p) {
    RawAstNode* lhs = tryParsePrimaryExpr(p);
    int stop = 0;
    while (lhs && !stop) {
        lhs = tryParsePostfixExprSuffix(p, lhs, &stop);
    }
    return lhs;
}
RawAstNode* tryParsePostfixExprSuffix(Parser* p, RawAstNode* lhs, int* stopP) {
    *stopP = 0;
    Loc loc = GetAstNodeLoc(lhs);
    if (match(p, TK_DOT)) {
        TokenInfo dotSuffix = lookaheadInfo(p,0);
        if (match(p, TK_VID)) {
            return CreateAstDotName(loc, lhs, dotSuffix.as.ID_symbolID);
        }
        if (match(p, TK_DINT_LIT) || match(p, TK_XINT_LIT)) {
            return CreateAstDotIndex(GetAstNodeLoc(lhs), lhs, dotSuffix.as.Int);
        }
    }
    *stopP = 1;
    return lhs;
}
RawAstNode* tryParseUnaryExpr(Parser* p) {
    Loc loc = lookaheadLoc(p,0);
    AstUnaryOperator operator;
    if (match(p, TK_NOT)) {
        operator = UOP_NOT;
    } else if (match(p, TK_CARET)) {
        operator = UOP_GETREF;
    } else if (match(p, TK_ASTERISK)) {
        operator = UOP_DEREF;
    } else if (match(p, TK_MINUS)) {
        operator = UOP_MINUS;
    } else if (match(p, TK_PLUS)) {
        operator = UOP_PLUS;
    } else {
        return tryParsePostfixExpr(p);
    }
    RawAstNode* operand = tryParseUnaryExpr(p);
    return CreateAstUnary(loc, operator, operand);
}
RawAstNode* tryParseBinaryExpr(Parser* p) {
    return tryParseBinaryExprAtPrecedence(p, binaryOpPrecedenceListHead);
}
RawAstNode* tryParseBinaryExprAtPrecedence(Parser* p, BinaryOpPrecedenceNode* highestPrecedenceNode) {
    RawAstNode* lhs;
    if (highestPrecedenceNode->nextHighest) {
        lhs = tryParseBinaryExprAtPrecedence(p, highestPrecedenceNode->nextHighest);
    } else {
        lhs = tryParseUnaryExpr(p);
    }
    if (lhs) {
        if (match(p, highestPrecedenceNode->tokenKind)) {
            RawAstNode* rhs = tryParseBinaryExprAtPrecedence(p, highestPrecedenceNode);
            return CreateAstBinary(GetAstNodeLoc(lhs), highestPrecedenceNode->bop, lhs, rhs);
        }
    }
    return lhs;
}
RawAstNode* tryParseCallExpr(Parser* p) {
    Loc loc = lookaheadLoc(p,0);

    RawAstNode** nodesSB = NULL;
    while (isFirstExprTokenKind(lookaheadKind(p,0))) {
        RawAstNode* arg = tryParseBinaryExpr(p);
        sb_push(nodesSB,arg);
    }

    int nodesCount = sb_count(nodesSB);
    
    RawAstNode* result;
    if (nodesCount == 0) {
        result = NULL;
    } else if (nodesCount == 1) {
        result = nodesSB[0];
    } else {
        result = CreateAstVCall(loc,nodesSB[0],nodesSB+1,nodesCount-1);
    }

    sb_free(nodesSB);
    return result;
}

int isFirstValuePatternTokenKind(TokenKind kind) {
    return kind == TK_VID || kind == TK_LPAREN;
}
int isFirstTemplatePatternTokenKind(TokenKind kind) {
    return kind == TK_TID || kind == TK_LSQBRK;
}
RawAstNode* parseValuePattern(Parser* p) {
    return helpParsePattern(p,1);
}
RawAstNode* parseTemplatePattern(Parser* p) {
    return helpParsePattern(p,0);
}
RawAstNode* helpParsePattern(Parser* p, int notTemplatePattern) {
    // by design, [...] means a type param, (...) means a value param.
    TokenKind lpTk,rpTk;
    TokenKind idTokenKind;
    char const* lpTkExpectMessage;
    char const* rpTkExpectMessage;
    if (notTemplatePattern) {
        lpTk = TK_LPAREN;
        rpTk = TK_RPAREN;
        lpTkExpectMessage = "an opening '('";
        rpTkExpectMessage = "a closing ')'";
        idTokenKind = TK_VID;
    } else {
        lpTk = TK_LSQBRK;
        rpTk = TK_RSQBRK;
        lpTkExpectMessage = "an opening '['";
        rpTkExpectMessage = "a closing ']'";
        idTokenKind = TK_TID;
    }

    // acquiring the location of the first token:
    Loc loc = lookaheadLoc(p,0);
    
    int isTemplatePattern = (!notTemplatePattern);
    RawAstNode* pattern = CreateAstPattern(loc,isTemplatePattern);

    if (match(p, lpTk)) {
        // (items...)
        int ok = 1;
        while (lookaheadKind(p,0) == idTokenKind) {
            parsePatternElement(p, pattern, &ok, notTemplatePattern, idTokenKind);
            if (!ok) {
                // bad pattern element
                return NULL;
            }
            if (!match(p, TK_COMMA)) {
                // end of comma-separated element sequence
                break;
            }
        }

        if (!expect(p, rpTk, rpTkExpectMessage)) {
            return NULL;
        }   
    } else {
        // item:T
        COMPILER_ERROR("NotImplemented: single-item patterns.\n");
    }

    return pattern;
}
void parsePatternElement(Parser* p, RawAstNode* pattern, int* okP, int hasTail, TokenKind idTokenKind) {
    if (hasTail) {
        parsePatternElementWithTail(p, pattern, okP, idTokenKind);
    } else {
        parsePatternElementWithoutTail(p, pattern, okP, idTokenKind);
    }
}
void parsePatternElementWithTail(Parser* p, RawAstNode* pattern, int* okP, TokenKind idTokenKind) {
    *okP = 1;
    Loc patternLoc = lookaheadLoc(p,0);
    
    SymbolID symbolID = lookaheadInfo(p,0).as.ID_symbolID;
    if (expect(p,idTokenKind,"a pattern label")) {
        if (expect(p,TK_COLON,"':'")) {
            RawAstNode* typespec = parseTypespec(p);
            PushFieldToAstPattern(patternLoc, pattern, symbolID, typespec);
        }    
    }
    *okP = 0;
}
void parsePatternElementWithoutTail(Parser* p, RawAstNode* pattern, int* okP, TokenKind idTokenKind) {
    // just 1 ID
    TokenInfo ti = lookaheadInfo(p,0);
    if (expect(p, idTokenKind, "a pattern ID")) {
        PushFieldToAstPattern(ti.loc, pattern, ti.as.ID_symbolID, NULL);
    } else {
        *okP = 0;
    }
}

//
// Typespecs:
//

int isFirstTypespecTokenKind(TokenKind kind) {
    return (
        kind == TK_TID ||
        kind == TK_LPAREN ||
        kind == TK_KW_STRUCT ||
        kind == TK_KW_ENUM ||
        0
    );
}
RawAstNode* parseTypespec(Parser* p) {
    Loc loc = lookaheadLoc(p,0);
    if (isFirstTypespecTokenKind(lookaheadKind(p,0))) {
        RawAstNode* typespec = tryParseTypespec(p);
        return typespec;
    } else {    
        FeedbackNote note = {
            .message = "here...",
            .loc = loc,
            .nextP = NULL
        };
        PostFeedback(FBK_ERROR, &note, "Expected a typespec");
        return NULL;
    }
}
RawAstNode* tryParseTypespec(Parser* p) {
    return tryParsePostfixTypespec(p);
}
RawAstNode* tryParsePrimaryTypespec(Parser* p) {
    TokenKind firstKind = lookaheadKind(p,0);
    TokenInfo firstInfo = lookaheadInfo(p,0);
    if (match(p,TK_TID)) {
        return NewAstTID(firstInfo.loc,firstInfo.as.ID_symbolID);
    }
    else if (match(p,TK_LPAREN)) {
        RawAstNode* firstNestedTypespec = tryParseTypespec(p);
        if (firstNestedTypespec) {
            RawAstNode* result;
            if (match(p,TK_COMMA)) {
                result = NewAstTTuple(firstInfo.loc);
                PushFieldToAstTuple(GetAstNodeLoc(firstNestedTypespec),result,firstNestedTypespec);
                do {
                    RawAstNode* nestedTypespecItem = parseTypespec(p);
                    if (nestedTypespecItem) {
                        PushFieldToAstTuple(GetAstNodeLoc(nestedTypespecItem),result,nestedTypespecItem);
                    } else {
                        return NULL;
                    }
                } while (match(p,TK_COMMA));
            } else {
                result = NewAstTParen(firstInfo.loc,firstNestedTypespec);
            }
            if (!expect(p,TK_RPAREN,"')'")) {
                return NULL;
            }
            return result;
        } else {
            return NULL;
        }
    }
    else if (match(p,TK_KW_STRUCT) || match(p,TK_KW_ENUM)) {
        if (DEBUG) {
            printf("!!- NotImplemented: 'struct' and 'enum' typespecs.\n");
        }
    }
    return NULL;
}
RawAstNode* tryParsePostfixTypespec(Parser* p) {
    RawAstNode* lhs = tryParsePrimaryExpr(p);
    while (match(p,TK_LSQBRK)) {
        RawAstNode** argsSB = NULL; {
            while (isFirstTypespecTokenKind(lookaheadKind(p,0))) {
                RawAstNode* arg = tryParseTypespec(p);
                if (arg == NULL) {
                    return NULL;
                } else {
                    sb_push(argsSB,arg);
                }
            }
        }

        // updating LHS:
        lhs = CreateAstTCall(GetAstNodeLoc(lhs),lhs,argsSB,sb_count(argsSB));
        sb_free(argsSB);

        if (!expect(p,TK_RSQBRK,"']'")) {
            return NULL;
        }
    }
    return lhs;
}

//
// Shared:
//

RawAstNode* parseString(Parser* p) {
    TokenInfo stringTokenInfo = lookaheadInfo(p, 0);
    if (match(p, TK_SQSTRING_LIT) || match(p, TK_DQSTRING_LIT)) {
        return CreateAstStringLiteral(stringTokenInfo.loc, stringTokenInfo.as.UnicodeStringSb);
    } else {
        expectError(p, "a string literal");
        return NULL;
    }
}

//
// API:
//

RawAstNode* ParseSource(Source* source) {
    Parser p = createParser(source);
    RawAstNode* module = CreateAstModule(lookaheadLoc(&p,0), SYM_NULL);    // todo: allow script name in syntax or remove from spec
    while (lookaheadKind(&p,0) != TK_EOS) {
        // todo: add support for import/export/params/etc...
        Loc loc = lookaheadLoc(&p,0);
        if (match(&p,TK_SEMICOLON)) {
            // no-op
        } else {
            if (lookaheadKind(&p,0) == TK_VID) {
                RawAstNode* def = parseDefValueStmt(&p);
                PushStmtToAstModule(module,def);
            } else if (lookaheadKind(&p,0) == TK_TID) {
                RawAstNode* td = parseDefTypeStmt(&p);
                PushStmtToAstModule(module,td);
            } else if (lookaheadKind(&p,0) == TK_KW_EXTERN) {
                RawAstNode* def = parseExternStmt(&p);
                PushStmtToAstModule(module,def);
            } else {
                FeedbackNote* note = CreateFeedbackNote("here...",loc,NULL);
                PostFeedback(FBK_ERROR,note,"Invalid module item");
                break;
            }

            if (!expect(&p,TK_SEMICOLON,"a terminating ';'")) {
                break;
            }
        }
    }
    return module;
}

// GRAND PARSER TODO:
// - match
