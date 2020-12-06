#ifndef INCLUDED_AST_NODE_HH
#define INCLUDED_AST_NODE_HH

#include <string>
#include "pdm/source/loc.hh"

#include "kind.hh"

namespace pdm::ast {

    class Node {
      // data members:
      private:
        Kind        m_kind;
        source::Loc m_loc;
        void*       m_more;

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
    
      // protected constructor:
      protected:
        Node(source::Loc loc, Kind kind)
        : m_kind(kind),
          m_loc(loc),
          m_more(nullptr) {}
    };

}   // namespace pdm::ast

#endif  // INCLUDED_AST_NODE_HH