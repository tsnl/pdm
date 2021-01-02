#include "manager.hh"

namespace pdm::ast {
    Manager::Manager(types::Manager* typer, size_t pool_size_in_bytes)
    : m_typer(typer),
      m_pool(new u8[pool_size_in_bytes]),
      m_pool_size_in_bytes(pool_size_in_bytes),
      m_pool_used_in_bytes(0) {}
    
    Manager::~Manager() {
        if (m_pool != nullptr) {
            delete[] m_pool;
        }
        m_pool_size_in_bytes = 0;
        m_pool_used_in_bytes = 0;
    }

    Script* Manager::new_script(source::Source* source, source::Loc loc, std::vector<Stmt*>&& stmts) {
        return emplace<Script>(source, loc, std::move(stmts));
    }

    ArrayExp* Manager::new_array_exp(source::Loc loc, std::vector<Exp*>&& items) {
        return emplace<ArrayExp>(loc, std::move(items));
    }
    BinaryExp* Manager::new_binary_exp(source::Loc loc, BinaryOperator binary_operator, Exp* lhs_operand, Exp* rhs_operand) {
        return emplace<BinaryExp>(loc, binary_operator, lhs_operand, rhs_operand);
    }
    ChainExp* Manager::new_chain_exp(source::Loc loc, std::vector<Stmt*>&& prefix, Exp* suffix) {
        return emplace<ChainExp>(loc, std::move(prefix), suffix);
    }
    DotNameExp* Manager::new_dot_name_exp(source::Loc loc, Exp* lhs, intern::String rhs_name, DotNameExp::RhsHint rhs_hint) {
        return emplace<DotNameExp>(loc, lhs, rhs_name, rhs_hint);
    }
    DotIndexExp* Manager::new_dot_index_exp(source::Loc loc, Exp* lhs, Exp* rhs_exp, DotIndexExp::RhsHint rhs_hint) {
        return emplace<DotIndexExp>(loc, lhs, rhs_exp, rhs_hint);
    }
    FloatExp* Manager::new_float_exp(source::Loc loc, long double value) {
        return emplace<FloatExp>(loc, value);
    }
    IdExp* Manager::new_id_exp(source::Loc loc, intern::String name) {
        return emplace<IdExp>(loc, name);
    }
    IfExp* Manager::new_if_exp(source::Loc loc, Exp* cond_exp, Exp* then_exp, Exp* else_exp) {
        return emplace<IfExp>(loc, cond_exp, then_exp, else_exp);
    }
    IntExp* Manager::new_int_exp(source::Loc loc, u64 value, IntExp::Base base) {
        return emplace<IntExp>(loc, value, base);
    }
    LambdaExp* Manager::new_lambda_exp(source::Loc loc, VPattern* lhs_lpattern, Exp* body) {
        return emplace<LambdaExp>(loc, lhs_lpattern, body);
    }
    ParenExp* Manager::new_paren_exp(source::Loc loc, Exp* nested) {
        return emplace<ParenExp>(loc, nested);
    }
    StringExp* Manager::new_string_exp(source::Loc loc, utf8::String content, StringExp::QuoteKind quote_kind) {
        return emplace<StringExp>(loc, content, quote_kind);
    }
    StringExp* Manager::new_string_exp(source::Loc loc, std::vector<StringExp::Piece>&& content) {
        return emplace<StringExp>(loc, std::move(content));
    }
    StructExp* Manager::new_struct_exp(source::Loc loc, std::vector<StructExp::Field*>&& fields) {
        return emplace<StructExp>(loc, std::move(fields));
    }
    TCallExp* Manager::new_tcall_exp(source::Loc loc, Exp* lhs_called, std::vector<TArg*>&& args) {
        return emplace<TCallExp>(loc, lhs_called, std::move(args));
    }
    TupleExp* Manager::new_tuple_exp(source::Loc loc, std::vector<Exp*>&& items) {
        return emplace<TupleExp>(loc, std::move(items));
    }
    TypeQueryExp* Manager::new_type_query_exp(source::Loc loc, TypeQueryKind kind, Typespec* lhs_typespec, Typespec* rhs_typespec) {
        return emplace<TypeQueryExp>(loc, kind, lhs_typespec, rhs_typespec);
    }
    UnaryExp* Manager::new_unary_exp(source::Loc loc, UnaryOperator unary_operator, Exp* operand) {
        return emplace<UnaryExp>(loc, unary_operator, operand);
    }
    UnitExp* Manager::new_unit_exp(source::Loc loc) {
        return emplace<UnitExp>(loc);
    }
    VCallExp* Manager::new_vcall_exp(source::Loc loc, Exp* lhs_called, std::vector<VArg*>&& args) {
        return emplace<VCallExp>(loc, lhs_called, std::move(args));
    }
    StructExp::Field* Manager::new_struct_exp_field(source::Loc loc, intern::String name, Exp* value) {
        return emplace<StructExp::Field>(loc, name, value);
    }
    
    LPattern* Manager::new_lpattern(source::Loc loc, std::vector<LPattern::Field*>&& fields) {
        return emplace<LPattern>(loc, std::move(fields));
    }
    TPattern* Manager::new_tpattern(source::Loc loc, std::vector<TPattern::Field*>&& fields, bool is_only_captured) {
        return emplace<TPattern>(loc, std::move(fields), is_only_captured);
    }
    VPattern* Manager::new_vpattern(source::Loc loc, std::vector<VPattern::Field*>&& fields) {
        return emplace<VPattern>(loc, std::move(fields));
    }
    LPattern::Field* Manager::new_lpattern_field(source::Loc loc, LPattern::FieldKind kind, intern::String name, Typespec* opt_rhs_typespec) {
        return emplace<LPattern::Field>(loc, kind, name, opt_rhs_typespec);
    }
    TPattern::Field* Manager::new_tpattern_field(source::Loc loc, TPattern::FieldKind kind, intern::String name, Typespec* rhs_typespec) {
        return emplace<TPattern::Field>(loc, kind, name, rhs_typespec);
    }
    VPattern::Field* Manager::new_vpattern_field(source::Loc loc, intern::String name, Typespec* rhs_typespec, VArgKind varg_kind) {
        return emplace<VPattern::Field>(loc, name, rhs_typespec, varg_kind);
    }

    BuiltinTypeStmt* Manager::new_builtin_type_stmt(std::string&& desc) {
        return emplace<BuiltinTypeStmt>(std::move(desc));
    }
    ConstStmt* Manager::new_const_stmt(source::Loc loc, LPattern* lhs_lpattern, Exp* rhs_exp) {
        return emplace<ConstStmt>(loc, lhs_lpattern, rhs_exp);
    }
    DiscardStmt* Manager::new_discard_stmt(source::Loc loc, Exp* exp) {
        return emplace<DiscardStmt>(loc, exp);
    }
    ValStmt* Manager::new_val_stmt(source::Loc loc, LPattern* lhs_lpattern, Exp* rhs_exp) {
        return emplace<ValStmt>(loc, lhs_lpattern, rhs_exp);
    }
    VarStmt* Manager::new_var_stmt(source::Loc loc, LPattern* lhs_lpattern, Exp* rhs_exp) {
        return emplace<VarStmt>(loc, lhs_lpattern, rhs_exp);
    }
    SetStmt* Manager::new_set_stmt(source::Loc loc, Exp* lhs, Exp* rhs) {
        return emplace<SetStmt>(loc, lhs, rhs);
    }
    
    ImportStmt* Manager::new_import_stmt(source::Loc loc, intern::String imported_name, utf8::String imported_from_exp, utf8::String imported_type_exp) {
        return emplace<ImportStmt>(loc, imported_name, imported_from_exp, imported_type_exp);
    }
    UsingStmt* Manager::new_using_stmt(source::Loc loc, intern::String module_name, std::string suffix) {
        return emplace<UsingStmt>(loc, module_name, suffix);
    }
    ExternStmt* Manager::new_extern_stmt(source::Loc loc, intern::String ext_mod_name, Exp* link_arg) {
        return emplace<ExternStmt>(loc, ext_mod_name, link_arg);
    }
    ModStmt* Manager::new_mod_stmt(source::Loc loc, intern::String module_name, std::vector<Stmt*>&& defns) {
        return emplace<ModStmt>(loc, module_name, std::move(defns));
    }
    FnStmt* Manager::new_fn_stmt(source::Loc loc, intern::String name, std::vector<TPattern*>&& tpatterns, VPattern* vpattern, Typespec* opt_return_ts, Exp* body) {
        return emplace<FnStmt>(loc, name, std::move(tpatterns), vpattern, opt_return_ts, body);
    }
    TypeStmt* Manager::new_type_stmt(source::Loc loc, intern::String lhs_name, std::vector<TPattern*>&& tpatterns, Typespec* rhs_typespec) {
        return emplace<TypeStmt>(loc, lhs_name, std::move(tpatterns), rhs_typespec);
    }
    EnumStmt* Manager::new_enum_stmt(source::Loc loc, intern::String name, std::vector<EnumStmt::Field*>&& fields) {
        return emplace<EnumStmt>(loc, name, std::move(fields));
    }
    TypeclassStmt* Manager::new_typeclass_stmt(source::Loc loc, intern::String lhs_name, intern::String candidate_name, Typespec* candidate_typespec, std::vector<TPattern*>&& tpatterns, std::vector<TypeQueryExp*>&& conditions) {
        return emplace<TypeclassStmt>(loc, lhs_name, candidate_name, candidate_typespec, std::move(tpatterns), std::move(conditions));
    }
    EnumStmt::Field* Manager::new_enum_stmt_field(source::Loc loc, intern::String name, std::vector<ast::Typespec*>&& typespecs, bool has_explicit_typespecs) {
        return emplace<EnumStmt::Field>(loc, name, std::move(typespecs), has_explicit_typespecs);
    }
    
    DotNameTypespec_TypePrefix* Manager::new_dot_name_typespec_with_type_prefix(source::Loc loc, Typespec* lhs_typespec, intern::String rhs_name) {
        return emplace<DotNameTypespec_TypePrefix>(loc, lhs_typespec, rhs_name);
    }
    DotNameTypespec_ModPrefix* Manager::new_dot_name_typespec_with_mod_prefix(source::Loc loc, std::vector<intern::String>&& lhs_prefixes, intern::String rhs_name) {
        return emplace<DotNameTypespec_ModPrefix>(loc, std::move(lhs_prefixes), rhs_name);
    }
    FnTypespec* Manager::new_fn_typespec(source::Loc loc, VPattern* lhs_vpattern, Typespec* rhs_typespec) {
        return emplace<FnTypespec>(loc, lhs_vpattern, rhs_typespec);
    }
    IdTypespec* Manager::new_id_typespec(source::Loc loc, intern::String name) {
        return emplace<IdTypespec>(loc, name);
    }
    ParenTypespec* Manager::new_paren_typespec(source::Loc loc, Typespec* nested_typespec) {
        return emplace<ParenTypespec>(loc, nested_typespec);
    }
    StructTypespec* Manager::new_struct_typespec(source::Loc loc, std::vector<StructTypespec::Field*>&& fields) {
        return emplace<StructTypespec>(loc, std::move(fields));
    }
    TCallTypespec* Manager::new_tcall_typespec(source::Loc loc, Typespec* lhs_called, std::vector<TArg*>&& args) {
        return emplace<TCallTypespec>(loc, lhs_called, std::move(args));
    }
    TupleTypespec* Manager::new_tuple_typespec(source::Loc loc, std::vector<Typespec*>&& items) {
        return emplace<TupleTypespec>(loc, std::move(items));
    }
    StructTypespec::Field* Manager::new_struct_typespec_field(source::Loc loc, intern::String name, Typespec* typespec) {
        return emplace<StructTypespec::Field>(loc, name, typespec);
    }

    TArg* Manager::new_targ_exp(source::Loc loc, Exp* exp) {
        return emplace<TArg>(loc, exp);
    }
    TArg* Manager::new_targ_typespec(source::Loc loc, Typespec* typespec) {
        return emplace<TArg>(loc, typespec);
    }
    VArg* Manager::new_varg(source::Loc loc, Exp* exp, VArgKind varg_kind) {
        return emplace<VArg>(loc, exp, varg_kind);
    }
}
