#include "pdm/parser/reader.hh"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

#include "pdm/feedback/feedback.hh"
#include "pdm/feedback/letter.hh"
#include "pdm/feedback/severity.hh"

namespace pdm::parser {

    Reader::Reader()
    : m_fp(nullptr),
      m_peek_pos(),
      m_peek_char(),
      m_promised_char(),
      m_at_eof() {}

    bool Reader::setup(source::ISource* source) {
        // disposing if already in use.
        if (m_opt_source != nullptr) {
            fclose(m_fp);
            m_opt_source = nullptr;
            m_fp = nullptr;
        }

        // trying to open the file:
        m_fp = fopen(source->abs_path().c_str(), "r");
        if (m_fp == nullptr) {
            feedback::post(new feedback::Letter(
                feedback::Severity::Error,
                "Failed to open source file at '" + source->abs_path() + "'.",
                "Are you sure it exists?"
            ));
            return false;
        }
        
        // success! initializing:
        m_opt_source = source;
        m_peek_pos.line(1);
        m_peek_pos.column(0);
        m_peek_char = EOF;
        m_promised_char = EOF;
        m_at_eof = 0;
        return true;
    }

    bool Reader::at_eof() const {
        return m_at_eof;
    }
    bool Reader::at_sof() const {
        return (!at_eof()) && (m_peek_char == EOF);
    }
    source::Pos const* Reader::opt_head_pos() const {
        if (at_sof()) {
            return nullptr;
        } else {
            return &m_peek_pos;
        }
    }
    int Reader::head_loc_rough() const {
        if (at_sof()) {
            return -1;
        } else if (at_eof()) {
            return +1;
        } else {
            return 0;
        }
    }

    int Reader::read_head() {
        return m_peek_char;
    }

    int Reader::advance_head() {
        // Reading a character from the file, or just returning a promised
        // char if stored.
        // If a second char was read and not used, it is 'promised' for later.
        // - Characters are promised when we read for and do not obtain CRLFs.
        // Reading a char = advancing tape by 1.

        // (peekChar, atEof)
        // |- EOF, false: at start of file, no chars loaded
        // |- EOF, true: at end of file, last char loaded
        // |- (*), false: reading from the file

        char readChar;
        if (m_promised_char != -1) {
            // using the promised char
            readChar = m_promised_char;
            m_promised_char = -1;
        } else if (at_eof()) {
            // already at EOF, cannot move further, returning 0
            return 0;
        } else {
            // reading a fresh char
            readChar = fgetc(m_fp);
            if (readChar < 0) {
                // found EOF, but read a char (moved into post-tape)
                m_peek_char = EOF;
                m_at_eof = 1;
                return 1;
            }
        }

        // Updating the peekChar, loc, and other attributes:
        m_peek_char = readChar;
        m_at_eof = 0;
        if (readChar == '\n' || readChar == '\r') {
            m_peek_pos.line(m_peek_pos.line()+1);
            m_peek_pos.column(0);
            
            // normalizing CRLF and CR line-endings to LF:
            if (readChar == '\r') {
                if (!feof(m_fp)) {
                    // reading the next char (for an LF)
                    char nextChar = fgetc(m_fp);
                    if (nextChar != '\n') {
                        // Whoops! Not a Windows CRLF.
                        // Let's promise the read character for later:
                        assert(nextChar != -1);
                        m_promised_char = nextChar;
                    }
                }
                m_peek_char = '\n';
            }
        } else {
            m_peek_pos.column(m_peek_pos.column()+1);
        }
        return 1;
    }
}
