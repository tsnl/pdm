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

      // general-purpose getters
      public:
        [[nodiscard]] Kind kind() const {
            return m_kind;
        }
        [[nodiscard]] source::Loc const& loc() const {
            return m_loc;
        }

        [[nodiscard]] source::Loc& mut_loc() {
            return m_loc;
        }

      // protected constructor:
      protected:
        Node(source::Loc loc, Kind kind)
        :   m_kind(kind),
            m_loc(loc)
        {}

      public:
        virtual ~Node() = default;
    };

}   // namespace pdm::ast

#endif  // INCLUDED_AST_NODE_HH