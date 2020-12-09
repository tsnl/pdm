#ifndef INCLUDED_PDM_TYPER_TYPER_HH
#define INCLUDED_PDM_TYPER_TYPER_HH

#include <string>
#include <deque>
#include <pdm/core/integer.hh>

#include "tv.hh"
#include "rule.hh"

// typer incrementally constructs and preserves two sets: 
//   1. of type variables (V), and 
//   2. rules (R) are applied.
// - each valid rule is a closed, n-ary relation on V.

// think of the typer as ITS OWN DYNAMICALLY TYPED OO-PL where TVs
// are objects.
// - everything in the system is a TV
// - you can define relations (rules) that are potentially recursive
// - the PL computes & checks constraints from these relations
// - to find solutions to TypeVars
// * allow values (incl. functions) as interned constants by AST node
namespace pdm::typer {

    class Typer {
      friend std::deque<TV>;

      // private data members:
      private:
        std::deque<TV> m_all_tvs;
        std::vector<Rule*> m_all_rules;

        TV* m_void_tv;
        TV* m_string_tv;
        TV* m_type_info_tv;
        TV* m_i8_tv;
        TV* m_i16_tv;
        TV* m_i32_tv;
        TV* m_i64_tv;
        TV* m_i128_tv;
        TV* m_u1_tv;
        TV* m_u8_tv;
        TV* m_u16_tv;
        TV* m_u32_tv;
        TV* m_u64_tv;
        TV* m_u128_tv;
        TV* m_f16_tv;
        TV* m_f32_tv;
        TV* m_f64_tv;
        std::vector<TV*> m_tuple_tvs;
        std::vector<TV*> m_struct_tvs;
        std::vector<TV*> m_enum_tvs;
        std::vector<TV*> m_vfunc_tvs;
        std::vector<TV*> m_tfunc_tvs;
        std::vector<TV*> m_module_tvs;
        std::vector<TV*> m_typeclass_tvs;
        std::vector<TV*> m_monomorphic_var_tvs;
        std::vector<TV*> m_polymorphic_var_tvs;

      public:
        Typer() {
            m_void_tv = new_void_tv();
            m_i8_tv = new_i8_tv();
            m_i16_tv = new_i16_tv();
            m_i32_tv = new_i32_tv();
            m_i64_tv = new_i64_tv();
            m_i128_tv = new_i128_tv();
            m_u1_tv = new_u1_tv();
            m_u8_tv = new_u8_tv();
            m_u16_tv = new_u16_tv();
            m_u32_tv = new_u32_tv();
            m_u64_tv = new_u64_tv();
            m_u128_tv = new_u128_tv();
            m_f16_tv = new_f16_tv();
            m_f32_tv = new_f32_tv();
            m_f64_tv = new_f64_tv();
        }

      protected:
        TV* new_tv(Soln* soln) {
            m_all_tvs.emplace_back(this, soln);
            return &m_all_tvs.back();
        }
        TV* new_void_tv() {
            return new_tv(VoidSoln::get());
        }
        TV* new_i8_tv() {
            return new_tv(IntSoln::get_i8());
        }
        TV* new_i16_tv() {
            return new_tv(IntSoln::get_i16());
        }
        TV* new_i32_tv() {
            return new_tv(IntSoln::get_i32());
        }
        TV* new_i64_tv() {
            return new_tv(IntSoln::get_i64());
        }
        TV* new_i128_tv() {
            return new_tv(IntSoln::get_i128());
        }
        TV* new_u1_tv() {
            return new_tv(IntSoln::get_u1());
        }
        TV* new_u8_tv() {
            return new_tv(IntSoln::get_u8());
        }
        TV* new_u16_tv() {
            return new_tv(IntSoln::get_u16());
        }
        TV* new_u32_tv() {
            return new_tv(IntSoln::get_u32());
        }
        TV* new_u64_tv() {
            return new_tv(IntSoln::get_u64());
        }
        TV* new_u128_tv() {
            return new_tv(IntSoln::get_u128());
        }
        TV* new_f16_tv() {
            return new_tv(FloatSoln::get_f16());
        }
        TV* new_f32_tv() {
            return new_tv(FloatSoln::get_f32());
        }
        TV* new_f64_tv() {
            return new_tv(FloatSoln::get_f64());
        }

      //
      // TV creation and acquisition:
      //

      public:
        TV* get_void_tv() { return m_void_tv; }
        TV* get_string_tv() { return m_string_tv; }
        TV* get_type_info_tv() { return m_type_info_tv; }

        TV* get_i8_tv()   { return m_i8_tv; }
        TV* get_i16_tv()  { return m_i16_tv; }
        TV* get_i32_tv()  { return m_i32_tv; }
        TV* get_i64_tv()  { return m_i64_tv; }
        TV* get_i128_tv() { return m_i128_tv; }
        
        TV* get_u1_tv()   { return m_u1_tv; }
        TV* get_u8_tv()   { return m_u8_tv; }
        TV* get_u16_tv()  { return m_u16_tv; }
        TV* get_u32_tv()  { return m_u32_tv; }
        TV* get_u64_tv()  { return m_u64_tv; }
        TV* get_u128_tv() { return m_u128_tv; }

        TV* get_f16_tv() { return m_f16_tv; }
        TV* get_f32_tv() { return m_f32_tv; }
        TV* get_f64_tv() { return m_f64_tv; }
        
        // todo: implement these handlers

        // TV* new_tuple_tv(std::vector<TV*>&& fields);
        // TV* new_struct_tv(std::vector<Field>&& fields);
        // TV* new_enum_tv(std::vector<Field>&& fields);
        // TV* new_class_tv(std::vector<Field>&& fields);
        // TV* new_vfunc_tv(int formal_arg_count);
        // TV* new_tfunc_tv(int formal_arg_count);
        // TV* new_module_tv(std::vector<Field>&& mod_fields);
        
        TV* new_monomorphic_var_tv(std::string&& name) {
            TV* tv = new_tv(new MonomorphicVarSoln(std::move(name)));
            m_monomorphic_var_tvs.push_back(tv);
            return tv;
        }

        TV* new_polymorphic_var_tv(std::string&& name) {
            TV* tv = new_tv(new PolymorphicVarSoln(std::move(name)));
            m_polymorphic_var_tvs.push_back(tv);
            return tv;
        }

        // TV* new_typeclass_tv();

      //
      // Rules:
      //

      public:
        void apply_vid_typespec_rule(ast::Node* ast_node, intern::String lhs_name, TV* lhs_tv, TV* rhs_typespec_tv) {
            typer::VIdTypespecRule* rule = new typer::VIdTypespecRule(ast_node, lhs_name, lhs_tv, rhs_typespec_tv);
            m_all_rules.push_back(rule);
        }
        void apply_tid_typespec_rule(ast::Node* ast_node, intern::String lhs_name, TV* lhs_tv, TV* rhs_typespec_tv) {
            typer::TIdTypespecRule* rule = new typer::TIdTypespecRule(ast_node, lhs_name, lhs_tv, rhs_typespec_tv);
            m_all_rules.push_back(rule);
        }

      // Dump:
      public:
        // todo: implement typer::dump
        void dump() const;
    };
    
}   // namespace pdm::typer

#endif  // INCLUDED_PDM_TYPER_TYPER_HH
