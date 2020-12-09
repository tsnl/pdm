#include "pdm/feedback/note.hh"

#include <ostream>

#include "pdm/ast/node.hh"

namespace pdm::feedback {

    source::Loc const* Note::opt_loc() const {
        return nullptr;
    }

    void Note::print(std::ostream& out, std::string const& indent_spacer) const {
        out << indent_spacer
            << "- " << this->desc() 
            << std::endl;

        if (opt_loc()) {
            out << indent_spacer
                << "  "
                << "[";
            this->opt_loc()->print(out);
            out << "]"
                << std::endl;
        }
    }

    source::Loc const* SourceLocNote::opt_loc() const {
        return &m_loc;
    }

    source::Loc const* AstNodeNote::opt_loc() const {
        return &m_node->loc();
    }

}
