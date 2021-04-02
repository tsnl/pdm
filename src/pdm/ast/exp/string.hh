#ifndef INCLUDED_PDM_AST_EXP_STRING_HH
#define INCLUDED_PDM_AST_EXP_STRING_HH

#include <vector>
#include <cassert>

#include <llvm-c/Core.h>

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
            source::Loc m_loc;
            utf8::String m_content;
            QuoteKind m_quote_kind;

          public:
            Piece(source::Loc loc, utf8::String content, QuoteKind quote_kind);

          public:
            [[nodiscard]] source::Loc loc() const;
            [[nodiscard]] utf8::String content() const;
          
          public:
            [[nodiscard]] QuoteKind quote_kind() const;
            [[nodiscard]] int quote_char() const;
        };

      private:
        std::vector<StringExp::Piece> m_pieces;
        utf8::String m_content;
        LLVMValueRef m_x_llvm_global;

      public:
        StringExp(source::Loc loc, std::vector<StringExp::Piece>&& pieces);

        StringExp(source::Loc loc, utf8::String content, QuoteKind quote_kind)
        : StringExp(loc, std::move(std::vector<Piece>{1,Piece{loc, std::move(content), quote_kind}})) {}

      public:
        [[nodiscard]] std::vector<StringExp::Piece> const& pieces() const;
        [[nodiscard]] utf8::String const& content() const;

      private:
        static utf8::String&& _content_from_pieces(std::vector<StringExp::Piece> const& pieces) {
            utf8::StringBuilder content_sb;
            for (StringExp::Piece const& piece: pieces) {
                content_sb.append_str(piece.content());
            }
            return std::move(content_sb.strdup());
        }

      public:
        void x_llvm_global(LLVMValueRef llvm_global);
        [[nodiscard]] LLVMValueRef x_llvm_global() const;
    };

    inline StringExp::StringExp(source::Loc loc, std::vector<StringExp::Piece>&& pieces)
    :   Exp(loc, Kind::StringExp),
        m_pieces(std::move(pieces)),
        m_content(std::move(_content_from_pieces(m_pieces))) {}

    inline StringExp::Piece::Piece(source::Loc loc, utf8::String content, StringExp::QuoteKind quote_kind)
    :   m_loc(loc),
        m_content(std::move(content)),
        m_quote_kind(quote_kind) {}

    inline std::vector<StringExp::Piece> const& StringExp::pieces() const {
        return m_pieces;
    }

    inline utf8::String const& StringExp::content() const {
        return m_content;
    }

    inline void StringExp::x_llvm_global(LLVMValueRef llvm_global) {
        m_x_llvm_global = llvm_global;
    }

    inline LLVMValueRef StringExp::x_llvm_global() const {
        return m_x_llvm_global;
    }

    inline source::Loc StringExp::Piece::loc() const {
        return m_loc;
    }

    inline utf8::String StringExp::Piece::content() const {
        return m_content;
    }

    inline StringExp::QuoteKind StringExp::Piece::quote_kind() const {
        return m_quote_kind;
    }

    inline int StringExp::Piece::quote_char() const {
        switch (quote_kind()) {
            case QuoteKind::SingleQuote: return '\'';
            case QuoteKind::DoubleQuote: return '"';
        }
    }

}

#endif  // INCLUDED_PDM_AST_EXP_STRING_HH
