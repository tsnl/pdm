#include "feedback.hh"

#include <ostream>

#include "pdm/feedback/letter.hh"
#include "pdm/feedback/manager.hh"

namespace pdm::feedback {
    
    Manager* new_manager() {
        return Manager::root()->add_child();
    }
    void post(Letter* letter) {
        Manager::root()->post(letter);
    }
    void print_all(std::ostream& out) {
        Manager::root()->print_all(out);
    }

}
