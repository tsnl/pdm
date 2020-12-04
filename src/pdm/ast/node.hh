#ifndef INCLUDED_AST_NODE_HH
#define INCLUDED_AST_NODE_HH

#include <string>

#include "pdm/source/span.hh"

#include "kind.hh"

namespace pdm::ast {

    class Node {
        struct NodeHeader;

      // data members:
      private:
        Kind        m_kind;
        NodeHeader* m_header;
        void*       m_more;

      // NodeHeader implementation:
      private:
        struct NodeHeader {
            // source::Span span;
            std::string  repr;
        };

      // subtype 'more' ptr access <=> Node fixed size
      protected:
        void* more() const {
            return m_more;
        }
        void* more(void* ptr) {
            return m_more = ptr;
        }

      // general-purpose getters
      public:
        Kind kind() const {
            return m_kind;
        }
    
      // basic constructors
      protected:
        Node(Kind kind);

      // public visitor API:
      protected:
        

      public:
    };

    struct _NodeHeader {
        // std::string repr;
        // Span span;
    };

}   // namespace pdm::ast

#endif  // INCLUDED_AST_NODE_HH