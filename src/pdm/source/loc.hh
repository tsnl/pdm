#ifndef INCLUDED_PDM_SOURCE_LOC_HH
#define INCLUDED_PDM_SOURCE_LOC_HH

#include <cassert>
#include <ostream>

#include "pos.hh"

namespace pdm::source {
    class ISource;
}

namespace pdm::source {

    class Loc {
      private:
        ISource* m_source;
      
      // BISON interface:
      // https://www.gnu.org/software/bison/manual/html_node/User-Defined-Location-Type.html
      public:
        source::Pos begin;
        source::Pos end;

      public:
        Loc() = default;

        Loc(Pos const& first_pos, Pos const& last_pos)
        : m_source(nullptr),
          begin(first_pos),
          end(last_pos) {}

        explicit Loc(Pos const& only_pos)
        : Loc(only_pos, only_pos) {}
    
        Loc(ISource* source, int first_line, int first_column, int last_line, int last_column)
        : Loc({first_line, first_column}, {last_line, last_column}) {
            this->source(source);
        }

      public:
        ISource* source() const {
            return m_source;
        }
        int first_line() const {
            return begin.line();
        }
        int first_column() const {
            return begin.column();
        }
        int last_line() const {
            return end.line();
        }
        int last_column() const {
            return end.column();
        }

      public:
        void source(ISource* source) {
            m_source = source;
        }
        void first_line(int first_line) { 
            begin.line(first_line);
        }
        void first_column(int first_column) { 
            begin.column(first_column);
        }
        void last_line(int last_line) { 
            end.line(last_line);
        }
        void last_column(int last_column) { 
            end.column(last_column);
        }

      public:
        void print(std::ostream& out) const;
        
      public:
        static Loc none;
    };

    inline std::ostream& operator<<(std::ostream& out, Loc loc);

    inline std::ostream& operator<<(std::ostream& out, Loc loc) {
        loc.print(out);
        return out;
    }

}   // namespace pdm::source

#endif  // INCLUDED_PDM_SOURCE_LOC_HH
