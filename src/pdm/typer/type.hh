#ifndef INCLUDED_PDM_TYPER_TYPE_HH
#define INCLUDED_PDM_TYPER_TYPE_HH

#include "soln.hh"

// Forward declarations:
namespace pdm::typer {

    class Typer;
    
}   // namespace pdm::typer


//
//
// Implementation:
//
//

namespace pdm::typer {

    class Type {
      // data members:
      private:
        Typer* m_typer;
        Soln*  m_soln;

      // public getters:
      public:
        Typer* typer() const {
            return m_typer;
        }
        
      // protected getters:
      protected:
        
      // protected constructor:
      protected:
        Type(Typer* typer, Soln* soln)
        : m_typer(typer), m_soln(soln) {}
    };

}   // namespace pdm::typer

#endif  // INCLUDED_PDM_TYPER_TYPE_HH