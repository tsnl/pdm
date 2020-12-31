#ifndef INCLUDED_PDM_TYPER_TYPER_HH
#define INCLUDED_PDM_TYPER_TYPER_HH

#include <string>
#include <deque>

#include "pdm/core/integer.hh"
#include "pdm/ast/stmt/builtin_type.hh"

#include "var.hh"
#include "type_soln.hh"

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
namespace pdm::typer {

    class Typer {
      friend std::deque<Var>;

      // storage for all types:
      private:
        std::deque<TypeVar>  m_all_tvs;
        std::deque<ClassVar> m_all_cvs;
        std::vector<Rule*>   m_all_rules;
        
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
        Typer();

      // create tv (TypeVar) and cv (ClassVar)
      public:
        TypeVar* new_tv(std::string&& name, TypeSoln* soln = nullptr, ast::Node* opt_client_ast_node = nullptr) {
            m_all_tvs.emplace_back(std::move(name), soln, opt_client_ast_node);
            return &m_all_tvs.back();
        }
        ClassVar* new_cv(std::string&& name, ast::Node* opt_client_ast_node = nullptr) {
            m_all_cvs.emplace_back(std::move(name), opt_client_ast_node);
            return &m_all_cvs.back();
        }

      //
      // TVs:
      //
      public:
        TypeVar* get_void_tv()     { return &m_void_tv; }
        TypeVar* get_string_tv()   { return &m_string_tv; }

        TypeVar* get_i8_tv()    { return &m_i8_tv; }
        TypeVar* get_i16_tv()   { return &m_i16_tv; }
        TypeVar* get_i32_tv()   { return &m_i32_tv; }
        TypeVar* get_i64_tv()   { return &m_i64_tv; }
        TypeVar* get_i128_tv()  { return &m_i128_tv; }
        
        TypeVar* get_u1_tv()   { return &m_u1_tv; }
        TypeVar* get_u8_tv()   { return &m_u8_tv; }
        TypeVar* get_u16_tv()  { return &m_u16_tv; }
        TypeVar* get_u32_tv()  { return &m_u32_tv; }
        TypeVar* get_u64_tv()  { return &m_u64_tv; }
        TypeVar* get_u128_tv() { return &m_u128_tv; }

        TypeVar* get_f16_tv() { return &m_f16_tv; }
        TypeVar* get_f32_tv() { return &m_f32_tv; }
        TypeVar* get_f64_tv() { return &m_f64_tv; }
        
      //
      // Rules:
      //

      public:
        // void apply_vid_typespec_rule (ast::Node* ast_node, intern::String lhs_name, TypeVar* lhs_var, Var* rhs_typespec_var) {
        //     typer::PatternTypespecRule_VId* rule = new typer::PatternTypespecRule_VId(ast_node, lhs_name, lhs_var, rhs_typespec_var);
        //     m_all_rules.push_back(rule);
        // }
        // void apply_tid_typespec_rule (ast::Node* ast_node, intern::String lhs_name, Var* lhs_var, Var* rhs_typespec_var) {
        //     typer::PatternTypespecRule_TId* rule = new typer::PatternTypespecRule_TId(ast_node, lhs_name, lhs_var, rhs_typespec_var);
        //     m_all_rules.push_back(rule);
        // }

      // Dump:
      public:
        // todo: implement typer::dump
        void dump() const;
    };

}   // namespace pdm::typer

#endif  // INCLUDED_PDM_TYPER_TYPER_HH
