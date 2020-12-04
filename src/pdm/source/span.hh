#ifndef INCLUDED_PDM_SOURCE_SPAN_HH
#define INCLUDED_PDM_SOURCE_SPAN_HH

#include "source.hh"

namespace pdm::source {
    // todo: implement bison interface
    // 'position' and 'location'
    // 'position': https://www.gnu.org/software/bison/manual/html_node/C_002b_002b-position.html
    // 'location': https://www.gnu.org/software/bison/manual/html_node/C_002b_002b-location.html

    class Span {
        Source* source;
        int m_first_line;
        int m_first_column;
        int m_last_line;
        int m_last_column;
    };
};

#endif  // INCLUDED_PDM_SOURCE_SPAN_HH