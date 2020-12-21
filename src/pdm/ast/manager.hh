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
#include "stmt/enum.hh"
#include "stmt/fn.hh"
#include "stmt/import.hh"
#include "stmt/let.hh"
#include "stmt/link.hh"
#include "stmt/mod.hh"
#include "stmt/type.hh"
#include "stmt/typeclass.hh"

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
        Script* new_script(source::Source* source);

        ArrayExp* new_array_exp(source::Loc loc, std::vector<Exp*>&& items);
        BinaryExp* new_binary_exp(source::Loc loc, BinaryOperator binary_operator, Exp* lhs_operand, Exp* rhs_operand);
        ChainExp* new_chain_exp(source::Loc loc, std::vector<Stmt*>&& prefix, Exp* suffix = nullptr);
        DotNameExp* new_dot_name_exp(source::Loc loc, Exp* lhs, intern::String rhs_name);
        DotIndexExp* new_dot_index_exp(source::Loc loc, Exp* lhs, Exp* rhs_exp);
        FloatExp* new_float_exp(source::Loc loc, long double value);
        IdExp* new_id_exp(source::Loc loc, intern::String name);
        IfExp* new_if_exp(source::Loc loc, Exp* cond_exp, Exp* then_exp, Exp* else_exp);
        IntExp* new_int_exp(source::Loc loc, u64 value);
        LambdaExp* new_lambda_exp(source::Loc loc, VPattern* lhs_vpattern, Exp* body);
        ParenExp* new_paren_exp(source::Loc loc, Exp* nested);
        StringExp* new_string_exp(source::Loc loc, utf8::String content);
        StructExp* new_struct_exp(source::Loc loc, std::vector<StructExp::Field*>&& fields);
        TCallExp* new_tcall_exp(source::Loc loc, Exp* lhs_called, std::vector<TCallExp::Arg*>&& args);
        TupleExp* new_tuple_exp(source::Loc loc, std::vector<Exp*>&& items);
        TypeQueryExp* new_type_query_exp(source::Loc loc, TypeQueryKind kind, Typespec* lhs_typespec, Typespec* rhs_typespec);
        UnaryExp* new_unary_exp(source::Loc loc, UnaryOperator unary_operator, Exp* operand);
        UnitExp* new_unit_exp(source::Loc loc);
        VCallExp* new_v_call_exp(source::Loc loc, Exp* lhs_called, std::vector<Exp*>&& args);
        StructExp::Field* new_struct_exp_field(intern::String name, Exp* value);
        TCallExp::Arg* new_t_call_exp_typespec_arg(Typespec* typespec);
        TCallExp::Arg* new_t_call_exp_exp_arg(Exp* exp);

        LPattern* new_l_pattern(source::Loc loc, std::vector<LPattern::Field*>&& fields);
        TPattern* new_t_pattern(source::Loc loc, std::vector<TPattern::Field*>&& fields, bool is_only_captured);
        VPattern* new_v_pattern(source::Loc loc, std::vector<VPattern::Field*>&& fields);
        LPattern::Field* new_l_pattern_field(LPattern::FieldKind kind, intern::String name, Typespec* opt_rhs_typespec = nullptr);
        TPattern::Field* new_t_pattern_field(TPattern::FieldKind kind, intern::String name, Typespec* rhs_typespec);
        VPattern::Field* new_v_pattern_field(intern::String name, Typespec* rhs_typespec);

        DotNameTypespec_TypePrefix* new_dot_name_typespec_with_type_prefix(source::Loc loc, Typespec* lhs_typespec, intern::String rhs_name);
        DotNameTypespec_ModPrefix* new_dot_name_typespec_with_mod_prefix(source::Loc loc, std::vector<intern::String>&& lhs_prefixes, intern::String rhs_name);
        FnTypespec* new_fn_typespec(source::Loc loc, VPattern* lhs_vpattern, Typespec* rhs_typespec);
        IdTypespec* new_id_typespec(source::Loc loc, intern::String name);
        MutTypespec* new_mut_typespec(source::Loc loc, Typespec* mutatee);
        PtrTypespec* new_ptr_typespec(source::Loc loc, Typespec* pointee);
        StructTypespec* new_struct_typespec(source::Loc loc, std::vector<StructTypespec::Field*>&& fields);
        TCallTypespec* new_t_call_typespec(source::Loc loc, Typespec* lhs_called, std::vector<TCallTypespec::Arg*>&& args);
        TupleTypespec* new_tuple_typespec(source::Loc loc, std::vector<Typespec*>&& items);
        StructTypespec::Field* new_struct_typespec_field(intern::String name, Typespec* typespec);

      public:
        typer::Typer* typer() const {
            return m_typer;
        }
    };

}   // namespace pdm::ast

#endif  // INCLUDED_PDM_AST_MANAGER_HH
