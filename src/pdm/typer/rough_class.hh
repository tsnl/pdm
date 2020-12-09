#ifndef INCLUDED_PDM_TYPER_ROUGH_CLASS_HH
#define INCLUDED_PDM_TYPER_ROUGH_CLASS_HH

namespace pdm::typer {

    // RoughClass indicates membership in a broad, *discrete* class
    
    // Known limitations:
    // - no parametric sets of classes => cannot formally spec a class as template arg
    // - no parametric sets of tfuncs => cannot formally spec/pass a template as template arg

    enum class RoughClass {
        // Solns in these classes are just types, i.e. sets of values.
        Void,
        Int,
        Float,
        Mut,
        Ptr,
        Struct,
        Enum,
        Module,
        VFunc,
        
        // Typeclasses are sets of types that satisfy constraints
        Typeclass,

        // TFunc maps constvals & types to a constval/type
        // for each formal arg,
        // - if class, then type arg.
        // - if type, then val arg.
        // - 
        TFunc,

        // TypeVars compute classes and accept one or more concrete substitutions.
        MonomorphicVar,
        PolymorphicVar,
        
        // ConstVals store constant values as args for TFuncs
        ConstVal,

        // after all real elements, '__Count'
        __Count
    };

}

#endif  // INCLUDED_PDM_TYPER_ROUGH_CLASS_HH