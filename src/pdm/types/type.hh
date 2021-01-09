#ifndef INCLUDED_PDM_TYPES_TYPE_SOLN_HH
#define INCLUDED_PDM_TYPES_TYPE_SOLN_HH

#include <string>
#include <vector>

#include "pdm/core/intern.hh"
#include "constraint.hh"
#include "type_kind.hh"

namespace pdm::types {
    class TypeVar;
}
namespace pdm::ast {
    class Exp;
}

namespace pdm::types {

    class Type {
      private:
        std::string m_name;
        TypeKind    m_type_kind;
              
      protected:
        Type(std::string name, TypeKind type_kind)
        : m_name(std::move(name)),
          m_type_kind(type_kind) {}

      public:
        std::string const& name() const;
        TypeKind type_kind() const;
        
      public:
        bool test_subtypeOf(Type const* supertype) const;
        bool test_supertypeOf(Type const* subtype) const;
      
      private:
        virtual bool help_test_subtypeOf_postKindCheck(Type const* supertype_of_same_type_kind) const;
    };
    inline std::string const& Type::name() const {
        return m_name;
    }
    inline TypeKind Type::type_kind() const {
        return m_type_kind;
    }
    inline bool Type::test_supertypeOf(Type const* subtype) const {
        return subtype->test_subtypeOf(this);
    }

    //
    // VoidType:
    //

    class VoidType: public Type {
      // shared singletons:
      private:
        static VoidType s_singleton;

      public:
        static VoidType* get() { 
            return &s_singleton; 
        }

      // protected constructor:
      protected:
        VoidType()
        : Type("VoidType", TypeKind::Void) {}
    };

    //
    // StringType:
    //

    class StringType: public Type {
      // shared singleton:
      private:
        static StringType s_singleton;

      public:
        static StringType* get() {
            return &s_singleton;
        }

      // protected singleton constructor:
      protected:
        StringType()
        : Type("StringType", TypeKind::String) {}
    };

    //
    // IntType:
    //

    class IntType: public Type {
      private:
        int  m_width_in_bits;
        bool m_using_sign_ext;

      // shared singletons:
      private:
        static IntType s_i8_singleton;
        static IntType s_i16_singleton;
        static IntType s_i32_singleton;
        static IntType s_i64_singleton;
        static IntType s_i128_singleton;

        static IntType s_u1_singleton;
        static IntType s_u8_singleton;
        static IntType s_u16_singleton;
        static IntType s_u32_singleton;
        static IntType s_u64_singleton;
        static IntType s_u128_singleton;

      public:
        static IntType* get_i8() { return &s_i8_singleton; }
        static IntType* get_i16() { return &s_i16_singleton; }
        static IntType* get_i32() { return &s_i32_singleton; }
        static IntType* get_i64() { return &s_i64_singleton; }
        static IntType* get_i128() { return &s_i128_singleton; }

        static IntType* get_u1() { return &s_u8_singleton; }
        static IntType* get_u8() { return &s_u8_singleton; }
        static IntType* get_u16() { return &s_u16_singleton; }
        static IntType* get_u32() { return &s_u32_singleton; }
        static IntType* get_u64() { return &s_u64_singleton; }
        static IntType* get_u128() { return &s_u128_singleton; }

      // protected constructor:
      protected:
        IntType(std::string&& name, int width_in_bits, bool using_sign_ext)
        : Type("IntType:" + std::move(name), TypeKind::Int), 
          m_width_in_bits(width_in_bits),
          m_using_sign_ext(using_sign_ext) {}
    };

    //
    // FloatType:
    //

    class FloatType: public Type {
      private:
        int m_width_in_bits;

      private:
        static FloatType s_float16_singleton;
        static FloatType s_float32_singleton;
        static FloatType s_float64_singleton;
      public:
        static FloatType* get_f16() { return &s_float16_singleton; }
        static FloatType* get_f32() { return &s_float32_singleton; }
        static FloatType* get_f64() { return &s_float64_singleton; }

      protected:
        FloatType(std::string&& name, int width_in_bits)
        : Type("FloatType:" + std::move(name), TypeKind::Float),
          m_width_in_bits(width_in_bits) {}
    };

    //
    // RefType:
    //

    // note: there is no type specifier for reference types; they cannot be freely manipulated in the language.
    //       they are used within the typer exclusively to check mutability of references (i.e. out, inout)
    class RefType: public Type {
      private:
        Type* m_pointee_soln;
        bool  m_readable;
        bool  m_writable;
      
      public:
        RefType(std::string&& name, Type* pointee_soln, bool readable, bool writable)
        : Type("RefType:" + std::move(name), TypeKind::Ref),
          m_pointee_soln(pointee_soln),
          m_readable(readable),
          m_writable(writable) {}
    };

    //
    // Tuples:
    //

    class TupleType: public Type {
      private:
        std::vector<Type*> m_fields;
      public:
        TupleType(std::string&& name, std::vector<Type*>&& fields);
    };
    inline TupleType::TupleType(std::string&& name, std::vector<Type*>&& fields)
    :   Type("TupleType:" + std::move(name), TypeKind::Tuple),
        m_fields(fields)
    {}

    //
    // Structs:
    //

    class StructTypeField {
      private:
        intern::String m_name;
        Type*          m_type;

      public:
        StructTypeField(intern::String name, Type* type)
        : m_name(name),
          m_type(type) {}
    };

    class StructType: public Type {
      private:
        std::vector<StructTypeField> m_fields;
      
      public:
        StructType(std::string&& name, std::vector<StructTypeField>&& fields)
        : Type("StructType:" + std::move(name), TypeKind::Struct),
          m_fields(std::move(fields)) {}
    };

    //
    // Enums:
    //

    enum class EnumFieldKind {
        ExplicitTs,
        DefaultTs
    };

    class EnumTypeField {
      private:
        EnumFieldKind   m_kind;
        intern::String  m_name;
        Type*           m_typepsec_soln;
      
      public:
        EnumTypeField(intern::String name)
        : m_kind(EnumFieldKind::DefaultTs),
          m_name(name),
          m_typepsec_soln(nullptr) {}

        EnumTypeField(intern::String name, Type* typespec_soln)
        : m_kind(EnumFieldKind::ExplicitTs),
          m_name(name),
          m_typepsec_soln(typespec_soln) {}
    };

    class EnumType: public Type {
      private:
        std::vector<EnumTypeField> m_fields;
      public:
        EnumType(std::string&& name, std::vector<EnumTypeField>&& fields)
        : Type("EnumType:" + std::move(name), TypeKind::Enum),
          m_fields(std::move(fields)) {}
    };
    
    //
    // Modules:
    //

    enum class ModuleFieldKind {
        Value,
        Type,
        Typeclass,
        ConstVal_TFunc,
        Type_TFunc
    };
    class ModuleField {
      private:
        ModuleFieldKind m_kind;
        intern::String  m_name;
        Type*           m_opt_type_soln;
      public:
        ModuleField(ModuleFieldKind kind, intern::String name, Type* opt_type_soln)
        : m_kind(kind),
          m_name(name),
          m_opt_type_soln(opt_type_soln) {}
    };
    class ModuleType: public Type {
      private:
        std::vector<ModuleField> m_fields;
      public:
        ModuleType(std::string&& name, std::vector<ModuleField>&& fields)
        : Type("ModuleType:" + std::move(name), TypeKind::Module),
          m_fields(std::move(fields)) {}
    };

    //
    // Functions:
    //

    enum class FuncArgReadWriteSpec {
        In,
        OpaquePtr,
        OutPtr,
        InOutPtr
    };
    class FuncTypeFormalArg {
      private:
        FuncArgReadWriteSpec m_read_write_spec;
        intern::String       m_name;
        Type*                m_arg_typespec;

      public:
        FuncTypeFormalArg(FuncArgReadWriteSpec read_write_spec, intern::String name, Type* arg_typespec)
        :   m_read_write_spec(read_write_spec),
            m_name(name),
            m_arg_typespec(arg_typespec)
        {}

      public:
        FuncArgReadWriteSpec read_write_spec() const;
        intern::String name() const;
        Type* arg_typespec() const;
    };
    inline FuncArgReadWriteSpec FuncTypeFormalArg::read_write_spec() const {
        return m_read_write_spec;
    }
    inline intern::String FuncTypeFormalArg::name() const {
        return m_name;
    }
    inline Type* FuncTypeFormalArg::arg_typespec() const {
        return m_arg_typespec;
    }
    class FuncTypeActualArg {
      private:
        FuncArgReadWriteSpec  m_read_write_spec;
        Type*                 m_arg_typespec;

      public:
        FuncTypeActualArg(FuncArgReadWriteSpec read_write_spec, Type* arg_typespec)
        :   m_read_write_spec(read_write_spec),
            m_arg_typespec(arg_typespec)
        {}
      
      public:
        FuncArgReadWriteSpec read_write_spec() const {
            return m_read_write_spec;
        }
        Type* arg_typespec() const {
            return m_arg_typespec;
        }
    };
    class FnType: public Type {
      private:
        std::vector<FuncTypeFormalArg> m_formal_args;
        TypeVar*                       m_ret_tv;
      public:
        FnType(std::string&& name, std::vector<FuncTypeFormalArg>&& formal_args, TypeVar* ret_tv)
        : Type("FnType:" + std::move(name), TypeKind::Fn),
          m_formal_args(std::move(formal_args)),
          m_ret_tv(ret_tv) {}
    };

}   // namespace pdm::typer

#endif  // INCLUDED_PDM_TYPES_TYPE_SOLN_HH
