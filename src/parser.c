#include "parser.h"

#include "lexer.h"

size_t const PARSER_LOOKAHEAD_COUNT = 2;

typedef struct Parser Parser;
typedef struct ParserLookahead ParserLookahead;

struct ParserLookahead {
    TokenKind peekKind;
    TokenInfo peekInfo;
};
struct Parser {
    Source* source;
    ParserLookahead lookaheadBuffer[PARSER_LOOKAHEAD_COUNT];
};
ParserLookahead* peekToken(Parser* p);
void advanceToken(Parser* p);

static AstNode* parseImportHeader(Parser* p);
static AstNode* parseExportHeader(Parser* p);
static AstNode* helpParseHeader(Parser* p);

static AstNode* parseStmt(Parser* p);
static AstNode* parseBindStmt(Parser* p);
static AstNode* parseCheckStmt(Parser* p);

static AstNode* parseExpr(Parser* p);
static AstNode* parseList(Parser* p);
static AstNode* parseStruct(Parser* p);
static AstNode* parsePattern(Parser* p);
static AstNode* parseChain(Parser* p);
static AstNode* parseIte(Parser* p);
static AstNode* parseDotIndex(Parser* p);
static AstNode* parseDotName(Parser* p);
static AstNode* parseLambda(Parser* p);
static AstNode* parseId(Parser* p);
static AstNode* parseInt(Parser* p);
static AstNode* parseFloat(Parser* p);
static AstNode* parseString(Parser* p);
static AstNode* parseLambda(Parser* p);
static AstNode* parseTemplateCall(Parser* p);
static AstNode* parseValueCall(Parser* p);

AstNode* CreateAstId(Loc loc, SymbolID symbolID);
AstNode* CreateAstIntLiteral(Loc loc, size_t value);
AstNode* CreateAstFloatLiteral(Loc loc, long double value);
AstNode* CreateAstStringLiteral(Loc loc, char* value);

AstNode* CreateAstList(Loc loc);
AstNode* CreateAstStruct(Loc loc);
AstNode* CreateAstChain(Loc loc);
AstNode* CreateAstPattern(Loc loc);

int PushItemToAstList(AstNode* slice, AstNode* pushed);
int PushFieldToAstStruct(Loc loc, AstNode* struct_, SymbolID name, AstNode* value);
int PushFieldToAstPattern(Loc loc, AstNode* pattern, SymbolID name, AstNode* typespec);
int PushStmtToAstChain(AstNode* chain, AstNode* statement);

AstNode* CreateAstIte(Loc loc, AstNode* cond, AstNode* ifTrue, AstNode* ifFalse);
AstNode* CreateAstDotIndex(Loc loc, AstNode* lhs, size_t index);
AstNode* CreateAstDotName(Loc loc, AstNode* lhs, SymbolID rhs);

AstNode* CreateAstLambda(Loc loc, AstNode* pattern, AstNode* body);

AstNode* CreateAstBindStmt(Loc loc, SymbolID lhs, AstNode* templatePattern, AstNode* rhs);
AstNode* CreateAstCheckStmt(Loc loc, AstNode* checked, char* messageValue);

AstNode* CreateAstTemplateCall(Loc loc, AstNode* lhs);
AstNode* CreateAstValueCall(Loc loc, AstNode* lhs);
AstNode* CreateAstSqBrkCall(Loc loc, AstNode* lhs);
int PushActualArgToAstCall(AstNode* call, AstNode* actualArg);

//
// API:
//

AstNode* ParseSource(Source* source) {
    // TODO: implement a source parser, delegating to the above.
    return NULL;
}