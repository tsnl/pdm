#include "typespec.hh"

namespace pdm::ast {
    
    Typespec::Typespec(source::Loc loc, Kind kind)
    :   Node(loc, kind),
        m_x_spectype_var(nullptr)
    {}

    types::Var* Typespec::x_spectype_var() const {
        return m_x_spectype_var;
    }

    void Typespec::x_spectype_var(types::Var* spectype_var) {
        m_x_spectype_var = spectype_var;
    }

}