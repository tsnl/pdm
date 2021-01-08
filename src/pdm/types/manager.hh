#ifndef INCLUDED_PDM_TYPES_MANAGER_HH
#define INCLUDED_PDM_TYPES_MANAGER_HH

#include <string>
#include <deque>

#include "pdm/core/integer.hh"
#include "pdm/ast/stmt/builtin_type.hh"
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
// - the PL computes & checks constraints from these relations
// - to find solutions to TypeVars
// * allow values (incl. functions) as interned constants by AST node
namespace pdm::types {

    class Manager {
      friend std::deque<Var>;

      // storage for all types:
      private:
        Compiler* m_opt_compiler_ptr;

        std::deque<TypeVar>           m_all_tvs;
        std::deque<ClassVar>          m_all_cvs;
        std::deque<ValueTemplateVar>  m_all_value_template_vars;
        std::deque<TypeTemplateVar>   m_all_type_template_vars;
        std::deque<ClassTemplateVar>  m_all_class_template_vars;
        std::vector<Relation*>        m_all_relations;
        
        TypeVar m_void_tv;
        TypeVar m_string_tv;
        
        TypeVar m_i8_tv;
        TypeVar m_i16_tv;
        TypeVar m_i32_tv;
        TypeVar m_i64_tv;
        TypeVar m_i128_tv;

        TypeVar m_u1_tv;
        TypeVar m_u8_tv;
        TypeVar m_u16_tv;
        TypeVar m_u32_tv;
        TypeVar m_u64_tv;
        TypeVar m_u128_tv;

        TypeVar m_f16_tv;
        TypeVar m_f32_tv;
        TypeVar m_f64_tv;
        
      public:
        Manager(Compiler* opt_compiler_ptr = nullptr);

      // create tv (TypeVar), cv (ClassVar), and template vars:
      public:
        TypeVar* new_fixed_tv(std::string&& name, Type* soln, ast::Node* opt_client_ast_node = nullptr);
        TypeVar* new_tv(std::string&& name, ast::Node* opt_client_ast_node = nullptr);
        TypeVar* new_proxy_tv(std::string&& name, ast::Node* opt_client_ast_node = nullptr);
        ClassVar* new_cv(std::string&& name, ast::Node* opt_client_ast_node = nullptr);

        ValueTemplateVar* new_value_template_var(std::string&& name, ast::Node* opt_client_ast_node = nullptr);
        TypeTemplateVar*  new_type_template_var(std::string&& name, ast::Node* opt_client_ast_node = nullptr);
        ClassTemplateVar* new_class_template_var(std::string&& name, ast::Node* opt_client_ast_node = nullptr);

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

      // interface
      public:
        // map each 'Relation' class to a function application here.
        AssumeOpResult assume(Relation* relation);
        TestOpResult test(Relation* relation);

      // Dump:
      public:
        void print(printer::Printer& p, std::string const& title) const;
    };

}   // namespace pdm::typer

#endif  // INCLUDED_PDM_TYPES_MANAGER_HH
