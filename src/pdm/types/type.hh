#ifndef INCLUDED_PDM_TYPES_TYPE_SOLN_HH
#define INCLUDED_PDM_TYPES_TYPE_SOLN_HH

#include <string>
#include <vector>

#include "pdm/core/intern.hh"
#include "pdm/printer/printer.hh"
#include "pdm/ast/arg/varg.hh"

#include "var_invariant.hh"
#include "kind.hh"

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
        Kind m_type_kind;

      protected:
        Type(std::string name, Kind type_kind)
        : m_name(std::move(name)),
          m_type_kind(type_kind) {}

      public:
        [[nodiscard]] std::string const& name() const;
        [[nodiscard]] Kind type_kind() const;

      public:
        void print(printer::Printer& p) const;
    };
    inline std::string const& Type::name() const {
        return m_name;
    }
    inline Kind Type::type_kind() const {
        return m_type_kind;
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
        : Type("VoidType", Kind::Void) {}
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
        : Type("StringType", Kind::String) {}
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
        :   Type("IntType:" + std::move(name), (using_sign_ext ? Kind::SignedInt : Kind::UnsignedInt)),
            m_width_in_bits(width_in_bits),
            m_using_sign_ext(using_sign_ext)
        {}
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
        :   Type("FloatType:" + std::move(name), Kind::Float),
            m_width_in_bits(width_in_bits) 
        {}
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
    :   Type("TupleType:" + std::move(name), Kind::Tuple),
        m_fields(fields)
    {}

    //
    // Structs:
    //

    class StructType: public Type {
      public:
        class Field {
          private:
            intern::String m_name;
            Type*          m_type;

          public:
            Field(intern::String name, Type* type)
            :   m_name(name),
                m_type(type) {}
        };

      private:
        std::vector<Field> m_fields;

      public:
        StructType(std::string&& name, std::vector<Field>&& fields)
        : Type("StructType:" + std::move(name), Kind::Struct),
          m_fields(std::move(fields)) {}
    };

    //
    // Enums:
    //

    class EnumType: public Type {
      public:
        enum class FieldKind {
            ExplicitTs,
            DefaultTs
        };

      public:
        class Field {
          private:
            FieldKind      m_kind;
            intern::String m_name;
            Type*          m_type;

          public:
            explicit Field(intern::String name)
            : m_kind(FieldKind::DefaultTs),
              m_name(name),
              m_type(nullptr) {}

            Field(intern::String name, Type* type_soln)
            : m_kind(FieldKind::ExplicitTs),
              m_name(name),
              m_type(type_soln) {}
        };

      private:
        std::vector<Field> m_fields;

      public:
        EnumType(std::string&& name, std::vector<Field>&& fields)
        :   Type("EnumType:" + std::move(name), Kind::Enum),
            m_fields(std::move(fields))
        {}
    };

    //
    // Modules:
    //

    class ModuleType: public Type {
      public:
        enum class FieldKind {
            Value,
            Type,
            Typeclass
        };

      public:
        class Field {
          private:
            FieldKind       m_kind;
            intern::String  m_name;
            Type*           m_opt_type_soln;
            bool            m_is_template;

          public:
            Field(FieldKind kind, intern::String name, Type* opt_type_soln, bool is_template)
            :   m_kind(kind),
                m_name(name),
                m_opt_type_soln(opt_type_soln),
                m_is_template(is_template)
            {}
        };

      private:
        std::vector<Field> m_fields;
      public:
        ModuleType(std::string&& name, std::vector<Field>&& fields)
        : Type("ModuleType:" + std::move(name), Kind::Module),
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
        ast::VArgAccessSpec m_arg_access_spec;
        intern::String      m_name;
        Type*               m_arg_typespec;

      public:
        FuncTypeFormalArg(ast::VArgAccessSpec arg_access_spec, intern::String name, Type* arg_typespec);

      public:
        [[nodiscard]] ast::VArgAccessSpec arg_access_spec() const;
        [[nodiscard]] intern::String name() const;
        [[nodiscard]] Type* arg_typespec() const;
    };
    inline FuncTypeFormalArg::FuncTypeFormalArg(ast::VArgAccessSpec arg_access_spec, intern::String name, Type* arg_typespec)
    :   m_arg_access_spec(arg_access_spec),
        m_name(name),
        m_arg_typespec(arg_typespec)
    {}
    inline ast::VArgAccessSpec FuncTypeFormalArg::arg_access_spec() const {
        return m_arg_access_spec;
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
        [[nodiscard]] FuncArgReadWriteSpec read_write_spec() const {
            return m_read_write_spec;
        }
        [[nodiscard]] Type* arg_typespec() const {
            return m_arg_typespec;
        }
    };
    class FnType: public Type {
      private:
        std::vector<FuncTypeFormalArg> m_formal_args;
        Type* m_typeof_ret;

      public:
        FnType(std::string&& name, std::vector<FuncTypeFormalArg>&& formal_args, Type* typeof_ret)
        : Type("FnType:" + std::move(name), Kind::Fn),
          m_formal_args(std::move(formal_args)),
          m_typeof_ret(typeof_ret)
        {}
    };

}   // namespace pdm::typer

#endif  // INCLUDED_PDM_TYPES_TYPE_SOLN_HH
