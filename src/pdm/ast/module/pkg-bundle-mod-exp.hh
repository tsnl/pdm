#ifndef INCLUDED__PDM__AST__MODULE__PACKAGE_MOD_EXP_HH
#define INCLUDED__PDM__AST__MODULE__PACKAGE_MOD_EXP_HH

#include "base-mod-exp.hh"
#include "pdm/source/loc.hh"

namespace pdm::ast {
    class Manager;
}

namespace pdm::ast {

    // PkgBundleModExp represents a monomorphic module containing only other modules for a package.
    // It is used for 2 cases:
    // - to wrap all fields in a package, given by 'pd-index.json'
    // - to wrap all modules in a script or package for a field in an index file, see 'IMPORT_ALL_FROM' or
    //   'import { * from "source.pd" }'
    class PkgBundleModExp: public BaseModExp {
        friend Manager;

      private:
        PkgBundleModExp(source::Loc loc, std::vector<BaseModExp::Field*>&& fields);
    };

    inline
    PkgBundleModExp::PkgBundleModExp(source::Loc loc, std::vector<BaseModExp::Field*>&& fields)
    :   BaseModExp(loc, Kind::PkgBundleModExp, std::move(fields))
    {}

}

#endif  // INCLUDED__PDM__AST__MODULE__PACKAGE_MOD_EXP_HH