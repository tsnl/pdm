#ifndef INCLUDED_PDM_TYPER_TYPER_HH
#define INCLUDED_PDM_TYPER_TYPER_HH

#include <string>
#include <deque>
#include <pdm/core/integer.hh>

#include "tv.hh"

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
      // private data members:
      private:
        std::deque<TV> m_all_tvs;
        TV* m_unit_tv;
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
        std::vector<TV*> m_class_tvs;
        std::vector<TV*> m_vfunc_tvs;
        std::vector<TV*> m_tfunc_tvs;
        std::vector<TV*> m_module_tvs;
        std::vector<TV*> m_free_var_tvs;
        std::vector<TV*> m_typeclass_tvs;

      protected:
        TV* new_tv();

      public:
        TV* get_unit_tv() { return m_unit_tv; }
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
        
        // TV* new_free_var_tv();
        // TV* new_typeclass_tv();
    };
    
}   // namespace pdm::typer

#endif  // INCLUDED_PDM_TYPER_TYPER_HH
