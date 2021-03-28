#ifndef PDM__AST__MODULE__EXTERN_MOD_EXP_HH
#define PDM__AST__MODULE__EXTERN_MOD_EXP_HH

#include "base-mod-exp.hh"

namespace pdm::ast {
    class Manager;
}

namespace pdm::ast {

    // ExternCModExp represents the contents of an externally loaded
    // C module.
    class ExternCModExp: public BaseModExp {
        friend Manager;

      private:
        ExternCModExp(source::Loc loc, std::vector<BaseModExp::Field*>&& fields);
    };

    inline
    ExternCModExp::ExternCModExp(source::Loc loc, std::vector<BaseModExp::Field*>&& fields)
    :   BaseModExp(loc, Kind::ExternModExp, std::move(fields))
    {}

}

#endif  // PDM__AST__MODULE__EXTERN_MOD_EXP_HH