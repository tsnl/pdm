#ifndef INCLUDED_PDM_TYPES_MANAGER_HH
#define INCLUDED_PDM_TYPES_MANAGER_HH

#include <string>
#include <deque>

#include "pdm/core/integer.hh"
#include "pdm/ast/stmt/builtin.hh"
#include "pdm/printer/printer.hh"

#include "var.hh"
#include "type.hh"
#include "typeop_result.hh"

namespace pdm {
    class Compiler;
}
namespace pdm::typer {
    class Relation;
}

// typer incrementally constructs and preserves two sets:
//   1. of type variables (V), and
//   2. rules (R) are applied.
// - each valid rule is a closed, n-ary relation on V.

// think of the typer as ITS OWN DYNAMICALLY TYPED OO-PL where Vars
// are objects.
// - everything in the system is a Var
// - you can define relations (rules) that are potentially recursive
// - the PL computes & checks invariants from these relations
// - to find solutions to TypeVars
// * allow values (incl. functions) as interned constants by AST node
namespace pdm::types {

    class Manager {
      friend std::deque<Var>;

      // storage for all types:
      private:
        Compiler* m_opt_compiler_ptr;

        std::deque<MonotypeTypeVar>   m_all_monotype_tvs;
        std::deque<ProxyTypeVar>      m_all_proxy_tvs;
        std::deque<UnknownClassVar>   m_all_unknown_cvs;
        std::deque<TemplateVar_RetValue>  m_all_value_template_vars;
        std::deque<TemplateVar_RetType>   m_all_type_template_vars;
        std::deque<TemplateVar_ClassType>  m_all_class_template_vars;
        std::vector<Relation*>        m_all_relations;

        VoidFixedTypeVar m_void_tv;
        StringFixedTypeVar m_string_tv;

        Int8FixedTypeVar m_i8_tv;
        Int16FixedTypeVar m_i16_tv;
        Int32FixedTypeVar m_i32_tv;
        Int64FixedTypeVar m_i64_tv;
        Int128FixedTypeVar m_i128_tv;

        UInt1FixedTypeVar m_u1_tv;
        UInt8FixedTypeVar m_u8_tv;
        UInt16FixedTypeVar m_u16_tv;
        UInt32FixedTypeVar m_u32_tv;
        UInt64FixedTypeVar m_u64_tv;
        UInt128FixedTypeVar m_u128_tv;

        Float16FixedTypeVar m_f16_tv;
        Float32FixedTypeVar m_f32_tv;
        Float64FixedTypeVar m_f64_tv;

        SignedIntFixedClassVar m_signed_int_cv;
        UnsignedIntFixedClassVar m_unsigned_int_cv;
        IntFixedClassVar m_int_cv;
        FloatFixedClassVar m_float_cv;
        NumberFixedClassVar m_number_cv;
        
      public:
        Manager(Compiler* opt_compiler_ptr = nullptr);

      // create tv (TypeVar), cv (ClassVar), and 3 kinds of TemplateVars:
      public:
        TypeVar* new_unknown_tv(std::string&& name, ast::Node* opt_client_ast_node = nullptr);
        TypeVar* new_proxy_tv(std::string&& name, ast::Node* opt_client_ast_node = nullptr);
        ClassVar* new_unknown_cv(std::string&& name, ast::Node* opt_client_ast_node = nullptr);

        TemplateVar_RetValue* new_value_template_var(std::string&& name, ast::Node* opt_client_ast_node = nullptr);
        TemplateVar_RetType*  new_type_template_var(std::string&& name, ast::Node* opt_client_ast_node = nullptr);
        TemplateVar_ClassType* new_class_template_var(std::string&& name, ast::Node* opt_client_ast_node = nullptr);

      //
      // TVs:
      //
      public:
        TypeVar* get_void_tv() { return &m_void_tv; }
        TypeVar* get_string_tv() { return &m_string_tv; }

        TypeVar* get_i8_tv() { return &m_i8_tv; }
        TypeVar* get_i16_tv() { return &m_i16_tv; }
        TypeVar* get_i32_tv() { return &m_i32_tv; }
        TypeVar* get_i64_tv() { return &m_i64_tv; }
        TypeVar* get_i128_tv() { return &m_i128_tv; }

        TypeVar* get_u1_tv() { return &m_u1_tv; }
        TypeVar* get_u8_tv() { return &m_u8_tv; }
        TypeVar* get_u16_tv() { return &m_u16_tv; }
        TypeVar* get_u32_tv() { return &m_u32_tv; }
        TypeVar* get_u64_tv() { return &m_u64_tv; }
        TypeVar* get_u128_tv() { return &m_u128_tv; }

        TypeVar* get_f16_tv() { return &m_f16_tv; }
        TypeVar* get_f32_tv() { return &m_f32_tv; }
        TypeVar* get_f64_tv() { return &m_f64_tv; }

        ClassVar* get_signed_int_cv() { return &m_signed_int_cv; }
        ClassVar* get_unsigned_int_cv() { return &m_unsigned_int_cv; }
        ClassVar* get_int_cv() { return &m_int_cv; }
        ClassVar* get_float_cv() { return &m_float_cv; }
        ClassVar* get_number_cv() { return &m_number_cv; }
        
      // interface
      public:
        // map each 'Relation' class to a function application here.
        SolvePhase2_Result assume_relation_holds(Relation* relation);
        TestOpResult test(Relation* relation);

      // Dump:
      public:
        void print(printer::Printer& p, std::string const& title) const;
    };

}   // namespace pdm::typer

#endif  // INCLUDED_PDM_TYPES_MANAGER_HH
