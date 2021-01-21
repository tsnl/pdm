#include "setspec.hh"

namespace pdm::ast {
    void SetSpec::x_spectype_var(types::Var* spectype_var) {
        m_x_spectype_var = spectype_var;
    }
}