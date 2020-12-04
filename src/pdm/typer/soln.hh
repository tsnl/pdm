#ifndef INCLUDED_KIND_HH
#define INCLUDED_KIND_HH

#include <vector>

#include "constraint.hh"

namespace pdm::typer {

    // RoughClass indicates membership in a broad, *discrete* class
    // if an instance is in more than 1 rough class, it is still ambig. and unsolved.
    // 'Free' => not in any class, ideally pending substitution
    enum class RoughClass {
        Unit    = 0x1,
        Int     = 0x2,
        Float   = 0x4,
        Struct  = 0x8,
        Enum    = 0x10,
        VFunc   = 0x20,
        Module  = 0x40,
        TFunc   = 0x80,
        Type    = 0x100,
        Class   = 0x200,
        Free    = 0x400
    };

    class Soln {
        RoughClass m_rough_class;
        std::vector<Constraint*> m_constraints;

      // public getters:
      public:
        RoughClass rough_class() const {
            return m_rough_class;
        }

      public:
        bool is_solved() const;
    };

}   // namespace pdm::typer

#endif  // INLCUDED_KIND_HH
