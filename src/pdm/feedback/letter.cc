#include "letter.hh"

#include <iostream>
#include <iomanip>

#include "pdm/source/loc.hh"
#include "pdm/feedback/note.hh"

namespace pdm::feedback {

    void Letter::print(std::ostream& out) {
        switch (severity()) {
            case Severity::FatalError:
            {
                out << "FATAL_ERROR: ";
                break;
            }
            case Severity::Error:
            {
                out << "ERROR: ";
                break;
            }
            case Severity::Info:
            {
                out << "INFO: ";
                break;
            }
            case Severity::Warning:
            {
                out << "WARNING: ";
                break;
            }
        }
        out << headline() << std::endl;
        out << "  " << more() << std::endl;
        for (Note* note: m_notes) {
            note->print(out, "    ");
        }
    }

}