#ifndef INCLUDED_PDM_PARSER_READER_HH
#define INCLUDED_PDM_PARSER_READER_HH

#include <cstdio>

#include "pdm/source/i-source.hh"
#include "pdm/source/pos.hh"

namespace pdm::parser {

    class Reader {
      private:
        FILE*           m_fp;
        source::ISource* m_opt_source;
        source::Pos     m_peek_pos;
        int             m_peek_char;
        int             m_promised_char;
        int             m_at_eof;

      public:
        Reader();

      public:
        // setup can be called multiple times to reuse the reader.
        // returns (1) if successfully opened, else (0)
        bool setup(source::ISource* source);

      public:
        source::ISource* opt_source() const {
            return m_opt_source;
        }

      // reader API:
      // WARNING: ensure you call 'setup' on a source::ISource* instance first!
      public:
        // advances the reading head by one character.
        // must be called before peeking the first character.
        // returns (0) if the head is in EOF after advancing, else (1) if in tape
        int advance_head();

        // returns the character under head in the filestream, else -1.
        int read_head();

        // returns (1) if the source is at SOF, else (0).
        // if Peek returns EOF and SourceReaderAtSof is (0), then we are at the EOF (end of file).
        bool at_sof() const;

        // returns (1) if the source is at EOF, else (0).
        // if Peek returns EOF and SourceReaderAtEof is (0), then we are at the SOF (start of file).
        bool at_eof() const;

        // returns a 'Pos' describing the head's position or nullptr if at SOF.
        source::Pos const* opt_head_pos() const;

        // returns (-1) if the head is before the tape, (0) if the head is in tape, or (+1) if the
        // head is after the tape.
        int head_loc_rough() const;
    };

}

#endif  // INCLUDED_PDM_PARSER_READER_HH
