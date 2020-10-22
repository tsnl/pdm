#include "primer.h"

#include <assert.h>

#include "stb/stretchy_buffer.h"

#include "useful.h"
#include "symbols.h"
#include "config.h"
#include "typer.h"

// Taking static references to pre-defined symbols:
static int symbols_loaded = 0;

static SymbolID symbol_u1 = SYM_NULL;
static SymbolID symbol_u8 = SYM_NULL;
static SymbolID symbol_u16 = SYM_NULL;
static SymbolID symbol_u32 = SYM_NULL;
static SymbolID symbol_u64 = SYM_NULL;
static SymbolID symbol_u128 = SYM_NULL;
static SymbolID symbol_s8 = SYM_NULL;
static SymbolID symbol_s16 = SYM_NULL;
static SymbolID symbol_s32 = SYM_NULL;
static SymbolID symbol_s64 = SYM_NULL;
static SymbolID symbol_s128 = SYM_NULL;
static SymbolID symbol_f32 = SYM_NULL;
static SymbolID symbol_f64 = SYM_NULL;

static SymbolID symbol_operator_mul_f64 = SYM_NULL;
static SymbolID symbol_operator_mul_f32 = SYM_NULL;
static SymbolID symbol_operator_mul_s128 = SYM_NULL;
static SymbolID symbol_operator_mul_s64 = SYM_NULL;
static SymbolID symbol_operator_mul_s32 = SYM_NULL;
static SymbolID symbol_operator_mul_s16 = SYM_NULL;
static SymbolID symbol_operator_mul_s8 = SYM_NULL;
static SymbolID symbol_operator_mul_u128 = SYM_NULL;
static SymbolID symbol_operator_mul_u64 = SYM_NULL;
static SymbolID symbol_operator_mul_u32 = SYM_NULL;
static SymbolID symbol_operator_mul_u16 = SYM_NULL;
static SymbolID symbol_operator_mul_u8 = SYM_NULL;
static SymbolID symbol_operator_mul_u1 = SYM_NULL;

static SymbolID symbol_operator_div_f64 = SYM_NULL;
static SymbolID symbol_operator_div_f32 = SYM_NULL;
static SymbolID symbol_operator_quo_s128 = SYM_NULL;
static SymbolID symbol_operator_quo_s64 = SYM_NULL;
static SymbolID symbol_operator_quo_s32 = SYM_NULL;
static SymbolID symbol_operator_quo_s16 = SYM_NULL;
static SymbolID symbol_operator_quo_s8 = SYM_NULL;
static SymbolID symbol_operator_quo_u128 = SYM_NULL;
static SymbolID symbol_operator_quo_u64 = SYM_NULL;
static SymbolID symbol_operator_quo_u32 = SYM_NULL;
static SymbolID symbol_operator_quo_u16 = SYM_NULL;
static SymbolID symbol_operator_quo_u8 = SYM_NULL;
static SymbolID symbol_operator_quo_u1 = SYM_NULL;

static SymbolID symbol_operator_rem_s128 = SYM_NULL;
static SymbolID symbol_operator_rem_s64 = SYM_NULL;
static SymbolID symbol_operator_rem_s32 = SYM_NULL;
static SymbolID symbol_operator_rem_s16 = SYM_NULL;
static SymbolID symbol_operator_rem_s8 = SYM_NULL;
static SymbolID symbol_operator_rem_u128 = SYM_NULL;
static SymbolID symbol_operator_rem_u64 = SYM_NULL;
static SymbolID symbol_operator_rem_u32 = SYM_NULL;
static SymbolID symbol_operator_rem_u16 = SYM_NULL;
static SymbolID symbol_operator_rem_u8 = SYM_NULL;
static SymbolID symbol_operator_rem_u1 = SYM_NULL;

static SymbolID symbol_operator_add_f64 = SYM_NULL;
static SymbolID symbol_operator_add_f32 = SYM_NULL;
static SymbolID symbol_operator_add_s128 = SYM_NULL;
static SymbolID symbol_operator_add_s64 = SYM_NULL;
static SymbolID symbol_operator_add_s32 = SYM_NULL;
static SymbolID symbol_operator_add_s16 = SYM_NULL;
static SymbolID symbol_operator_add_s8 = SYM_NULL;
static SymbolID symbol_operator_add_u128 = SYM_NULL;
static SymbolID symbol_operator_add_u64 = SYM_NULL;
static SymbolID symbol_operator_add_u32 = SYM_NULL;
static SymbolID symbol_operator_add_u16 = SYM_NULL;
static SymbolID symbol_operator_add_u8 = SYM_NULL;
static SymbolID symbol_operator_add_u1 = SYM_NULL;

static SymbolID symbol_operator_subtract_f64 = SYM_NULL;
static SymbolID symbol_operator_subtract_f32 = SYM_NULL;
static SymbolID symbol_operator_subtract_s128 = SYM_NULL;
static SymbolID symbol_operator_subtract_s64 = SYM_NULL;
static SymbolID symbol_operator_subtract_s32 = SYM_NULL;
static SymbolID symbol_operator_subtract_s16 = SYM_NULL;
static SymbolID symbol_operator_subtract_s8 = SYM_NULL;
static SymbolID symbol_operator_subtract_u128 = SYM_NULL;
static SymbolID symbol_operator_subtract_u64 = SYM_NULL;
static SymbolID symbol_operator_subtract_u32 = SYM_NULL;
static SymbolID symbol_operator_subtract_u16 = SYM_NULL;
static SymbolID symbol_operator_subtract_u8 = SYM_NULL;
static SymbolID symbol_operator_subtract_u1 = SYM_NULL;

static SymbolID symbol_operator_lessThan_f64 = SYM_NULL;
static SymbolID symbol_operator_lessThan_f32 = SYM_NULL;
static SymbolID symbol_operator_lessThan_s128 = SYM_NULL;
static SymbolID symbol_operator_lessThan_s64 = SYM_NULL;
static SymbolID symbol_operator_lessThan_s32 = SYM_NULL;
static SymbolID symbol_operator_lessThan_s16 = SYM_NULL;
static SymbolID symbol_operator_lessThan_s8 = SYM_NULL;
static SymbolID symbol_operator_lessThan_u128 = SYM_NULL;
static SymbolID symbol_operator_lessThan_u64 = SYM_NULL;
static SymbolID symbol_operator_lessThan_u32 = SYM_NULL;
static SymbolID symbol_operator_lessThan_u16 = SYM_NULL;
static SymbolID symbol_operator_lessThan_u8 = SYM_NULL;
static SymbolID symbol_operator_lessThan_u1 = SYM_NULL;

static SymbolID symbol_operator_greaterThan_f64 = SYM_NULL;
static SymbolID symbol_operator_greaterThan_f32 = SYM_NULL;
static SymbolID symbol_operator_greaterThan_s128 = SYM_NULL;
static SymbolID symbol_operator_greaterThan_s64 = SYM_NULL;
static SymbolID symbol_operator_greaterThan_s32 = SYM_NULL;
static SymbolID symbol_operator_greaterThan_s16 = SYM_NULL;
static SymbolID symbol_operator_greaterThan_s8 = SYM_NULL;
static SymbolID symbol_operator_greaterThan_u128 = SYM_NULL;
static SymbolID symbol_operator_greaterThan_u64 = SYM_NULL;
static SymbolID symbol_operator_greaterThan_u32 = SYM_NULL;
static SymbolID symbol_operator_greaterThan_u16 = SYM_NULL;
static SymbolID symbol_operator_greaterThan_u8 = SYM_NULL;
static SymbolID symbol_operator_greaterThan_u1 = SYM_NULL;

static SymbolID symbol_operator_lessThanOrEquals_f64 = SYM_NULL;
static SymbolID symbol_operator_lessThanOrEquals_f32 = SYM_NULL;
static SymbolID symbol_operator_lessThanOrEquals_s128 = SYM_NULL;
static SymbolID symbol_operator_lessThanOrEquals_s64 = SYM_NULL;
static SymbolID symbol_operator_lessThanOrEquals_s32 = SYM_NULL;
static SymbolID symbol_operator_lessThanOrEquals_s16 = SYM_NULL;
static SymbolID symbol_operator_lessThanOrEquals_s8 = SYM_NULL;
static SymbolID symbol_operator_lessThanOrEquals_u128 = SYM_NULL;
static SymbolID symbol_operator_lessThanOrEquals_u64 = SYM_NULL;
static SymbolID symbol_operator_lessThanOrEquals_u32 = SYM_NULL;
static SymbolID symbol_operator_lessThanOrEquals_u16 = SYM_NULL;
static SymbolID symbol_operator_lessThanOrEquals_u8 = SYM_NULL;
static SymbolID symbol_operator_lessThanOrEquals_u1 = SYM_NULL;

static SymbolID symbol_operator_greaterThanOrEquals_f64 = SYM_NULL;
static SymbolID symbol_operator_greaterThanOrEquals_f32 = SYM_NULL;
static SymbolID symbol_operator_greaterThanOrEquals_s128 = SYM_NULL;
static SymbolID symbol_operator_greaterThanOrEquals_s64 = SYM_NULL;
static SymbolID symbol_operator_greaterThanOrEquals_s32 = SYM_NULL;
static SymbolID symbol_operator_greaterThanOrEquals_s16 = SYM_NULL;
static SymbolID symbol_operator_greaterThanOrEquals_s8 = SYM_NULL;
static SymbolID symbol_operator_greaterThanOrEquals_u128 = SYM_NULL;
static SymbolID symbol_operator_greaterThanOrEquals_u64 = SYM_NULL;
static SymbolID symbol_operator_greaterThanOrEquals_u32 = SYM_NULL;
static SymbolID symbol_operator_greaterThanOrEquals_u16 = SYM_NULL;
static SymbolID symbol_operator_greaterThanOrEquals_u8 = SYM_NULL;
static SymbolID symbol_operator_greaterThanOrEquals_u1 = SYM_NULL;

static SymbolID symbol_operator_equals_f64 = SYM_NULL;
static SymbolID symbol_operator_equals_f32 = SYM_NULL;
static SymbolID symbol_operator_equals_s128 = SYM_NULL;
static SymbolID symbol_operator_equals_s64 = SYM_NULL;
static SymbolID symbol_operator_equals_s32 = SYM_NULL;
static SymbolID symbol_operator_equals_s16 = SYM_NULL;
static SymbolID symbol_operator_equals_s8 = SYM_NULL;
static SymbolID symbol_operator_equals_u128 = SYM_NULL;
static SymbolID symbol_operator_equals_u64 = SYM_NULL;
static SymbolID symbol_operator_equals_u32 = SYM_NULL;
static SymbolID symbol_operator_equals_u16 = SYM_NULL;
static SymbolID symbol_operator_equals_u8 = SYM_NULL;
static SymbolID symbol_operator_equals_u1 = SYM_NULL;

static SymbolID symbol_operator_notEquals_f64 = SYM_NULL;
static SymbolID symbol_operator_notEquals_f32 = SYM_NULL;
static SymbolID symbol_operator_notEquals_s128 = SYM_NULL;
static SymbolID symbol_operator_notEquals_s64 = SYM_NULL;
static SymbolID symbol_operator_notEquals_s32 = SYM_NULL;
static SymbolID symbol_operator_notEquals_s16 = SYM_NULL;
static SymbolID symbol_operator_notEquals_s8 = SYM_NULL;
static SymbolID symbol_operator_notEquals_u128 = SYM_NULL;
static SymbolID symbol_operator_notEquals_u64 = SYM_NULL;
static SymbolID symbol_operator_notEquals_u32 = SYM_NULL;
static SymbolID symbol_operator_notEquals_u16 = SYM_NULL;
static SymbolID symbol_operator_notEquals_u8 = SYM_NULL;
static SymbolID symbol_operator_notEquals_u1 = SYM_NULL;

static SymbolID symbol_operator_and_u128 = SYM_NULL;
static SymbolID symbol_operator_and_u64 = SYM_NULL;
static SymbolID symbol_operator_and_u32 = SYM_NULL;
static SymbolID symbol_operator_and_u16 = SYM_NULL;
static SymbolID symbol_operator_and_u8 = SYM_NULL;
static SymbolID symbol_operator_and_u1 = SYM_NULL;

static SymbolID symbol_operator_xor_u128 = SYM_NULL;
static SymbolID symbol_operator_xor_u64 = SYM_NULL;
static SymbolID symbol_operator_xor_u32 = SYM_NULL;
static SymbolID symbol_operator_xor_u16 = SYM_NULL;
static SymbolID symbol_operator_xor_u8 = SYM_NULL;
static SymbolID symbol_operator_xor_u1 = SYM_NULL;

static SymbolID symbol_operator_or_u128 = SYM_NULL;
static SymbolID symbol_operator_or_u64 = SYM_NULL;
static SymbolID symbol_operator_or_u32 = SYM_NULL;
static SymbolID symbol_operator_or_u16 = SYM_NULL;
static SymbolID symbol_operator_or_u8 = SYM_NULL;
static SymbolID symbol_operator_or_u1 = SYM_NULL;

static void ensureStaticSymbolsLoaded(void);
static Scope* builtinVDef(Scope* parent, Typer* typer, SymbolID symbolID, AstBuiltinVDefKind builtinVDefKind);

// The primer performs `Lexical Analysis`, which involves traversing the AST, building a tree of
// contexts from linked list node stored in stack frames, and using this tree to look up symbols'
// types.
// At the end of Lexical Analysis, we have a typeP for each typed expression, ready for 
// typing/unification after analysis.
// Crucially, each context contains at most *one* definition.

struct Primer {
    Scope* root;

    // the typer is used by the primer to create metatypes.
    Typer* typer;

    // new scopes can extend previous ones, and are organized into 'frames' stored in this stack:
    Frame* frameStackSB;
    int frameStackCount;
};

size_t allocatedPrimersCount = 0;
Primer allocatedPrimers[MAX_PRIMER_COUNT];

static Primer* createPrimer(Typer* typer);
static void pushSymbol(Primer* primer, SymbolID defnID, void* type, AstNode* node, AstContext context, int isOverloadedDefn);
static Scope* pushFrame(Primer* primer, Scope* scope, AstContext ctx, AstNode* func);
static Frame popFrame(Primer* primer);
Frame* topFrame(Primer* primer);
Scope* topFrameScope(Primer* primer);
AstNode* topFrameFunc(Primer* primer);
static AstContext topFrameContext(Primer* primer);

static size_t allocatedScopeCount = 0;
static Scope allocatedScopes[MAX_AST_NODE_COUNT];
inline static Scope* newScope(Scope* parent, SymbolID defnID, void* type, AstNode* defn, AstContext context, int isOverloadedDefn);
static Scope* newRootScope(Typer* typer);
static Defn* lookupSymbolUntil(Scope* scope, SymbolID lookupID, Scope* endScopeP, AstContext context);

//
// Static implementation:
//

void ensureStaticSymbolsLoaded() {
    if (symbols_loaded == 0) {
        symbol_u1   = Symbol("U1");
        symbol_u8   = Symbol("U8");
        symbol_u16  = Symbol("U16");
        symbol_u32  = Symbol("U32");
        symbol_u64  = Symbol("U64");
        symbol_u128 = Symbol("U128");
        symbol_s8   = Symbol("S8");
        symbol_s16  = Symbol("S16");
        symbol_s32  = Symbol("S32");
        symbol_s64  = Symbol("S64");
        symbol_s128 = Symbol("S128");
        symbol_f32  = Symbol("F32");
        symbol_f64  = Symbol("F64");

        symbol_operator_mul_f64  = Symbol("operator_mul_f64");
        symbol_operator_mul_f32  = Symbol("operator_mul_f32");
        symbol_operator_mul_s128 = Symbol("operator_mul_s128");
        symbol_operator_mul_s64  = Symbol("operator_mul_s64");
        symbol_operator_mul_s32  = Symbol("operator_mul_s32");
        symbol_operator_mul_s16  = Symbol("operator_mul_s16");
        symbol_operator_mul_s8   = Symbol("operator_mul_s8");
        symbol_operator_mul_u128 = Symbol("operator_mul_u128");
        symbol_operator_mul_u64  = Symbol("operator_mul_u64");
        symbol_operator_mul_u32  = Symbol("operator_mul_u32");
        symbol_operator_mul_u16  = Symbol("operator_mul_u16");
        symbol_operator_mul_u8   = Symbol("operator_mul_u8");
        symbol_operator_mul_u1   = Symbol("operator_mul_u1");

        symbol_operator_div_f64  = Symbol("operator_div_f64");
        symbol_operator_div_f32  = Symbol("operator_div_f32");
        symbol_operator_quo_s128 = Symbol("operator_quo_s128");
        symbol_operator_quo_s64  = Symbol("operator_quo_s64");
        symbol_operator_quo_s32  = Symbol("operator_quo_s32");
        symbol_operator_quo_s16  = Symbol("operator_quo_s16");
        symbol_operator_quo_s8   = Symbol("operator_quo_s8");
        symbol_operator_quo_u128 = Symbol("operator_quo_u128");
        symbol_operator_quo_u64  = Symbol("operator_quo_u64");
        symbol_operator_quo_u32  = Symbol("operator_quo_u32");
        symbol_operator_quo_u16  = Symbol("operator_quo_u16");
        symbol_operator_quo_u8   = Symbol("operator_quo_u8");
        symbol_operator_quo_u1   = Symbol("operator_quo_u1");

        symbol_operator_add_f64  = Symbol("operator_add_f64");
        symbol_operator_add_f32  = Symbol("operator_add_f32");
        symbol_operator_add_s128 = Symbol("operator_add_s128");
        symbol_operator_add_s64  = Symbol("operator_add_s64");
        symbol_operator_add_s32  = Symbol("operator_add_s32");
        symbol_operator_add_s16  = Symbol("operator_add_s16");
        symbol_operator_add_s8   = Symbol("operator_add_s8");
        symbol_operator_add_u128 = Symbol("operator_add_u128");
        symbol_operator_add_u64  = Symbol("operator_add_u64");
        symbol_operator_add_u32  = Symbol("operator_add_u32");
        symbol_operator_add_u16  = Symbol("operator_add_u16");
        symbol_operator_add_u8   = Symbol("operator_add_u8");
        symbol_operator_add_u1   = Symbol("operator_add_u1");

        symbol_operator_subtract_f64  = Symbol("operator_subtract_f64");
        symbol_operator_subtract_f32  = Symbol("operator_subtract_f32");
        symbol_operator_subtract_s128 = Symbol("operator_subtract_s128");
        symbol_operator_subtract_s64  = Symbol("operator_subtract_s64");
        symbol_operator_subtract_s32  = Symbol("operator_subtract_s32");
        symbol_operator_subtract_s16  = Symbol("operator_subtract_s16");
        symbol_operator_subtract_s8   = Symbol("operator_subtract_s8");
        symbol_operator_subtract_u128 = Symbol("operator_subtract_u128");
        symbol_operator_subtract_u64  = Symbol("operator_subtract_u64");
        symbol_operator_subtract_u32  = Symbol("operator_subtract_u32");
        symbol_operator_subtract_u16  = Symbol("operator_subtract_u16");
        symbol_operator_subtract_u8   = Symbol("operator_subtract_u8");
        symbol_operator_subtract_u1   = Symbol("operator_subtract_u1");

        symbol_operator_lessThan_f64  = Symbol("operator_lessThan_f64");
        symbol_operator_lessThan_f32  = Symbol("operator_lessThan_f32");
        symbol_operator_lessThan_s128 = Symbol("operator_lessThan_s128");
        symbol_operator_lessThan_s64  = Symbol("operator_lessThan_s64");
        symbol_operator_lessThan_s32  = Symbol("operator_lessThan_s32");
        symbol_operator_lessThan_s16  = Symbol("operator_lessThan_s16");
        symbol_operator_lessThan_s8   = Symbol("operator_lessThan_s8");
        symbol_operator_lessThan_u128 = Symbol("operator_lessThan_u128");
        symbol_operator_lessThan_u64  = Symbol("operator_lessThan_u64");
        symbol_operator_lessThan_u32  = Symbol("operator_lessThan_u32");
        symbol_operator_lessThan_u16  = Symbol("operator_lessThan_u16");
        symbol_operator_lessThan_u8   = Symbol("operator_lessThan_u8");
        symbol_operator_lessThan_u1   = Symbol("operator_lessThan_u1");

        symbol_operator_greaterThan_f64  = Symbol("operator_greaterThan_f64");
        symbol_operator_greaterThan_f32  = Symbol("operator_greaterThan_f32");
        symbol_operator_greaterThan_s128 = Symbol("operator_greaterThan_s128");
        symbol_operator_greaterThan_s64  = Symbol("operator_greaterThan_s64");
        symbol_operator_greaterThan_s32  = Symbol("operator_greaterThan_s32");
        symbol_operator_greaterThan_s16  = Symbol("operator_greaterThan_s16");
        symbol_operator_greaterThan_s8   = Symbol("operator_greaterThan_s8");
        symbol_operator_greaterThan_u128 = Symbol("operator_greaterThan_u128");
        symbol_operator_greaterThan_u64  = Symbol("operator_greaterThan_u64");
        symbol_operator_greaterThan_u32  = Symbol("operator_greaterThan_u32");
        symbol_operator_greaterThan_u16  = Symbol("operator_greaterThan_u16");
        symbol_operator_greaterThan_u8   = Symbol("operator_greaterThan_u8");
        symbol_operator_greaterThan_u1   = Symbol("operator_greaterThan_u1");

        symbol_operator_lessThanOrEquals_f64  = Symbol("operator_lessThanOrEquals_f64");
        symbol_operator_lessThanOrEquals_f32  = Symbol("operator_lessThanOrEquals_f32");
        symbol_operator_lessThanOrEquals_s128 = Symbol("operator_lessThanOrEquals_s128");
        symbol_operator_lessThanOrEquals_s64  = Symbol("operator_lessThanOrEquals_s64");
        symbol_operator_lessThanOrEquals_s32  = Symbol("operator_lessThanOrEquals_s32");
        symbol_operator_lessThanOrEquals_s16  = Symbol("operator_lessThanOrEquals_s16");
        symbol_operator_lessThanOrEquals_s8   = Symbol("operator_lessThanOrEquals_s8");
        symbol_operator_lessThanOrEquals_u128 = Symbol("operator_lessThanOrEquals_u128");
        symbol_operator_lessThanOrEquals_u64  = Symbol("operator_lessThanOrEquals_u64");
        symbol_operator_lessThanOrEquals_u32  = Symbol("operator_lessThanOrEquals_u32");
        symbol_operator_lessThanOrEquals_u16  = Symbol("operator_lessThanOrEquals_u16");
        symbol_operator_lessThanOrEquals_u8   = Symbol("operator_lessThanOrEquals_u8");
        symbol_operator_lessThanOrEquals_u1   = Symbol("operator_lessThanOrEquals_u1");

        symbol_operator_greaterThanOrEquals_f64  = Symbol("operator_greaterThanOrEquals_f64");
        symbol_operator_greaterThanOrEquals_f32  = Symbol("operator_greaterThanOrEquals_f32");
        symbol_operator_greaterThanOrEquals_s128 = Symbol("operator_greaterThanOrEquals_s128");
        symbol_operator_greaterThanOrEquals_s64  = Symbol("operator_greaterThanOrEquals_s64");
        symbol_operator_greaterThanOrEquals_s32  = Symbol("operator_greaterThanOrEquals_s32");
        symbol_operator_greaterThanOrEquals_s16  = Symbol("operator_greaterThanOrEquals_s16");
        symbol_operator_greaterThanOrEquals_s8   = Symbol("operator_greaterThanOrEquals_s8");
        symbol_operator_greaterThanOrEquals_u128 = Symbol("operator_greaterThanOrEquals_u128");
        symbol_operator_greaterThanOrEquals_u64  = Symbol("operator_greaterThanOrEquals_u64");
        symbol_operator_greaterThanOrEquals_u32  = Symbol("operator_greaterThanOrEquals_u32");
        symbol_operator_greaterThanOrEquals_u16  = Symbol("operator_greaterThanOrEquals_u16");
        symbol_operator_greaterThanOrEquals_u8   = Symbol("operator_greaterThanOrEquals_u8");
        symbol_operator_greaterThanOrEquals_u1   = Symbol("operator_greaterThanOrEquals_u1");

        symbol_operator_equals_f64  = Symbol("operator_equals_f64");
        symbol_operator_equals_f32  = Symbol("operator_equals_f32");
        symbol_operator_equals_s128 = Symbol("operator_equals_s128");
        symbol_operator_equals_s64  = Symbol("operator_equals_s64");
        symbol_operator_equals_s32  = Symbol("operator_equals_s32");
        symbol_operator_equals_s16  = Symbol("operator_equals_s16");
        symbol_operator_equals_s8   = Symbol("operator_equals_s8");
        symbol_operator_equals_u128 = Symbol("operator_equals_u128");
        symbol_operator_equals_u64  = Symbol("operator_equals_u64");
        symbol_operator_equals_u32  = Symbol("operator_equals_u32");
        symbol_operator_equals_u16  = Symbol("operator_equals_u16");
        symbol_operator_equals_u8   = Symbol("operator_equals_u8");
        symbol_operator_equals_u1   = Symbol("operator_equals_u1");

        symbol_operator_notEquals_f64  = Symbol("operator_notEquals_f64");
        symbol_operator_notEquals_f32  = Symbol("operator_notEquals_f32");
        symbol_operator_notEquals_s128 = Symbol("operator_notEquals_s128");
        symbol_operator_notEquals_s64  = Symbol("operator_notEquals_s64");
        symbol_operator_notEquals_s32  = Symbol("operator_notEquals_s32");
        symbol_operator_notEquals_s16  = Symbol("operator_notEquals_s16");
        symbol_operator_notEquals_s8   = Symbol("operator_notEquals_s8");
        symbol_operator_notEquals_u128 = Symbol("operator_notEquals_u128");
        symbol_operator_notEquals_u64  = Symbol("operator_notEquals_u64");
        symbol_operator_notEquals_u32  = Symbol("operator_notEquals_u32");
        symbol_operator_notEquals_u16  = Symbol("operator_notEquals_u16");
        symbol_operator_notEquals_u8   = Symbol("operator_notEquals_u8");
        symbol_operator_notEquals_u1   = Symbol("operator_notEquals_u1");

        symbol_operator_and_u128 = Symbol("operator_and_u128");
        symbol_operator_and_u64  = Symbol("operator_and_u64");
        symbol_operator_and_u32  = Symbol("operator_and_u32");
        symbol_operator_and_u16  = Symbol("operator_and_u16");
        symbol_operator_and_u8   = Symbol("operator_and_u8");
        symbol_operator_and_u1   = Symbol("operator_and_u1");

        symbol_operator_xor_u128 = Symbol("operator_xor_u128");
        symbol_operator_xor_u64  = Symbol("operator_xor_u64");
        symbol_operator_xor_u32  = Symbol("operator_xor_u32");
        symbol_operator_xor_u16  = Symbol("operator_xor_u16");
        symbol_operator_xor_u8   = Symbol("operator_xor_u8");
        symbol_operator_xor_u1   = Symbol("operator_xor_u1");

        symbol_operator_or_u128 = Symbol("operator_or_u128");
        symbol_operator_or_u64  = Symbol("operator_or_u64");
        symbol_operator_or_u32  = Symbol("operator_or_u32");
        symbol_operator_or_u16  = Symbol("operator_or_u16");
        symbol_operator_or_u8   = Symbol("operator_or_u8");
        symbol_operator_or_u1   = Symbol("operator_or_u1");

        symbols_loaded = 1;
    }
}
Scope* builtinVDef(Scope* parent, Typer* typer, SymbolID symbolID, AstBuiltinVDefKind builtinVDefKind) {
    AstNode* defnNode = NewAstBuiltinVDefStmt(symbolID,builtinVDefKind);
    Type* type = GetAstBuiltinVDefType(typer,builtinVDefKind);
    Scope* scope = newScope(parent, symbolID,type,defnNode, ASTCTX_TYPING, 1);
    return scope;
}

Primer* createPrimer(Typer* typer) {
    ensureStaticSymbolsLoaded();
    
    Primer* primer = NULL;
    if (allocatedPrimersCount < MAX_PRIMER_COUNT) {
        primer = &allocatedPrimers[allocatedPrimersCount++];
    } else {
        return NULL;
    }
    primer->typer = typer;
    primer->frameStackSB = NULL;
    primer->frameStackCount = 0;
    primer->root = newRootScope(typer);

    pushFrame(primer,primer->root,ASTCTX_VALUE,topFrameFunc(primer));

    return primer;
}
void pushSymbol(Primer* primer, SymbolID defnID, void* type, AstNode* defnAstNode, AstContext context, int isOverloadedDefn) {
    if (defnID) {
        Scope* parent = topFrameScope(primer);
        Scope* scope = newScope(parent, defnID, type, defnAstNode, context, isOverloadedDefn);
        primer->frameStackSB[primer->frameStackCount-1].endScope = scope;

        AstNode* topLambda = topFrameFunc(primer);
        if (topLambda) {
            Defn* defn = scope;
            AddAstLambdaDefn(topLambda,defn);
        }
    }
}
Scope* pushFrame(Primer* primer, Scope* optNewScope, AstContext ctx, AstNode* func) {
    if (func) {
        AstKind nodeKind = GetAstNodeKind(func);
        COMPILER_ASSERT_VA(
            nodeKind == AST_LAMBDA, 
            "Non-lambda parent func in `pushFrame`: %s", AstKindAsText(nodeKind)
        );
    }

    Scope* topScope = topFrameScope(primer);
    if (optNewScope == NULL) {
        optNewScope = topScope;
    } else if (topScope != primer->root) {
        int ok = (optNewScope->parent == topScope);
        if (!ok) {
            if (DEBUG) {
                printf("!!- Invalid scope pushed in primer; parent must be the top frame scope at push-time.\n");
            } else {
                assert(0 && "primer: invalid scope pushed; parent must be the top frame scope at push-time.");
            }
            return NULL;
        }
    }
    Frame frame = {ctx,optNewScope,optNewScope,func};
    int bufCount = sb_count(primer->frameStackSB);
    if (primer->frameStackCount == bufCount) {
        sb_push(primer->frameStackSB,frame);
    } else {
        primer->frameStackSB[primer->frameStackCount] = frame;
    }
    primer->frameStackCount++;
    return optNewScope;
}
Frame popFrame(Primer* primer) {
    if (primer->frameStackCount > 0) {
        primer->frameStackCount--;
        Frame frame = primer->frameStackSB[primer->frameStackCount];
        primer->frameStackSB[primer->frameStackCount].context = __ASTCTX_NONE;
        return frame;
    } else {
        if (DEBUG) {
            printf("!!- primer: Cannot pop from an empty frame.\n");
        } else {
            assert(0 && "primer: Cannot pop from an empty frame.\n");
        }
        Frame frame;
        frame.context = __ASTCTX_NONE;
        return frame;
    }
}
Frame* topFrame(Primer* primer) {
    if (primer->frameStackCount > 0) {
        Frame* topFrame = NULL;
        for (int index = primer->frameStackCount-1; index >= 0; index--) {
            Frame* frame = &primer->frameStackSB[index];
            int isEmpty = (frame->begScope == frame->endScope && frame->begScope == NULL);
            if (!isEmpty) {
                topFrame = frame;
                break;
            }
        }
        if (topFrame) {
            return topFrame;
        }
    }
    return NULL;
}
Scope* topFrameScope(Primer* primer) {
    Frame* frame = topFrame(primer);
    if (frame) {
        return frame->endScope;
    }
    return primer->root;
}
AstNode* topFrameFunc(Primer* primer) {
    Frame* frame = topFrame(primer);
    if (frame) {
        return frame->func;
    }
    return NULL;
}
AstContext topFrameContext(Primer* primer) {
    if (!primer->frameStackSB) {
        if (DEBUG) {
            printf("!!- Primer context stack empty.\n");
        } else {
            assert(0 && "Primer context stack empty.");
        }
        return __ASTCTX_NONE;
    }
    return primer->frameStackSB[primer->frameStackCount-1].context;
}

inline Scope* newScope(Scope* parent, SymbolID defnID, void* type, AstNode* defnAstNode, AstContext context, int isOverloadedDefn) {
    Scope* scope = &allocatedScopes[allocatedScopeCount++];
    scope->parent = parent;
    scope->defnID = defnID;
    scope->type = type;
    scope->context = context;
    scope->defnAstNode = defnAstNode;
    scope->isOverloadedDefn = isOverloadedDefn;
    return scope;
}
Scope* newRootScope(Typer* typer) {
    Scope* root = NULL;
    
    //
    // Native scalar types:
    //

    root = newScope(root, symbol_u1, GetIntType(typer,INT_1,0), NULL, ASTCTX_TYPING, 0);
    root = newScope(root, symbol_u8, GetIntType(typer,INT_8,0), NULL, ASTCTX_TYPING, 0);
    root = newScope(root, symbol_u16, GetIntType(typer,INT_16,0), NULL, ASTCTX_TYPING, 0);
    root = newScope(root, symbol_u32, GetIntType(typer,INT_32,0), NULL, ASTCTX_TYPING, 0);
    root = newScope(root, symbol_u64, GetIntType(typer,INT_64,0), NULL, ASTCTX_TYPING, 0);
    root = newScope(root, symbol_u128, GetIntType(typer,INT_128,0), NULL, ASTCTX_TYPING, 0);

    root = newScope(root, symbol_s8, GetIntType(typer,INT_8,1), NULL, ASTCTX_TYPING, 0);
    root = newScope(root, symbol_s16, GetIntType(typer,INT_16,1), NULL, ASTCTX_TYPING, 0);
    root = newScope(root, symbol_s32, GetIntType(typer,INT_32,1), NULL, ASTCTX_TYPING, 0);
    root = newScope(root, symbol_s64, GetIntType(typer,INT_64,1), NULL, ASTCTX_TYPING, 0);
    root = newScope(root, symbol_s128, GetIntType(typer,INT_128,1), NULL, ASTCTX_TYPING, 0);

    root = newScope(root, symbol_f32, GetFloatType(typer,FLOAT_32), NULL, ASTCTX_TYPING, 0);
    root = newScope(root, symbol_f64, GetFloatType(typer,FLOAT_64), NULL, ASTCTX_TYPING, 0);

    //
    // Builtin arithmetic operations:
    //

    // f64:
    root = builtinVDef(root, typer, symbol_operator_mul_f64, AST_BUILTIN_MUL_F64);
    root = builtinVDef(root, typer, symbol_operator_div_f64, AST_BUILTIN_DIV_F64);
    root = builtinVDef(root, typer, symbol_operator_add_f64, AST_BUILTIN_ADD_F64);
    root = builtinVDef(root, typer, symbol_operator_subtract_f64, AST_BUILTIN_SUBTRACT_F64);
    root = builtinVDef(root, typer, symbol_operator_lessThan_f64, AST_BUILTIN_LTHAN_F64);
    root = builtinVDef(root, typer, symbol_operator_greaterThan_f64, AST_BUILTIN_GTHAN_F64);
    root = builtinVDef(root, typer, symbol_operator_lessThanOrEquals_f64, AST_BUILTIN_LETHAN_F64);
    root = builtinVDef(root, typer, symbol_operator_greaterThanOrEquals_f64, AST_BUILTIN_GETHAN_F64);
    root = builtinVDef(root, typer, symbol_operator_equals_f64, AST_BUILTIN_EQUALS_F64);
    root = builtinVDef(root, typer, symbol_operator_notEquals_f64, AST_BUILTIN_NOTEQUALS_F64);
    // f32:
    root = builtinVDef(root, typer, symbol_operator_mul_f32, AST_BUILTIN_MUL_F32);
    root = builtinVDef(root, typer, symbol_operator_div_f32, AST_BUILTIN_DIV_F32);
    root = builtinVDef(root, typer, symbol_operator_add_f32, AST_BUILTIN_ADD_F32);
    root = builtinVDef(root, typer, symbol_operator_subtract_f32, AST_BUILTIN_SUBTRACT_F32);
    root = builtinVDef(root, typer, symbol_operator_lessThan_f32, AST_BUILTIN_LTHAN_F32);
    root = builtinVDef(root, typer, symbol_operator_greaterThan_f32, AST_BUILTIN_GTHAN_F32);
    root = builtinVDef(root, typer, symbol_operator_lessThanOrEquals_f32, AST_BUILTIN_LETHAN_F32);
    root = builtinVDef(root, typer, symbol_operator_greaterThanOrEquals_f32, AST_BUILTIN_GETHAN_F32);
    root = builtinVDef(root, typer, symbol_operator_equals_f32, AST_BUILTIN_EQUALS_F32);
    root = builtinVDef(root, typer, symbol_operator_notEquals_f32, AST_BUILTIN_NOTEQUALS_F32);

    // s128:
    root = builtinVDef(root, typer, symbol_operator_mul_s128, AST_BUILTIN_MUL_S128);
    root = builtinVDef(root, typer, symbol_operator_quo_s128, AST_BUILTIN_QUO_S128);
    root = builtinVDef(root, typer, symbol_operator_rem_s128, AST_BUILTIN_REM_S128);
    root = builtinVDef(root, typer, symbol_operator_add_s128, AST_BUILTIN_ADD_S128);
    root = builtinVDef(root, typer, symbol_operator_subtract_s128, AST_BUILTIN_SUBTRACT_S128);
    root = builtinVDef(root, typer, symbol_operator_lessThan_s128, AST_BUILTIN_LTHAN_S128);
    root = builtinVDef(root, typer, symbol_operator_greaterThan_s128, AST_BUILTIN_GTHAN_S128);
    root = builtinVDef(root, typer, symbol_operator_lessThanOrEquals_s128, AST_BUILTIN_LETHAN_S128);
    root = builtinVDef(root, typer, symbol_operator_greaterThanOrEquals_s128, AST_BUILTIN_GETHAN_S128);
    root = builtinVDef(root, typer, symbol_operator_equals_s128, AST_BUILTIN_EQUALS_S128);
    root = builtinVDef(root, typer, symbol_operator_notEquals_s128, AST_BUILTIN_NOTEQUALS_S128);
    // s64:
    root = builtinVDef(root, typer, symbol_operator_mul_s64, AST_BUILTIN_MUL_S64);
    root = builtinVDef(root, typer, symbol_operator_quo_s64, AST_BUILTIN_QUO_S64);
    root = builtinVDef(root, typer, symbol_operator_rem_s64, AST_BUILTIN_REM_S64);
    root = builtinVDef(root, typer, symbol_operator_add_s64, AST_BUILTIN_ADD_S64);
    root = builtinVDef(root, typer, symbol_operator_subtract_s64, AST_BUILTIN_SUBTRACT_S64);
    root = builtinVDef(root, typer, symbol_operator_lessThan_s64, AST_BUILTIN_LTHAN_S64);
    root = builtinVDef(root, typer, symbol_operator_greaterThan_s64, AST_BUILTIN_GTHAN_S64);
    root = builtinVDef(root, typer, symbol_operator_lessThanOrEquals_s64, AST_BUILTIN_LETHAN_S64);
    root = builtinVDef(root, typer, symbol_operator_greaterThanOrEquals_s64, AST_BUILTIN_GETHAN_S64);
    root = builtinVDef(root, typer, symbol_operator_equals_s64, AST_BUILTIN_EQUALS_S64);
    root = builtinVDef(root, typer, symbol_operator_notEquals_s64, AST_BUILTIN_NOTEQUALS_S64);
    // s32:
    root = builtinVDef(root, typer, symbol_operator_mul_s32, AST_BUILTIN_MUL_S32);
    root = builtinVDef(root, typer, symbol_operator_quo_s32, AST_BUILTIN_QUO_S32);
    root = builtinVDef(root, typer, symbol_operator_rem_s32, AST_BUILTIN_REM_S32);
    root = builtinVDef(root, typer, symbol_operator_add_s32, AST_BUILTIN_ADD_S32);
    root = builtinVDef(root, typer, symbol_operator_subtract_s32, AST_BUILTIN_SUBTRACT_S32);
    root = builtinVDef(root, typer, symbol_operator_lessThan_s32, AST_BUILTIN_LTHAN_S32);
    root = builtinVDef(root, typer, symbol_operator_greaterThan_s32, AST_BUILTIN_GTHAN_S32);
    root = builtinVDef(root, typer, symbol_operator_lessThanOrEquals_s32, AST_BUILTIN_LETHAN_S32);
    root = builtinVDef(root, typer, symbol_operator_greaterThanOrEquals_s32, AST_BUILTIN_GETHAN_S32);
    root = builtinVDef(root, typer, symbol_operator_equals_s32, AST_BUILTIN_EQUALS_S32);
    root = builtinVDef(root, typer, symbol_operator_notEquals_s32, AST_BUILTIN_NOTEQUALS_S32);
    // s16:
    root = builtinVDef(root, typer, symbol_operator_mul_s16, AST_BUILTIN_MUL_S16);
    root = builtinVDef(root, typer, symbol_operator_quo_s16, AST_BUILTIN_QUO_S16);
    root = builtinVDef(root, typer, symbol_operator_rem_s16, AST_BUILTIN_REM_S16);
    root = builtinVDef(root, typer, symbol_operator_add_s16, AST_BUILTIN_ADD_S16);
    root = builtinVDef(root, typer, symbol_operator_subtract_s16, AST_BUILTIN_SUBTRACT_S16);
    root = builtinVDef(root, typer, symbol_operator_lessThan_s16, AST_BUILTIN_LTHAN_S16);
    root = builtinVDef(root, typer, symbol_operator_greaterThan_s16, AST_BUILTIN_GTHAN_S16);
    root = builtinVDef(root, typer, symbol_operator_lessThanOrEquals_s16, AST_BUILTIN_LETHAN_S16);
    root = builtinVDef(root, typer, symbol_operator_greaterThanOrEquals_s16, AST_BUILTIN_GETHAN_S16);
    root = builtinVDef(root, typer, symbol_operator_equals_s16, AST_BUILTIN_EQUALS_S16);
    root = builtinVDef(root, typer, symbol_operator_notEquals_s16, AST_BUILTIN_NOTEQUALS_S16);
    // s8:
    root = builtinVDef(root, typer, symbol_operator_quo_s8, AST_BUILTIN_QUO_S8);
    root = builtinVDef(root, typer, symbol_operator_mul_s8, AST_BUILTIN_MUL_S8);
    root = builtinVDef(root, typer, symbol_operator_rem_s8, AST_BUILTIN_REM_S8);
    root = builtinVDef(root, typer, symbol_operator_add_s8, AST_BUILTIN_ADD_S8);
    root = builtinVDef(root, typer, symbol_operator_subtract_s8, AST_BUILTIN_SUBTRACT_S8);
    root = builtinVDef(root, typer, symbol_operator_lessThan_s8, AST_BUILTIN_LTHAN_S8);
    root = builtinVDef(root, typer, symbol_operator_greaterThan_s8, AST_BUILTIN_GTHAN_S8);
    root = builtinVDef(root, typer, symbol_operator_lessThanOrEquals_s8, AST_BUILTIN_LETHAN_S8);
    root = builtinVDef(root, typer, symbol_operator_greaterThanOrEquals_s8, AST_BUILTIN_GETHAN_S8);
    root = builtinVDef(root, typer, symbol_operator_equals_s8, AST_BUILTIN_EQUALS_S8);
    root = builtinVDef(root, typer, symbol_operator_notEquals_s8, AST_BUILTIN_NOTEQUALS_S8);

    // u128:
    root = builtinVDef(root, typer, symbol_operator_mul_u128, AST_BUILTIN_MUL_U128);
    root = builtinVDef(root, typer, symbol_operator_quo_u128, AST_BUILTIN_QUO_U128);
    root = builtinVDef(root, typer, symbol_operator_rem_u128, AST_BUILTIN_REM_U128);
    root = builtinVDef(root, typer, symbol_operator_add_u128, AST_BUILTIN_ADD_U128);
    root = builtinVDef(root, typer, symbol_operator_subtract_u128, AST_BUILTIN_SUBTRACT_U128);
    root = builtinVDef(root, typer, symbol_operator_lessThan_u128, AST_BUILTIN_LTHAN_U128);
    root = builtinVDef(root, typer, symbol_operator_greaterThan_u128, AST_BUILTIN_GTHAN_U128);
    root = builtinVDef(root, typer, symbol_operator_lessThanOrEquals_u128, AST_BUILTIN_LETHAN_U128);
    root = builtinVDef(root, typer, symbol_operator_greaterThanOrEquals_u128, AST_BUILTIN_GETHAN_U128);
    root = builtinVDef(root, typer, symbol_operator_equals_u128, AST_BUILTIN_EQUALS_U128);
    root = builtinVDef(root, typer, symbol_operator_notEquals_u128, AST_BUILTIN_NOTEQUALS_U128);
    // u64:
    root = builtinVDef(root, typer, symbol_operator_mul_u64, AST_BUILTIN_MUL_U64);
    root = builtinVDef(root, typer, symbol_operator_quo_u64, AST_BUILTIN_QUO_U64);
    root = builtinVDef(root, typer, symbol_operator_rem_u64, AST_BUILTIN_REM_U64);
    root = builtinVDef(root, typer, symbol_operator_add_u64, AST_BUILTIN_ADD_U64);
    root = builtinVDef(root, typer, symbol_operator_subtract_u64, AST_BUILTIN_SUBTRACT_U64);
    root = builtinVDef(root, typer, symbol_operator_lessThan_u64, AST_BUILTIN_LTHAN_U64);
    root = builtinVDef(root, typer, symbol_operator_greaterThan_u64, AST_BUILTIN_GTHAN_U64);
    root = builtinVDef(root, typer, symbol_operator_lessThanOrEquals_u64, AST_BUILTIN_LETHAN_U64);
    root = builtinVDef(root, typer, symbol_operator_greaterThanOrEquals_u64, AST_BUILTIN_GETHAN_U64);
    root = builtinVDef(root, typer, symbol_operator_equals_u64, AST_BUILTIN_EQUALS_U64);
    root = builtinVDef(root, typer, symbol_operator_notEquals_u64, AST_BUILTIN_NOTEQUALS_U64);
    // u32:
    root = builtinVDef(root, typer, symbol_operator_mul_u32, AST_BUILTIN_MUL_U32);
    root = builtinVDef(root, typer, symbol_operator_quo_u32, AST_BUILTIN_QUO_U32);
    root = builtinVDef(root, typer, symbol_operator_rem_u32, AST_BUILTIN_REM_U32);
    root = builtinVDef(root, typer, symbol_operator_add_u32, AST_BUILTIN_ADD_U32);
    root = builtinVDef(root, typer, symbol_operator_subtract_u32, AST_BUILTIN_SUBTRACT_U32);
    root = builtinVDef(root, typer, symbol_operator_lessThan_u32, AST_BUILTIN_LTHAN_U32);
    root = builtinVDef(root, typer, symbol_operator_greaterThan_u32, AST_BUILTIN_GTHAN_U32);
    root = builtinVDef(root, typer, symbol_operator_lessThanOrEquals_u32, AST_BUILTIN_LETHAN_U32);
    root = builtinVDef(root, typer, symbol_operator_greaterThanOrEquals_u32, AST_BUILTIN_GETHAN_U32);
    root = builtinVDef(root, typer, symbol_operator_equals_u32, AST_BUILTIN_EQUALS_U32);
    root = builtinVDef(root, typer, symbol_operator_notEquals_u32, AST_BUILTIN_NOTEQUALS_U32);
    // u16:
    root = builtinVDef(root, typer, symbol_operator_mul_u16, AST_BUILTIN_MUL_U16);
    root = builtinVDef(root, typer, symbol_operator_quo_u16, AST_BUILTIN_QUO_U16);
    root = builtinVDef(root, typer, symbol_operator_rem_u16, AST_BUILTIN_REM_U16);
    root = builtinVDef(root, typer, symbol_operator_add_u16, AST_BUILTIN_ADD_U16);
    root = builtinVDef(root, typer, symbol_operator_subtract_u16, AST_BUILTIN_SUBTRACT_U16);
    root = builtinVDef(root, typer, symbol_operator_lessThan_u16, AST_BUILTIN_LTHAN_U16);
    root = builtinVDef(root, typer, symbol_operator_greaterThan_u16, AST_BUILTIN_GTHAN_U16);
    root = builtinVDef(root, typer, symbol_operator_lessThanOrEquals_u16, AST_BUILTIN_LETHAN_U16);
    root = builtinVDef(root, typer, symbol_operator_greaterThanOrEquals_u16, AST_BUILTIN_GETHAN_U16);
    root = builtinVDef(root, typer, symbol_operator_equals_u16, AST_BUILTIN_EQUALS_U16);
    root = builtinVDef(root, typer, symbol_operator_notEquals_u16, AST_BUILTIN_NOTEQUALS_U16);
    // u8:
    root = builtinVDef(root, typer, symbol_operator_quo_u8, AST_BUILTIN_QUO_U8);
    root = builtinVDef(root, typer, symbol_operator_mul_u8, AST_BUILTIN_MUL_U8);
    root = builtinVDef(root, typer, symbol_operator_rem_u8, AST_BUILTIN_REM_U8);
    root = builtinVDef(root, typer, symbol_operator_add_u8, AST_BUILTIN_ADD_U8);
    root = builtinVDef(root, typer, symbol_operator_subtract_u8, AST_BUILTIN_SUBTRACT_U8);
    root = builtinVDef(root, typer, symbol_operator_lessThan_u8, AST_BUILTIN_LTHAN_U8);
    root = builtinVDef(root, typer, symbol_operator_greaterThan_u8, AST_BUILTIN_GTHAN_U8);
    root = builtinVDef(root, typer, symbol_operator_lessThanOrEquals_u8, AST_BUILTIN_LETHAN_U8);
    root = builtinVDef(root, typer, symbol_operator_greaterThanOrEquals_u8, AST_BUILTIN_GETHAN_U8);
    root = builtinVDef(root, typer, symbol_operator_equals_u8, AST_BUILTIN_EQUALS_U8);
    root = builtinVDef(root, typer, symbol_operator_notEquals_u8, AST_BUILTIN_NOTEQUALS_U8);
    // u1:
    root = builtinVDef(root, typer, symbol_operator_quo_u1, AST_BUILTIN_QUO_U1);
    root = builtinVDef(root, typer, symbol_operator_mul_u1, AST_BUILTIN_MUL_U1);
    root = builtinVDef(root, typer, symbol_operator_rem_u1, AST_BUILTIN_REM_U1);
    root = builtinVDef(root, typer, symbol_operator_add_u1, AST_BUILTIN_ADD_U1);
    root = builtinVDef(root, typer, symbol_operator_subtract_u1, AST_BUILTIN_SUBTRACT_U1);
    root = builtinVDef(root, typer, symbol_operator_lessThan_u1, AST_BUILTIN_LTHAN_U1);
    root = builtinVDef(root, typer, symbol_operator_greaterThan_u1, AST_BUILTIN_GTHAN_U1);
    root = builtinVDef(root, typer, symbol_operator_lessThanOrEquals_u1, AST_BUILTIN_LETHAN_U1);
    root = builtinVDef(root, typer, symbol_operator_greaterThanOrEquals_u1, AST_BUILTIN_GETHAN_U1);
    root = builtinVDef(root, typer, symbol_operator_equals_u1, AST_BUILTIN_EQUALS_U1);
    root = builtinVDef(root, typer, symbol_operator_notEquals_u1, AST_BUILTIN_NOTEQUALS_U1);

    return root;
}
Defn* lookupSymbolUntil(Scope* scope, SymbolID lookupID, Scope* endScopeP, AstContext context) {
    if (lookupID == SYM_NULL) {
        return NULL;
    }
    if (scope->context == context && scope->defnID == lookupID) {
        return scope;
    }
    if (scope == endScopeP) {
        // this is the last scope
        // we haven't found the symbol
        // return NULL => not found.
        return NULL;
    } else {
        // try repeating on parent
        if (scope->parent) {
            return lookupSymbolUntil(scope->parent, lookupID, endScopeP, context);
        } else {
            return NULL;
        }
    }
}

//
// Implementation:
//

// primer_pre and primer_post are the pre and post visitor callbacks for the primer pass.
// - primer_pre runs before all children are visited (prefix order)
// - primer_post runs after all children are visited (postfix order)
static int primer_pre(void* primer, AstNode* node);
static int primer_post(void* primer, AstNode* node);

int primer_pre(void* rawPrimer, AstNode* node) {
    Primer* primer = rawPrimer;
    SetAstNodeLookupContext(node,topFrameContext(primer));
    AstNode* topFunc = topFrameFunc(primer);
    if (topFunc) {
        SetAstNodeParentFunc(node,topFunc);
    }
    
    AstKind kind = GetAstNodeKind(node);
    switch (kind) {
        case AST_TID:
        {
            SetAstIdLookupScope(node, topFrameScope(primer));
            SetAstNodeLookupContext(node, ASTCTX_TYPING);
            break;
        }
        case AST_VID:
        {
            SetAstIdLookupScope(node, topFrameScope(primer));
            SetAstNodeLookupContext(node, ASTCTX_VALUE);
            break;
        }
        case AST_VLET:
        {
            break;
        }
        case AST_VSTRUCT:
        {
            break;
        }
        case AST_TPATTERN:
        case AST_VPATTERN:
        {
            break;
        }
        case AST_VPAREN:
        case AST_CHAIN:
        {
            pushFrame(primer, NULL, ASTCTX_VALUE, topFrameFunc(primer));
            break;
        }
        case AST_UNARY:
        {
            break;
        }
        case AST_BINARY:
        {
            break;
        }
        case AST_TPATTERN_SINGLETON:
        case AST_TPATTERN_FIELD:
        case AST_VPATTERN_SINGLETON:
        case AST_VPATTERN_FIELD:
        {
            // defining and storing on pattern

            int isTyping = ((kind == AST_TPATTERN_SINGLETON) || (kind == AST_TPATTERN_FIELD));
            int isValue = ((kind == AST_VPATTERN_SINGLETON) || (kind == AST_VPATTERN_FIELD));

            Loc loc = GetAstNodeLoc(node);
            SymbolID defnID = SYM_NULL;
            if (kind == AST_TPATTERN_SINGLETON || kind == AST_VPATTERN_SINGLETON) {
                defnID = GetAstSingletonPatternName(node);
            } else {
                defnID = GetAstFieldName(node);
            }

            void* patternType = NewMetavarType(loc, primer->typer, "%cpattern:%s", (isValue ? 'v':'t'), GetSymbolText(defnID));
            pushSymbol(primer, defnID, patternType, node, (isValue ? ASTCTX_VALUE:ASTCTX_TYPING), 0);
            
            if (isValue) {
                SetAstNodeTypingExt_Value(node,patternType);
            } else {
                SetAstNodeTypingExt_Type(node,patternType);
            }

            if (isValue) {
                // pushing a new typing frame for RHS in mixed (value/type) items:
                pushFrame(primer,NULL,ASTCTX_TYPING,topFrameFunc(primer));
            }

            break;
        }
        case AST_VSTRUCT_FIELD:
        {
            // SymbolID defnID = GetAstFieldName(node);
            SetAstNodeTypingExt_Value(node, GetAstNodeTypingExt_Value(GetAstFieldRhs(node)));
            break;
        }
        case AST_LAMBDA:
        {
            // pushing a new frame for the function's contents:
            pushFrame(primer,NULL,ASTCTX_VALUE,node);
            break;
        }
        case AST_EXTERN:
        case AST_TDEF:
        {
            pushFrame(primer,NULL,ASTCTX_TYPING,topFrameFunc(primer));
            break;
        }
        case AST_VCAST:
        {
            // push a value scope, let type2val push a separate type scope.
            pushFrame(primer,NULL,ASTCTX_VALUE,topFrameFunc(primer));
            break;
        }
        case AST_TYPE2VAL:
        {
            // push a type scope, just for this little typespec
            pushFrame(primer,NULL,ASTCTX_TYPING,topFrameFunc(primer));
            break;
        }
        default:
        {
            break;
        }
    }
    return 1;
}
int primer_post(void* rawPrimer, AstNode* node) {
    Primer* primer = rawPrimer;
    AstKind kind = GetAstNodeKind(node);
    switch (kind) {
        case AST_CHAIN:
        case AST_VPAREN:
        case AST_LAMBDA:
        case AST_VPATTERN_FIELD:
        case AST_EXTERN:
        case AST_TDEF:
        case AST_VCAST:
        case AST_TYPE2VAL:
        {
            // pop for each case where a frame is pushed in `primer_pre`.
            popFrame(primer);
            break;
        }
        default:
        {
            break;
        }
    }
    return 1;
}

//
//
// API:
//
//

Primer* CreatePrimer(void* typer) {
    return createPrimer(typer);
}
int PrimeModule(Primer* primer, AstNode* module) {
    if (DEBUG) {
        assert(GetAstNodeKind(module) == AST_MODULE);
    }

    // defining all module-symbols in one go, storing as typing extensions:
    pushFrame(primer,NULL,ASTCTX_VALUE,topFrameFunc(primer));
    size_t moduleStmtLength = GetAstModuleLength(module);
    for (size_t index = 0; index < moduleStmtLength; index++) {
        // todo: HACKY let the symbol define itself as type or value in `PrimeModule`
        AstNode* stmt = GetAstModuleStmtAt(module, index);
        Loc loc = GetAstNodeLoc(stmt);
        AstKind stmtKind = GetAstNodeKind(stmt);
        if (stmtKind == AST_VDEF) {
            SymbolID lhs = GetAstDefValueStmtLhs(stmt);
            void* valueType = NewMetavarType(loc,primer->typer,"def-func:%s",GetSymbolText(lhs));
            pushSymbol(primer,lhs,valueType,stmt,ASTCTX_VALUE,1);
            SetAstNodeTypingExt_Value(stmt,valueType);
        } else if (stmtKind == AST_EXTERN) {
            SymbolID lhs = GetAstExternStmtName(stmt);
            void* valueType = NewMetavarType(loc,primer->typer,"extern:%s",GetSymbolText(lhs));
            pushSymbol(primer,lhs,valueType,stmt,ASTCTX_VALUE,1);
            SetAstNodeTypingExt_Value(stmt,valueType);
        } else if (stmtKind == AST_TDEF) {
            SymbolID lhs = GetAstTypedefStmtName(stmt);
            char const* symbolText = GetSymbolText(lhs);
            void* typingType = NewMetavarType(loc,primer->typer,"typedef:%s",symbolText);
            pushSymbol(primer,lhs,typingType,stmt,ASTCTX_TYPING,0);
            SetAstNodeTypingExt_Type(stmt, typingType);
        } else {
            if (DEBUG) {
                printf("!!- PrimeModule: Unsupported statement kind in module\n");
            } else {
                assert(0 && "PrimeModule: Unsupported statement kind in module");
            }
        }
    }
    // visiting the AST:
    if (!RecursivelyVisitAstNode(primer, module, primer_pre, primer_post)) {
        return 0;
    }
    popFrame(primer);
    return 1;
}
Defn* LookupSymbol(Scope* scope, SymbolID lookupID, AstContext context) {
    return lookupSymbolUntil(scope, lookupID, NULL, context);
}
Defn* LookupSymbolUntil(Scope* scope, SymbolID lookupID, Scope* endScopeP, AstContext context) {
    return lookupSymbolUntil(scope, lookupID, endScopeP, context);
}

// After definition, IDs are looked up, map to type IDs.
// These type IDs can be stored in the AST.

SymbolID GetDefnName(Defn* defn) {
    return defn->defnID;
}
AstNode* GetDefnNode(Defn* defn) {
    return defn->defnAstNode;
}
AstContext GetDefnContext(Defn* defn) {
    return defn->context;
}
void* GetDefnType(Defn* defn) {
    return defn->type;
}
