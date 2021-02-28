#ifndef INCLUDED_PDM_TYPES_TYPE_SOLN_HH
#define INCLUDED_PDM_TYPES_TYPE_SOLN_HH

#include <string>
#include <vector>

#include "pdm/core/intern.hh"
#include "pdm/printer/printer.hh"
#include "pdm/ast/arg/varg.hh"

#include "var_invariant.hh"
#include "kind.hh"
#include "type_trie.hh"

namespace pdm::types {
    class TypeVar;
}
namespace pdm::ast {
    class Exp;
}

namespace pdm::types {

    // Type instances are unique representations of algebraic types.
    // - unique required to efficiently verify compounds not infinite in size.
    // - use tries to efficiently store and access elements.
    class Type {
      protected:
        struct FiniteCheckStackFrame {
            FiniteCheckStackFrame* parent;
            Type const* type;
        };
      private:
        std::string m_name;
        Kind m_type_kind;

      protected:
        Type(std::string name, Kind type_kind)
        :   m_name(std::move(name)),
            m_type_kind(type_kind) {}

      public:
        [[nodiscard]] std::string const& name() const;
        [[nodiscard]] Kind type_kind() const;

      public:
        void print(printer::Printer& p) const;

      public:
        bool check_finite() const;
        bool check_finite_impl(FiniteCheckStackFrame* parent_frame) const;
      protected:
        virtual bool check_contents_finite(FiniteCheckStackFrame* top_frame) const;
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
        :   Type("VoidType", Kind::Void) 
        {}
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
    // Compound types: 
    //
    // Compound types rely on TypeTrie nodes to stay unique.
    // - each Type is turned into a LIST with well-defined order
    //    - for tuples, just order of fields
    //    - for structs & enums, ordered by intern::String ID (stable per-compilation)
    //    - for functions, [args..., return type]
    // - when a new compound is created, an existing Type Trie node is obtained if possible.
    //   otherwise, a new node is inserted into the Type Trie.
    // - like all types, two pointers are equal if *and only if* they represent the same type.
    //

    class CompoundType: public Type {
      protected:
        CompoundType(std::string name, Kind kind);

      protected:
        bool check_contents_finite(Type::FiniteCheckStackFrame* top_frame) const override = 0;
    };

    inline CompoundType::CompoundType(std::string name, Kind kind)
    : Type(std::move(name), kind)
    {}

    //
    // Tuples:
    //

    class TupleType: public CompoundType {
      private:
        static tt::TupleTypeTrie s_type_trie;
        static TupleType* tt_ctor(tt::TupleTypeTrie::Node* node);

      private:
        tt::TupleTypeTrie::Node* m_tt_node;

      protected:
        explicit TupleType(tt::TupleTypeTrie::Node* tt_node);

      public:
        static TupleType* get(std::vector<tt::TupleField> const& fields);

      protected:
        bool check_contents_finite(Type::FiniteCheckStackFrame* top_frame) const override;
    };
    inline TupleType::TupleType(tt::TupleTypeTrie::Node* tt_node)
    :   CompoundType("TupleType", Kind::Tuple),
        m_tt_node(tt_node)
    {}

    //
    // Structs:
    //

    class StructType: public CompoundType {
      private:
        static tt::StructTypeTrie s_type_trie;
        static StructType* tt_ctor(tt::StructTypeTrie::Node* node);

      private:
        tt::StructTypeTrie::Node* m_tt_node;

      protected:
        explicit StructType(tt::StructTypeTrie::Node* tt_node);

      public:
        static StructType* get(std::vector<tt::StructField> const& fields);

      protected:
        bool check_contents_finite(Type::FiniteCheckStackFrame* top_frame) const override;
    };

    inline StructType::StructType(tt::StructTypeTrie::Node* tt_node)
    :   CompoundType("StructType(" + std::to_string(tt_node->hops_to_root) + ")", Kind::Struct),
        m_tt_node(tt_node)
    {}

    //
    // Enums:
    //

    class EnumType: public CompoundType {
     private:
        static tt::EnumTypeTrie s_type_trie;
        static EnumType* tt_ctor(tt::EnumTypeTrie::Node* node);

      private:
        tt::EnumTypeTrie::Node* m_tt_node;

      protected:
        explicit EnumType(tt::EnumTypeTrie::Node* tt_node);

      public:
        static EnumType* get(std::vector<tt::EnumField> const& fields);

      protected:
        bool check_contents_finite(Type::FiniteCheckStackFrame* top_frame) const override;
    };

    inline EnumType::EnumType(tt::EnumTypeTrie::Node* tt_node)
    :   CompoundType("EnumType(" + std::to_string(tt_node->hops_to_root) + ")", Kind::Enum),
        m_tt_node(tt_node)
    {}

    //
    // Modules:
    //

    class ModuleType: public CompoundType {
     private:
        static tt::ModuleTypeTrie s_type_trie;
        static ModuleType* tt_ctor(tt::ModuleTypeTrie::Node* node);

      private:
        tt::ModuleTypeTrie::Node* m_tt_node;

      protected:
        explicit ModuleType(tt::ModuleTypeTrie::Node* tt_node);

      public:
        static ModuleType* get(std::vector<tt::ModuleField> const& fields);

      protected:
        bool check_contents_finite(Type::FiniteCheckStackFrame* top_frame) const override;
    };

    inline ModuleType::ModuleType(tt::ModuleTypeTrie::Node* tt_node)
    :   CompoundType("ModuleType", Kind::Module),
        m_tt_node(tt_node)
    {}

    //
    // Functions:
    //

    class FnType: public CompoundType {
     private:
        static tt::FnTypeTrie s_type_trie;
        static FnType* tt_ctor(tt::FnTypeTrie::Node* node);

      private:
        tt::FnTypeTrie::Node* m_tt_node;

      protected:
        explicit FnType(tt::FnTypeTrie::Node* tt_node);

      public:
        static FnType* get(std::vector<tt::FnField> const& fields);

      protected:
        bool check_contents_finite(Type::FiniteCheckStackFrame* top_frame) const override;
    };

    inline FnType::FnType(tt::FnTypeTrie::Node* tt_node)
    :   CompoundType("FnType", Kind::Fn),
        m_tt_node(tt_node)
    {}

}   // namespace pdm::typer

#endif  // INCLUDED_PDM_TYPES_TYPE_SOLN_HH
