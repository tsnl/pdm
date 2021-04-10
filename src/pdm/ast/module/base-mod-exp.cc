#include "base-mod-exp.hh"

#include "pdm/scoper/defn.hh"
#include "pdm/types/var.hh"

namespace pdm::ast {

    types::Var* BaseModExp::Field::x_defn_var() const {
        return x_defn()->var();
    }

}