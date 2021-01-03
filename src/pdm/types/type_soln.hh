#ifndef INCLUDED_PDM_TYPES_TYPE_SOLN_HH
#define INCLUDED_PDM_TYPES_TYPE_SOLN_HH

#include <vector>

#include "pdm/core/intern.hh"

#include "type_constraint.hh"
#include "type_kind.hh"

namespace pdm::types {
    class TypeVar;
}
namespace pdm::ast {
    class Exp;
}

namespace pdm::types {

    // typer maps each 'TypeVar' to a 'TypeSoln' type:
    class TypeSoln {
      private:
        std::string m_name;
        TypeKind    m_type_kind;
              
      public:
        TypeSoln(std::string&& name, TypeKind type_kind)
        : m_name(std::move(name)),
          m_type_kind(type_kind) {}

      public:
        std::string const& name() const {
            return m_name;
        }
        TypeKind type_kind() const {
            return m_type_kind;
        }
    };

    class VoidTypeSoln: public TypeSoln {
      // shared singletons:
      private:
        static VoidTypeSoln s_singleton;
      public:
        static VoidTypeSoln* get() { 
            return &s_singleton; 
        }

      // protected constructor:
      protected:
        VoidTypeSoln()
        : TypeSoln("VoidType", TypeKind::Void) {}
    };

    class StringTypeSoln: public TypeSoln {
      // shared singleton:
      private:
        static StringTypeSoln s_singleton;
      public:
        static StringTypeSoln* get() {
            return &s_singleton;
        }

      // protected singleton constructor:
      protected:
        StringTypeSoln()
        : TypeSoln("StringType", TypeKind::String) {}
    };

    class IntTypeSoln: public TypeSoln {
      private:
        int  m_width_in_bits;
        bool m_using_sign_ext;

      // shared singletons:
      private:
        static IntTypeSoln s_i8_singleton;
        static IntTypeSoln s_i16_singleton;
        static IntTypeSoln s_i32_singleton;
        static IntTypeSoln s_i64_singleton;
        static IntTypeSoln s_i128_singleton;

        static IntTypeSoln s_u1_singleton;
        static IntTypeSoln s_u8_singleton;
        static IntTypeSoln s_u16_singleton;
        static IntTypeSoln s_u32_singleton;
        static IntTypeSoln s_u64_singleton;
        static IntTypeSoln s_u128_singleton;

      public:
        static IntTypeSoln* get_i8() { return &s_i8_singleton; }
        static IntTypeSoln* get_i16() { return &s_i16_singleton; }
        static IntTypeSoln* get_i32() { return &s_i32_singleton; }
        static IntTypeSoln* get_i64() { return &s_i64_singleton; }
        static IntTypeSoln* get_i128() { return &s_i128_singleton; }

        static IntTypeSoln* get_u1() { return &s_u8_singleton; }
        static IntTypeSoln* get_u8() { return &s_u8_singleton; }
        static IntTypeSoln* get_u16() { return &s_u16_singleton; }
        static IntTypeSoln* get_u32() { return &s_u32_singleton; }
        static IntTypeSoln* get_u64() { return &s_u64_singleton; }
        static IntTypeSoln* get_u128() { return &s_u128_singleton; }

      // protected constructor:
      protected:
        IntTypeSoln(std::string&& name, int width_in_bits, bool using_sign_ext)
        : TypeSoln("IntType:" + std::move(name), TypeKind::Int), 
          m_width_in_bits(width_in_bits),
          m_using_sign_ext(using_sign_ext) {}
    };

    class FloatTypeSoln: public TypeSoln {
      private:
        int m_width_in_bits;

      private:
        static FloatTypeSoln s_float16_singleton;
        static FloatTypeSoln s_float32_singleton;
        static FloatTypeSoln s_float64_singleton;
      public:
        static FloatTypeSoln* get_f16() { return &s_float16_singleton; }
        static FloatTypeSoln* get_f32() { return &s_float32_singleton; }
        static FloatTypeSoln* get_f64() { return &s_float64_singleton; }

      protected:
        FloatTypeSoln(std::string&& name, int width_in_bits)
        : TypeSoln("FloatType:" + std::move(name), TypeKind::Float),
          m_width_in_bits(width_in_bits) {}
    };

    // note: there is no type specifier for reference types; they cannot be freely manipulated in the language.
    //       they are used within the typer exclusively to check mutability of references (i.e. out, inout)
    class RefTypeSoln: public TypeSoln {
      private:
        TypeSoln* m_pointee_soln;
        bool      m_readable;
        bool      m_writable;
      
      public:
        RefTypeSoln(std::string&& name, TypeSoln* pointee_soln, bool readable, bool writable)
        : TypeSoln("RefType:" + std::move(name), TypeKind::Ref),
          m_pointee_soln(pointee_soln),
          m_readable(readable),
          m_writable(writable) {}
    };

    class StructTypeSoln: public TypeSoln {
      public:
        class Field {
          private:
            bool            m_embed;
            intern::String  m_name;
            TypeSoln*       m_type;
          public:
            Field(bool embed, intern::String name, TypeSoln* type)
            : m_embed(embed),
              m_name(name),
              m_type(type) {}
        };
      
      private:
        std::vector<StructTypeSoln::Field> m_fields;
      
      public:
        StructTypeSoln(std::string&& name, std::vector<StructTypeSoln::Field>&& fields)
        : TypeSoln("StructType:" + std::move(name), TypeKind::Struct),
          m_fields(std::move(fields)) {}
    };

    class EnumTypeSoln: public TypeSoln {
      public:
        enum class FieldKind {
            ExplicitTs,
            DefaultTs
        };

        class Field {
          private:
            EnumTypeSoln::FieldKind m_kind;
            intern::String      m_name;
            TypeSoln*           m_typepsec_soln;
          
          public:
            Field(intern::String name)
            : m_kind(EnumTypeSoln::FieldKind::DefaultTs),
              m_name(name),
              m_typepsec_soln(nullptr) {}

            Field(intern::String name, TypeSoln* typespec_soln)
            : m_kind(EnumTypeSoln::FieldKind::ExplicitTs),
              m_name(name),
              m_typepsec_soln(typespec_soln) {}
        };

      private:
        std::vector<Field> m_fields;
      
      public:
        EnumTypeSoln(std::string&& name, std::vector<EnumTypeSoln::Field>&& fields)
        : TypeSoln("EnumType:" + std::move(name), TypeKind::Enum),
          m_fields(std::move(fields)) {}
    };
    
    class ModuleTypeSoln: public TypeSoln {
      public:
        enum class FieldKind {
            Value,
            Type,
            Typeclass,
            ConstVal_TFunc,
            Type_TFunc
        };
        class Field {
          private:
            ModuleTypeSoln::FieldKind m_kind;
            intern::String        m_name;
            TypeSoln*         m_opt_type_soln;
          public:
            Field(ModuleTypeSoln::FieldKind kind, intern::String name, TypeSoln* opt_type_soln)
            : m_kind(kind),
              m_name(name),
              m_opt_type_soln(opt_type_soln) {}
        };
      private:
        std::vector<ModuleTypeSoln::Field> m_fields;

      public:
        ModuleTypeSoln(std::string&& name, std::vector<ModuleTypeSoln::Field>&& fields)
        : TypeSoln("ModuleType:" + std::move(name), TypeKind::Module),
          m_fields(std::move(fields)) {}
    };

    class FuncTypeSoln: public TypeSoln {
      public:
        class FormalArg {
          private:
            intern::String    m_name;
            TypeSoln* m_arg_type;

          public:
            FormalArg(intern::String name, TypeSoln* arg_type)
            : m_name(name),
              m_arg_type(arg_type) {}
        };

      private:
        std::vector<FuncTypeSoln::FormalArg> m_formal_args;
        TypeVar*                             m_ret_tv;

      public:
        FuncTypeSoln(std::string&& name, std::vector<FuncTypeSoln::FormalArg>&& formal_args, TypeVar* ret_tv)
        : TypeSoln("FuncType:" + std::move(name), TypeKind::Func),
          m_formal_args(std::move(formal_args)),
          m_ret_tv(ret_tv) {}
    };

}   // namespace pdm::typer

#endif  // INCLUDED_PDM_TYPES_TYPE_SOLN_HH
