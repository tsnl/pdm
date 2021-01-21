#ifndef INCLUDED_PDM_AST_MANAGER_HH
#define INCLUDED_PDM_AST_MANAGER_HH

#include <vector>

#include "pdm/core/integer.hh"
#include "pdm/core/units.hh"

#include "script/script.hh"

#include "exp/exp.hh"
#include "exp/array.hh"
#include "exp/binary.hh"
#include "exp/chain.hh"
#include "exp/dot.hh"
#include "exp/float.hh"
#include "exp/id.hh"
#include "exp/if.hh"
#include "exp/int.hh"
#include "exp/lambda.hh"
#include "exp/paren.hh"
#include "exp/string.hh"
#include "exp/struct.hh"
#include "exp/tcall.hh"
#include "exp/tuple.hh"
#include "exp/type_query.hh"
#include "exp/unary.hh"
#include "exp/unit.hh"
#include "exp/vcall.hh"

#include "pattern/lpattern.hh"
#include "pattern/vpattern.hh"
#include "pattern/tpattern.hh"

#include "stmt/builtin.hh"
#include "stmt/const.hh"
#include "stmt/discard.hh"
#include "stmt/mod_enum.hh"
#include "stmt/mod_type.hh"
#include "stmt/mod_typeclass.hh"
#include "stmt/mod_val.hh"
#include "stmt/import.hh"
#include "stmt/extern.hh"
#include "stmt/mod.hh"
#include "stmt/set.hh"
#include "stmt/using.hh"
#include "stmt/val.hh"
#include "stmt/var.hh"

#include "arg/targ.hh"
#include "arg/varg.hh"

#include "setspec/type_spec.hh"
#include "setspec/dot.hh"
#include "setspec/fn.hh"
#include "setspec/id_type_spec.hh"
#include "setspec/id_class_spec.hh"
#include "setspec/paren.hh"
#include "setspec/struct.hh"
#include "setspec/tcall.hh"
#include "setspec/tuple.hh"

namespace pdm {
    class Compiler;
}
namespace pdm::types {
    class Manager;
    class TypeVar;
}

namespace pdm::ast {

    class Manager {
      private:
        Compiler* m_compiler_ptr;
        u8*                 m_pool;
        size_t              m_pool_size_in_bytes;
        size_t              m_pool_used_in_bytes;

      public:
        Manager(Compiler* compiler_ptr, size_t pool_size_in_bytes = megabytes_in_bytes(64));
        ~Manager();

      private:
        u8* alloc(size_t alloc_size_in_bytes) {
            u8* ptr = m_pool + m_pool_used_in_bytes;
            m_pool_used_in_bytes += alloc_size_in_bytes;
            return ptr;
        }

        template <typename R, typename... Ts>
        R* emplace(Ts&&... args) {
            return new(alloc(sizeof(R))) R(std::forward<Ts>(args)...);
        }

      public:
        Script* new_script(source::Source* source, source::Loc loc, std::vector<Stmt*>&& head_stmts, std::vector<ModStmt*>&& body_mod_stmts);

        ArrayExp* new_array_exp(source::Loc loc, std::vector<Exp*>&& items);
        BinaryExp* new_binary_exp(source::Loc loc, BinaryOperator binary_operator, Exp* lhs_operand, Exp* rhs_operand);
        ChainExp* new_chain_exp(source::Loc loc, std::vector<Stmt*>&& prefix, Exp* suffix = nullptr);
        StructDotNameExp* new_struct_dot_name_exp(source::Loc loc, Exp* lhs, intern::String rhs_name);
        EnumDotNameExp* new_enum_dot_name_exp(source::Loc loc, Exp* lhs, intern::String rhs_name, std::vector<ast::Exp*>&& args);
        ModuleDotExp* new_module_dot_exp(source::Loc loc, std::vector<intern::String>&& module_names, intern::String rhs_name);
        DotIndexExp* new_dot_index_exp(source::Loc loc, Exp* lhs, Exp* rhs_exp, DotIndexExp::RhsHint rhs_hint);
        FloatExp* new_float_exp(source::Loc loc, long double value);
        IdExp* new_id_exp(source::Loc loc, intern::String name);
        IfExp* new_if_exp(source::Loc loc, Exp* cond_exp, Exp* then_exp, Exp* else_exp);
        IntExp* new_int_exp(source::Loc loc, u64 value, IntExp::Base base);
        LambdaExp* new_lambda_exp(source::Loc loc, VPattern* lhs_lpattern, TypeSpec* opt_ret_typespec, Exp* body);
        ParenExp* new_paren_exp(source::Loc loc, Exp* nested);
        StringExp* new_string_exp(source::Loc loc, utf8::String content, StringExp::QuoteKind quote_kind);
        StringExp* new_string_exp(source::Loc loc, std::vector<StringExp::Piece>&& content);
        StructExp* new_struct_exp(source::Loc loc, std::vector<StructExp::Field*>&& fields);
        TCallExp* new_tcall_exp(source::Loc loc, Exp* lhs_called, std::vector<TArg*>&& args);
        TupleExp* new_tuple_exp(source::Loc loc, std::vector<Exp*>&& items);
        TypeQueryExp* new_type_query_exp(source::Loc loc, TypeQueryKind kind, TypeSpec* lhs_typespec, TypeSpec* rhs_typespec);
        UnaryExp* new_unary_exp(source::Loc loc, UnaryOperator unary_operator, Exp* operand);
        UnitExp* new_unit_exp(source::Loc loc);
        VCallExp* new_vcall_exp(source::Loc loc, Exp* lhs_called, std::vector<VArg*>&& args);
        StructExp::Field* new_struct_exp_field(source::Loc loc, intern::String name, Exp* value);
        
        LPattern* new_lpattern(source::Loc loc, std::vector<LPattern::Field*>&& fields, bool destructure);
        TPattern* new_tpattern(source::Loc loc, std::vector<TPattern::Field*>&& fields, bool is_only_captured);
        VPattern* new_vpattern(source::Loc loc, std::vector<VPattern::Field*>&& fields);
        LPattern::Field* new_lpattern_field(source::Loc loc, LPattern::FieldKind kind, intern::String name, TypeSpec* opt_rhs_typespec = nullptr);
        TPattern::Field* new_tpattern_field(source::Loc loc, TPattern::FieldKind kind, intern::String name, SetSpec* rhs_set_spec);
        VPattern::Field* new_vpattern_field(source::Loc loc, intern::String name, TypeSpec* rhs_typespec, VArgAccessSpec varg_kind);

        BuiltinStmt* new_builtin_stmt(std::string&& desc);
        ConstStmt* new_const_stmt(source::Loc loc, LPattern* lhs_lpattern, Exp* rhs_exp);
        DiscardStmt* new_discard_stmt(source::Loc loc, Exp* exp);
        ValStmt* new_val_stmt(source::Loc loc, LPattern* lhs_lpattern, Exp* rhs_exp);
        VarStmt* new_var_stmt(source::Loc loc, LPattern* lhs_lpattern, Exp* rhs_exp);
        SetStmt* new_set_stmt(source::Loc loc, Exp* lhs, Exp* rhs);
        
        ImportStmt* new_import_stmt(source::Loc loc, intern::String imported_name, utf8::String imported_from_exp, utf8::String imported_type_exp);
        UsingStmt* new_using_stmt(source::Loc loc, intern::String module_name, std::string suffix);
        ExternStmt* new_extern_stmt(source::Loc loc, intern::String ext_mod_name, Exp* link_arg);
        ModStmt* new_mod_stmt(source::Loc loc, intern::String module_name, std::vector<TPattern*>&& tpatterns, std::vector<ModContentStmt*>&& defns);
        ModValStmt* new_internal_mod_val_stmt(
            source::Loc loc,
            intern::String name,
            std::vector<TPattern*>&& tpatterns,
            Exp* body
        );
        ModValStmt* new_external_mod_val_stmt(
            source::Loc loc,
            intern::String name,
            std::vector<TPattern*>&& tpatterns,
            TypeSpec* typespec,
            intern::String ext_mod_name,
            utf8::String ext_fn_name
        );
        ModTypeStmt* new_mod_type_stmt(source::Loc loc, intern::String lhs_name, std::vector<TPattern*>&& tpatterns, TypeSpec* rhs_typespec);
        ModEnumStmt* new_mod_enum_stmt(source::Loc loc, intern::String lhs_name, std::vector<TPattern*>&& tpatterns, std::vector<ModEnumStmt::Field*>&& fields);
        ModTypeclassStmt* new_mod_typeclass_stmt(source::Loc loc, intern::String lhs_name, intern::String candidate_name, ClassSpec* candidate_typespec, std::vector<TPattern*>&& tpatterns, std::vector<TypeQueryExp*>&& conditions);
        ModEnumStmt::Field* new_enum_stmt_field(source::Loc loc, intern::String name, std::vector<ast::TypeSpec*>&& typespecs, bool has_explicit_typespecs);
        
        DotNameTypeSpec_ModPrefix* new_dot_name_type_spec_with_mod_prefix(source::Loc loc, std::vector<intern::String>&& lhs_prefixes, intern::String rhs_name);
        FnTypeSpec* new_fn_type_spec(source::Loc loc, VPattern* lhs_vpattern, TypeSpec* rhs_typespec);
        IdTypeSpec* new_id_type_spec(source::Loc loc, intern::String name);
        IdClassSpec* new_id_class_spec(source::Loc loc, intern::String name);
        ParenTypeSpec* new_paren_type_spec(source::Loc loc, TypeSpec* nested_typespec);
        StructTypeSpec* new_struct_type_spec(source::Loc loc, std::vector<StructTypeSpec::Field*>&& fields);
        TCallTypeSpec* new_tcall_type_spec(source::Loc loc, TypeSpec* lhs_called, std::vector<TArg*>&& args);
        TCallClassSpec* new_tcall_class_spec(source::Loc loc, ClassSpec* lhs_called, std::vector<TArg*>&& args);
        TupleTypeSpec* new_tuple_type_spec(source::Loc loc, std::vector<TypeSpec*>&& items);
        StructTypeSpec::Field* new_struct_type_spec_field(source::Loc loc, intern::String name, TypeSpec* typespec);

        TArg* new_targ_exp(source::Loc loc, Exp* exp);
        TArg* new_targ_type_spec(source::Loc loc, TypeSpec* typespec);
        VArg* new_varg(source::Loc, Exp* exp, VArgAccessSpec varg_kind);

      public:
        Compiler* compiler();

      public:
        types::Manager* types_mgr() const;
    };

}   // namespace pdm::ast

#endif  // INCLUDED_PDM_AST_MANAGER_HH
