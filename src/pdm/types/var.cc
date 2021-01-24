#include "var.hh"

#include <string>
#include <iostream>

#include "pdm/core/bitsets.hh"
#include "pdm/ast/node.hh"
#include "pdm/printer/printer.hh"

#include "var_kind.hh"
#include "invariant.hh"
#include "typeop_result.hh"

// TODO: insert KDVS creation between SP1 and SP2... ;-;

namespace pdm::types {

    KdResult Var::assume_invariant_holds(Invariant* invariant) {
        return assume_invariant_holds_impl(invariant, false);
    }
    KdResult Var::assume_invariant_holds__override_fixed_to_init(Invariant* invariant) {
        return assume_invariant_holds_impl(invariant, true);
    }
    KdResult Var::higher_order_assume_equals(Var* var) {
        KdResult res1 = help_assume_subvar(this, var, true);
        KdResult res2 = help_assume_subvar(var, this, true);
        return kdr_and(res1, res2);
    }
    KdResult Var::higher_order_assume_subvar(Var* var) {
        return help_assume_subvar(this, var, true);
    }

    KdResult Var::assume_invariant_holds_impl(Invariant* invariant, bool override_fixed) {
        // if this invariant was not intended for a Var of this VarKind, then meta-type error:
        if (var_kind() != invariant->domain_var_kind()) {
            // todo: intercept templates here-- get their ret_tv and type that instead.
            return KdResult::TypingError;
        }

        // unless NotImplemented, AssumeOp will return 'Applied' from here.
        
        // if constant/fixed and 'override_fixed' is not set, this Var is 'change_forbidden'
        // this means ONLY subvar and supervar invariants are stored.
        // - use 'override_fixed=true' to setup fixed Vars
        // - then, use 'override_fixed=false' to setup everything else
        bool change_forbidden = is_constant() && !override_fixed;

        // if a common invariant, adding and applying immediately.
        CommonInvariant* common_invariant = nullptr;
        if ((common_invariant = dynamic_cast<CommonInvariant*>(invariant)) != nullptr) {
            m_assumed_common_invariants.push_back(common_invariant);

            // Kind invariants update the assumed_kind_bitset
            // - ignore kind bitset-modifying invariants for 'fixed' (still adding subvar, supervar)
            // - in 'assume', every invariant is 'unified'
            auto kind_invariant = dynamic_cast<KindInvariant*>(invariant);
            if (kind_invariant != nullptr) {
                if (!change_forbidden) {
                    TypeKindBitset supervar_kind_bitset = m_assumed_kind_bitset | kind_invariant->allowed_type_kinds_bitset();
                    if (supervar_kind_bitset == m_assumed_kind_bitset) {
                        return KdResult::NoChange;
                    } else {
                        m_assumed_kind_bitset = supervar_kind_bitset;
                        return KdResult::UpdatedOrFresh;
                    }
                }
            } 

            // subtype:
            auto subtype_of_invariant = dynamic_cast<SubtypeOfInvariant*>(invariant);
            if (subtype_of_invariant != nullptr) {
                return help_assume_subvar(this, subtype_of_invariant->supertype_tv(), false);
            }

            // subclass:
            auto subclass_of_invariant = dynamic_cast<SubclassOfInvariant*>(invariant);
            if (subclass_of_invariant != nullptr) {
                return help_assume_subvar(this, subclass_of_invariant->superclass_cv(), false);
            }
        
            // class instanceship:
            auto classof_invariant = dynamic_cast<ClassOfInvariant*>(invariant);
            if (classof_invariant != nullptr) {
                return help_assume_subvar(classof_invariant->member_tv(), this, false);
            }

            // Unknown CommonInvariant kind...
            assert(0 && "Unknown CommonInvariant.");
        }

        // if a kind-dependent invariant, adding to a list and deferring for later.
        // - we defer because if a TypeVar is multi-kind, we already have an error, so we can halt with the simplest error message.
        // - before KindDependentInvariant
        // also adding a kind-invariant corresponding to the assumed kind.
        // - NOTE: if change forbidden => ignore ALL kind-dependent invariants.
        if (change_forbidden) {
            return KdResult::NoChange;
        } else {
            KindDependentInvariant* kind_dependent_invariant = nullptr;
            if ((kind_dependent_invariant = dynamic_cast<KindDependentInvariant*>(invariant)) != nullptr) {
                // *sweats in bad memory management*
                KdResult result = assume_invariant_holds_impl(new KindInvariant(
                    invariant->parent_relation(), 
                    invariant->domain_var_kind(), 
                    tk_bits(kind_dependent_invariant->required_type_kind())
                ), override_fixed);
                
                // kind-dependent invariants deferred for later.
                m_assumed_kind_dependent_invariants.push_back(kind_dependent_invariant);

                // returning the result of just the kind application:
                return result;
            }
        }
        
        return KdResult::TypingError;
    }

    //
    // Solution:
    //

    // phase 1:
    // - check VarKind against TypeKind bitset
    KcResult Var::kind_check() {
        switch (var_kind())
        {
            case VarKind::Type:
            {
                auto self = dynamic_cast<TypeVar*>(this);
                switch (self->soln_bill())
                {
                    case TypeVarSolnBill::Fixed:
                    case TypeVarSolnBill::Monotype:
                    {
                        return help_kind_check_for_mixed_types();
                    }
                    case TypeVarSolnBill::ProxyForMany:
                    {
                        // ignore any mixed-kind errors
                        return KcResult::Ok;
                    }
                }
            }
            case VarKind::Template_RetValue:
            case VarKind::Template_RetType:
            {
                return help_kind_check_for_mixed_types();
            }
            case VarKind::Class:
            case VarKind::Template_RetClass:
            {
                // mixed-kind ok, since disjoint sets ok
                return KcResult::Ok;
            }
        }
    }

    KcResult Var::help_kind_check_for_mixed_types() {
        // verifying only a single 'kind' bit is set.
        // https://stackoverflow.com/questions/51094594/how-to-check-if-exactly-one-bit-is-set-in-an-int/51094793
        // - all po2 -1 has 1s in every lower position. po2 has 0s in every lower position. 
        // - '&' them. if (0), then po2.
        TypeKindBitset bitset = m_assumed_kind_bitset;
        if (bitset == 0) {
            return KcResult::InsufficientInfo;
        } else {
            if (exactly_1_bit_is_1_in_bitset(bitset)) {
                return KcResult::Ok;
            } else {
                return KcResult::Error_MixedKind;
            }
        }
    }

    KdResult Var::update_kd_invariants() {
        KdResult iter_sir = update_kd_invariants_impl();
        m_prev_solve_iter_result = iter_sir;
        return iter_sir;
    }
    KdResult Var::update_kd_invariants_impl() {
        if (m_prev_solve_iter_result == KdResult::TypingError) {
            return KdResult::TypingError;
        }
        if (m_prev_solve_iter_result == KdResult::CompilerError) {
            return KdResult::CompilerError;
        }
        
        assert(
            (m_prev_solve_iter_result == KdResult::UpdatedOrFresh) ||
            (m_prev_solve_iter_result == KdResult::NoChange)
        );

        // since the last update, there have been (1) new supervars, (2) new subvars, and (3) new invariants.

        // start by assuming no change has occurred. If any changes are applied,
        // they set 'kd_res'.
        KdResult kd_res = KdResult::NoChange;

        // unify kind bitsets based on super-vars and subvars:
        {
            auto const unify_kind_bitset_from = [] (std::vector<Var*> const& related_vars) {
                // must update from all related vars since any could have gained new kind bits since the
                // last iteration.
                TypeKindBitset related_kind_bitset = 0;
                size_t related_var_count = related_vars.size();
                for (size_t index = 0; index < related_var_count; index++) {
                    related_kind_bitset |= related_vars[index]->m_assumed_kind_bitset;
                }
                return related_kind_bitset;
            };
            // applying all super-var bitsets to own, calculating an SP2_Result accordingly:
            TypeKindBitset new_kind_bitset = m_assumed_kind_bitset;
            new_kind_bitset |= unify_kind_bitset_from(m_assumed_supervars);
            new_kind_bitset |= unify_kind_bitset_from(m_assumed_subvars);
            if (new_kind_bitset != m_assumed_kind_bitset) {
                // supervar_kind_bitset has expanded.
                m_assumed_kind_bitset = new_kind_bitset;

                // running an SP1 pass to check validity.
                KcResult kc_res = kind_check();
                switch (kc_res)
                {
                    // if still insufficient info or OK,
                    //   we've updated successfully.
                    case KcResult::InsufficientInfo:
                    case KcResult::Ok:
                    {
                        kd_res = KdResult::UpdatedOrFresh;
                        break;
                    }

                    // if mixed kinds, then typing error.
                    case KcResult::Error_MixedKind:
                    {
                        kd_res = KdResult::TypingError;
                        break;
                    }
                }
            } else {
                // kd_res remains at NoChange since new_kind_bitset == old_kind_bitset
            }
        }
        if (kdr_is_error(kd_res)) {
            // early return if error already detected
            return kd_res;
        } else {
            // creating the KDVS:
            if (m_kdvs == nullptr) {
                NewKDVS kdvs_create_info = try_new_kdvs_for(m_var_kind, m_assumed_kind_bitset);
                switch (kdvs_create_info.result)
                {
                    case KcResult::InsufficientInfo:
                    {
                        // do nothing; kdvs stays at nullptr.
                        break;
                    }
                    case KcResult::Ok:
                    {
                        // create a KDVS!
                        m_kdvs = kdvs_create_info.kdvs;
                        kd_res = kdr_and(kd_res, KdResult::UpdatedOrFresh);
                        break;
                    }
                    case KcResult::Error_MixedKind:
                    {
                        // error in kind-check above!
                        std::cout << "!!- Faulty kind-check detected in Var::update_kd_invariants_impl" << std::endl;
                        kd_res = kdr_and(kd_res, KdResult::CompilerError);
                        break;
                    }
                }
            } else {
                // KDVS already exists; still valid.
            }
        }

        // flushing invariants to the KDVS:
        if (m_kdvs != nullptr && !m_assumed_kind_dependent_invariants.empty()) {
            size_t a = m_kdvs_consumed_kd_invariant_count;
            size_t b = m_assumed_kind_dependent_invariants.size() - 1;
            for (size_t i = a; i <= b; i++) {
                KindDependentInvariant* kd_invariant = m_assumed_kind_dependent_invariants[i];
                m_kdvs->try_add_invariant(kd_invariant);
            }
            m_kdvs_consumed_kd_invariant_count = b;
        }

        // - fresh subvars need all invariants, old and new.
        // - old subvars only need new invariants.
        // - after propagating updates, need to update bounds for next iter.
        {
            size_t old_invariant_count = m_sp2_propagated_sofar_kd_invariant_count;
            // size_t old_invariant_count = m_sp2_propagated_sofar_kd_invariant_count;
            size_t old_subvar_count = m_sp2_propagated_sofar_subvar_count;

            // adding only new invariants to old subvars:
            for (size_t old_subvar_index = 0; old_subvar_index < old_subvar_count; old_subvar_index++) {
                Var* old_subvar = m_assumed_subvars[old_subvar_index];
                for (
                    size_t new_invariant_index = old_invariant_count;
                    new_invariant_index < m_assumed_kind_dependent_invariants.size();
                    new_invariant_index++
                ) {
                    Invariant* new_invariant = m_assumed_kind_dependent_invariants[new_invariant_index];
                    kd_res = kdr_and(kd_res, old_subvar->assume_invariant_holds(new_invariant));
                }
            }
            
            // adding all invariants to only new subvars:
            for (size_t new_subvar_index = old_subvar_count; new_subvar_index < m_assumed_subvars.size(); new_subvar_index++) {
                Var* new_subvar = m_assumed_subvars[new_subvar_index];
                for (Invariant* invariant: m_assumed_kind_dependent_invariants) {
                    kd_res = kdr_and(new_subvar->assume_invariant_holds(invariant), kd_res);
                }
            }

            // updating bounds for next iter:
            // assume all invariants and all subvars so far have been propagated.
            m_sp2_propagated_sofar_kd_invariant_count = m_assumed_kind_dependent_invariants.size();
            m_sp2_propagated_sofar_subvar_count = m_assumed_subvars.size();
        }
        
        return kd_res;
    }

    TestOpResult Var::test(Invariant* invariant) {
        std::cout << "NotImplemented: Var::test." << std::endl;
        return TestOpResult::ErrorOccurred;
    }
    
    KdResult Var::help_assume_subvar(Var* subvar, Var* supervar, bool is_second_order_invariant) {
        KdResult assume_op_result = KdResult::NoChange;

        {   // inserting super-var into sub-var:
            bool existing_supervar_matches_supervar = false;
            for (Var* existing_supervar: subvar->m_assumed_supervars) {
                if (existing_supervar == supervar) {
                    existing_supervar_matches_supervar = true;
                    break;
                }
            }
            if (!existing_supervar_matches_supervar) {
                subvar->m_assumed_supervars.push_back(supervar);
                assume_op_result = KdResult::UpdatedOrFresh;
            }
        }

        {   // inserting sub-var into super-var:
            bool existing_subvar_matches_supervar = false;
            for (Var* existing_subvar: supervar->m_assumed_subvars) {
                if (existing_subvar == supervar) {
                    existing_subvar_matches_supervar = true;
                    break;
                }
            }
            if (!existing_subvar_matches_supervar) {
                supervar->m_assumed_subvars.push_back(subvar);
                assume_op_result = KdResult::UpdatedOrFresh;
            }
        }
        
        return assume_op_result;
    }

    KdResult TypeVar::initial_sp2_result_for_soln_bill(TypeVarSolnBill soln_bill) {
        switch (soln_bill) {
            case TypeVarSolnBill::Fixed: 
            {
                return KdResult::NoChange;
            }
            case TypeVarSolnBill::Monotype:
            case TypeVarSolnBill::ProxyForMany:
            {
                return KdResult::UpdatedOrFresh;
            }
        }
    }

    //
    // Printing:
    //

    void Var::print(printer::Printer& p) const {
        print_title(p);
        p.print_cstr(" {");
        p.print_newline_indent();
        {
            help_print_assumed_kind_bitset(p);
            p.print_newline();
            help_print_assumed_common_invariants(p);
            p.print_newline();
            help_print_assumed_kind_dependent_invariants(p);
            p.print_newline();
            help_print_assumed_subvars(p);
            p.print_newline();
            help_print_assumed_supervars(p);
            p.print_newline();
            if (m_opt_client_ast_node != nullptr) {
                help_print_opt_client_ast_node(p);
                p.print_newline();
            }
            help_print_kdvs(p);
        }
        p.print_newline_deindent();
        p.print_cstr("}");
        p.print_newline();
    }

    void Var::print_title(printer::Printer& p) const {
        // printing a prefix denoting var_kind():
        switch (var_kind())
        {
            case VarKind::Type:
            {
                p.print_cstr("Type");
                break;
            }
            case VarKind::Class:
            {
                p.print_cstr("Class");
                break;
            }
            case VarKind::Template_RetValue:
            {
                p.print_cstr("ValueTemplate");
                break;
            }
            case VarKind::Template_RetType:
            {
                p.print_cstr("TypeTemplate");
                break;
            }
            case VarKind::Template_RetClass:
            {
                p.print_cstr("ClassTemplate");
                break;
            }
            default:
            {
                p.print_cstr("Var(?)");
                break;
            }
        }
        p.print_cstr(" ");

        // printing the var name:
        p.print_str(name());

        // printing last kdr changed:
        switch (m_prev_solve_iter_result)
        {
            case KdResult::UpdatedOrFresh:
            {
                p.print_cstr(" (UpdatedOrFresh)");
                break;
            }
            case KdResult::NoChange:
            {
                p.print_cstr(" (NoChange)");
                break;
            }
            case KdResult::TypingError:
            {
                p.print_cstr(" (TypingError)");
                break;
            }
            case KdResult::CompilerError:
            {
                p.print_cstr(" (CompilerError)");
                break;
            }
        }

        // printing the var addr:
        p.print_cstr(" @ ");
        p.print_uint_hex(reinterpret_cast<u64>(this));
    }
    void Var::help_print_assumed_kind_bitset(printer::Printer& p) const {
        p.print_cstr("assume TypeKinds");
        if (m_assumed_kind_bitset != 0) {
            p.print_newline();
            auto tk_index_first = static_cast<TypeKindBitset>(TypeKind::META_Min);
            auto tk_index_last = static_cast<TypeKindBitset>(TypeKind::META_Max);
            for (auto tk_index = tk_index_first; tk_index <= tk_index_last; tk_index++) {
                auto tk = static_cast<TypeKind>(tk_index);
                if (m_assumed_kind_bitset & tk_bits(tk)) {
                    p.print_cstr("| ");
                    p.print_cstr(type_kind_as_str(tk));
                }
            }
        } else {
            p.print_cstr(": None");
        }
    }
    void Var::help_print_assumed_common_invariants(printer::Printer& p) const {
        p.print_cstr("assume CommonInvariants:");
        if (assumed_common_invariants().empty()) {
            p.print_cstr(" None");
        } else {
            for (Invariant* invariant: assumed_common_invariants()) {
                p.print_newline();
                p.print_cstr("- ");
                p.print_str(invariant->name());
            }
        }
    }
    void Var::help_print_assumed_kind_dependent_invariants(printer::Printer& p) const {
        p.print_cstr("assume KindDependentInvariants:");
        if (assumed_kind_dependent_invariants().empty()) {
            p.print_cstr(" None");
        } else {
            for (Invariant* invariant: assumed_kind_dependent_invariants()) {
                p.print_newline();
                p.print_cstr("- ");
                p.print_str(invariant->name());
            }
        }
    }
    void Var::help_print_assumed_subvars(printer::Printer& p) const {
        p.print_cstr("assume Sub-vars:");
        if (assumed_subvars().empty()) {
            p.print_cstr(" None");
        } else {
            for (size_t index = 0; index < m_assumed_subvars.size(); index++) {
                Var* assumed_subvar = m_assumed_subvars[index];
                p.print_newline();
                p.print_cstr("- ");
                assumed_subvar->print_title(p);
            }
        }
    }
    void Var::help_print_assumed_supervars(printer::Printer& p) const {
        p.print_cstr("assume Super-vars:");
        if (assumed_supervars().empty()) {
            p.print_cstr(" None");
        } else {
            for (auto assumed_supervar : m_assumed_supervars) {
                p.print_newline();
                p.print_cstr("- ");
                assumed_supervar->print_title(p);
            }
        }
    }
    void Var::help_print_kdvs(printer::Printer& p) const {
        p.print_cstr("kdvs: ");
        if (m_kdvs != nullptr) {
            m_kdvs->print(p);
        } else {
            p.print_cstr("None");
        }
    }
    void Var::help_print_opt_client_ast_node(printer::Printer& p) const {
        if (m_opt_client_ast_node != nullptr) {
            p.print_cstr("client: ");
            p.print_cstr(ast::kind_as_text(m_opt_client_ast_node->kind()));
            p.print_cstr(" @ ");
            p.print_uint_hex(reinterpret_cast<u64>(m_opt_client_ast_node));
        }
    }

    //
    // Constant types:
    //
    // todo: implement constant Relations for these invariants to be applied from.

    FixedTypeVar::FixedTypeVar(std::string&& name, Type* fixed_soln)
    :   TypeVar("FixedType:" + std::move(name), fixed_soln, nullptr, TypeVarSolnBill::Fixed)
    {}
    
    VoidFixedTypeVar::VoidFixedTypeVar()
    :   FixedTypeVar(std::move(std::string("Void")), VoidType::get()) 
    { 
        assume_invariant_holds__override_fixed_to_init(new IsVoidInvariant(nullptr, VarKind::Type)); 
    }
    StringFixedTypeVar::StringFixedTypeVar()
    :   FixedTypeVar(std::move(std::string("String")), StringType::get())
    {
        assume_invariant_holds__override_fixed_to_init(new IsStringInvariant(nullptr, VarKind::Type));
    }
    
    Int8FixedTypeVar::Int8FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("Int8")), IntType::get_i8())
    {
        assume_invariant_holds__override_fixed_to_init(new IsIntInvariant(nullptr, VarKind::Type, 8, 8, true));
    }
    Int16FixedTypeVar::Int16FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("Int16")), IntType::get_i16())
    {
        assume_invariant_holds__override_fixed_to_init(new IsIntInvariant(nullptr, VarKind::Type, 16, 16, true));
    }
    Int32FixedTypeVar::Int32FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("Int32")), IntType::get_i32())
    {
        assume_invariant_holds__override_fixed_to_init(new IsIntInvariant(nullptr, VarKind::Type, 32, 32, true));
    }
    Int64FixedTypeVar::Int64FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("Int64")), IntType::get_i64())
    {
        assume_invariant_holds__override_fixed_to_init(new IsIntInvariant(nullptr, VarKind::Type, 64, 64, true));
    }
    Int128FixedTypeVar::Int128FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("Int128")), IntType::get_i128())
    {
        assume_invariant_holds__override_fixed_to_init(new IsIntInvariant(nullptr, VarKind::Type, 128, 128, true));
    }

    UInt1FixedTypeVar::UInt1FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("UInt1")), IntType::get_u8())
    {
        assume_invariant_holds__override_fixed_to_init(new IsIntInvariant(nullptr, VarKind::Type, 1, 1, false));
    }
    UInt8FixedTypeVar::UInt8FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("UInt8")), IntType::get_u8())
    {
        assume_invariant_holds__override_fixed_to_init(new IsIntInvariant(nullptr, VarKind::Type, 8, 8, false));
    }
    UInt16FixedTypeVar::UInt16FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("UInt16")), IntType::get_u16())
    {
        assume_invariant_holds__override_fixed_to_init(new IsIntInvariant(nullptr, VarKind::Type, 16, 16, false));
    }
    UInt32FixedTypeVar::UInt32FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("UInt32")), IntType::get_u32())
    {
        assume_invariant_holds__override_fixed_to_init(new IsIntInvariant(nullptr, VarKind::Type, 32, 32, false));
    }
    UInt64FixedTypeVar::UInt64FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("UInt64")), IntType::get_u64())
    {
        assume_invariant_holds__override_fixed_to_init(new IsIntInvariant(nullptr, VarKind::Type, 64, 64, false));
    }
    UInt128FixedTypeVar::UInt128FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("UInt128")), IntType::get_u128())
    {
        assume_invariant_holds__override_fixed_to_init(new IsIntInvariant(nullptr, VarKind::Type, 128, 128, false));
    }

    Float16FixedTypeVar::Float16FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("Float16")), FloatType::get_f16())
    {
        assume_invariant_holds__override_fixed_to_init(new IsFloatInvariant(nullptr, VarKind::Type, 16, 16));
    }
    Float32FixedTypeVar::Float32FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("Float32")), FloatType::get_f32())
    {
        assume_invariant_holds__override_fixed_to_init(new IsFloatInvariant(nullptr, VarKind::Type, 32, 32));
    }
    Float64FixedTypeVar::Float64FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("Float64")), FloatType::get_f32())
    {
        assume_invariant_holds__override_fixed_to_init(new IsFloatInvariant(nullptr, VarKind::Type, 64, 64));
    }
    
    //
    // Constant classes:
    //
    // todo: implement constant Relations for these invariants to be applied from.

    SignedIntFixedClassVar::SignedIntFixedClassVar()
    :   FixedClassVar(std::move(std::string("FixedClass:SignedInt")))
    {
        assume_invariant_holds__override_fixed_to_init(new KindInvariant(nullptr, VarKind::Class, tk_bits(TypeKind::SignedInt)));
    }
    UnsignedIntFixedClassVar::UnsignedIntFixedClassVar()
    :   FixedClassVar(std::move(std::string("FixedClass:UnsignedInt")))
    {
        assume_invariant_holds__override_fixed_to_init(new KindInvariant(nullptr, VarKind::Class, tk_bits(TypeKind::UnsignedInt)));
    }
    FloatFixedClassVar::FloatFixedClassVar()
    :   FixedClassVar(std::move(std::string("FixedClass:Float")))
    {
        assume_invariant_holds__override_fixed_to_init(new KindInvariant(nullptr, VarKind::Class, tk_bits(TypeKind::Float)));
    }
}