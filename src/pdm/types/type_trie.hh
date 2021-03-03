#ifndef INCLUDED__PDM__TYPES__TYPE_TRIE_HH
#define INCLUDED__PDM__TYPES__TYPE_TRIE_HH

#include <vector>

#include "pdm/core/intern.hh"
#include "pdm/ast/arg/varg.hh"

namespace pdm::types {
    class Type;
    class TupleType;
    class StructType;
    class EnumType;
    class ModuleType;
    class FnType;
}

namespace pdm::types {

    namespace tt {
        struct TupleField {
            Type* type;

            bool operator==(const TupleField&) const = default;
        };

        struct StructField {
            intern::String name;
            Type* type;

            bool operator==(const StructField&) const = default;
        };

        struct EnumField {
            intern::String name;
            Type* type;

            bool operator==(const EnumField&) const = default;
        };

        enum class ModuleFieldKind {
            Value,
            Type,
            Typeclass
        };
        struct ModuleField {
            intern::String name;
            Type* type;
            ModuleFieldKind field_kind;

            bool operator==(const ModuleField&) const = default;
        };

        // Fns are unwrapped into lists that are tracked with TT.
        struct FnField {
            ast::VArgAccessSpec access_spec;
            intern::String name;
            Type* type;
            bool is_ret_not_arg;

            bool operator==(const FnField&) const = default;
        };

        template <typename FieldType, typename NodeType>
        class GenericTypeTrie {
          public:
            struct Node;
            struct Edge;
            typedef NodeType*(*TypeCtor)(GenericTypeTrie::Node* node);

            struct Node {
                std::vector<Edge> edges;
                NodeType* result;
                Node* parent;
                size_t parent_edge_index;
                int hops_to_root;

                Node();
            };
            struct Edge {
                FieldType field;
                Node* result;
            };

          private:
            Node*    m_root;
            TypeCtor m_ctor;

          public:
            explicit GenericTypeTrie(TypeCtor ctor);

          public:
            [[nodiscard]] Node* root_node() const;

          public:
            Node* get(std::vector<FieldType> const& sorted_fields);

          private:
            Node* get(std::vector<FieldType> const& sorted_fields, int fields_start_index, Node* root_node);
        };

        using TupleTypeTrie = GenericTypeTrie<tt::TupleField, TupleType>;
        using StructTypeTrie = GenericTypeTrie<tt::StructField, StructType>;
        using EnumTypeTrie = GenericTypeTrie<tt::EnumField, EnumType>;
        using ModuleTypeTrie = GenericTypeTrie<tt::ModuleField, ModuleType>;
        using FnTypeTrie = GenericTypeTrie<tt::FnField, FnType>;

        //
        //
        // Implementation:
        //
        //

        template <typename FieldType, typename NodeType>
        GenericTypeTrie<FieldType, NodeType>::Node::Node()
        :   edges{}, 
            result(nullptr),
            parent(nullptr),
            parent_edge_index(-1),
            hops_to_root(0) 
        {}

        template <typename FieldType, typename NodeType>
        typename GenericTypeTrie<FieldType, NodeType>::Node*
        GenericTypeTrie<FieldType, NodeType>::root_node() const {
            return m_root;
        }

        template <typename FieldType, typename NodeType>
        GenericTypeTrie<FieldType, NodeType>::GenericTypeTrie(TypeCtor ctor)
        :   m_root(new Node),
            m_ctor(ctor)
        {
            m_root->result = m_ctor(m_root);
        }

        template <typename FieldType, typename NodeType>
        typename GenericTypeTrie<FieldType, NodeType>::Node*
        GenericTypeTrie<FieldType, NodeType>::get(
            std::vector<FieldType> const& sorted_fields
        ) {
            return get(sorted_fields, 0, m_root);
        }

        template <typename FieldType, typename NodeType>
        typename GenericTypeTrie<FieldType, NodeType>::Node*
        GenericTypeTrie<FieldType, NodeType>::get(
            std::vector<FieldType> const& sorted_fields,
            int fields_start_index,
            Node* root_node
        ) {
            if (fields_start_index >= sorted_fields.size()) {
                return root_node;
            } else {
                FieldType const &first_field = sorted_fields[0];

                // checking for an existing edge:
                for (int index = fields_start_index; index < root_node->edges.size(); index++) {
                    GenericTypeTrie::Edge const& edge = root_node->edges[index];
                    if (edge.field == first_field) {
                        return get(sorted_fields, 1 + fields_start_index, edge.result);
                    }
                }

                // fall-through, need to create a new edge with new destination node:
                auto new_node = new GenericTypeTrie::Node{};

                // first initializing 'new_node':
                new_node->parent = root_node;
                new_node->parent_edge_index = root_node->edges.size();
                new_node->hops_to_root = fields_start_index;
                new_node->result = nullptr;

                // then, initializing 'result' using fields in 'new_node':
                new_node->result = m_ctor(new_node);

                Edge new_edge{first_field, new_node};
                root_node->edges.push_back(new_edge);

                return get(sorted_fields, 1 + fields_start_index, new_node);
            }
        }
    }

}

#endif  // INCLUDED_PANDEMONIUM_TYPE_TRIE_HH
