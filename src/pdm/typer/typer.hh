#ifndef INCLUDED_PDM_TYPER_TYPER_HH
#define INCLUDED_PDM_TYPER_TYPER_HH

#include <string>
#include <deque>

#include "pdm/core/integer.hh"
#include "pdm/ast/stmt/builtin_type.hh"

#include "typer_config.hh"
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

      // private data members:
      private:
        std::deque<TypeVar> m_all_tvs;
        std::deque<ClassVar> m_all_cvs;
        std::vector<Rule*> m_all_rules;

      // constant types:
      private:
        TypeVar* m_void_tv;
        TypeVar* m_string_tv;
        
        TypeVar* m_i8_tv;
        TypeVar* m_i16_tv;
        TypeVar* m_i32_tv;
        TypeVar* m_i64_tv;
        TypeVar* m_i128_tv;

        TypeVar* m_u1_tv;
        TypeVar* m_u8_tv;
        TypeVar* m_u16_tv;
        TypeVar* m_u32_tv;
        TypeVar* m_u64_tv;
        TypeVar* m_u128_tv;

        TypeVar* m_f16_tv;
        TypeVar* m_f32_tv;
        TypeVar* m_f64_tv;
        
        std::vector<TypeVar*> m_tuple_tvs;
        std::vector<TypeVar*> m_struct_tvs;
        std::vector<TypeVar*> m_enum_tvs;
        std::vector<TypeVar*> m_vfunc_tvs;
        std::vector<TypeVar*> m_tfunc_tvs;
        std::vector<TypeVar*> m_module_tvs;
        std::vector<TypeVar*> m_typeclass_tvs;
        std::vector<TypeVar*> m_monomorphic_var_tvs;
        std::vector<TypeVar*> m_polymorphic_var_tvs;

      public:
        Typer(TyperConfig typer_config) {
            m_void_tv = new_void_tv(typer_config.void_tv_client_astn);
            m_string_tv = new_string_tv(typer_config.string_tv_client_astn);
            m_i8_tv = new_i8_tv(typer_config.i8_tv_client_astn);
            m_i16_tv = new_i16_tv(typer_config.i16_tv_client_astn);
            m_i32_tv = new_i32_tv(typer_config.i32_tv_client_astn);
            m_i64_tv = new_i64_tv(typer_config.i64_tv_client_astn);
            m_i128_tv = new_i128_tv(typer_config.i128_tv_client_astn);
            m_u1_tv = new_u1_tv(typer_config.u1_tv_client_astn);
            m_u8_tv = new_u8_tv(typer_config.u8_tv_client_astn);
            m_u16_tv = new_u16_tv(typer_config.u16_tv_client_astn);
            m_u32_tv = new_u32_tv(typer_config.u32_tv_client_astn);
            m_u64_tv = new_u64_tv(typer_config.u64_tv_client_astn);
            m_u128_tv = new_u128_tv(typer_config.u128_tv_client_astn);
            m_f16_tv = new_f16_tv(typer_config.f16_tv_client_astn);
            m_f32_tv = new_f32_tv(typer_config.f32_tv_client_astn);
            m_f64_tv = new_f64_tv(typer_config.f64_tv_client_astn);
        }

      protected:
        TypeVar* new_tv(ast::Node* client_ast_node, TypeSoln* soln = nullptr) {
            m_all_tvs.emplace_back(client_ast_node, soln);
            return &m_all_tvs.back();
        }

        TypeVar* new_void_tv(ast::BuiltinTypeStmt* client_ast_node) {
            return new_tv(client_ast_node, VoidTypeSoln::get());
        }
        TypeVar* new_string_tv(ast::BuiltinTypeStmt* client_ast_node) {
            return new_tv(client_ast_node, StringTypeSoln::get());
        }

        TypeVar* new_i8_tv(ast::BuiltinTypeStmt* client_ast_node) {
            return new_tv(client_ast_node, IntTypeSoln::get_i8());
        }
        TypeVar* new_i16_tv(ast::BuiltinTypeStmt* client_ast_node) {
            return new_tv(client_ast_node, IntTypeSoln::get_i16());
        }
        TypeVar* new_i32_tv(ast::BuiltinTypeStmt* client_ast_node) {
            return new_tv(client_ast_node, IntTypeSoln::get_i32());
        }
        TypeVar* new_i64_tv(ast::BuiltinTypeStmt* client_ast_node) {
            return new_tv(client_ast_node, IntTypeSoln::get_i64());
        }
        TypeVar* new_i128_tv(ast::BuiltinTypeStmt* client_ast_node) {
            return new_tv(client_ast_node, IntTypeSoln::get_i128());
        }

        TypeVar* new_u1_tv(ast::BuiltinTypeStmt* client_ast_node) {
            return new_tv(client_ast_node, IntTypeSoln::get_u1());
        }
        TypeVar* new_u8_tv(ast::BuiltinTypeStmt* client_ast_node) {
            return new_tv(client_ast_node, IntTypeSoln::get_u8());
        }
        TypeVar* new_u16_tv(ast::BuiltinTypeStmt* client_ast_node) {
            return new_tv(client_ast_node, IntTypeSoln::get_u16());
        }
        TypeVar* new_u32_tv(ast::BuiltinTypeStmt* client_ast_node) {
            return new_tv(client_ast_node, IntTypeSoln::get_u32());
        }
        TypeVar* new_u64_tv(ast::BuiltinTypeStmt* client_ast_node) {
            return new_tv(client_ast_node, IntTypeSoln::get_u64());
        }
        TypeVar* new_u128_tv(ast::BuiltinTypeStmt* client_ast_node) {
            return new_tv(client_ast_node, IntTypeSoln::get_u128());
        }

        TypeVar* new_f16_tv(ast::BuiltinTypeStmt* client_ast_node) {
            return new_tv(client_ast_node, FloatTypeSoln::get_f16());
        }
        TypeVar* new_f32_tv(ast::BuiltinTypeStmt* client_ast_node) {
            return new_tv(client_ast_node, FloatTypeSoln::get_f32());
        }
        TypeVar* new_f64_tv(ast::BuiltinTypeStmt* client_ast_node) {
            return new_tv(client_ast_node, FloatTypeSoln::get_f64());
        }

      protected:
        ClassVar* new_cv() {
            m_all_cvs.emplace_back();
        }

      //
      // TVs:
      //
      public:
        TypeVar* get_void_tv()     const { return m_void_tv; }
        TypeVar* get_string_tv()   const { return m_string_tv; }

        TypeVar* get_i8_tv()    const { return m_i8_tv; }
        TypeVar* get_i16_tv()   const { return m_i16_tv; }
        TypeVar* get_i32_tv()   const { return m_i32_tv; }
        TypeVar* get_i64_tv()   const { return m_i64_tv; }
        TypeVar* get_i128_tv()  const { return m_i128_tv; }
        
        TypeVar* get_u1_tv()   const { return m_u1_tv; }
        TypeVar* get_u8_tv()   const { return m_u8_tv; }
        TypeVar* get_u16_tv()  const { return m_u16_tv; }
        TypeVar* get_u32_tv()  const { return m_u32_tv; }
        TypeVar* get_u64_tv()  const { return m_u64_tv; }
        TypeVar* get_u128_tv() const { return m_u128_tv; }

        TypeVar* get_f16_tv() const { return m_f16_tv; }
        TypeVar* get_f32_tv() const { return m_f32_tv; }
        TypeVar* get_f64_tv() const { return m_f64_tv; }
        
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
