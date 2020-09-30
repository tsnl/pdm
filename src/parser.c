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
// static int matchIf(Parser* p, TokenKindPredicate tokenKindPredicate);
static int expect(Parser* p, TokenKind tokenKind, char const* expectedDesc);
// static int expectIf(Parser* p, TokenKindPredicate tokenKindPredicate, char const* expectedDesc);

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
BinaryOpPrecedenceNode equalsBinaryOpPrecedenceNode = {&geThanBinaryOpPrecedenceNode, TK_EQUALS, BOP_EQUALS};
BinaryOpPrecedenceNode notEqualsBinaryOpPrecedenceNode = {&equalsBinaryOpPrecedenceNode, TK_NEQUALS, BOP_NEQUALS};
BinaryOpPrecedenceNode andBinaryOpPrecedenceNode = {&notEqualsBinaryOpPrecedenceNode, TK_AND, BOP_AND};
BinaryOpPrecedenceNode xorBinaryOpPrecedenceNode = {&andBinaryOpPrecedenceNode, TK_CARET, BOP_XOR};
BinaryOpPrecedenceNode orBinaryOpPrecedenceNode = {&xorBinaryOpPrecedenceNode, TK_OR, BOP_OR};
BinaryOpPrecedenceNode* binaryOpPrecedenceListHead = &orBinaryOpPrecedenceNode;

// static RawAstNode* parseStmt(Parser* p);
static RawAstNode* tryParseStmt(Parser* p);
static RawAstNode* parseLetStmt(Parser* p);
static RawAstNode* parseDefStmt(Parser* p);
static RawAstNode* parseCheckStmt(Parser* p);

static RawAstNode* parseExpr(Parser* p);
static RawAstNode* tryParseExpr(Parser* p);
static RawAstNode* tryParsePrimaryExpr(Parser* p);
static RawAstNode* tryParsePostfixExpr(Parser* p);
static RawAstNode* tryParsePostfixExprSuffix(Parser* p, RawAstNode* lhs, int* stopP);
static RawAstNode* tryParseUnaryExpr(Parser* p);
static RawAstNode* tryParseBinaryExprAtPrecedence(Parser* p, BinaryOpPrecedenceNode* highestPrecedenceNode);
static RawAstNode* tryParseBinaryExpr(Parser* p);
static RawAstNode* tryParseCallExpr(Parser* p);

static RawAstNode* parsePattern(Parser* p, TokenKind lpTk, TokenKind rpTk, int hasTail);
static void parsePatternElement(Parser* p, RawAstNode* pattern, int* okP, int hasTail);
static void parsePatternElementWithTail(Parser* p, RawAstNode* pattern, int* okP);
static void parsePatternElementWithoutTail(Parser* p, RawAstNode* pattern, int* okP);

static RawAstNode* parseString(Parser* p);

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
    if (lookaheadKind(p,0) == TK_KW_CHECK) {
        return parseCheckStmt(p);
    }
    if (lookaheadKind(p,0) == TK_KW_LET) {
        return parseLetStmt(p);
    }
    return NULL;
}
RawAstNode* parseLetStmt(Parser* p) {
    Loc loc = lookaheadLoc(p,0);
    if (!expect(p, TK_KW_LET, "'let'")) {
        return NULL;
    }
    SymbolID lhs = SYM_NULL; {
        TokenInfo idTokenInfo = lookaheadInfo(p, 0);
        if (expect(p, TK_ID, "the defined (lhs) identifier")) {
            lhs = idTokenInfo.as.ID;
        } else {
            return NULL;
        }
    }
    AstNode* typespec = NULL; {
        if (match(p,TK_COLON)) {
            typespec = tryParsePrimaryExpr(p);
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
        if (!expect(p, TK_EQUALS, "the '=' (bind) operator")) {
            return NULL;
        }
        rhs = parseExpr(p);
        if (!rhs) {
            return NULL;
        }
    }
    return CreateAstLetStmt(loc,lhs,typespec,rhs);
}
RawAstNode* parseDefStmt(Parser* p) {
    Loc loc = lookaheadLoc(p,0);

    if (!expect(p, TK_KW_DEF, "'def'")) {
        return NULL;
    }

    SymbolID lhs = SYM_NULL; {
        TokenInfo idTokenInfo = lookaheadInfo(p,0);
        if (expect(p, TK_ID, "the defined (lhs) identifier")) {
            lhs = idTokenInfo.as.ID;
        } else {
            return NULL;
        }
    }

    AstNode* defStmt = CreateAstDefStmt(loc,lhs);

    while (lookaheadKind(p,0) != TK_EQUALS) {
        AstNode* pattern = NULL;
        if (lookaheadKind(p,0) == TK_LPAREN) {
            pattern = parsePattern(p, TK_LPAREN, TK_RPAREN,1);
        } else if (lookaheadKind(p,0) == TK_LSQBRK) {
            pattern = parsePattern(p, TK_LSQBRK, TK_RSQBRK,0);
        }
        if (pattern) {
            PushPatternToAstDefStmt(defStmt,pattern);
        }
    }
    
    RawAstNode* rhs = NULL; {
        if (!expect(p, TK_EQUALS, "the '=' (bind) operator")) {
            return NULL;
        }
        rhs = parseExpr(p);
        if (!rhs) {
            return NULL;
        }
    }
    SetAstDefStmtBody(defStmt,rhs);
    FinalizeAstDefStmt(defStmt);
    return defStmt;
}
RawAstNode* parseCheckStmt(Parser* p) {
    Loc loc = lookaheadLoc(p,0);
    RawAstNode* checked;
    RawAstNode* message;
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

RawAstNode* parseExpr(Parser* p) {
    Loc loc = lookaheadLoc(p,0);

    RawAstNode* expr = tryParseExpr(p);
    if (expr) {
        return expr;
    }

    FeedbackNote note = {
        .message = "here...",
        .loc = loc,
        .nextP = NULL
    };
    PostFeedback(FBK_ERROR, &note, "Expected an expression");
    return NULL;
}
RawAstNode* tryParseExpr(Parser* p) {
    return tryParseCallExpr(p);
}
RawAstNode* tryParsePrimaryExpr(Parser* p) {
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
                expr = CreateAstTuple(loc);

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
                expr = CreateAstParen(loc, expr);
            }

            if (!expect(p, TK_RPAREN, "a closing ')'")) {
                return NULL;
            }

            return expr;
        }
        case TK_DOLLAR: 
        {
            // todo: un-disable lambda statement
            int disabled = 1;
            if (disabled) {
                if (DEBUG) {
                    printf("!!- NotImplemented: lambda expression (in parser).\n");
                } else {
                    assert(0 && "NotImplemented: lambda expression (in parser).");
                }
                return NULL;
            }
                
            if (!expect(p,TK_DOLLAR,"'$'")) {
                return NULL;
            }

            RawAstNode* pattern = parsePattern(p,TK_LPAREN,TK_RPAREN,1);
            if (!pattern) {
                return NULL;
            }
            // if (!expect(p, TK_ARROW, "'->'")) {
            //     return NULL;
            // }
            RawAstNode* body = parseExpr(p);
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

            RawAstNode* result;
            if (lookaheadKind(p,0) == TK_ID && lookaheadKind(p,1) == TK_COLON) {
                // struct/namedtuple
                RawAstNode* structNode = CreateAstStruct(loc);
                for (;;) {
                    TokenInfo labelInfo = lookaheadInfo(p,0);
                    if (expect(p, TK_ID, "a label")) {
                        if (expect(p, TK_COLON, "a label's colon")) {
                            RawAstNode* rhs = parseExpr(p);
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
    RawAstNode* lhs = tryParseBinaryExpr(p);
    for (;;) {
        RawAstNode* rhs = tryParseBinaryExpr(p);
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

RawAstNode* parsePattern(Parser* p, TokenKind lpTk, TokenKind rpTk, int hasTail) {
    if (DEBUG) {
        assert(lpTk == TK_LPAREN || lpTk == TK_LSQBRK);
        assert(rpTk == TK_RPAREN || rpTk == TK_RSQBRK);
    }

    Loc loc = lookaheadLoc(p,0);
    
    if (!expect(p, lpTk, "an opening '[' or '(' (for a pattern)")) {
        return NULL;
    }
    
    int ok = 1;
    RawAstNode* pattern = CreateAstPattern(loc,lpTk==TK_LSQBRK);
    while (lookaheadKind(p,0) == TK_ID) {
        parsePatternElement(p, pattern, &ok, hasTail);
        if (!ok) {
            // bad pattern element
            return NULL;
        }
        if (!match(p, TK_COMMA)) {
            // end of comma-separated element sequence
            break;
        }
    }

    if (!expect(p, rpTk, "a closing ']' or ')' (for a pattern)")) {
        return NULL;
    }

    return pattern;
}
void parsePatternElement(Parser* p, RawAstNode* pattern, int* okP, int hasTail) {
    if (hasTail) {
        parsePatternElementWithTail(p, pattern, okP);
    } else {
        parsePatternElementWithoutTail(p, pattern, okP);
    }
}
void parsePatternElementWithTail(Parser* p, RawAstNode* pattern, int* okP) {
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

    // push all banked fields, read tail
    Loc rhsLoc = lookaheadLoc(p,0);
    RawAstNode* rhs = parseExpr(p);
    if (rhs) {
        for (int i = 0; i < bankedSymbolsCount; i++) {
            PushFieldToAstPattern(patternLoc, pattern, bankedSymbols[i], rhs);
        }
    } else {
        *okP = 0;
        FeedbackNote noteParent = {"in pattern...", patternLoc, NULL};
        FeedbackNote noteHere = {"here...", rhsLoc, &noteParent};
        PostFeedback(FBK_ERROR, &noteHere, "Expected a field RHS");
    }
}
void parsePatternElementWithoutTail(Parser* p, RawAstNode* pattern, int* okP) {
    // just 1 ID
    TokenInfo ti = lookaheadInfo(p,0);
    if (expect(p, TK_ID, "a pattern ID")) {
        PushFieldToAstPattern(ti.loc, pattern, ti.as.ID, NULL);
    } else {
        *okP = 0;
    }
}

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
        } else if (lookaheadKind(&p,0) == TK_KW_DEF) {
            RawAstNode* def = parseDefStmt(&p);
            if (!expect(&p,TK_SEMICOLON,"a terminating ';'")) {
                break;
            }
            PushAstDefStmtToAstModule(module,def);
        } else {
            FeedbackNote* note = CreateFeedbackNote("here...",loc,NULL);
            PostFeedback(FBK_ERROR,note,"Invalid module item");
            break;
        }
    }
    return module;
}

// GRAND PARSER TODO:
// - ite
// - match
