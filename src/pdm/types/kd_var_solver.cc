#include "kd_var_solver.hh"

#include <vector>
#include <string>
#include <map>
#include <cassert>

#include "pdm/core/bitsets.hh"
#include "pdm/core/intern.hh"
#include "pdm/core/integer.hh"
#include "pdm/ast/arg/varg.hh"

#include "var.hh"
#include "invariant.hh"
#include "type_kind.hh"


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
        printer.print_cstr(" (tk: ");
        printer.print_cstr(type_kind_as_str(m_required_type_kind));
        printer.print_cstr(", vk: ");
        printer.print_cstr(var_kind_as_str(m_var_kind));
        printer.print_cstr(") {");

        // indent + body:
        printer.print_newline_indent();
        {
            // printing all added kind-dependent invariants:
            u64 invariant_count = m_added_invariants.size();
            printer.print_cstr("- Invariants (");
            printer.print_uint_dec(invariant_count);
            printer.print_cstr(")");
            if (!m_added_invariants.empty()) {
                printer.print_newline_indent();

                for (auto it = m_added_invariants.begin(); it != m_added_invariants.end(); it++) {
                    if (it != m_added_invariants.begin()) {
                        printer.print_newline();
                    }
                    printer.print_cstr("- ");
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

    //
    //
    // Private:
    //
    //

    // SimplestKDVS is used to implement opaque types without any order:
    // Unit, String
    class SimplestKDVS: public KindDependentVarSolver {
      public:
        inline SimplestKDVS(VarKind var_kind, TypeKind required_type_kind);

      public:
        KdResult lazy_try_add_invariant_impl(KindDependentInvariant* invariant) override;

      public:
        void print(printer::Printer& printer) const override;
    };

    inline SimplestKDVS::SimplestKDVS(VarKind var_kind, TypeKind required_type_kind)
    :   KindDependentVarSolver(VarKind::Type, required_type_kind)
    {}

    KdResult SimplestKDVS::lazy_try_add_invariant_impl(KindDependentInvariant* new_invariant) {
        if (required_type_kind() == TypeKind::Void) {
            if (dynamic_cast<IsVoidInvariant*>(new_invariant) != nullptr) {
                return KdResult::NoChange;
            } else {
                return KdResult::TypingError;
            }
        }
        else if (required_type_kind() == TypeKind::String) {
            if (dynamic_cast<IsStringInvariant*>(new_invariant) != nullptr) {
                return KdResult::NoChange;
            } else {
                return KdResult::TypingError;
            }
        }
        else {
            return KdResult::CompilerError;
        }
    }

    void SimplestKDVS::print(printer::Printer& printer) const {
        help_print_common_and_start_indented_block(printer, "Simplest");
        {}
        printer.print_newline_deindent();
        printer.print_cstr("}");
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
        KdResult lazy_try_add_invariant_impl(KindDependentInvariant* new_invariant) override;

      public:
        void print(printer::Printer& printer) const override;
    };

    NumberKDVS::NumberKDVS(VarKind var_kind, TypeKind type_kind)
    :   KindDependentVarSolver(var_kind, type_kind),
        m_opt_min_width_in_bits(-1),
        m_opt_max_width_in_bits(-1)
    {}

    KdResult NumberKDVS::lazy_try_add_invariant_impl(KindDependentInvariant* new_invariant) {
        switch (required_type_kind())
        {
            case TypeKind::SignedInt:
            case TypeKind::UnsignedInt:
            {
                auto int_invariant = dynamic_cast<IsIntInvariant*>(new_invariant);
                
                // checking 'uses_sign_extension' is valid:
                bool needs_sign_extension = (required_type_kind() == TypeKind::SignedInt);
                if (int_invariant->uses_sign_extension() != needs_sign_extension) {
                    return KdResult::TypingError;
                }

                // solving intersection of min and max width,
                // updating result if applied:
                KdResult result = KdResult::NoChange;
                {
                    if (m_opt_min_width_in_bits < 0 || m_opt_min_width_in_bits < int_invariant->min_width_in_bits()) {
                        m_opt_min_width_in_bits = int_invariant->min_width_in_bits();
                        result = KdResult::UpdatedOrFresh;
                    }
                    if (m_opt_max_width_in_bits < 0 || m_opt_max_width_in_bits > int_invariant->max_width_in_bits()) {
                        m_opt_max_width_in_bits = int_invariant->max_width_in_bits();
                        result = KdResult::UpdatedOrFresh;
                    }
                }
                
                return result;
            }
            case TypeKind::Float:
            {
                auto float_invariant = dynamic_cast<IsFloatInvariant*>(new_invariant);

                // solving intersection of min and max width,
                // updating result if applied:
                KdResult result = KdResult::NoChange;
                {
                    if (m_opt_min_width_in_bits < 0 || m_opt_min_width_in_bits < float_invariant->min_width_in_bits()) {
                        m_opt_min_width_in_bits = float_invariant->min_width_in_bits();
                        result = kdr_and(result, KdResult::UpdatedOrFresh);
                    }
                    if (m_opt_max_width_in_bits < 0 || m_opt_max_width_in_bits > float_invariant->max_width_in_bits()) {
                        m_opt_max_width_in_bits = float_invariant->max_width_in_bits();
                        result = kdr_and(result, KdResult::UpdatedOrFresh);
                    }
                }
                
                return result;
            }
            default:
            {
                return KdResult::CompilerError;
            }
        }
    }

    void NumberKDVS::print(printer::Printer &printer) const {
        help_print_common_and_start_indented_block(printer, "Number");
        {
            printer.print_cstr("- Min-WidthInBits: ");
            if (m_opt_min_width_in_bits >= 0) {
                printer.print_uint_dec(m_opt_min_width_in_bits);
            } else {
                printer.print_cstr("Any");
            }

            printer.print_newline();
            printer.print_cstr("- Max-WidthInBits: ");
            if (m_opt_max_width_in_bits >= 0) {
                printer.print_uint_dec(m_opt_max_width_in_bits);
            } else {
                printer.print_cstr("Any");
            }
        }
        printer.print_newline_deindent();
        printer.print_cstr("}");
    }

    // TupleKDVS is used to typecheck tuples.
    // Tuple
    class TupleKDVS: public KindDependentVarSolver {
      private:
        std::vector<TypeVar*> m_typeof_items_tvs;
        bool m_newborn;

      public:
        explicit TupleKDVS(VarKind var_kind);

      public:
        KdResult lazy_try_add_invariant_impl(KindDependentInvariant* new_invariant) override;

      public:
        void print(printer::Printer& printer) const override;
    };

    TupleKDVS::TupleKDVS(VarKind var_kind)
    :   KindDependentVarSolver(var_kind, TypeKind::Tuple),
        m_typeof_items_tvs(),
        m_newborn(true)
    {}

    KdResult TupleKDVS::lazy_try_add_invariant_impl(KindDependentInvariant* new_invariant) {
        auto tuple_invariant = dynamic_cast<IsTupleInvariant*>(new_invariant);
        if (tuple_invariant == nullptr) {
            return KdResult::TypingError;
        }

        // if 'newborn', i.e. no invariants processed yet, then no existing properties to compare.
        if (m_newborn) {
            m_newborn = true;
            m_typeof_items_tvs = tuple_invariant->typeof_items_tvs();
            return KdResult::UpdatedOrFresh;
        }
        
        if (m_typeof_items_tvs.size() != tuple_invariant->typeof_items_tvs().size()) {
            return KdResult::TypingError;
        }

        // equating fields:
        {
            KdResult result = KdResult::NoChange;

            assert(m_typeof_items_tvs.size() == tuple_invariant->typeof_items_tvs().size());
            for (size_t index = 0; index < m_typeof_items_tvs.size(); index++) {
                Var* old_field_var = m_typeof_items_tvs[index];
                Var* new_field_var = tuple_invariant->typeof_items_tvs()[index];

                KdResult ao_res = old_field_var->higher_order_assume_equals(new_field_var);
                result = kdr_and(result, ao_res);
            }

            return result;
        }
    }

    void TupleKDVS::print(printer::Printer& printer) const {
        help_print_common_and_start_indented_block(printer, "TupleKDVS");
        {
            printer.print_cstr("- Items (");
            printer.print_uint_dec(m_typeof_items_tvs.size());
            printer.print_cstr("):");
            printer.print_newline();
            {
                size_t count = m_typeof_items_tvs.size();
                for (size_t i = 0; i < count; i++) {
                    printer.print_cstr("- Field ");
                    printer.print_uint_dec(i);
                    printer.print_cstr(": ");
                    m_typeof_items_tvs[i]->print_title(printer);

                    if (i+1 != count) {
                        printer.print_newline();
                    }
                }
            }
        }
        printer.print_newline_deindent();
        printer.print_cstr("}");
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
        KdResult lazy_try_add_invariant_impl(KindDependentInvariant* new_invariant) override;

      public:
        void print(printer::Printer& printer) const override;
    };

    FieldCollectionKDVS::FieldCollectionKDVS(VarKind var_kind, TypeKind type_kind)
    :   KindDependentVarSolver(var_kind, type_kind)
    {}

    KdResult FieldCollectionKDVS::lazy_try_add_invariant_impl(KindDependentInvariant* new_invariant) {
        // ensuring IsFieldCollectionInvariant:
        auto new_field_collection_invariant = dynamic_cast<IsFieldCollectionInvariant*>(new_invariant);
        if (new_field_collection_invariant == nullptr) {
            return KdResult::TypingError;
        }

        // checking type_kind against Invariant kind:
        switch (required_type_kind())
        {
            case TypeKind::Struct:
            {
                auto new_struct_invariant = dynamic_cast<IsStructInvariant*>(new_invariant);
                if (new_struct_invariant == nullptr) {
                    return KdResult::TypingError;
                }
                break;
            }
            case TypeKind::Enum:
            {
                auto new_enum_invariant = dynamic_cast<IsEnumInvariant*>(new_invariant);
                if (new_enum_invariant == nullptr) {
                    return KdResult::TypingError;
                }
                break;
            }
            case TypeKind::Module:
            {
                auto new_module_invariant = dynamic_cast<IsModuleInvariant*>(new_invariant);
                if (new_module_invariant == nullptr) {
                    return KdResult::TypingError;
                }
                break;
            }
            default:
            {
                // unexpected type kind.
                return KdResult::CompilerError;
            }
        }

        // updating fields:
        KdResult result = KdResult::NoChange;
        for (auto pair: new_field_collection_invariant->fields()) {
            intern::String field_name = pair.first;
            Var* struct_invariant_field_var = pair.second;
            
            auto kdvs_field_iterator = m_fields.find(field_name);
            if (kdvs_field_iterator != m_fields.end()) {
                // equals existing field
                Var* kdvs_field_var = kdvs_field_iterator->second;
                result = kdr_and(
                        result,
                        kdvs_field_var->higher_order_assume_equals(struct_invariant_field_var)
                );   
            } else {
                // insert invariant field var:
                auto field_insert_res = m_fields.insert({field_name, struct_invariant_field_var});
                assert(field_insert_res.second);
                result = kdr_and(result, KdResult::UpdatedOrFresh);
            }
        }
        return result;
    }

    void FieldCollectionKDVS::print(printer::Printer& printer) const {
        help_print_common_and_start_indented_block(printer, "FieldCollection");
        {
            printer.print_newline();
            printer.print_cstr("- Fields (");
            printer.print_uint_dec(m_fields.size());
            printer.print_cstr(")");
            // each field prints its own prefix newline, incl. one extra for here.
            if (!m_fields.empty()) {
                for (auto it: m_fields) {
                    printer.print_newline();
                    printer.print_cstr("- Field '");
                    printer.print_intstr(it.first);
                    printer.print_cstr("': ");
                    it.second->print_title(printer);
                }
            }
        }
        printer.print_newline_deindent();
        printer.print_cstr("}");
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
        explicit FnKDVS(VarKind var_kind);

      public:
        KdResult lazy_try_add_invariant_impl(KindDependentInvariant* new_invariant) override;
      private:
        KdResult help_eat_invariant(IsVCallableInvariant* new_fn_invariant);

      public:
        void print(printer::Printer& printer) const override;
    };

    FnKDVS::FnKDVS(VarKind var_kind) 
    :   KindDependentVarSolver(var_kind, TypeKind::Fn) ,
        m_args(),
        m_typeof_ret_tv(nullptr),
        m_primary_formal_invariant(nullptr),
        m_fulfilled_formal_invariant_count(0),
        m_fulfilled_actual_invariant_count(0)
    {}
    KdResult FnKDVS::lazy_try_add_invariant_impl(KindDependentInvariant* new_invariant) {
        KdResult result = KdResult::NoChange;

        auto new_fn_invariant = dynamic_cast<IsVCallableInvariant*>(new_invariant);
        if (new_fn_invariant == nullptr) {
            return KdResult::TypingError;
        }

        // We cannot handle any 'actual'-strength invariants before a 'formal'-strength invariant.
        // We store all invariants in sorted arrays and then complete remaining elements once ready.

        // sorting invariants by strength:
        {
            switch (new_fn_invariant->strength()) {
                case VCallInvariantStrength::Formal:
                {
                    result = kdr_and(KdResult::UpdatedOrFresh, result);
                    m_found_formal_invariants.push_back(new_fn_invariant);
                    break;
                }
                case VCallInvariantStrength::Actual:
                {
                    result = kdr_and(KdResult::UpdatedOrFresh, result);
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
                result = kdr_and(result, KdResult::UpdatedOrFresh);
            }
        }

        // if we have a [potentially brand new] primary formal invariant, we can check other formal and actual
        // invariants now that properties are initialized.
        if (m_primary_formal_invariant) {
            // eating formal-strength invariants:
            assert(!m_found_formal_invariants.empty());
            {
                size_t beg_ix = 1 + m_fulfilled_formal_invariant_count;
                size_t end_ix = m_found_formal_invariants.size() - 1;
                for (size_t i = beg_ix; i <= end_ix; i++) {
                    IsVCallableInvariant *fn_invariant = m_found_formal_invariants[i];
                    help_eat_invariant(fn_invariant);
                }
            }

            // eating actual-strength invariants:
            if (!m_deferred_actual_invariants.empty()) {
                size_t beg_ix = m_fulfilled_actual_invariant_count;
                size_t end_ix = m_deferred_actual_invariants.size() - 1;
                for (size_t i = beg_ix; i <= end_ix; i++) {
                    IsVCallableInvariant* fn_invariant = m_found_formal_invariants[i];
                    help_eat_invariant(fn_invariant);
                }
            }
        }

        return result;
    }

    KdResult FnKDVS::help_eat_invariant(IsVCallableInvariant* new_fn_invariant) {
        KdResult res = KdResult::NoChange;

        // checking same arg count
        if (m_args.size() != new_fn_invariant->formal_args().size()) {
            return KdResult::TypingError;
        }

        // relating each arg:
        size_t args_count = m_args.size();
        for (size_t index = 0; index < args_count; index++) {
            VCallArg const& fn_invariant_fn_arg = new_fn_invariant->formal_args()[index];
            VCallArg const& fn_kdvs_arg = m_args[index];

            // checking same arg access spec:
            if (fn_invariant_fn_arg.varg_access_spec != fn_kdvs_arg.varg_access_spec) {
                return KdResult::TypingError;
            } else {
                if (new_fn_invariant->strength() == VCallInvariantStrength::Formal) {
                    res = kdr_and(res,
                        fn_invariant_fn_arg.typeof_arg_tv->higher_order_assume_equals(fn_kdvs_arg.typeof_arg_tv)
                    );
                } else if (new_fn_invariant->strength() == VCallInvariantStrength::Actual) {
                    res = kdr_and(res,
                        fn_invariant_fn_arg.typeof_arg_tv->higher_order_assume_subvar(fn_kdvs_arg.typeof_arg_tv)
                    );
                } else {
                    return KdResult::CompilerError;
                }
            }
        }

        // relating the return type:
        TypeVar* fn_invariant_typeof_ret_tv = new_fn_invariant->typeof_ret_tv();
        TypeVar* fn_kdvs_typeof_ret_tv = m_typeof_ret_tv;
        if (new_fn_invariant->strength() == VCallInvariantStrength::Formal) {
            res = kdr_and(res,
                fn_invariant_typeof_ret_tv->higher_order_assume_equals(fn_kdvs_typeof_ret_tv)
            );
        } else if (new_fn_invariant->strength() == VCallInvariantStrength::Actual) {
            res = kdr_and(res,
                fn_invariant_typeof_ret_tv->higher_order_assume_subvar(fn_kdvs_typeof_ret_tv)
            );
        } else {
            return KdResult::CompilerError;
        }

        return res;
    }

    void FnKDVS::print(printer::Printer& printer) const {
        help_print_common_and_start_indented_block(printer, "Fn");
        {
            // printer.print_newline();
            printer.print_cstr("- Args (");
            printer.print_uint_dec(m_args.size());
            printer.print_cstr(")");
            if (!m_args.empty()) {
                printer.print_newline_indent();
                for (size_t arg_index = 0; arg_index < m_args.size(); arg_index++) {
                    VCallArg const& arg = m_args[arg_index];

                    // printing a list item prefix:
                    printer.print_cstr("- ");

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
                            printer.print_cstr("out ");
                            break;
                        }
                        case ast::VArgAccessSpec::InOut:
                        {
                            printer.print_cstr("inout ");
                            break;
                        }
                    }

                    // printing arg name:
                    if (arg.name.has_value()) {
                        printer.print_intstr(arg.name.value());
                    } else {
                        printer.print_cstr("*");
                    }

                    // printing arg type var:
                    printer.print_cstr(": ");
                    arg.typeof_arg_tv->print_title(printer);

                    if (arg_index+1 != m_args.size()) {
                        printer.print_newline();
                    }
                }
                printer.print_newline_deindent();
            } else {
                printer.print_newline();
            }

            printer.print_cstr("- Returns: ");
            if (m_typeof_ret_tv) {
                m_typeof_ret_tv->print_title(printer);
            } else {
                printer.print_cstr("<Unknown>");
            }
        }
        printer.print_newline_deindent();
        printer.print_cstr("}");
    }


    // Array:
    class ArrayKDVS: public KindDependentVarSolver {
      private:
        TypeVar* m_opt_typeof_element_tv;

      public:
        explicit inline ArrayKDVS(VarKind var_kind);

      public:
        inline TypeVar* opt_typeof_element_tv() const;
        inline void opt_typeof_element_tv(TypeVar* tv);
        
      public:
        KdResult lazy_try_add_invariant_impl(KindDependentInvariant* new_invariant) override;

      public:
        void print(printer::Printer& printer) const override;
    };
    
    inline ArrayKDVS::ArrayKDVS(VarKind var_kind)
    :   KindDependentVarSolver(var_kind, TypeKind::Array),
        m_opt_typeof_element_tv(nullptr)
    {}
    inline TypeVar* ArrayKDVS::opt_typeof_element_tv() const {
        return m_opt_typeof_element_tv;
    }
    inline void ArrayKDVS::opt_typeof_element_tv(TypeVar* tv) {
        m_opt_typeof_element_tv = tv;
    }

    KdResult ArrayKDVS::lazy_try_add_invariant_impl(KindDependentInvariant* new_invariant) {
        auto new_array_invariant = dynamic_cast<IsArrayInvariant*>(new_invariant);
        if (new_array_invariant == nullptr) {
            return KdResult::TypingError;
        }

        TypeVar* typeof_array_invariant_item_tv = new_array_invariant->item_tv();
        if (m_opt_typeof_element_tv == nullptr) {
            m_opt_typeof_element_tv = typeof_array_invariant_item_tv;
            return KdResult::UpdatedOrFresh;
        } else {
            return m_opt_typeof_element_tv->higher_order_assume_equals(typeof_array_invariant_item_tv);
        }
    }

    void ArrayKDVS::print(printer::Printer& printer) const {
        help_print_common_and_start_indented_block(printer, "Array");
        {
            printer.print_cstr("- ItemType: ");
            m_opt_typeof_element_tv->print_title(printer);
        }
        printer.print_newline_deindent();
        printer.print_cstr("}");
    }

}

//
// Interface:
//

namespace pdm::types {

    KdResult KindDependentVarSolver::try_add_invariant(KindDependentInvariant* invariant) {
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
            return KdResult::NoChange;
        }
    }

    NewKDVS try_new_kdvs_for(VarKind var_kind, u64 allowed_type_kinds_bitset) {
        NewKDVS rv{};
        auto local_allowed_type_kinds_bitset = allowed_type_kinds_bitset;

        if (local_allowed_type_kinds_bitset == 0) {
            rv.result = KcResult::InsufficientInfo;
            rv.kdvs = nullptr;
        } 
        else if (is_type_var_kind(var_kind)) {
            if (exactly_1_bit_is_1_in_bitset(local_allowed_type_kinds_bitset)) {
                rv.result = KcResult::Ok;
                auto type_kind = extract_type_kind_from_bitset(local_allowed_type_kinds_bitset);
                assert(type_kind <= TypeKind::META_Max && "bug in 'exactly_1_bit_is_1_in_bitset'");
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
                    case TypeKind::Array:
                    {
                        rv.kdvs = new ArrayKDVS(var_kind);
                        break;
                    }
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