#include "kd_var_solver.hh"

#include <vector>
#include <map>
#include <cassert>

#include "pdm/core/bitsets.hh"
#include "pdm/core/intern.hh"
#include "pdm/ast/arg/varg.hh"

#include "var.hh"
#include "invariant.hh"
#include "type_kind.hh"


namespace pdm::types {

    // SimplestKDVS is used to implement opaque types without any order:
    // Unit, String
    class SimplestKDVS: public KindDependentVarSolver {
      public:
        inline SimplestKDVS(VarKind var_kind, TypeKind required_type_kind);

      public:
        virtual SolvePhase2_Result lazy_try_add_invariant_impl(KindDependentInvariant* invariant) override;
    };

    inline SimplestKDVS::SimplestKDVS(VarKind var_kind, TypeKind required_type_kind)
    :   KindDependentVarSolver(VarKind::Type, required_type_kind)
    {}

    SolvePhase2_Result SimplestKDVS::lazy_try_add_invariant_impl(KindDependentInvariant* new_invariant) {
        if (required_type_kind() == TypeKind::Void) {
            if (dynamic_cast<VoidInvariant*>(new_invariant) != nullptr) {
                return SolvePhase2_Result::NoChange;
            }
        }
        else if (required_type_kind() == TypeKind::String) {
            if (dynamic_cast<StringInvariant*>(new_invariant) != nullptr) {
                return SolvePhase2_Result::NoChange;
            }
        }
        else {
            return SolvePhase2_Result::CompilerError;
        }
        return SolvePhase2_Result::TypingError;
    }

    // NumberKDVS is used to typecheck sets of numbers:
    // SignedInt, UnsignedInt, and Float are the three disjoint subclasses,
    // as well as accommodating conversions possible between them.
    class NumberKDVS: public KindDependentVarSolver {
      private:
        int m_opt_min_width_in_bits;
        int m_opt_max_width_in_bits;

      public:
        NumberKDVS(VarKind var_kind, TypeKind type_kind);

      public:
        virtual SolvePhase2_Result lazy_try_add_invariant_impl(KindDependentInvariant* new_invariant) override;
    };

    NumberKDVS::NumberKDVS(VarKind var_kind, TypeKind type_kind)
    :   KindDependentVarSolver(var_kind, type_kind),
        m_opt_min_width_in_bits(-1),
        m_opt_max_width_in_bits(-1)
    {}

    SolvePhase2_Result NumberKDVS::lazy_try_add_invariant_impl(KindDependentInvariant* new_invariant) {
        switch (required_type_kind())
        {
            case TypeKind::SignedInt:
            case TypeKind::UnsignedInt:
            {
                auto int_invariant = dynamic_cast<IntInvariant*>(new_invariant);
                
                // checking 'uses_sign_extension' is valid:
                bool needs_sign_extension = (required_type_kind() == TypeKind::SignedInt ? true : false);
                if (int_invariant->uses_sign_extension() != needs_sign_extension) {
                    return SolvePhase2_Result::TypingError;
                }

                // solving intersection of min and max width,
                // updating result if applied:
                SolvePhase2_Result result = SolvePhase2_Result::NoChange; 
                {
                    if (m_opt_min_width_in_bits < 0 || m_opt_min_width_in_bits < int_invariant->min_width_in_bits()) {
                        m_opt_min_width_in_bits = int_invariant->min_width_in_bits();
                        result = SolvePhase2_Result::UpdatedOrFresh;
                    }
                    if (m_opt_max_width_in_bits < 0 || m_opt_max_width_in_bits > int_invariant->max_width_in_bits()) {
                        m_opt_max_width_in_bits = int_invariant->max_width_in_bits();
                        result = SolvePhase2_Result::UpdatedOrFresh;
                    }
                }
                
                return result;
            }
            case TypeKind::Float:
            {
                auto float_invariant = dynamic_cast<FloatInvariant*>(new_invariant);

                // solving intersection of min and max width,
                // updating result if applied:
                SolvePhase2_Result result = SolvePhase2_Result::NoChange; 
                {
                    if (m_opt_min_width_in_bits < 0 || m_opt_min_width_in_bits < float_invariant->min_width_in_bits()) {
                        m_opt_min_width_in_bits = float_invariant->min_width_in_bits();
                        result = sp2res_and(result, SolvePhase2_Result::UpdatedOrFresh);
                    }
                    if (m_opt_max_width_in_bits < 0 || m_opt_max_width_in_bits > float_invariant->max_width_in_bits()) {
                        m_opt_max_width_in_bits = float_invariant->max_width_in_bits();
                        result = sp2res_and(result, SolvePhase2_Result::UpdatedOrFresh);
                    }
                }
                
                return result;
            }
            default:
            {
                return SolvePhase2_Result::CompilerError;
            }
        }
    }

    // TupleKDVS is used to typecheck tuples.
    // Tuple
    class TupleKDVS: public KindDependentVarSolver {
      private:
        std::vector<TypeVar*> m_typeof_items_tvs;

      public:
        TupleKDVS(VarKind var_kind);

      public:
        virtual SolvePhase2_Result lazy_try_add_invariant_impl(KindDependentInvariant* new_invariant) override;
    };

    TupleKDVS::TupleKDVS(VarKind var_kind)
    :   KindDependentVarSolver(var_kind, TypeKind::Tuple),
        m_typeof_items_tvs()
    {}

    SolvePhase2_Result TupleKDVS::lazy_try_add_invariant_impl(KindDependentInvariant* new_invariant) {
        auto tuple_invariant = dynamic_cast<TupleInvariant*>(new_invariant);
        if (tuple_invariant == nullptr) {
            return SolvePhase2_Result::TypingError;
        }
        
        if (m_typeof_items_tvs.size() != tuple_invariant->typeof_items_tvs().size()) {
            return SolvePhase2_Result::TypingError;
        }

        SolvePhase2_Result result = SolvePhase2_Result::NoChange;
        
        // equating fields:
        assert(m_typeof_items_tvs.size() == tuple_invariant->typeof_items_tvs().size());
        for (size_t index = 0; index < m_typeof_items_tvs.size(); index++) {
            Var* old_field_var = m_typeof_items_tvs[index];
            Var* new_field_var = tuple_invariant->typeof_items_tvs()[index];
            
            SolvePhase2_Result ao_res = old_field_var->higher_order_assume_equals(new_field_var);
            result = sp2res_and(result, ao_res);
        }
        
        return result;
    }

    // FieldCollectionKDVS is used to typecheck types with items a dictionary of fields:
    // Modules, Structs, and Enums.
    // Note that a Fielder subvars another Fielder if all fields are subvars.
    // E.g., for a module, this means...
    // - submodule value fields must subtype super-module value fields
    // - submodule type fields must subtype super-module type fields
    // - submodule typeclass fields must be subclasses of super-module typeclass fields
    // - submodule fields that do not occur in super-module are ignored
    class FieldCollectionKDVS: public KindDependentVarSolver {
      private:
        std::map<intern::String, Var*> m_fields;
    
      public:
        FieldCollectionKDVS(VarKind var_kind, TypeKind type_kind);

      public:
        virtual SolvePhase2_Result lazy_try_add_invariant_impl(KindDependentInvariant* new_invariant) override;
    };

    FieldCollectionKDVS::FieldCollectionKDVS(VarKind var_kind, TypeKind type_kind)
    :   KindDependentVarSolver(var_kind, type_kind)
    {}

    SolvePhase2_Result FieldCollectionKDVS::lazy_try_add_invariant_impl(KindDependentInvariant* new_invariant) {
        // ensuring FieldCollectionInvariant:
        auto new_field_collection_invariant = dynamic_cast<FieldCollectionInvariant*>(new_invariant);
        if (new_field_collection_invariant == nullptr) {
            return SolvePhase2_Result::TypingError;
        }

        // checking type_kind against Invariant kind:
        switch (required_type_kind())
        {
            case TypeKind::Struct:
            {
                auto new_struct_invariant = dynamic_cast<StructInvariant*>(new_invariant);
                if (new_struct_invariant == nullptr) {
                    return SolvePhase2_Result::TypingError;
                }
                break;
            }
            case TypeKind::Enum:
            {
                auto new_enum_invariant = dynamic_cast<EnumInvariant*>(new_invariant);
                if (new_enum_invariant == nullptr) {
                    return SolvePhase2_Result::TypingError;
                }
                break;
            }
            case TypeKind::Module:
            {
                auto new_module_invariant = dynamic_cast<ModuleInvariant*>(new_invariant);
                if (new_module_invariant == nullptr) {
                    return SolvePhase2_Result::TypingError;
                }
                break;
            }
            default:
            {
                // unexpected type kind.
                return SolvePhase2_Result::CompilerError;
            }
        }

        // updating fields:
        SolvePhase2_Result result = SolvePhase2_Result::NoChange;
        for (
            auto struct_invariant_field_iterator = new_field_collection_invariant->fields().begin(); 
            struct_invariant_field_iterator != new_field_collection_invariant->fields().end(); 
            struct_invariant_field_iterator++
        ) {
            intern::String field_name = struct_invariant_field_iterator->first;
            Var* struct_invariant_field_var = struct_invariant_field_iterator->second;
            
            auto kdvs_field_iterator = m_fields.find(field_name);
            if (kdvs_field_iterator != m_fields.end()) {
                // equals existing field
                Var* kdvs_field_var = kdvs_field_iterator->second;
                result = sp2res_and(
                    result,
                    kdvs_field_var->higher_order_assume_equals(struct_invariant_field_var)
                );   
            } else {
                // insert invariant field var:
                auto field_insert_res = m_fields.insert({field_name, struct_invariant_field_var});
                assert(field_insert_res.second);
                result = sp2res_and(result, SolvePhase2_Result::UpdatedOrFresh);
            }
        }
        return result;
    }

    // FnKDVS is used to typecheck TypeVars that contain functions.
    class FnKDVS: public KindDependentVarSolver {
      public:
        struct FnArg {
            ast::VArgAccessSpec varg_access_spec;
            TypeVar* typeof_arg_tv;
        };

      private:
        std::vector<FnArg> m_args;
        TypeVar* m_typeof_ret_tv;

      public:
        FnKDVS(VarKind var_kind);

      public:
        virtual SolvePhase2_Result lazy_try_add_invariant_impl(KindDependentInvariant* new_invariant) override;
    };
    
    FnKDVS::FnKDVS(VarKind var_kind) 
    :   KindDependentVarSolver(var_kind, TypeKind::Fn) ,
        m_args(),
        m_typeof_ret_tv(nullptr)
    {}
    SolvePhase2_Result FnKDVS::lazy_try_add_invariant_impl(KindDependentInvariant* new_invariant) {
        auto new_fn_invariant = dynamic_cast<FnInvariant*>(new_invariant);
        if (new_fn_invariant == nullptr) {
            return SolvePhase2_Result::TypingError;
        }

        // checking same arg count
        if (m_args.size() != new_fn_invariant->formal_args().size()) {
            return SolvePhase2_Result::TypingError;
        }

        // relating each arg:
        size_t args_count = m_args.size();
        for (size_t index = 0; index < args_count; index++) {
            FnInvariant_FnArg const& fn_invariant_fn_arg = new_fn_invariant->formal_args()[index];
            FnKDVS::FnArg const& fn_kdvs_arg = m_args[index];
            
            // checking same arg access spec:
            if (fn_invariant_fn_arg.varg_access_spec != fn_kdvs_arg.varg_access_spec) {
                return SolvePhase2_Result::TypingError;
            } else {
                if (new_fn_invariant->strength() == FnInvariant_Strength::Formal) {
                    return fn_invariant_fn_arg.typeof_arg_tv->higher_order_assume_equals(fn_kdvs_arg.typeof_arg_tv);
                } else if (new_fn_invariant->strength() == FnInvariant_Strength::Actual) {
                    return fn_invariant_fn_arg.typeof_arg_tv->higher_order_assume_subvar(fn_kdvs_arg.typeof_arg_tv);
                } else {
                    return SolvePhase2_Result::CompilerError;
                }
            }
        }

        // relating the return type:
        TypeVar* fn_invariant_typeof_ret_tv = new_fn_invariant->typeof_ret_tv();
        TypeVar* fn_kdvs_typeof_ret_tv = m_typeof_ret_tv;
        if (new_fn_invariant->strength() == FnInvariant_Strength::Formal) {
            return fn_invariant_typeof_ret_tv->higher_order_assume_equals(fn_kdvs_typeof_ret_tv);
        } else if (new_fn_invariant->strength() == FnInvariant_Strength::Actual) {
            return fn_invariant_typeof_ret_tv->higher_order_assume_subvar(fn_kdvs_typeof_ret_tv);
        } else {
            return SolvePhase2_Result::CompilerError;
        }
    }

}

//
// Interface:
//

namespace pdm::types {

    SolvePhase2_Result KindDependentVarSolver::try_add_invariant(KindDependentInvariant* invariant) {
        // from https://www.cplusplus.com/reference/set/set/insert/
        // The single element versions (1) return a pair, with its member pair::first set to 
        // an iterator pointing to [the inserted element in the collection].
        // The pair::second element in the pair is set to true if a
        // new element was inserted or false if an equivalent element already existed.
        auto insert_result = m_added_invariants.insert(invariant);
        bool new_element_inserted = insert_result.second;
        if (new_element_inserted) {
            return lazy_try_add_invariant_impl(invariant);
        } else {
            return SolvePhase2_Result::NoChange;
        }
    }

    NewKDVS try_new_kdvs_for(VarKind var_kind, TypeKindBitset local_allowed_type_kinds_bitset) {
        NewKDVS rv;

        if (local_allowed_type_kinds_bitset == 0) {
            rv.result = SolvePhase1_Result::InsufficientInfo;
            rv.kdvs = nullptr;
        } 
        else if (is_type_var_kind(var_kind)) {
            if (exactly_1_bit_is_1_in_bitset(local_allowed_type_kinds_bitset)) {
                rv.result = SolvePhase1_Result::Ok;
                TypeKind type_kind = static_cast<TypeKind>(local_allowed_type_kinds_bitset);
                assert(type_kind <= TypeKind::__Max && "bug in 'exactly_1_bit_is_1_in_bitset'");
                switch (type_kind)
                {
                    case TypeKind::Void:
                    case TypeKind::String:
                    {
                        rv.kdvs = new SimplestKDVS(var_kind, type_kind);
                        break;
                    }
                    case TypeKind::SignedInt:
                    {
                        rv.kdvs = new NumberKDVS(var_kind, TypeKind::SignedInt);
                        break;
                    }
                    case TypeKind::UnsignedInt:
                    {
                        rv.kdvs = new NumberKDVS(var_kind, TypeKind::UnsignedInt);
                        break;
                    }
                    case TypeKind::Float:
                    {
                        rv.kdvs = new NumberKDVS(var_kind, TypeKind::Float);
                        break;
                    }
                    case TypeKind::Tuple:
                    {
                        rv.kdvs = new TupleKDVS(var_kind);
                        break;
                    }
                    case TypeKind::Struct:
                    {
                        rv.kdvs = new FieldCollectionKDVS(var_kind, TypeKind::Struct);
                        break;
                    }
                    case TypeKind::Enum:
                    {
                        rv.kdvs = new FieldCollectionKDVS(var_kind, TypeKind::Enum);
                        break;
                    }
                    case TypeKind::Module:
                    {
                        rv.kdvs = new FieldCollectionKDVS(var_kind, TypeKind::Module);
                        break;
                    }
                    case TypeKind::Fn:
                    {
                        rv.kdvs = new FnKDVS(var_kind);
                        break;
                    }
                }
            }
        } 
        else {
            rv.result = SolvePhase1_Result::Error_MixedKind;
            rv.kdvs = nullptr;
        }

        return rv;
    }
}