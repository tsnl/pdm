#include "manager.hh"
#include "pdm/compiler/compiler.hh"

#include "pdm/ast/arg/varg.hh"

namespace pdm::ast {
    Manager::Manager(Compiler* compiler_ptr, size_t pool_size_in_bytes)
    : m_compiler_ptr(compiler_ptr),
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

    Compiler* Manager::compiler() {
        return m_compiler_ptr;
    }
    types::Manager* Manager::types_mgr() const {
        return m_compiler_ptr->types_mgr();
    }

    Script* Manager::new_script(source::Source* source, source::Loc loc, std::vector<Stmt*>&& head_stmts, std::vector<ModStmt*>&& body_mod_stmts) {
        return emplace<Script>(source, loc, std::move(head_stmts), std::move(body_mod_stmts));
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
    StructDotNameExp* Manager::new_struct_dot_name_exp(source::Loc loc, Exp* lhs, intern::String rhs_name) {
        return emplace<StructDotNameExp>(loc, lhs, rhs_name);
    }
    EnumDotNameExp* Manager::new_enum_dot_name_exp(source::Loc loc, Exp* lhs, intern::String rhs_name, std::vector<ast::Exp*>&& args) {
        return emplace<EnumDotNameExp>(loc, lhs, rhs_name, std::move(args));
    }
    ModuleDotExp* Manager::new_module_dot_exp(source::Loc loc, std::vector<intern::String>&& module_names, intern::String rhs_name) {
        return emplace<ModuleDotExp>(loc, std::move(module_names), rhs_name);
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
    IntExp* Manager::new_int_exp(source::Loc loc, u64 value, IntExp::Base base, bool force_unsigned) {
        return emplace<IntExp>(loc, value, base, force_unsigned);
    }
    LambdaExp* Manager::new_lambda_exp(source::Loc loc, VPattern* lhs_lpattern, TypeSpec* opt_ret_typespec, Exp* body) {
        return emplace<LambdaExp>(loc, lhs_lpattern, opt_ret_typespec, body);
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
    TypeQueryExp* Manager::new_type_query_exp(source::Loc loc, TypeQueryKind kind, TypeSpec* lhs_typespec, TypeSpec* rhs_typespec) {
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
    
    LPattern* Manager::new_lpattern(source::Loc loc, std::vector<LPattern::Field*>&& fields, bool destructure) {
        return emplace<LPattern>(loc, std::move(fields), destructure);
    }
    TPattern* Manager::new_tpattern(source::Loc loc, std::vector<TPattern::Field*>&& fields, bool is_only_captured) {
        return emplace<TPattern>(loc, std::move(fields), is_only_captured);
    }
    VPattern* Manager::new_vpattern(source::Loc loc, std::vector<VPattern::Field*>&& fields) {
        return emplace<VPattern>(loc, std::move(fields));
    }
    LPattern::Field* Manager::new_lpattern_field(source::Loc loc, LPattern::FieldKind kind, intern::String name, TypeSpec* opt_rhs_typespec) {
        return emplace<LPattern::Field>(loc, kind, name, opt_rhs_typespec);
    }
    TPattern::Field* Manager::new_tpattern_field(source::Loc loc, TPattern::FieldKind kind, intern::String name, SetSpec* rhs_set_spec) {
        return emplace<TPattern::Field>(loc, kind, name, rhs_set_spec);
    }
    VPattern::Field* Manager::new_vpattern_field(source::Loc loc, intern::String name, TypeSpec* rhs_typespec, VArgAccessSpec varg_kind) {
        return emplace<VPattern::Field>(loc, name, rhs_typespec, varg_kind);
    }

    BuiltinStmt* Manager::new_builtin_stmt(std::string&& desc) {
        return emplace<BuiltinStmt>(std::move(desc));
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
    ModStmt* Manager::new_mod_stmt(source::Loc loc, intern::String module_name, std::vector<TPattern*>&& args, std::vector<ModContentStmt*>&& defns) {
        return emplace<ModStmt>(loc, module_name, std::move(args), std::move(defns), ModStmtKind::TopModule);
    }
    ModValStmt* Manager::new_internal_mod_val_stmt(
        source::Loc loc,
        intern::String name,
        std::vector<TPattern*>&& tpatterns,
        Exp* body
    ) {
        return emplace<ModValStmt>(loc, name, std::move(tpatterns), body);
    }
    ModValStmt* Manager::new_external_mod_val_stmt(
        source::Loc loc,
        intern::String name,
        std::vector<TPattern*>&& tpatterns,
        TypeSpec* ext_typespec,
        intern::String ext_mod_name,
        utf8::String ext_fn_name
    ) {
        return emplace<ModValStmt>(loc, name, std::move(tpatterns), ext_typespec, ext_mod_name, ext_fn_name);
    }
    ModTypeStmt* Manager::new_mod_type_stmt(source::Loc loc, intern::String lhs_name, std::vector<TPattern*>&& tpatterns, TypeSpec* rhs_typespec) {
        return emplace<ModTypeStmt>(loc, lhs_name, std::move(tpatterns), rhs_typespec);
    }
    ModEnumStmt* Manager::new_mod_enum_stmt(source::Loc loc, intern::String name, std::vector<TPattern*>&& tpatterns, std::vector<ModEnumStmt::Field*>&& fields) {
        return emplace<ModEnumStmt>(loc, name, std::move(tpatterns), std::move(fields));
    }
    ModTypeclassStmt* Manager::new_mod_typeclass_stmt(source::Loc loc, intern::String lhs_name, intern::String candidate_name, ClassSpec* candidate_typespec, std::vector<TPattern*>&& tpatterns, std::vector<TypeQueryExp*>&& conditions) {
        return emplace<ModTypeclassStmt>(loc, lhs_name, candidate_name, candidate_typespec, std::move(tpatterns), std::move(conditions));
    }
    ModEnumStmt::Field* Manager::new_enum_stmt_field(source::Loc loc, intern::String name, std::vector<ast::TypeSpec*>&& typespecs, bool has_explicit_typespecs) {
        return emplace<ModEnumStmt::Field>(loc, name, std::move(typespecs), has_explicit_typespecs);
    }
    
    DotNameTypeSpec_ModPrefix* Manager::new_dot_name_type_spec_with_mod_prefix(source::Loc loc, std::vector<intern::String>&& lhs_prefixes, intern::String rhs_name) {
        return emplace<DotNameTypeSpec_ModPrefix>(loc, std::move(lhs_prefixes), rhs_name);
    }
    FnTypeSpec* Manager::new_fn_type_spec(source::Loc loc, VPattern* lhs_vpattern, TypeSpec* rhs_typespec) {
        return emplace<FnTypeSpec>(loc, lhs_vpattern, rhs_typespec);
    }
    IdTypeSpec* Manager::new_id_type_spec(source::Loc loc, intern::String name) {
        return emplace<IdTypeSpec>(loc, name);
    }
    IdClassSpec* Manager::new_id_class_spec(source::Loc loc, intern::String name) {
        return emplace<IdClassSpec>(loc, name);
    }
    TCallClassSpec* Manager::new_tcall_class_spec(source::Loc loc, ClassSpec* lhs_called, std::vector<TArg*>&& args) {
        return emplace<TCallClassSpec>(loc, lhs_called, std::move(args));
    }
    ParenTypeSpec* Manager::new_paren_type_spec(source::Loc loc, TypeSpec* nested_typespec) {
        return emplace<ParenTypeSpec>(loc, nested_typespec);
    }
    StructTypeSpec* Manager::new_struct_type_spec(source::Loc loc, std::vector<StructTypeSpec::Field*>&& fields) {
        return emplace<StructTypeSpec>(loc, std::move(fields));
    }
    TCallTypeSpec* Manager::new_tcall_type_spec(source::Loc loc, TypeSpec* lhs_called, std::vector<TArg*>&& args) {
        return emplace<TCallTypeSpec>(loc, lhs_called, std::move(args));
    }
    TupleTypeSpec* Manager::new_tuple_type_spec(source::Loc loc, std::vector<TypeSpec*>&& items) {
        return emplace<TupleTypeSpec>(loc, std::move(items));
    }
    StructTypeSpec::Field* Manager::new_struct_type_spec_field(source::Loc loc, intern::String name, TypeSpec* typespec) {
        return emplace<StructTypeSpec::Field>(loc, name, typespec);
    }

    TArg* Manager::new_targ_exp(source::Loc loc, Exp* exp) {
        return emplace<TArg>(loc, exp);
    }
    TArg* Manager::new_targ_type_spec(source::Loc loc, TypeSpec* typespec) {
        return emplace<TArg>(loc, typespec);
    }
    VArg* Manager::new_varg(source::Loc loc, Exp* exp, VArgAccessSpec varg_kind) {
        return emplace<VArg>(loc, exp, varg_kind);
    }
}
