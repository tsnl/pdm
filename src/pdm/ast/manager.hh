#ifndef INCLUDED_PDM_AST_MANAGER_HH
#define INCLUDED_PDM_AST_MANAGER_HH

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

#include "stmt/builtin_type.hh"
#include "stmt/const.hh"
#include "stmt/discard.hh"
#include "stmt/enum.hh"
#include "stmt/fn.hh"
#include "stmt/import.hh"
#include "stmt/let.hh"
#include "stmt/link.hh"
#include "stmt/mod.hh"
#include "stmt/set.hh"
#include "stmt/type.hh"
#include "stmt/typeclass.hh"
#include "stmt/using.hh"

#include "targ/targ.hh"

#include "typespec/typespec.hh"
#include "typespec/dot.hh"
#include "typespec/fn.hh"
#include "typespec/id.hh"
#include "typespec/mut.hh"
#include "typespec/ptr.hh"
#include "typespec/struct.hh"
#include "typespec/tcall.hh"
#include "typespec/tuple.hh"

namespace pdm::typer {
    class Typer;
}

namespace pdm::ast {

    class ArrayExp;
    class BinaryExp;
    class ChainExp;
    class DotNameExp;
    class DotIndexExp;
    class IdExp;
    class IfExp;
    class IntExp;
    class LambdaExp;
    class ParenExp;
    class StringExp;
    class StructExp;
    class TCallExp;
    class TupleExp;
    class TypeQueryExp;
    class UnaryExp;
    class UnitExp;
    class VCallExp;

    class LPattern;
    class TPattern;
    class VPattern;

    class Script;

    class BuiltinTypeStmt;
    class ConstStmt;
    class FnStmt;
    class EnumStmt;
    class ImportStmt;
    class LetStmt;
    class LinkStmt;
    class ModuleStmt;
    class TypeStmt;
    class TypeclassStmt;

    class Manager {
      private:
        typer::Typer* m_typer;

      public:
        Manager(typer::Typer* typer)
        : m_typer(typer) {}

      public:
        Script* new_script(source::Source* source, source::Loc loc, std::vector<Stmt*>&& stmts);

        ArrayExp* new_array_exp(source::Loc loc, std::vector<Exp*>&& items);
        BinaryExp* new_binary_exp(source::Loc loc, BinaryOperator binary_operator, Exp* lhs_operand, Exp* rhs_operand);
        ChainExp* new_chain_exp(source::Loc loc, std::vector<Stmt*>&& prefix, Exp* suffix = nullptr);
        DotNameExp* new_dot_name_exp(source::Loc loc, Exp* lhs, intern::String rhs_name, DotNameExp::RhsHint rhs_hint);
        DotIndexExp* new_dot_index_exp(source::Loc loc, Exp* lhs, Exp* rhs_exp);
        FloatExp* new_float_exp(source::Loc loc, long double value);
        IdExp* new_id_exp(source::Loc loc, intern::String name);
        IfExp* new_if_exp(source::Loc loc, Exp* cond_exp, Exp* then_exp, Exp* else_exp);
        IntExp* new_int_exp(source::Loc loc, u64 value, IntExp::Base base);
        LambdaExp* new_lambda_exp(source::Loc loc, LPattern* lhs_lpattern, Exp* body);
        ParenExp* new_paren_exp(source::Loc loc, Exp* nested);
        StringExp* new_string_exp(source::Loc loc, std::vector<StringExp::Piece*>&& content);
        StructExp* new_struct_exp(source::Loc loc, std::vector<StructExp::Field*>&& fields);
        TCallExp* new_tcall_exp(source::Loc loc, Exp* lhs_called, std::vector<TArg*>&& args);
        TupleExp* new_tuple_exp(source::Loc loc, std::vector<Exp*>&& items);
        TypeQueryExp* new_type_query_exp(source::Loc loc, TypeQueryKind kind, Typespec* lhs_typespec, Typespec* rhs_typespec);
        UnaryExp* new_unary_exp(source::Loc loc, UnaryOperator unary_operator, Exp* operand);
        UnitExp* new_unit_exp(source::Loc loc);
        VCallExp* new_vcall_exp(source::Loc loc, Exp* lhs_called, std::vector<Exp*>&& args);
        StructExp::Field* new_struct_exp_field(source::Loc loc, intern::String name, Exp* value);
        TArg* new_tcall_exp_typespec_arg(source::Loc loc, Typespec* typespec);
        TArg* new_tcall_exp_exp_arg(source::Loc loc, Exp* exp);

        LPattern* new_lpattern(source::Loc loc, std::vector<LPattern::Field*>&& fields);
        TPattern* new_tpattern(source::Loc loc, std::vector<TPattern::Field*>&& fields, bool is_only_captured);
        VPattern* new_vpattern(source::Loc loc, std::vector<VPattern::Field*>&& fields);
        LPattern::Field* new_lpattern_field(source::Loc loc, LPattern::FieldKind kind, intern::String name, Typespec* opt_rhs_typespec = nullptr);
        TPattern::Field* new_tpattern_field(source::Loc loc, TPattern::FieldKind kind, intern::String name, Typespec* rhs_typespec);
        VPattern::Field* new_vpattern_field(source::Loc loc, intern::String name, Typespec* rhs_typespec);

        BuiltinTypeStmt* new_builtin_type_stmt(std::string&& desc, typer::TV* tv);
        ConstStmt* new_const_stmt(source::Loc loc, LPattern* lhs_lpattern, Exp* rhs_exp);
        DiscardStmt* new_discard_stmt(source::Loc loc, Exp* exp);
        LetStmt* new_let_stmt(source::Loc loc, LPattern* lhs_lpattern, Exp* rhs_exp);
        SetStmt* new_set_stmt(source::Loc loc, Exp* lhs, Exp* rhs);
        
        ImportStmt* new_import_stmt(source::Loc loc, intern::String imported_name, Exp* imported_from_exp, Exp* imported_type_exp);
        UsingStmt* new_using_stmt(source::Loc loc, Exp* used_exp);
        LinkStmt* new_link_stmt(source::Loc loc, Exp* linkage_name_exp, Exp* linked_file_array_exp, std::vector<LinkStmt::Item>&& items);
        ModStmt* new_mod_stmt(source::Loc loc, intern::String module_name, std::vector<Stmt*>&& defns);
        FnStmt* new_fn_stmt(
            source::Loc loc,
            intern::String name,
            std::vector<TPattern*>&& tpatterns,
            VPattern* vpattern,
            Typespec* opt_return_ts,
            Exp* body
        );
        TypeStmt* new_type_stmt(source::Loc loc, intern::String lhs_name, std::vector<TPattern*>&& tpatterns, Typespec* rhs_typespec);
        // todo: EnumStmt and TypeclassStmt need much more work.
        EnumStmt* new_enum_stmt(source::Loc loc, intern::String name, std::vector<EnumStmt::Field*>&& fields);
        TypeclassStmt* new_typeclass_stmt(
            source::Loc loc,
            intern::String lhs_name,
            intern::String candidate_name,
            Typespec* candidate_typespec,
            std::vector<TPattern*>&& tpatterns,
            std::vector<Exp*>&& conditions
        );
        EnumStmt::Field* new_enum_stmt_field(intern::String name, std::vector<ast::Typespec*>&& typespecs, bool has_explicit_typespecs);
        
        DotNameTypespec_TypePrefix* new_dot_name_typespec_with_type_prefix(source::Loc loc, Typespec* lhs_typespec, intern::String rhs_name);
        DotNameTypespec_ModPrefix* new_dot_name_typespec_with_mod_prefix(source::Loc loc, std::vector<intern::String>&& lhs_prefixes, intern::String rhs_name);
        FnTypespec* new_fn_typespec(source::Loc loc, VPattern* lhs_vpattern, Typespec* rhs_typespec);
        IdTypespec* new_id_typespec(source::Loc loc, intern::String name);
        // MutTypespec* new_mut_typespec(source::Loc loc, Typespec* mutatee);     // deprecated
        PtrTypespec* new_ptr_typespec(source::Loc loc, Typespec* pointee);
        StructTypespec* new_struct_typespec(source::Loc loc, std::vector<StructTypespec::Field*>&& fields);
        TCallTypespec* new_tcall_typespec(source::Loc loc, Typespec* lhs_called, std::vector<TArg*>&& args);
        TupleTypespec* new_tuple_typespec(source::Loc loc, std::vector<Typespec*>&& items);
        StructTypespec::Field* new_struct_typespec_field(source::Loc loc, intern::String name, Typespec* typespec);
        TArg* new_tcall_typespec_typespec_arg(source::Loc loc, Typespec* typespec);
        TArg* new_tcall_typespec_exp_arg(source::Loc loc, Exp* exp);

        // todo: add 'tcall_typespec_exp_arg' and '_type_arg'

      public:
        typer::Typer* typer() const {
            return m_typer;
        }
    };

}   // namespace pdm::ast

#endif  // INCLUDED_PDM_AST_MANAGER_HH
