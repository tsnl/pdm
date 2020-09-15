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
static Parser createParser(Source* source);
static TokenKind lookaheadKind(Parser* p, int index);
static TokenInfo lookaheadInfo(Parser* p, int index);
static Loc lookaheadLoc(Parser* p, int index);
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
BinaryOpPrecedenceNode mulBinaryOpPrecedenceNode = {NULL, TK_ASTERISK, BOP_MUL};
BinaryOpPrecedenceNode divBinaryOpPrecedenceNode = {&mulBinaryOpPrecedenceNode, TK_FSLASH, BOP_DIV};
BinaryOpPrecedenceNode remBinaryOpPrecedenceNode = {&divBinaryOpPrecedenceNode, TK_PERCENT, BOP_REM};
BinaryOpPrecedenceNode addBinaryOpPrecedenceNode = {&remBinaryOpPrecedenceNode, TK_PLUS, BOP_ADD};
BinaryOpPrecedenceNode subBinaryOpPrecedenceNode = {&addBinaryOpPrecedenceNode, TK_MINUS, BOP_SUB};
BinaryOpPrecedenceNode lThanBinaryOpPrecedenceNode = {&subBinaryOpPrecedenceNode, TK_LTHAN, BOP_LTHAN};
BinaryOpPrecedenceNode gThanBinaryOpPrecedenceNode = {&lThanBinaryOpPrecedenceNode, TK_GTHAN, BOP_GTHAN};
BinaryOpPrecedenceNode leThanBinaryOpPrecedenceNode = {&gThanBinaryOpPrecedenceNode, TK_LETHAN, BOP_LETHAN};
BinaryOpPrecedenceNode geThanBinaryOpPrecedenceNode = {&leThanBinaryOpPrecedenceNode, TK_GETHAN, BOP_GETHAN};
BinaryOpPrecedenceNode andBinaryOpPrecedenceNode = {&geThanBinaryOpPrecedenceNode, TK_AND, BOP_AND};
BinaryOpPrecedenceNode xorBinaryOpPrecedenceNode = {&andBinaryOpPrecedenceNode, TK_CARET, BOP_XOR};
BinaryOpPrecedenceNode orBinaryOpPrecedenceNode = {&xorBinaryOpPrecedenceNode, TK_OR, BOP_OR};
BinaryOpPrecedenceNode* binaryOpPrecedenceListHead = &orBinaryOpPrecedenceNode;

static AstNode* parseStmt(Parser* p);
static AstNode* tryParseStmt(Parser* p);
static AstNode* parseBindStmt(Parser* p);
static AstNode* parseCheckStmt(Parser* p);

static AstNode* parseExpr(Parser* p);
static AstNode* tryParseExpr(Parser* p);
static AstNode* tryParsePrimaryExpr(Parser* p);
static AstNode* tryParsePostfixExpr(Parser* p);
static AstNode* tryParsePostfixExprSuffix(Parser* p, AstNode* lhs, int* stopP);
static AstNode* tryParseUnaryExpr(Parser* p);
static AstNode* tryParseBinaryExprAtPrecedence(Parser* p, BinaryOpPrecedenceNode* highestPrecedenceNode);
static AstNode* tryParseBinaryExpr(Parser* p);
static AstNode* tryParseCallExpr(Parser* p);

static AstNode* parsePattern(Parser* p);
static void parsePatternElement(Parser* p, AstNode* pattern, int* okP);

static AstNode* parseString(Parser* p);

//
// Implementation:
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
static int matchIf(Parser* p, TokenKindPredicate tokenKindPredicate) {
    if (tokenKindPredicate(lookaheadKind(p,0))) {
        advance(p);
        return 1;
    } else {
        return 0;
    }
}
inline static void expectError(Parser* p, char const* expectedDesc) {
    char errorText[512];
    TokenKind kind = lookaheadKind(p,0);
    TokenInfo info = lookaheadInfo(p,0);
    TokenToText(kind, &info, errorText, 512);
    
    FeedbackNote* note = CreateFeedbackNote("here...", p->source, info.loc, NULL);
    PostFeedback(FBK_ERROR, note, "Before '%s' expected %s.", errorText, expectedDesc);
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
    Loc loc = lookaheadLoc(p,0);

    AstNode* stmt = tryParseStmt(p);
    if (stmt) {
        return stmt;
    }

    FeedbackNote note = {
        .message = "here...",
        .sourceP = p->source,
        .loc = loc,
        .nextP = NULL
    };
    PostFeedback(FBK_ERROR, &note, "Expected a statement");
    return NULL;
}
static AstNode* tryParseStmt(Parser* p) {
    if (lookaheadKind(p,0) == TK_KW_CHECK) {
        return parseCheckStmt(p);
    }
    if (lookaheadKind(p,0) == TK_ID && lookaheadKind(p,1) == TK_BIND) {
        return parseBindStmt(p);
    }
    return NULL;
}
static AstNode* parseBindStmt(Parser* p) {
    Loc loc = lookaheadLoc(p,0);

    TokenInfo idTokenInfo = lookaheadInfo(p, 0);
    SymbolID lhs = SYM_NULL;
    AstNode* templatePattern = NULL;
    AstNode* rhs = NULL;

    if (expect(p, TK_ID, "the defined (lhs) identifier")) {
        lhs = idTokenInfo.as.ID;
    } else {
        return NULL;
    }
    if (!expect(p, TK_BIND, "the '=' (bind) operator")) {
        return NULL;
    }
    rhs = parseExpr(p);
    if (!rhs) {
        return NULL;
    }

    return CreateAstBindStmt(loc, lhs, rhs);
}
static AstNode* parseCheckStmt(Parser* p) {
    Loc loc = lookaheadLoc(p,0);
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
    Loc loc = lookaheadLoc(p,0);

    AstNode* expr = tryParseExpr(p);
    if (expr) {
        return expr;
    }

    FeedbackNote note = {
        .message = "here...",
        .sourceP = p->source,
        .loc = loc,
        .nextP = NULL
    };
    PostFeedback(FBK_ERROR, &note, "Expected an expression");
    return NULL;
}
static AstNode* tryParseExpr(Parser* p) {
    return tryParseCallExpr(p);
}
static AstNode* tryParsePrimaryExpr(Parser* p) {
    Loc loc = lookaheadLoc(p,0); 

    switch (lookaheadKind(p,0)) {
        case TK_ID: 
        { 
            TokenInfo idTokenInfo = lookaheadInfo(p, 0);
            if (expect(p, TK_ID, "a bound identifier")) {
                return CreateAstId(idTokenInfo.loc, idTokenInfo.as.ID);
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

            AstNode* expr = parseExpr(p);
            if (!expr) {
                return NULL;
            }

            if (match(p, TK_COMMA)) {
                // tuple
                AstNode* firstExpr = expr;
                expr = CreateAstTuple(loc);

                PushFieldToAstTuple(GetAstNodeLoc(firstExpr), expr, firstExpr);
                do {
                    AstNode* nextExpr = parseExpr(p);
                    if (!nextExpr) {
                        return NULL;
                    }
                    PushFieldToAstTuple(GetAstNodeLoc(nextExpr), expr, nextExpr);
                } while (match(p, TK_COMMA));
            } else {
                // paren
                expr = CreateAstParen(loc, expr);
            }

            if (!expect(p, TK_RPAREN, "a closing ')'")) {
                return NULL;
            }

            return expr;
        }
        case TK_LSQBRK: 
        { 
            AstNode* pattern = parsePattern(p);
            if (!pattern) {
                return NULL;
            }
            if (!expect(p, TK_ARROW, "'->'")) {
                return NULL;
            }
            AstNode* body = parseExpr(p);
            if (!body) {
                return NULL;
            }
            return CreateAstLambda(GetAstNodeLoc(pattern), pattern, body);
        }
        case TK_LCYBRK: 
        {
            if (!expect(p, TK_LCYBRK, "an opening '{'")) {
                return NULL;
            }

            AstNode* result;
            if (lookaheadKind(p,0) == TK_ID && lookaheadKind(p,1) == TK_COLON) {
                // struct/namedtuple
                AstNode* structNode = CreateAstStruct(loc);
                for (;;) {
                    TokenInfo labelInfo = lookaheadInfo(p,0);
                    if (expect(p, TK_ID, "a label")) {
                        if (expect(p, TK_COLON, "a label's colon")) {
                            AstNode* rhs = parseExpr(p);
                            if (!rhs) {
                                return NULL;
                            }
                            PushFieldToAstStruct(loc, structNode, labelInfo.as.ID, rhs);
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
                AstNode* chainNode = CreateAstChain(loc);
                AstNode* elementNode;

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
                            .sourceP = p->source,
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
        default: 
        { 
            return NULL; 
        }
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
        TokenInfo dotSuffix = lookaheadInfo(p,0);
        if (match(p, TK_ID)) {
            return CreateAstDotName(GetAstNodeLoc(lhs), lhs, dotSuffix.as.ID);
        }
        if (match(p, TK_DINT_LIT) || match(p, TK_XINT_LIT)) {
            return CreateAstDotIndex(GetAstNodeLoc(lhs), lhs, dotSuffix.as.Int);
        }
    }
    *stopP = 1;
    return lhs;
}
static AstNode* tryParseUnaryExpr(Parser* p) {
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
    Loc loc = lookaheadLoc(p,0);
    
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
    return pattern;
}
static void parsePatternElement(Parser* p, AstNode* pattern, int* okP) {
    Loc patternLoc = lookaheadLoc(p,0);
    SymbolID bankedSymbols[MAX_IDS_PER_SHARED_FIELD];
    int bankedSymbolsCount = 0;

    do {
        // label
        TokenInfo tokenInfo = lookaheadInfo(p,0);
        if (expect(p, TK_ID, "a pattern label")) {
            // bank this label
            bankedSymbols[bankedSymbolsCount++] = tokenInfo.as.ID;
            if (DEBUG) {
                assert(bankedSymbolsCount < MAX_IDS_PER_SHARED_FIELD);
            }
        }
        // colon?
        if (match(p, TK_COLON)) {
            break;
        }
    } while (match(p, TK_COMMA));

    // push all banked fields
    Loc rhsLoc = lookaheadLoc(p,0);
    AstNode* rhs = parseExpr(p);
    if (rhs) {
        for (int i = 0; i < bankedSymbolsCount; i++) {
            PushFieldToAstPattern(patternLoc, pattern, bankedSymbols[i], rhs);
        }
    } else {
        *okP = 0;
        FeedbackNote noteParent = {"in pattern...", p->source, patternLoc, NULL};
        FeedbackNote noteHere = {"here...", p->source, rhsLoc, &noteParent};
        PostFeedback(FBK_ERROR, &noteHere, "Expected a field RHS");
    }
}

AstNode* parseString(Parser* p) {
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

AstNode* ParseSource(Source* source) {
    Parser p = createParser(source);
    AstNode* module = CreateAstModule(lookaheadLoc(&p,0), SYM_NULL);    // todo: allow script name in syntax or remove from spec
    while (lookaheadKind(&p,0) != TK_EOS) {
        // todo: add support for import/export/params/etc...
        TokenInfo tokenInfo = lookaheadInfo(&p,0);
        if (match(&p, TK_ID)) {
            SymbolID lhsID = tokenInfo.as.ID;

            AstNode* templatePattern = NULL;
            if (lookaheadKind(&p,0) == TK_LSQBRK) {
                templatePattern = parsePattern(&p);
                if (!templatePattern) {
                    // bad pattern
                    return NULL;
                }
            }

            if (!expect(&p, TK_COLON, "a label's colon")) {
                return NULL;
            }
            
            AstNode* rhs = parseExpr(&p);
            if (!expect(&p, TK_SEMICOLON, "a terminating semicolon")) {
                return NULL;
            }

            PushFieldToAstModule(tokenInfo.loc, module, lhsID, templatePattern, rhs);
        } else {
            break;
        }
    }
    return module;
}

// GRAND PARSER TODO:
// - ite
// - match
