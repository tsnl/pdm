#include "pdm/feedback/manager.hh"

#include <vector>
#include <ostream>

#include "pdm/feedback/letter.hh"

namespace pdm::feedback {

    Manager Manager::s_root{nullptr};

    Manager* Manager::root() {
        return &s_root;
    }

    Manager* Manager::add_child() {
        Manager* infant = new Manager(this);
        m_children.push_back(infant);
        return infant;
    }

    void Manager::post(Letter* letter) {
        m_letters.push_back(letter);
    }

    void Manager::print_all(std::ostream& out) {
        if (visible()) {
            for (Letter* letter: m_letters) {
                letter->print(out);
            }
            for (Manager* manager: m_children) {
                manager->print_all(out);
            }
        }
    }

}
