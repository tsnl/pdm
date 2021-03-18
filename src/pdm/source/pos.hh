#ifndef INCLUDED_PDM_SOURCE_POS_HH
#define INCLUDED_PDM_SOURCE_POS_HH

#include "i-source.hh"

namespace pdm::source {
    // todo: implement bison interface
    // 'position' and 'location'
    // 'position': https://www.gnu.org/software/bison/manual/html_node/C_002b_002b-position.html
    // 'location': https://www.gnu.org/software/bison/manual/html_node/C_002b_002b-location.html

    class Pos {
      private:
        int m_line;
        int m_column;

      public:
        Pos(int line, int column)
        : m_line(line), m_column(column) {}

        Pos(Pos const& other) = default;

        Pos() = default;

      public:
        int line() const { 
            return m_line; 
        }
        int column() const { 
            return m_column; 
        }

      public:
        void line(int new_line) {
            m_line = new_line;
        }
        void column(int new_column) {
            m_column = new_column;
        }

      public:
        bool is_valid() const {
            return m_line >= 0 && m_column >= 0;
        }
    };
};

#endif  // INCLUDED_PDM_SOURCE_POS_HH