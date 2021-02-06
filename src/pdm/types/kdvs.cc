#include "kdvs.hh"

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cassert>

#include "pdm/core/bitsets.hh"
#include "pdm/core/intern.hh"
#include "pdm/core/integer.hh"
#include "pdm/ast/arg/varg.hh"

#include "var.hh"
#include "var_invariant.hh"
#include "kind.hh"


namespace pdm::types {

    //
    // Shared print helpers:
    //

    void KindDependentVarSolver::help_print_common_and_start_indented_block(
        printer::Printer& printer,
        std::string const& name
    ) const {
        // headline:
        printer.print_str("KDVS ");
        printer.print_str(name);
        printer.print_c_str(" (tk: ");
        printer.print_c_str(type_kind_as_str(m_required_type_kind));
        printer.print_c_str(", vk: ");
        printer.print_c_str(var_archetype_as_str(m_var_kind));
        printer.print_c_str(") {");

        // indent + body:
        printer.print_newline_indent();
        {
            // printing all added kind-dependent invariants:
            u64 invariant_count = m_added_invariants.size();
            printer.print_c_str("- Invariants (");
            printer.print_uint_dec(invariant_count);
            printer.print_c_str(")");
            if (!m_added_invariants.empty()) {
                printer.print_newline_indent();

                for (auto it = m_added_invariants.begin(); it != m_added_invariants.end(); it++) {
                    if (it != m_added_invariants.begin()) {
                        printer.print_newline();
                    }
                    printer.print_c_str("- ");
                    (*it)->print(printer);
                }
                printer.print_newline_deindent();
            } else {
                printer.print_newline();
            }
        }

        // note that the caller must call 'deindent'
        // note this block always ends with a trailing newline.
    }

    Type* KindDependentVarSolver::reify(Var *parent_var) {
        return m_reified_soln = reify_impl(parent_var);
    }

    //
    //
    // Private:
    //
    //

    // SimplestKDVS is used to implement opaque types without any order:
    // Unit, String
    class SimplestKDVS: public KindDependentVarSolver {
      public:
        inline SimplestKDVS(VarArchetype var_kind, Kind required_type_kind);

      public:
        SolveResult lazy_try_add_invariant_impl(KindDependentInvariant* invariant) override;
        Type* reify_impl(Var* var) override;

      public:
        void print(printer::Printer& printer) const override;
    };

    inline SimplestKDVS::SimplestKDVS(VarArchetype var_kind, Kind required_type_kind)
    :   KindDependentVarSolver(VarArchetype::Type, required_type_kind)
    {}

    SolveResult SimplestKDVS::lazy_try_add_invariant_impl(KindDependentInvariant* new_invariant) {
        if (required_type_kind() == Kind::Void) {
            if (dynamic_cast<IsVoidInvariant*>(new_invariant) != nullptr) {
                return SolveResult::NoChange;
            } else {
                return SolveResult::TypingError;
            }
        }
        else if (required_type_kind() == Kind::String) {
            if (dynamic_cast<IsStringInvariant*>(new_invariant) != nullptr) {
                return SolveResult::NoChange;
            } else {
                return SolveResult::TypingError;
            }
        }
        else {
            return SolveResult::CompilerError;
        }
    }

    Type* SimplestKDVS::reify_impl(Var* var) {
        switch (required_type_kind()) {
            case Kind::Void:
            {
                return VoidType::get();
            }
            case Kind::String:
            {
                return StringType::get();
            }
            default:
            {
                if (pdm::DEBUG) {
                    assert(0 && "Invalid Kind for SimplestKDVS");
                }
                return nullptr;
            }
        }
    }

    void SimplestKDVS::print(printer::Printer& printer) const {
        help_print_common_and_start_indented_block(printer, "Simplest");
        {}
        printer.print_newline_deindent();
        printer.print_c_str("}");
    }

    // NumberKDVS is used to typecheck sets of numbers:
    // SignedInt, UnsignedInt, and Float are the three disjoint subclasses,
    // as well as accommodating conversions possible between them.
    class NumberKDVS: public KindDependentVarSolver {
      private:
        int m_opt_min_width_in_bits;
        int m_opt_max_width_in_bits;

      public:
        NumberKDVS(VarArchetype var_kind, Kind type_kind);

      protected:
        SolveResult lazy_try_add_invariant_impl(KindDependentInvariant* new_invariant) override;
        Type* reify_impl(Var* var) override;

      public:
        void print(printer::Printer& printer) const override;
    };

    NumberKDVS::NumberKDVS(VarArchetype var_kind, Kind type_kind)
    :   KindDependentVarSolver(var_kind, type_kind),
        m_opt_min_width_in_bits(-1),
        m_opt_max_width_in_bits(-1)
    {}

    SolveResult NumberKDVS::lazy_try_add_invariant_impl(KindDependentInvariant* new_invariant) {
        switch (required_type_kind())
        {
            case Kind::SignedInt:
            case Kind::UnsignedInt:
            {
                auto int_invariant = dynamic_cast<IsIntInvariant*>(new_invariant);
                
                // checking 'uses_sign_extension' is valid:
                bool needs_sign_extension = (required_type_kind() == Kind::SignedInt);
                if (int_invariant->uses_sign_extension() != needs_sign_extension) {
                    return SolveResult::TypingError;
                }

                // solving intersection of min and max width,
                // updating result if applied:
                SolveResult result = SolveResult::NoChange;
                {
                    if (m_opt_min_width_in_bits < 0 || m_opt_min_width_in_bits < int_invariant->min_width_in_bits()) {
                        m_opt_min_width_in_bits = int_invariant->min_width_in_bits();
                        result = SolveResult::UpdatedOrFresh;
                    }
                    if (m_opt_max_width_in_bits < 0 || m_opt_max_width_in_bits > int_invariant->max_width_in_bits()) {
                        m_opt_max_width_in_bits = int_invariant->max_width_in_bits();
                        result = SolveResult::UpdatedOrFresh;
                    }
                }
                
                return result;
            }
            case Kind::Float:
            {
                auto float_invariant = dynamic_cast<IsFloatInvariant*>(new_invariant);

                // solving intersection of min and max width,
                // updating result if applied:
                SolveResult result = SolveResult::NoChange;
                {
                    if (m_opt_min_width_in_bits < 0 || m_opt_min_width_in_bits < float_invariant->min_width_in_bits()) {
                        m_opt_min_width_in_bits = float_invariant->min_width_in_bits();
                        result = result_and(result, SolveResult::UpdatedOrFresh);
                    }
                    if (m_opt_max_width_in_bits < 0 || m_opt_max_width_in_bits > float_invariant->max_width_in_bits()) {
                        m_opt_max_width_in_bits = float_invariant->max_width_in_bits();
                        result = result_and(result, SolveResult::UpdatedOrFresh);
                    }
                }
                
                return result;
            }
            default:
            {
                return SolveResult::CompilerError;
            }
        }
    }

    Type* NumberKDVS::reify_impl(Var* var) {
        // computing the desired width:
        int width_in_bits = -1;
        {
            int default_width_in_bits = 64;
            if (m_opt_min_width_in_bits != -1 && m_opt_max_width_in_bits != -1) {
                if (m_opt_min_width_in_bits <= m_opt_max_width_in_bits) {
                    width_in_bits = m_opt_min_width_in_bits;
                } else {
                    // todo: explain that min and max bounds get crossed
                    if (pdm::DEBUG) {
                        // assert(0 && "NotImplemented: error reporting for min/max bounds crossed in NumberKDVS");
                        std::cout << "NotImplemented: error reporting for min/max bounds crossed in NumberKDVS"
                                  << std::endl;
                    }
                    return nullptr;
                }
            } else if (m_opt_min_width_in_bits != -1) {
                width_in_bits = m_opt_min_width_in_bits;
            } else if (m_opt_max_width_in_bits != -1) {
                width_in_bits = m_opt_max_width_in_bits;
            } else {
                width_in_bits = default_width_in_bits;
            }
        }
        assert(width_in_bits != -1);

        switch (required_type_kind())
        {
            case Kind::SignedInt:
            {
                switch (width_in_bits)
                {
                    case 8: return IntType::get_i8();
                    case 16: return IntType::get_i16();
                    case 32: return IntType::get_i32();
                    case 64: return IntType::get_i64();
                    case 128: return IntType::get_i128();
                    default:
                    {
                        if (pdm::DEBUG) {
                            assert(0 && "Unknown width in bits for SignedInt");
                        }
                        return nullptr;
                    }
                }
            }
            case Kind::UnsignedInt:
            {

                switch (width_in_bits)
                {
                    case 1: return IntType::get_u1();
                    case 8: return IntType::get_u8();
                    case 16: return IntType::get_u16();
                    case 32: return IntType::get_u32();
                    case 64: return IntType::get_u64();
                    case 128: return IntType::get_u128();
                    default:
                    {
                        if (pdm::DEBUG) {
                            assert(0 && "Unknown width in bits for UnsignedInt");
                        }
                        return nullptr;
                    }
                    break;
                }
            }
            case Kind::Float:
            {
                switch (width_in_bits)
                {
                    case 16: return FloatType::get_f16();
                    case 32: return FloatType::get_f32();
                    case 64: return FloatType::get_f64();
                    default:
                    {
                        if (pdm::DEBUG) {
                            assert(0 && "Unknown width in bits for Float");
                        }
                        return nullptr;
                    }
                }
                break;
            }
            default:
            {
                if (pdm::DEBUG) {
                    assert(0 && "Invalid type Kind in NumberKDVS::reify_impl");
                }
                return nullptr;
            }
        }
    }

    void NumberKDVS::print(printer::Printer &printer) const {
        help_print_common_and_start_indented_block(printer, "Number");
        {
            printer.print_c_str("- Min-WidthInBits: ");
            if (m_opt_min_width_in_bits >= 0) {
                printer.print_uint_dec(m_opt_min_width_in_bits);
            } else {
                printer.print_c_str("Any");
            }

            printer.print_newline();
            printer.print_c_str("- Max-WidthInBits: ");
            if (m_opt_max_width_in_bits >= 0) {
                printer.print_uint_dec(m_opt_max_width_in_bits);
            } else {
                printer.print_c_str("Any");
            }
        }
        printer.print_newline_deindent();
        printer.print_c_str("}");
    }

    // TupleKDVS is used to typecheck tuples.
    // Tuple
    class TupleKDVS: public KindDependentVarSolver {
      private:
        std::vector<TypeVar*> m_typeof_items_tvs;
        bool m_newborn;

      public:
        explicit TupleKDVS(VarArchetype var_kind);

      protected:
        SolveResult lazy_try_add_invariant_impl(KindDependentInvariant* new_invariant) override;
        Type* reify_impl(Var* var) override;

      public:
        void print(printer::Printer& printer) const override;
    };

    TupleKDVS::TupleKDVS(VarArchetype var_kind)
    :   KindDependentVarSolver(var_kind, Kind::Tuple),
        m_typeof_items_tvs(),
        m_newborn(true)
    {}

    SolveResult TupleKDVS::lazy_try_add_invariant_impl(KindDependentInvariant* new_invariant) {
        auto tuple_invariant = dynamic_cast<IsTupleInvariant*>(new_invariant);
        if (tuple_invariant == nullptr) {
            return SolveResult::TypingError;
        }

        // if 'newborn', i.e. no invariants processed yet, then no existing properties to compare.
        if (m_newborn) {
            m_newborn = true;
            m_typeof_items_tvs = tuple_invariant->typeof_items_tvs();
            return SolveResult::UpdatedOrFresh;
        }
        
        if (m_typeof_items_tvs.size() != tuple_invariant->typeof_items_tvs().size()) {
            return SolveResult::TypingError;
        }

        // equating fields:
        {
            SolveResult result = SolveResult::NoChange;

            assert(m_typeof_items_tvs.size() == tuple_invariant->typeof_items_tvs().size());
            for (size_t index = 0; index < m_typeof_items_tvs.size(); index++) {
                Var* old_field_var = m_typeof_items_tvs[index];
                Var* new_field_var = tuple_invariant->typeof_items_tvs()[index];

                SolveResult ao_res = old_field_var->equals_by_induction(new_field_var);
                result = result_and(result, ao_res);
            }

            return result;
        }
    }

    Type* TupleKDVS::reify_impl(Var* var) {
        assert(0 && "NotImplemented: TupleKDVS::reify_impl");
    }

    void TupleKDVS::print(printer::Printer& printer) const {
        help_print_common_and_start_indented_block(printer, "TupleKDVS");
        {
            printer.print_c_str("- Items (");
            printer.print_uint_dec(m_typeof_items_tvs.size());
            printer.print_c_str("):");
            printer.print_newline();
            {
                size_t count = m_typeof_items_tvs.size();
                for (size_t i = 0; i < count; i++) {
                    printer.print_c_str("- Field ");
                    printer.print_uint_dec(i);
                    printer.print_c_str(": ");
                    m_typeof_items_tvs[i]->print_title(printer);

                    if (i+1 != count) {
                        printer.print_newline();
                    }
                }
            }
        }
        printer.print_newline_deindent();
        printer.print_c_str("}");
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
        FieldCollectionKDVS(VarArchetype var_kind, Kind type_kind);

      protected:
        SolveResult lazy_try_add_invariant_impl(KindDependentInvariant* new_invariant) override;
        Type* reify_impl(Var* var) override;

      public:
        void print(printer::Printer& printer) const override;
    };

    FieldCollectionKDVS::FieldCollectionKDVS(VarArchetype var_kind, Kind type_kind)
    :   KindDependentVarSolver(var_kind, type_kind)
    {}

    SolveResult FieldCollectionKDVS::lazy_try_add_invariant_impl(KindDependentInvariant* new_invariant) {
        // ensuring IsFieldCollectionInvariant:
        auto new_field_collection_invariant = dynamic_cast<IsFieldCollectionInvariant*>(new_invariant);
        if (new_field_collection_invariant == nullptr) {
            return SolveResult::TypingError;
        }

        // checking type_kind against Invariant kind:
        switch (required_type_kind())
        {
            case Kind::Struct:
            {
                auto new_struct_invariant = dynamic_cast<IsStructInvariant*>(new_invariant);
                if (new_struct_invariant == nullptr) {
                    return SolveResult::TypingError;
                }
                break;
            }
            case Kind::Enum:
            {
                auto new_enum_invariant = dynamic_cast<IsEnumInvariant*>(new_invariant);
                if (new_enum_invariant == nullptr) {
                    return SolveResult::TypingError;
                }
                break;
            }
            case Kind::Module:
            {
                auto new_module_invariant = dynamic_cast<IsModuleInvariant*>(new_invariant);
                if (new_module_invariant == nullptr) {
                    return SolveResult::TypingError;
                }
                break;
            }
            default:
            {
                // unexpected type kind.
                return SolveResult::CompilerError;
            }
        }

        // updating fields:
        SolveResult result = SolveResult::NoChange;
        for (auto pair: new_field_collection_invariant->fields()) {
            intern::String field_name = pair.first;
            Var* struct_invariant_field_var = pair.second;
            
            auto kdvs_field_iterator = m_fields.find(field_name);
            if (kdvs_field_iterator != m_fields.end()) {
                // equals existing field
                Var* kdvs_field_var = kdvs_field_iterator->second;
                result = result_and(
                    result,
                    kdvs_field_var->equals_by_induction(struct_invariant_field_var)
                );   
            } else {
                // insert invariant field var:
                auto field_insert_res = m_fields.insert({field_name, struct_invariant_field_var});
                assert(field_insert_res.second);
                result = result_and(result, SolveResult::UpdatedOrFresh);
            }
        }
        return result;
    }

    Type* FieldCollectionKDVS::reify_impl(Var* var) {
        assert(0 && "NotImplemented: FieldCollectionKDVS::reify_impl");
        return nullptr;
    }

    void FieldCollectionKDVS::print(printer::Printer& printer) const {
        help_print_common_and_start_indented_block(printer, "FieldCollection");
        {
            printer.print_newline();
            printer.print_c_str("- Fields (");
            printer.print_uint_dec(m_fields.size());
            printer.print_c_str(")");
            // each field prints its own prefix newline, incl. one extra for here.
            if (!m_fields.empty()) {
                for (auto it: m_fields) {
                    printer.print_newline();
                    printer.print_c_str("- Field '");
                    printer.print_intstr(it.first);
                    printer.print_c_str("': ");
                    it.second->print_title(printer);
                }
            }
        }
        printer.print_newline_deindent();
        printer.print_c_str("}");
    }

    // FnKDVS is used to typecheck TypeVars that contain functions.
    class FnKDVS: public KindDependentVarSolver {
      private:
        std::vector<VCallArg> m_args;
        TypeVar* m_typeof_ret_tv;
        IsVCallableInvariant* m_primary_formal_invariant;
        std::vector<IsVCallableInvariant*> m_found_formal_invariants;
        size_t m_fulfilled_formal_invariant_count;
        std::vector<IsVCallableInvariant*> m_deferred_actual_invariants;
        size_t m_fulfilled_actual_invariant_count;

      public:
        explicit FnKDVS(VarArchetype var_kind);

      protected:
        SolveResult lazy_try_add_invariant_impl(KindDependentInvariant* new_invariant) override;
        SolveResult help_eat_invariant(IsVCallableInvariant* new_fn_invariant);

        Type* reify_impl(Var* var) override;

      public:
        void print(printer::Printer& printer) const override;
    };

    FnKDVS::FnKDVS(VarArchetype var_kind)
    :   KindDependentVarSolver(var_kind, Kind::Fn) ,
        m_args(),
        m_typeof_ret_tv(nullptr),
        m_primary_formal_invariant(nullptr),
        m_fulfilled_formal_invariant_count(0),
        m_fulfilled_actual_invariant_count(0)
    {}
    SolveResult FnKDVS::lazy_try_add_invariant_impl(KindDependentInvariant* new_invariant) {
        SolveResult result = SolveResult::NoChange;

        auto new_fn_invariant = dynamic_cast<IsVCallableInvariant*>(new_invariant);
        if (new_fn_invariant == nullptr) {
            return SolveResult::TypingError;
        }

        // We cannot handle any 'actual'-strength invariants before a 'formal'-strength invariant.
        // We store all invariants in sorted arrays and then complete remaining elements once ready.

        // sorting invariants by strength:
        {
            switch (new_fn_invariant->strength()) {
                case VCallInvariantStrength::Formal:
                {
                    result = result_and(SolveResult::UpdatedOrFresh, result);
                    m_found_formal_invariants.push_back(new_fn_invariant);
                    break;
                }
                case VCallInvariantStrength::Actual:
                {
                    result = result_and(SolveResult::UpdatedOrFresh, result);
                    m_deferred_actual_invariants.push_back(new_fn_invariant);
                    break;
                }
            }
        }

        // if we found any formal invariants, we must use the first as the primary formal invariant:
        if (m_primary_formal_invariant == nullptr) {
            if (!m_found_formal_invariants.empty()) {
                m_primary_formal_invariant = m_found_formal_invariants[0];
                m_args = m_primary_formal_invariant->formal_args();
                m_typeof_ret_tv = m_primary_formal_invariant->typeof_ret_tv();
                result = result_and(result, SolveResult::UpdatedOrFresh);
            }
        }

        // if we have a [potentially brand new] primary formal invariant, we can check other formal and actual
        // invariants now that properties are initialized.
        if (m_primary_formal_invariant) {
            // eating formal-strength invariants:
            assert(!m_found_formal_invariants.empty());
            {
                size_t beg_ix = 1 + m_fulfilled_formal_invariant_count;
                size_t last_ix = m_found_formal_invariants.size() - 1;
                for (size_t i = beg_ix; i <= last_ix; i++) {
                    IsVCallableInvariant *fn_invariant = m_found_formal_invariants[i];
                    assert(fn_invariant->strength() == VCallInvariantStrength::Formal);
                    help_eat_invariant(fn_invariant);
                }
            }

            // eating actual-strength invariants:
            if (!m_deferred_actual_invariants.empty()) {
                size_t beg_ix = m_fulfilled_actual_invariant_count;
                size_t end_ix = m_deferred_actual_invariants.size();
                for (size_t i = beg_ix; i < end_ix; i++) {
                    IsVCallableInvariant* fn_invariant = m_deferred_actual_invariants[i];
                    assert(fn_invariant->strength() == VCallInvariantStrength::Actual);
                    help_eat_invariant(fn_invariant);
                }
            }
        }

        return result;
    }
    SolveResult FnKDVS::help_eat_invariant(IsVCallableInvariant* new_fn_invariant) {
        SolveResult res = SolveResult::NoChange;

        // checking same arg count
        if (m_args.size() != new_fn_invariant->formal_args().size()) {
            return SolveResult::TypingError;
        }

        // relating each arg:
        size_t args_count = m_args.size();
        for (size_t index = 0; index < args_count; index++) {
            VCallArg const& fn_invariant_fn_arg = new_fn_invariant->formal_args()[index];
            VCallArg const& fn_kdvs_arg = m_args[index];

            // checking same arg access spec:
            if (fn_invariant_fn_arg.varg_access_spec != fn_kdvs_arg.varg_access_spec) {
                return SolveResult::TypingError;
            } else {
                if (new_fn_invariant->strength() == VCallInvariantStrength::Formal) {
                    res = result_and(
                        res,
                        fn_invariant_fn_arg.typeof_arg_tv->equals_by_induction(fn_kdvs_arg.typeof_arg_tv)
                    );
                } else if (new_fn_invariant->strength() == VCallInvariantStrength::Actual) {
                    res = result_and(
                        res,
                        fn_invariant_fn_arg.typeof_arg_tv->sub_var_by_induction(fn_kdvs_arg.typeof_arg_tv)
                    );
                } else {
                    return SolveResult::CompilerError;
                }
            }
        }

        // relating the return type:
        TypeVar* fn_invariant_typeof_ret_tv = new_fn_invariant->typeof_ret_tv();
        TypeVar* fn_kdvs_typeof_ret_tv = m_typeof_ret_tv;
        if (new_fn_invariant->strength() == VCallInvariantStrength::Formal) {
            res = result_and(
                res,
                fn_invariant_typeof_ret_tv->equals_by_induction(fn_kdvs_typeof_ret_tv)
            );
        } else if (new_fn_invariant->strength() == VCallInvariantStrength::Actual) {
            res = result_and(
                res,
                fn_invariant_typeof_ret_tv->sub_var_by_induction(fn_kdvs_typeof_ret_tv)
            );
        } else {
            return SolveResult::CompilerError;
        }

        return res;
    }

    Type* FnKDVS::reify_impl(Var* var) {
        std::vector<FuncTypeFormalArg> formal_args;
        {
            size_t args_count = m_args.size();
            formal_args.reserve(args_count);

            for (size_t i = 0; i < args_count; i++) {
                VCallArg const& arg = m_args[i];
                assert(arg.name.has_value());
                intern::String arg_name = arg.name.value();
                TypeVar* arg_tv = arg.typeof_arg_tv;
                ast::VArgAccessSpec access_spec = arg.varg_access_spec;

                Type* arg_type_soln = arg_tv->get_type_soln();
                if (arg_type_soln == nullptr) {
                    // arg type reification failed
                    return nullptr;
                }
                formal_args.emplace_back(access_spec, arg_name, arg_type_soln);
            }
        }
        Type* ret_type_soln = nullptr;
        if (m_typeof_ret_tv) {
            ret_type_soln = m_typeof_ret_tv->get_type_soln();
        }
        if (ret_type_soln == nullptr) {
            // return type reification failed.
            return nullptr;
        }

        std::string name = var->name();
        return new FnType(
            std::move(name),
            std::move(formal_args),
            ret_type_soln
        );
    }

    void FnKDVS::print(printer::Printer& printer) const {
        help_print_common_and_start_indented_block(printer, "Fn");
        {
            // printer.print_newline();
            printer.print_c_str("- Args (");
            printer.print_uint_dec(m_args.size());
            printer.print_c_str(")");
            if (!m_args.empty()) {
                printer.print_newline_indent();
                for (size_t arg_index = 0; arg_index < m_args.size(); arg_index++) {
                    VCallArg const& arg = m_args[arg_index];

                    // printing a list item prefix:
                    printer.print_c_str("- ");

                    // printing the access spec:
                    switch (arg.varg_access_spec)
                    {
                        case ast::VArgAccessSpec::In:
                        {
                            // do nothing.
                            break;
                        }
                        case ast::VArgAccessSpec::Out:
                        {
                            printer.print_c_str("out ");
                            break;
                        }
                        case ast::VArgAccessSpec::InOut:
                        {
                            printer.print_c_str("inout ");
                            break;
                        }
                    }

                    // printing arg name:
                    if (arg.name.has_value()) {
                        printer.print_intstr(arg.name.value());
                    } else {
                        printer.print_c_str("*");
                    }

                    // printing arg type var:
                    printer.print_c_str(": ");
                    arg.typeof_arg_tv->print_title(printer);

                    if (arg_index+1 != m_args.size()) {
                        printer.print_newline();
                    }
                }
                printer.print_newline_deindent();
            } else {
                printer.print_newline();
            }

            printer.print_c_str("- Returns: ");
            if (m_typeof_ret_tv) {
                m_typeof_ret_tv->print_title(printer);
            } else {
                printer.print_c_str("<Unknown>");
            }
        }
        printer.print_newline_deindent();
        printer.print_c_str("}");
    }


    // Array:
    class ArrayKDVS: public KindDependentVarSolver {
      private:
        TypeVar* m_opt_typeof_element_tv;

      public:
        explicit inline ArrayKDVS(VarArchetype var_kind);

      public:
        inline TypeVar* opt_typeof_element_tv() const;
        inline void opt_typeof_element_tv(TypeVar* tv);
        
      protected:
        SolveResult lazy_try_add_invariant_impl(KindDependentInvariant* new_invariant) override;
        Type* reify_impl(Var* var) override;

      public:
        void print(printer::Printer& printer) const override;
    };
    
    inline ArrayKDVS::ArrayKDVS(VarArchetype var_kind)
    :   KindDependentVarSolver(var_kind, Kind::Array),
        m_opt_typeof_element_tv(nullptr)
    {}
    inline TypeVar* ArrayKDVS::opt_typeof_element_tv() const {
        return m_opt_typeof_element_tv;
    }
    inline void ArrayKDVS::opt_typeof_element_tv(TypeVar* tv) {
        m_opt_typeof_element_tv = tv;
    }

    SolveResult ArrayKDVS::lazy_try_add_invariant_impl(KindDependentInvariant* new_invariant) {
        auto new_array_invariant = dynamic_cast<IsArrayInvariant*>(new_invariant);
        if (new_array_invariant == nullptr) {
            return SolveResult::TypingError;
        }

        TypeVar* typeof_array_invariant_item_tv = new_array_invariant->item_tv();
        if (m_opt_typeof_element_tv == nullptr) {
            m_opt_typeof_element_tv = typeof_array_invariant_item_tv;
            return SolveResult::UpdatedOrFresh;
        } else {
            return m_opt_typeof_element_tv->equals_by_induction(typeof_array_invariant_item_tv);
        }
    }

    Type* ArrayKDVS::reify_impl(Var* var) {
        assert(0 && "NotImplemented: ArrayKDVS::reify_impl");
        return nullptr;
    }

    void ArrayKDVS::print(printer::Printer& printer) const {
        help_print_common_and_start_indented_block(printer, "Array");
        {
            printer.print_c_str("- ItemType: ");
            m_opt_typeof_element_tv->print_title(printer);
        }
        printer.print_newline_deindent();
        printer.print_c_str("}");
    }

}

//
// Interface:
//

namespace pdm::types {

    SolveResult KindDependentVarSolver::try_add_invariant(KindDependentInvariant* invariant) {
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
            return SolveResult::NoChange;
        }
    }

    NewKDVS try_new_kdvs_for(VarArchetype var_kind, Kind type_kind) {
        NewKDVS rv{};
        if (type_kind == Kind::META_Unknown) {
            rv.result = KcResult::InsufficientInfo;
            rv.kdvs = nullptr;
        } 
        else if (is_type_var_archetype(var_kind)) {
            rv.result = KcResult::Ok;
            switch (type_kind)
            {
                case Kind::Void:
                case Kind::String:
                {
                    rv.kdvs = new SimplestKDVS(var_kind, type_kind);
                    break;
                }
                case Kind::SignedInt:
                {
                    rv.kdvs = new NumberKDVS(var_kind, Kind::SignedInt);
                    break;
                }
                case Kind::UnsignedInt:
                {
                    rv.kdvs = new NumberKDVS(var_kind, Kind::UnsignedInt);
                    break;
                }
                case Kind::Float:
                {
                    rv.kdvs = new NumberKDVS(var_kind, Kind::Float);
                    break;
                }
                case Kind::Tuple:
                {
                    rv.kdvs = new TupleKDVS(var_kind);
                    break;
                }
                case Kind::Struct:
                {
                    rv.kdvs = new FieldCollectionKDVS(var_kind, Kind::Struct);
                    break;
                }
                case Kind::Enum:
                {
                    rv.kdvs = new FieldCollectionKDVS(var_kind, Kind::Enum);
                    break;
                }
                case Kind::Module:
                {
                    rv.kdvs = new FieldCollectionKDVS(var_kind, Kind::Module);
                    break;
                }
                case Kind::Fn:
                {
                    rv.kdvs = new FnKDVS(var_kind);
                    break;
                }
                case Kind::Array:
                {
                    rv.kdvs = new ArrayKDVS(var_kind);
                    break;
                }
                default:
                {
                    assert(0 && "Unknown 'Kind' in 'try_new_kdvs_for'");
                }
            }
        }
        else {
            rv.result = KcResult::Error_MixedKind;
            rv.kdvs = nullptr;
        }

        return rv;
    }
}