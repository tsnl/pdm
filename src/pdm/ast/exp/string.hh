#ifndef INCLUDED_PDM_AST_EXP_STRING_HH
#define INCLUDED_PDM_AST_EXP_STRING_HH

#include <vector>
#include <cassert>

#include "pdm/core/utf8.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/exp/exp.hh"
#include "pdm/ast/pattern/vpattern.hh"
#include "pdm/source/loc.hh"

namespace pdm::ast {

    class Manager;

    class StringExp: public Exp {
        friend Manager;

      public:
        class Piece {
            friend Manager;
          
          private:
            source::Loc  m_loc;
            utf8::String m_content;

          protected:
            Piece(source::Loc loc, utf8::String content)
            : m_loc(loc),
              m_content(content) {}
        };

      private:
        utf8::String m_content;
    
      public:
        StringExp(source::Loc loc, utf8::String content)
        : Exp(loc, Kind::StringExp),
          m_content(std::move(content)) {}

      public:
        utf8::String const& content() const {
            return m_content;
        }
    };

}

#endif  // INCLUDED_PDM_AST_EXP_STRING_HH
