#include "loc.hh"

#include "i_source.hh"

namespace pdm::source {

    Loc Loc::none {nullptr, -1, -1, -1, -1};

    void Loc::print(std::ostream& out) const {
        if (this->source()) {
            out << this->source()->abs_path() << ":";
        }
        out << this->first_line() << ":" << this->first_column();
        if (this->first_line() == this->last_line()) {
            if (this->first_column() != this->last_column()) {
                out << "-" << this->last_column();
            }
        } else {
            out << "-" << this->last_line() << ":" << this->last_column();
        }
    }

}