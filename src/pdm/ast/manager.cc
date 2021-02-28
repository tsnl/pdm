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

    Script* Manager::new_script(
        source::Source* source, source::Loc loc,
        std::vector<HeaderStmt*>&& head_stmts, std::vector<Script::Field*>&& body_mod_stmts
    ) {
        return emplace<Script>(source, loc, std::move(head_stmts), std::move(body_mod_stmts));
    }
    Script::Field* Manager::new_script_field(source::Loc loc, intern::String name, ast::ModExp* mod_exp) {
        return emplace<Script::Field>(loc, name, mod_exp);
    }

    ModExp* Manager::new_mod_exp(
        source::Loc loc,
        ast::TPattern* opt_template_pattern, std::vector<ast::ModExp::Field*>&& fields
    ) {
        return emplace<ModExp>(loc, std::move(fields), opt_template_pattern);
    }
    ModExp::ModuleField* Manager::new_mod_mod_field(
        source::Loc loc,
        intern::String lhs_name, ast::ModExp* mod_exp
    ) {
        return emplace<ModExp::ModuleField>(loc, lhs_name, mod_exp);
    }
    ModExp::ValueField* Manager::new_value_mod_field(
        source::Loc loc,
        intern::String lhs_name, ast::Exp* rhs_exp
    ) {
        return emplace<ModExp::ValueField>(loc, lhs_name, rhs_exp);
    }
    ModExp::TypeField* Manager::new_type_mod_field(
        source::Loc loc,
        intern::String lhs_name, ast::TypeSpec* rhs_type_spec
    ) {
        return emplace<ModExp::TypeField>(loc, lhs_name, rhs_type_spec);
    }
    ModExp::ClassField* Manager::new_class_mod_field(
        source::Loc loc,
        intern::String lhs_name, ast::ClassSpec* rhs_class_spec
    ) {
        return emplace<ModExp::ClassField>(loc, lhs_name, rhs_class_spec);
    }
    ModAddress* Manager::new_mod_address(
        source::Loc loc,
        ModAddress* opt_lhs, intern::String rhs_name,
        std::vector<ast::TArg*>&& template_args
    ) {
        return emplace<ModAddress>(loc, opt_lhs, rhs_name, std::move(template_args));
    }


    ArrayExp* Manager::new_array_exp(
        source::Loc loc, std::vector<Exp*>&& items
    ) {
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
    EnumDotNameExp* Manager::new_enum_dot_name_exp(source::Loc loc, TypeSpec* lhs, intern::String rhs_name, Exp* opt_using_arg) {
        return emplace<EnumDotNameExp>(loc, lhs, rhs_name, opt_using_arg);
    }
    ModuleDotExp* Manager::new_module_dot_name_exp(source::Loc loc, ast::ModAddress* lhs_address, intern::String rhs_name) {
        return emplace<ModuleDotExp>(loc, lhs_address, rhs_name);
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
    LambdaExp* Manager::new_lambda_exp(source::Loc loc, FnTypeSpec* fn_type_spec, Exp* body) {
        return emplace<LambdaExp>(loc, fn_type_spec, body);
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
    // TPattern::Field* Manager::new_tpattern_field(source::Loc loc, TPattern::FieldKind kind, intern::String name, SetSpec* rhs_set_spec) {
    //     return emplace<TPattern::Field>(loc, kind, name, rhs_set_spec);
    // }
    TPattern::Field* Manager::new_value_tpattern_field(source::Loc loc, intern::String name, TypeSpec* type_spec) {
        return emplace<TPattern::Field>(loc, TPattern::FieldKind::Value, name, type_spec);
    }
    TPattern::Field* Manager::new_type_tpattern_field(source::Loc loc, intern::String name, ClassSpec* class_spec) {
        return emplace<TPattern::Field>(loc, TPattern::FieldKind::Type, name, class_spec);
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
    
    ImportStmt* Manager::new_import_stmt(source::Loc loc, intern::String import_name, utf8::String imported_from_exp, utf8::String imported_type_exp) {
        return emplace<ImportStmt>(loc, import_name, imported_from_exp, imported_type_exp);
    }
    UsingStmt* Manager::new_using_stmt(source::Loc loc, intern::String module_name, std::string suffix) {
        return emplace<UsingStmt>(loc, module_name, suffix);
    }
    ExternStmt* Manager::new_extern_stmt(source::Loc loc, intern::String ext_mod_name, Exp* link_arg) {
        return emplace<ExternStmt>(loc, ext_mod_name, link_arg);
    }
    ModAddressIdTypeSpec* Manager::new_ma_type_spec(source::Loc loc, ast::ModAddress* lhs_mod_address, intern::String rhs_name) {
        return emplace<ModAddressIdTypeSpec>(loc, lhs_mod_address, rhs_name);
    }
    FnTypeSpec* Manager::new_fn_type_spec(source::Loc loc, VPattern* lhs_vpattern, TypeSpec* rhs_typespec) {
        return emplace<FnTypeSpec>(loc, lhs_vpattern, rhs_typespec);
    }
    IdTypeSpec* Manager::new_id_type_spec(source::Loc loc, intern::String name) {
        return emplace<IdTypeSpec>(loc, name);
    }
    StructTypeSpec* Manager::new_struct_type_spec(source::Loc loc, std::vector<StructTypeSpec::Field*>&& fields) {
        return emplace<StructTypeSpec>(loc, std::move(fields));
    }
    EnumTypeSpec* Manager::new_enum_type_spec(source::Loc loc, std::vector<EnumTypeSpec::Field*>&& fields) {
        return emplace<EnumTypeSpec>(loc, std::move(fields));
    }
    TupleTypeSpec* Manager::new_tuple_type_spec(source::Loc loc, std::vector<TypeSpec*>&& items) {
        return emplace<TupleTypeSpec>(loc, std::move(items));
    }
    StructTypeSpec::Field* Manager::new_struct_type_spec_field(source::Loc loc, intern::String name, TypeSpec* type_spec) {
        return emplace<StructTypeSpec::Field>(loc, name, type_spec);
    }
    EnumTypeSpec::Field* Manager::new_enum_type_spec_field(source::Loc loc, intern::String name, TypeSpec* opt_type_spec) {
        return emplace<EnumTypeSpec::Field>(loc, name, opt_type_spec);
    }

    IdClassSpec* Manager::new_id_class_spec(source::Loc loc, intern::String name) {
        return emplace<IdClassSpec>(loc, name);
    }
    ClassExpClassSpec* Manager::new_class_exp_class_spec(
        source::Loc loc,
        intern::String candidate_type_name,
        ClassSpec* candidate_class_name,
        std::vector<ast::TypeQueryExp*>&& type_query_exps
    ) {
        return emplace<ClassExpClassSpec>(loc, candidate_type_name, candidate_class_name, std::move(type_query_exps));
    }
    ModAddressIdClassSpec* Manager::new_ma_class_spec(
        source::Loc loc,
        ModAddress* lhs_mod_address,
        intern::String rhs_name
    ) {
        return emplace<ModAddressIdClassSpec>(loc, lhs_mod_address, rhs_name);
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
