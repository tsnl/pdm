#ifndef INCLUDED_PDM_AST_MANAGER_HH
#define INCLUDED_PDM_AST_MANAGER_HH

#include <vector>
#include <pdm/ast/type_spec/enum.hh>

#include "pdm/core/integer.hh"
#include "pdm/core/units.hh"

#include "source-node/script.hh"
#include "source-node/package.hh"

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

#include "header/import_stmt.hh"

#include "module/mod-address.hh"
#include "module/native-mod-exp.hh"

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
#include "header/extern_stmt.hh"
#include "stmt/set.hh"
#include "stmt/using.hh"
#include "stmt/val.hh"
#include "stmt/var.hh"

#include "arg/targ.hh"
#include "arg/varg.hh"

#include "pdm/ast/type_spec/type_spec.hh"
#include "pdm/ast/type_spec/mai.hh"
#include "pdm/ast/type_spec/fn.hh"
#include "pdm/ast/type_spec/id.hh"
#include "pdm/ast/type_spec/struct.hh"
#include "pdm/ast/type_spec/tuple.hh"

#include "pdm/ast/class_spec/id.hh"
#include "pdm/ast/class_spec/class_exp.hh"
#include "pdm/ast/class_spec/mai.hh"

#include "pdm/source/local-script-source.hh"
#include "pdm/source/local-package-source.hh"


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
        Script* new_script(
            source::ISource* source, source::Loc loc,
            std::vector<HeaderStmt*>&& header_stmts, std::vector<Script::Field*>&& fields
        );
        Script::Field* new_script_field(source::Loc loc, intern::String name, ast::BaseModExp* mod_exp);

        NativeModExp* new_native_mod_exp(source::Loc loc, ast::TPattern* opt_template_pattern, std::vector<BaseModExp::Field*>&& fields);
        ExternCModExp* new_extern_c_mod_exp(source::Loc loc, std::vector<BaseModExp::Field*>&& fields);
        PkgBundleModExp* new_pkg_bundle_mod_exp(source::Loc loc, std::vector<BaseModExp::Field*>&& fields);
        BaseModExp::ModuleField* new_mod_field_for_mod_exp(source::Loc loc, intern::String lhs_name, ast::BaseModExp* mod_exp);
        BaseModExp::ValueField* new_value_field_for_mod_exp(source::Loc loc, intern::String lhs_name, ast::Exp* rhs_exp);
        BaseModExp::TypeField* new_type_field_for_mod_exp(source::Loc loc, intern::String lhs_name, ast::TypeSpec* rhs_type_spec);
        BaseModExp::ClassField* new_class_field_for_mod_exp(source::Loc loc, intern::String lhs_name, ast::ClassSpec* rhs_class_spec);

        ModAddress* new_mod_address(source::Loc loc, ModAddress* opt_lhs, intern::String rhs_name, std::vector<ast::TArg*>&& template_args);

        ArrayExp* new_array_exp(source::Loc loc, std::vector<Exp*>&& items);
        BinaryExp* new_binary_exp(source::Loc loc, BinaryOperator binary_operator, Exp* lhs_operand, Exp* rhs_operand);
        ChainExp* new_chain_exp(source::Loc loc, std::vector<Stmt*>&& prefix, Exp* suffix = nullptr);
        StructDotNameExp* new_struct_dot_name_exp(source::Loc loc, Exp* lhs, intern::String rhs_name);
        EnumDotNameExp* new_enum_dot_name_exp(source::Loc loc, TypeSpec* lhs, intern::String rhs_name, ast::Exp* opt_using_exp);
        ModuleDotExp* new_module_dot_name_exp(source::Loc loc, ast::ModAddress* lhs_address, intern::String rhs_name);
        DotIndexExp* new_dot_index_exp(source::Loc loc, Exp* lhs, Exp* rhs_exp, DotIndexExp::RhsHint rhs_hint);
        FloatExp* new_float_exp(source::Loc loc, long double value);
        IdExp* new_id_exp(source::Loc loc, intern::String name);
        IfExp* new_if_exp(source::Loc loc, Exp* cond_exp, Exp* then_exp, Exp* else_exp);
        IntExp* new_int_exp(source::Loc loc, u64 value, IntExp::Base base, bool force_unsigned);
        LambdaExp* new_lambda_exp(source::Loc loc, FnTypeSpec* fn_type_spec, Exp* body);
        ParenExp* new_paren_exp(source::Loc loc, Exp* nested);
        StringExp* new_string_exp(source::Loc loc, utf8::String content, StringExp::QuoteKind quote_kind);
        StringExp* new_string_exp(source::Loc loc, std::vector<StringExp::Piece>&& content);
        StructExp* new_struct_exp(source::Loc loc, std::vector<StructExp::Field*>&& fields);
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
        TPattern::Field* new_value_tpattern_field(source::Loc loc, intern::String name, TypeSpec* type_spec);
        TPattern::Field* new_type_tpattern_field(source::Loc loc, intern::String name, ClassSpec* class_spec);
        VPattern::Field* new_vpattern_field(source::Loc loc, intern::String name, TypeSpec* rhs_typespec, VArgAccessSpec varg_kind);

        BuiltinStmt* new_builtin_stmt(std::string&& desc);
        ConstStmt* new_const_stmt(source::Loc loc, LPattern* lhs_lpattern, Exp* rhs_exp);
        DiscardStmt* new_discard_stmt(source::Loc loc, Exp* exp);
        ValStmt* new_val_stmt(source::Loc loc, LPattern* lhs_lpattern, Exp* rhs_exp);
        VarStmt* new_var_stmt(source::Loc loc, LPattern* lhs_lpattern, Exp* rhs_exp);
        SetStmt* new_set_stmt(source::Loc loc, Exp* lhs, Exp* rhs);
        
        ImportStmt* new_import_stmt(source::Loc loc, std::vector<ast::ImportStmt::FieldGroup*> import_field_groups);
        ImportStmt::FieldGroup* new_import_field_group(source::Loc loc, std::vector<ImportStmt::Field*> pull_names, utf8::String from_str);
        ImportStmt::Field* new_import_field(source::Loc loc, intern::String field_name);
        UsingStmt* new_using_stmt(source::Loc loc, intern::String module_name, std::string suffix);
        ExternStmt* new_extern_stmt(source::Loc loc, intern::String ext_mod_name, Exp* link_arg);

        ModAddressIdTypeSpec* new_ma_type_spec(source::Loc loc, ast::ModAddress* lhs_mod_address, intern::String rhs_name);
        FnTypeSpec* new_fn_type_spec(source::Loc loc, VPattern* lhs_vpattern, TypeSpec* rhs_typespec);
        IdTypeSpec* new_id_type_spec(source::Loc loc, intern::String name);
        StructTypeSpec* new_struct_type_spec(source::Loc loc, std::vector<StructTypeSpec::Field*>&& fields);
        EnumTypeSpec* new_enum_type_spec(source::Loc loc, std::vector<EnumTypeSpec::Field*>&& fields);
        TupleTypeSpec* new_tuple_type_spec(source::Loc loc, std::vector<TypeSpec*>&& items);
        StructTypeSpec::Field* new_struct_type_spec_field(source::Loc loc, intern::String name, TypeSpec* type_spec);
        EnumTypeSpec::Field* new_enum_type_spec_field(source::Loc loc, intern::String name, TypeSpec* opt_type_spec);

        IdClassSpec* new_id_class_spec(source::Loc loc, intern::String name);
        ClassExpClassSpec* new_class_exp_class_spec(
            source::Loc loc,
            intern::String candidate_type_name,
            ClassSpec* candidate_class_name,
            std::vector<ast::TypeQueryExp*>&& type_query_exps
        );
        ModAddressIdClassSpec* new_ma_class_spec(
            source::Loc loc,
            ModAddress* lhs_mod_address,
            intern::String rhs_name
        );

        TArg* new_targ_exp(source::Loc loc, Exp* exp);
        TArg* new_targ_type_spec(source::Loc loc, TypeSpec* typespec);
        VArg* new_varg(source::Loc, Exp* exp, VArgAccessSpec varg_kind);

        Package* new_package(
            source::LocalPackageSource* package_source,
            source::Loc loc,
            std::vector<Package::ExportField*>&& export_fields
        );
        Package::ExportField_ExternModuleInC* new_package_export_field_for_extern_module_in_c(
            source::Loc loc,
            intern::String name,
            Package::ExportField_ExternModuleInC::CoreCompilerArgs&& core_compiler_args,
            Package::ExportField_ExternModuleInC::PlatformCompilerArgs&& platform_compiler_args
        );
        Package::ExportField_ImportAllModulesFrom* new_package_export_field_for_import_modules_from(
            source::Loc loc,
            intern::String name,
            std::string&& path
        );

      public:
        Compiler* compiler();

      public:
        [[nodiscard]] types::Manager* types_mgr() const;
    };

}   // namespace pdm::ast

#endif  // INCLUDED_PDM_AST_MANAGER_HH
