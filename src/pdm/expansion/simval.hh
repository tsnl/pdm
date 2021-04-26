#ifndef INCLUDED_PDM_EXPANSION_SIMVAL_HH
#define INCLUDED_PDM_EXPANSION_SIMVAL_HH

#include <variant>
#include <vector>

#include "pdm/ast/exp/lambda.hh"

namespace pdm::expansion {

    class Val {};

    struct ValField {
        intern::String name;
        Val* val;
    };

    class UIntVal: public Val {
      public:
        uint64_t m_val;
        uint64_t m_mod;

      public:
        // note: mod = 0 for full 64-bit width.
        UIntVal(uint64_t val, uint64_t mod): m_val(val), m_mod(mod) {}
    };

    class SIntVal: public UIntVal {
        // todo: implement a signed int on top of unsigned int using casts
    };

    class FloatVal: public Val {
      public:
        long double m_value;

      public:
        explicit FloatVal(long double value): m_value(value) {}
    };

    class StringVal: public Val {
      public:
        std::string m_value;

      public:
        explicit StringVal(std::string value): m_value(value) {}
    };

    class TupleVal: public Val {
      public:
        std::vector<Val*> m_items;

      public:
        explicit TupleVal(std::vector<Val*> items): m_items(std::move(items)) {}
    };

    class StructVal: public Val {
      public:
        std::vector<ValField> m_fields;

      public:
        explicit StructVal(std::vector<ValField> items): m_fields(std::move(items)) {}
    };

    class EnumVal: public Val {
      public:
        ValField* m_active_field;

      public:
        explicit EnumVal(intern::String field_name, Val* field_val)
        :   m_active_field(new ValField{field_name, field_val})
        {}
    };

    class ArrayVal: public Val {
      private:
        std::vector<Val*> m_items;

      public:
        explicit ArrayVal(std::vector<Val*> items): m_items(std::move(items)) {}
    };

    class FnVal: public Val {
      private:
        ast::LambdaExp* m_lambda_exp;

      public:
        explicit FnVal(ast::LambdaExp* lambda_exp): m_lambda_exp(lambda_exp) {}
    };

}

#endif  // INCLUDED_PDM_EXPANSION_SIMVAL_HH