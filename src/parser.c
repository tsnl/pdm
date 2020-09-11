#include "parser.h"

#include <stdio.h>
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
static AstNode* tryParseBinaryExpr(Parser* p, BinaryOpPrecedenceNode* highestPrecedenceNode);

static AstNode* parseList(Parser* p);
static AstNode* parseStruct(Parser* p);
static AstNode* parsePattern(Parser* p);
static AstNode* parseChain(Parser* p);
static AstNode* parseIte(Parser* p);
static AstNode* parseDotIndex(Parser* p);
static AstNode* parseDotName(Parser* p);
static AstNode* parseLambda(Parser* p);
static AstNode* parseID(Parser* p);
static AstNode* parseInt(Parser* p);
static AstNode* parseFloat(Parser* p);
static AstNode* parseString(Parser* p);
static AstNode* parseLambda(Parser* p);
static AstNode* parseTemplateCall(Parser* p);
static AstNode* parseValueCall(Parser* p);

static AstNode* CreateAstId(Loc loc, SymbolID symbolID);
static AstNode* CreateAstIntLiteral(Loc loc, size_t value);
static AstNode* CreateAstFloatLiteral(Loc loc, long double value);
static AstNode* CreateAstStringLiteral(Loc loc, char* value);

static AstNode* CreateAstList(Loc loc);
static AstNode* CreateAstStruct(Loc loc);
static AstNode* CreateAstChain(Loc loc);
static AstNode* CreateAstPattern(Loc loc);

static int PushItemToAstList(AstNode* slice, AstNode* pushed);
static int PushFieldToAstStruct(Loc loc, AstNode* struct_, SymbolID name, AstNode* value);
static int PushFieldToAstPattern(Loc loc, AstNode* pattern, SymbolID name, AstNode* typespec);
static int PushStmtToAstChain(AstNode* chain, AstNode* statement);

static AstNode* CreateAstIte(Loc loc, AstNode* cond, AstNode* ifTrue, AstNode* ifFalse);
static AstNode* CreateAstDotIndex(Loc loc, AstNode* lhs, size_t index);
static AstNode* CreateAstDotName(Loc loc, AstNode* lhs, SymbolID rhs);

static AstNode* CreateAstLambda(Loc loc, AstNode* pattern, AstNode* body);

static AstNode* CreateAstBindStmt(Loc loc, SymbolID lhs, AstNode* templatePattern, AstNode* rhs);
static AstNode* CreateAstCheckStmt(Loc loc, AstNode* checked, char* messageValue);

static AstNode* CreateAstTemplateCall(Loc loc, AstNode* lhs);
static AstNode* CreateAstValueCall(Loc loc, AstNode* lhs);
static AstNode* CreateAstSqBrkCall(Loc loc, AstNode* lhs);
static int PushActualArgToAstCall(AstNode* call, AstNode* actualArg);

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
    if (match(p, TK_LSQBRK)) {
        templatePattern = parsePattern(p);
        return NULL;
    }
    if (!expect(p, TK_BIND, "the '=' (bind) operator")) {
        return NULL;
    }
    rhs = parseExpr(p);
    if (!rhs) {
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
    return tryParseBinaryExpr(p, binaryOpPrecedenceListHead);
}
static AstNode* tryParsePrimaryExpr(Parser* p) {
    switch (lookaheadKind(p,0)) {
        case TK_ID: { return parseID(p); }
        case TK_DINT_LIT: { return parseInt(p); }
        case TK_XINT_LIT: { return parseInt(p); }
        case TK_FLOAT_LIT: { return parseFloat(p); }
        case TK_SQSTRING_LIT: { return parseString(p); }
        case TK_DQSTRING_LIT: { return parseString(p); }
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
    TokenKind ltKind = lookaheadKind(p,0);
    if (match(p, TK_LPAREN) || match(p, TK_LSQBRK)) {
        AstNode* pattern = parsePattern(p);
        
        TokenKind rtKind;
        char const* rtMsg;
        if (ltKind == TK_LPAREN) { rtKind = TK_RPAREN; rtMsg = "a matching ')' bracket"; }
        if (ltKind == TK_LSQBRK) { rtKind = TK_RSQBRK; rtMsg = "a matching ']' bracket"; }
        if (!expect(p, rtKind, rtMsg)) {
            return NULL;
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
static AstNode* tryParseBinaryExpr(Parser* p, BinaryOpPrecedenceNode* highestPrecedenceNode) {
    AstNode* lhs;
    if (highestPrecedenceNode->nextHighest) {
        lhs = tryParseBinaryExpr(p, highestPrecedenceNode->nextHighest);
    } else {
        lhs = tryParseUnaryExpr(p);
    }

    if (match(p, highestPrecedenceNode->tokenKind)) {
        AstNode* rhs = tryParseBinaryExpr(p, highestPrecedenceNode);
        return CreateAstBinary(GetAstNodeLoc(lhs), highestPrecedenceNode->bop, lhs, rhs);
    } else {
        return lhs;
    }
}

static AstNode* parseID(Parser* p) {
    TokenInfo* idTokenInfo = lookaheadInfo(p, 0);
    if (expect(p, TK_ID, "a bound identifier")) {
        return CreateAstId(idTokenInfo->loc, idTokenInfo->as.ID);
    } else {
        return NULL;
    }
}
static AstNode* parseInt(Parser* p) {
    TokenInfo* intTokenInfo = lookaheadInfo(p, 0);
    if (match(p, TK_DINT_LIT) || match(p, TK_XINT_LIT)) {
        return CreateAstIntLiteral(intTokenInfo->loc, intTokenInfo->as.Int);
    } else {
        expectError(p, "an integer literal");
        return NULL;
    }
}
static AstNode* parseFloat(Parser* p) {
    TokenInfo* floatTokenInfo = lookaheadInfo(p, 0);
    if (expect(p, TK_FLOAT_LIT, "a float literal")) {
        return CreateAstFloatLiteral(floatTokenInfo->loc, floatTokenInfo->as.Float);
    } else {
        return NULL;
    }
}
static AstNode* parseString(Parser* p) {
    TokenInfo* stringTokenInfo = lookaheadInfo(p, 0);
    if (match(p, TK_SQSTRING_LIT) || match(p, TK_DQSTRING_LIT)) {
        return CreateAstStringLiteral(stringTokenInfo->loc, stringTokenInfo->as.Utf8String);
    } else {
        expectError(p, "a string literal");
        return NULL;
    }
}

//
// API:
//

AstNode* ParseSource(Source* source) {
    // TODO: implement a source parser, delegating to the above.
    return NULL;
}
