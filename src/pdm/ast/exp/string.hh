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
        enum class QuoteKind {
            SingleQuote,
            DoubleQuote
        };

      public:
        class Piece {
            friend Manager;
          
          private:
            source::Loc  m_loc;
            utf8::String m_content;
            QuoteKind    m_quote_kind;

          public:
            Piece(source::Loc loc, utf8::String content, QuoteKind quote_kind)
            : m_loc(loc),
              m_content(content),
              m_quote_kind(quote_kind) {}

          public:
            source::Loc loc() const {
                return m_loc;
            }
            utf8::String content() const {
                return m_content;
            }
          
          public:
            QuoteKind quote_kind() const {
                return m_quote_kind;
            }
            int quote_char() const {
                switch (quote_kind()) {
                    case QuoteKind::SingleQuote: return '\'';
                    case QuoteKind::DoubleQuote: return '"';
                }
            }
        };

      private:
        std::vector<StringExp::Piece> m_pieces;
        utf8::String                  m_content;

      public:
        StringExp(source::Loc loc, std::vector<StringExp::Piece>&& pieces)
        : Exp(loc, Kind::StringExp),
          m_pieces(std::move(pieces)),
          m_content(std::move(_content_from_pieces(m_pieces))) {}

        StringExp(source::Loc loc, utf8::String content, QuoteKind quote_kind)
        : StringExp(loc, std::move(std::vector<Piece>{1,Piece{loc,content,quote_kind}})) {}

      public:
        std::vector<StringExp::Piece> const& pieces() const {
            return m_pieces;
        }
        utf8::String const& content() const {
            return m_content;
        }

      private:
        static utf8::String&& _content_from_pieces(std::vector<StringExp::Piece> const& pieces) {
            utf8::StringBuilder content_sb;
            for (StringExp::Piece piece: pieces) {
                content_sb.append_str(piece.content());
            }
            return std::move(content_sb.strdup());
        }
    };

}

#endif  // INCLUDED_PDM_AST_EXP_STRING_HH
