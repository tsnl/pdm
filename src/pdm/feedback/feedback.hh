#ifndef INCLUDED_PDM_FEEDBACK_FEEDBACK_HH
#define INCLUDED_PDM_FEEDBACK_FEEDBACK_HH

#include <ostream>

namespace pdm::feedback {

    class Manager;
    class Letter;

    Manager* new_manager();
    void post(Letter* letter);
    void print_all(std::ostream& out);

}

#endif  // INCLUDED_PDM_FEEDBACK_FEEDBACK_HH