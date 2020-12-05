#ifndef INCLUDED_PDM_TYPER_ROUGH_CLASS_HH
#define INCLUDED_PDM_TYPER_ROUGH_CLASS_HH

namespace pdm::typer {

    // RoughClass indicates membership in a broad, *discrete* class
    
    // Known limitations:
    // - no parametric sets of classes => cannot formally spec a class as template arg
    // - no parametric sets of tfuncs => cannot formally spec/pass a template as template arg

    enum class RoughClass {
        // Solns in these classes are just types, i.e. sets of values.
        Unit           = 0x1,
        Int            = 0x2,
        Float          = 0x4,
        Mut            = 0x8,
        Ptr            = 0x10,
        Struct         = 0x20,
        Enum           = 0x40,
        Module         = 0x80,
        Class          = 0x100,
        VFunc          = 0x200,
        
        // Typeclasses are sets of types that satisfy constraints
        Typeclass      = 0x400,

        // TFunc maps constvals & types to a constval/type
        // for each formal arg,
        // - if class, then type arg.
        // - if type, then val arg.
        // - 
        TFunc          = 0x800,

        // TypeVars compute classes and accept one or more concrete substitutions.
        MonomorphicVar = 0x1000,
        PolymorphicVar = 0x2000,
        
        // ConstVals store constant values as args for TFuncs
        ConstVal       = 0x4000
    };

}

#endif  // INCLUDED_PDM_TYPER_ROUGH_CLASS_HH