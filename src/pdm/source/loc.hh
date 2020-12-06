#ifndef INCLUDED_PDM_SOURCE_LOC_HH
#define INCLUDED_PDM_SOURCE_LOC_HH

#include <cassert>

#include "pos.hh"

namespace pdm::source {
    class Source;
}

namespace pdm::source {

    class Loc {
      private:
        Source* m_source;
        int m_first_line;
        int m_first_column;
        int m_last_line;
        int m_last_column;

      public:
        Loc(Source* source, int first_line, int first_column, int last_line, int last_column)
        : m_source(source), 
          m_first_line(first_line), m_first_column(first_column),
          m_last_line(last_line), m_last_column(last_column) {}

        Loc(Pos const& first_pos, Pos const& last_pos)
        : Loc(first_pos.source(), first_pos.line(), first_pos.column(), last_pos.line(), last_pos.column()) {
            assert(first_pos.source() == last_pos.source() && "Cannot create Loc from Pos with different sources.");
        }
    
      public:
        Source* source() const {
            return m_source;
        }
        int first_line() const {
            return m_first_line;
        }
        int first_column() const {
            return m_first_column;
        }
        int last_line() const {
            return m_last_line;
        }
        int last_column() const {
            return m_last_column;
        }

      public:
        static Loc none;
    };

}   // namespace pdm::source

#endif  // INCLUDED_PDM_SOURCE_LOC_HH