#include "type.hh"

#include "pdm/core/intern.hh"

namespace pdm::types {

    void Type::print(printer::Printer& p) const {
        p.print_c_str("Type ");
        p.print_c_str(type_kind_as_str(m_type_kind));
        p.print_c_str(" ");
        p.print_c_str(m_name.c_str());
    }

    VoidType VoidType::s_singleton {};
    StringType StringType::s_singleton {};

    IntType IntType::s_i8_singleton {"Int8", 8, true};
    IntType IntType::s_i16_singleton {"Int16", 16, true};
    IntType IntType::s_i32_singleton {"Int32", 32, true};
    IntType IntType::s_i64_singleton {"Int64", 64, true};
    IntType IntType::s_i128_singleton {"Int128", 128, true};
    IntType IntType::s_u1_singleton {"UInt1", 1, false};
    IntType IntType::s_u8_singleton {"UInt8", 8, false};
    IntType IntType::s_u16_singleton {"UInt16", 16, false};
    IntType IntType::s_u32_singleton {"UInt32", 32, false};
    IntType IntType::s_u64_singleton {"UInt64", 64, false};
    IntType IntType::s_u128_singleton {"UInt128", 128, false};

    FloatType FloatType::s_float16_singleton {"Float16", 16};
    FloatType FloatType::s_float32_singleton {"Float32", 32};
    FloatType FloatType::s_float64_singleton {"Float64", 64};

    tt::TupleTypeTrie TupleType::s_type_trie{TupleType::tt_ctor};
    tt::StructTypeTrie StructType::s_type_trie{StructType::tt_ctor};
    tt::EnumTypeTrie EnumType::s_type_trie{EnumType::tt_ctor};
    tt::ModuleTypeTrie ModuleType::s_type_trie{ModuleType::tt_ctor};
    tt::FnTypeTrie FnType::s_type_trie{FnType::tt_ctor};

    TupleType* TupleType::tt_ctor(tt::TupleTypeTrie::Node* node) {
        return new TupleType(node);
    }
    StructType* StructType::tt_ctor(tt::StructTypeTrie::Node* node) {
        return new StructType(node);
    }
    EnumType* EnumType::tt_ctor(tt::EnumTypeTrie::Node* node) {
        return new EnumType(node);
    }
    ModuleType* ModuleType::tt_ctor(tt::ModuleTypeTrie::Node *node) {
        return new ModuleType(node);
    }
    FnType* FnType::tt_ctor(tt::FnTypeTrie::Node *node) {
        return new FnType(node);
    }

    TupleType* TupleType::get(std::vector<tt::TupleField> const& fields) {
        tt::TupleTypeTrie::Node* node = s_type_trie.get(fields);
        if (node) {
            return node->result;
        } else {
            return nullptr;
        }
    }

    EnumType* EnumType::get(std::vector<tt::EnumField> const& fields) {
        tt::EnumTypeTrie::Node* node = s_type_trie.get(fields);
        if (node) {
            return node->result;
        } else {
            return nullptr;
        }
    }

    StructType* StructType::get(std::vector<tt::StructField> const& fields) {
        tt::StructTypeTrie::Node* node = s_type_trie.get(fields);
        if (node) {
            return node->result;
        } else {
            return nullptr;
        }
    }

    ModuleType* ModuleType::get(std::vector<tt::ModuleField> const& fields) {
        tt::ModuleTypeTrie::Node* node = s_type_trie.get(fields);
        if (node) {
            return node->result;
        } else {
            return nullptr;
        }
    }

    FnType* FnType::get(std::vector<tt::FnField> const& fields) {
        tt::FnTypeTrie::Node* node = s_type_trie.get(fields);
        if (node) {
            return node->result;
        } else {
            return nullptr;
        }
    }

};