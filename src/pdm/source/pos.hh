#ifndef INCLUDED_PDM_SOURCE_POS_HH
#define INCLUDED_PDM_SOURCE_POS_HH

#include "source.hh"

namespace pdm::source {
    // todo: implement bison interface
    // 'position' and 'location'
    // 'position': https://www.gnu.org/software/bison/manual/html_node/C_002b_002b-position.html
    // 'location': https://www.gnu.org/software/bison/manual/html_node/C_002b_002b-location.html

    class Pos {
      private:
        Source* m_source;
        int m_line;
        int m_column;

      public:
        Pos(Source* source, int line, int column)
        : m_source(source), m_line(line), m_column(column) {}

      public:
        Source* source() const { return m_source; }
        int line() const { return m_line; }
        int column() const { return m_column; }
    };
};

#endif  // INCLUDED_PDM_SOURCE_POS_HH