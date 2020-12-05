#ifndef INCLUDED_PDM_TYPER_TYPE_HH
#define INCLUDED_PDM_TYPER_TYPE_HH

#include "tv_kind.hh"
#include "soln.hh"

namespace pdm::typer {
    class Typer;
}

namespace pdm::typer {

    // each TV is just a stable wrapper around a changing 'soln' ptr.
    // the typer 'solves' by iteratively substituting a suitable soln for each variable.
    // when consecutive substitution passes reach a fixed point, the system is either definitely solved or in error.
    class TV {
        friend class pdm::typer::Typer;

      // data members:
      private:
        Typer* m_typer;
        Soln*  m_soln;

      // public getters:
      public:
        Typer* typer() const {
            return m_typer;
        }

      // protected constructor:
      protected:
        TV(Typer* typer, Soln* soln)
        : m_typer(typer), m_soln(soln) {}

      // public solver API:
      public:
        bool is_solved() const {
            return (m_soln != nullptr) && (m_soln->is_concrete());
        }
        void solve();

      // dynamic 'tv_kind':
      public:
        TvKind tv_kind() const {
            if (m_soln != nullptr) {
                return m_soln->tv_kind();
            } else {
                return TvKind::Unknown;
            }
        }
    };

}   // namespace pdm::typer

#endif  // INCLUDED_PDM_TYPER_TYPE_HH