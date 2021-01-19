#include "var.hh"

#include <string>
#include <iostream>

#include "pdm/core/bitsets.hh"
#include "pdm/ast/node.hh"
#include "pdm/printer/printer.hh"

#include "var_kind.hh"
#include "invariant.hh"
#include "typeop_result.hh"

namespace pdm::types {

    SolvePhase2_Result Var::assume_invariant_holds(Invariant* invariant) {
        return assume_invariant_holds_impl(invariant, false);
    }
    SolvePhase2_Result Var::assume_invariant_holds__override_fixed_to_init(Invariant* invariant) {
        return assume_invariant_holds_impl(invariant, true);
    }
    SolvePhase2_Result Var::higher_order_assume_equals(Var* var) {
        SolvePhase2_Result res1 = help_assume_subvar(this, var, true);
        SolvePhase2_Result res2 = help_assume_subvar(var, this, true);
        return sp2res_and(res1, res2);
    }
    SolvePhase2_Result Var::higher_order_assume_subvar(Var* var) {
        return help_assume_subvar(this, var, true);
    }

    SolvePhase2_Result Var::assume_invariant_holds_impl(Invariant* invariant, bool override_fixed) {
        // if this invariant was not intended for a Var of this VarKind,
        // typer's meta-type error:
        if (var_kind() != invariant->domain_var_kind()) {
            return SolvePhase2_Result::TypingError;
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
            KindInvariant* kind_invariant = dynamic_cast<KindInvariant*>(invariant);
            if (kind_invariant != nullptr) {
                if (!change_forbidden) {
                    TypeKindBitset new_kind_bitset = m_assumed_kind_bitset | kind_invariant->allowed_type_kinds_bitset();
                    if (new_kind_bitset == m_assumed_kind_bitset) {
                        return SolvePhase2_Result::NoChange;
                    } else {
                        m_assumed_kind_bitset = new_kind_bitset;
                        return SolvePhase2_Result::UpdatedOrFresh;
                    }
                }
            } 

            // subtype:
            SubtypeOfInvariant* subtype_of_invariant = dynamic_cast<SubtypeOfInvariant*>(invariant);
            if (subtype_of_invariant != nullptr) {
                return help_assume_subvar(this, subtype_of_invariant->supertype_tv(), false);
            }

            // subclass:
            SubclassOfInvariant* subclass_of_invariant = dynamic_cast<SubclassOfInvariant*>(invariant);
            if (subclass_of_invariant != nullptr) {
                return help_assume_subvar(this, subclass_of_invariant->superclass_cv(), false);
            }
        
            // class instanceship:
            ClassOfInvariant* classof_invariant = dynamic_cast<ClassOfInvariant*>(invariant);
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
            return SolvePhase2_Result::NoChange;
        } else {
            KindDependentInvariant* kind_dependent_invariant = nullptr;
            if ((kind_dependent_invariant = dynamic_cast<KindDependentInvariant*>(invariant)) != nullptr) {
                // *sweats in bad memory management*
                SolvePhase2_Result result = assume_invariant_holds_impl(new KindInvariant(
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
        
        return SolvePhase2_Result::TypingError;
    }

    //
    // Solution:
    //

    // phase 1:
    // - check VarKind against TypeKind bitset
    SolvePhase1_Result Var::solve_phase1() {
        switch (var_kind())
        {
            case VarKind::Type:
            {
                TypeVar* self = dynamic_cast<TypeVar*>(this);
                switch (self->soln_bill())
                {
                    case TypeVarSolnBill::Fixed:
                    case TypeVarSolnBill::Monotype:
                    {
                        return help_check_phase1_type_bitset_for_mixed_kinds();
                    }
                    case TypeVarSolnBill::ProxyForMany:
                    {
                        // ignore any mixed-kind errors
                        return SolvePhase1_Result::Ok;
                    }
                }
            }
            case VarKind::Template_RetValue:
            case VarKind::Template_RetType:
            {
                return help_check_phase1_type_bitset_for_mixed_kinds();
            }
            case VarKind::Class:
            case VarKind::Template_RetClass:
            {
                // mixed-kind ok, since disjoint sets ok
                return SolvePhase1_Result::Ok;
            }
        }
    }

    SolvePhase1_Result Var::help_check_phase1_type_bitset_for_mixed_kinds() {
        // verifying only a single 'kind' bit is set.
        // https://stackoverflow.com/questions/51094594/how-to-check-if-exactly-one-bit-is-set-in-an-int/51094793
        // - all po2 -1 has 1s in every lower position. po2 has 0s in every lower position. 
        // - '&' them. if (0), then po2.
        TypeKindBitset bitset = m_assumed_kind_bitset;
        if (bitset == 0) {
            return SolvePhase1_Result::InsufficientInfo;
        } else {
            if (exactly_1_bit_is_1_in_bitset(bitset)) {
                return SolvePhase1_Result::Ok;
            } else {
                return SolvePhase1_Result::Error_MixedKind;
            }
        }
    }

    SolvePhase2_Result Var::solve_phase2_iter() {
        SolvePhase2_Result iter_sir = solve_phase2_iter_impl();
        m_prev_solve_iter_result = iter_sir;
        return iter_sir;
    }
    SolvePhase2_Result Var::solve_phase2_iter_impl() {
        if (m_prev_solve_iter_result == SolvePhase2_Result::NoChange) {
            return SolvePhase2_Result::NoChange;
        }
        if (m_prev_solve_iter_result == SolvePhase2_Result::TypingError) {
            return SolvePhase2_Result::TypingError;
        }
        if (m_prev_solve_iter_result == SolvePhase2_Result::CompilerError) {
            return SolvePhase2_Result::CompilerError;
        }
        
        assert(m_prev_solve_iter_result == SolvePhase2_Result::UpdatedOrFresh);

        // since the last update, there have been (1) new subvars, and (2) new invariants.
        // - fresh subvars need all invariants, old and new.
        // - old subvars only need new invariants.
        // - after propagating updates, need to update bounds for next iter.
        {
            SolvePhase2_Result result = SolvePhase2_Result::NoChange;
            size_t old_invariant_count = m_sp2_propagated_sofar_kd_invariant_count;
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
                    result = sp2res_and(result, old_subvar->assume_invariant_holds(new_invariant));
                }
            }
            
            // adding all invariants to only new subvars:
            for (size_t new_subvar_index = old_subvar_count; new_subvar_index < m_assumed_subvars.size(); new_subvar_index++) {
                Var* new_subvar = m_assumed_subvars[new_subvar_index];
                for (Invariant* invariant: m_assumed_kind_dependent_invariants) {
                    result = sp2res_and(new_subvar->assume_invariant_holds(invariant), result);
                }
            }

            // updating bounds for next iter:
            // assume all invariants and all subvars so far have been propagated.
            m_sp2_propagated_sofar_kd_invariant_count = m_assumed_kind_dependent_invariants.size();
            m_sp2_propagated_sofar_subvar_count = m_assumed_subvars.size();
        }

        std::cout << "NotImplemented: solve_phase2_iter_impl" << std::endl;
        return SolvePhase2_Result::TypingError;
    }

    TestOpResult Var::test(Invariant* invariant) {
        std::cout << "NotImplemented: Var::test." << std::endl;
        return TestOpResult::ErrorOccurred;
    }
    
    SolvePhase2_Result Var::help_assume_subvar(Var* subvar, Var* supervar, bool is_second_order_invariant) {
        SolvePhase2_Result assume_op_result = SolvePhase2_Result::NoChange;

        {   // inserting super-var into sub-var:
            bool existing_supervar_matches_supervar = false;
            for (Var* existing_supervar: subvar->m_assumed_supervars) {
                if (existing_supervar == supervar) {
                    existing_supervar_matches_supervar = true;
                    break;
                }
            }
            if (existing_supervar_matches_supervar) {
                subvar->m_assumed_supervars.push_back(supervar);
                assume_op_result = SolvePhase2_Result::UpdatedOrFresh;
            }
        }

        {   // inserting sub-var into super-var:
            bool existing_subvar_matches_subvar = false;
            for (Var* existing_subvar: supervar->m_assumed_subvars) {
                if (existing_subvar == supervar) {
                    existing_subvar_matches_subvar = true;
                    break;
                }
            }
            if (existing_subvar_matches_subvar) {
                subvar->m_assumed_supervars.push_back(supervar);
                assume_op_result = SolvePhase2_Result::UpdatedOrFresh;
            }
        }
        
        return assume_op_result;
    }

    SolvePhase2_Result TypeVar::initial_sp2_result_for_soln_bill(TypeVarSolnBill soln_bill) {
        switch (soln_bill) {
            case TypeVarSolnBill::Fixed: 
            {
                return SolvePhase2_Result::NoChange;
            }
            case TypeVarSolnBill::Monotype:
            case TypeVarSolnBill::ProxyForMany:
            {
                return SolvePhase2_Result::UpdatedOrFresh;
            }
        }
    }

    //
    // Printing:
    //

    void Var::print(printer::Printer& p) const {
        help_print_title(p);
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
        }
        p.print_newline_deindent();
        p.print_cstr("}");
        p.print_newline();
    }

    void Var::help_print_title(printer::Printer& p) const {
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

        // printing the var addr:
        p.print_cstr(" @ ");
        p.print_uint_hex(reinterpret_cast<u64>(this));
    }
    void Var::help_print_assumed_kind_bitset(printer::Printer& p) const {
        p.print_cstr("assume TypeKinds");
        if (m_assumed_kind_bitset != 0) {
            p.print_newline();
            if (m_assumed_kind_bitset & static_cast<u64>(TypeKind::Void))        { p.print_cstr("| Void "); }
            if (m_assumed_kind_bitset & static_cast<u64>(TypeKind::String))      { p.print_cstr("| String "); }
            if (m_assumed_kind_bitset & static_cast<u64>(TypeKind::SignedInt))   { p.print_cstr("| SignedInt "); }
            if (m_assumed_kind_bitset & static_cast<u64>(TypeKind::UnsignedInt)) { p.print_cstr("| UnsignedInt "); }
            if (m_assumed_kind_bitset & static_cast<u64>(TypeKind::Float))       { p.print_cstr("| Float "); }
            if (m_assumed_kind_bitset & static_cast<u64>(TypeKind::Struct))      { p.print_cstr("| Struct "); }
            if (m_assumed_kind_bitset & static_cast<u64>(TypeKind::Enum))        { p.print_cstr("| Enum "); }
            if (m_assumed_kind_bitset & static_cast<u64>(TypeKind::Module))      { p.print_cstr("| Module "); }
            if (m_assumed_kind_bitset & static_cast<u64>(TypeKind::Fn))          { p.print_cstr("| Fn "); }
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
                assumed_subvar->help_print_title(p);
            }
        }
    }
    void Var::help_print_assumed_supervars(printer::Printer& p) const {
        p.print_cstr("assume Super-vars:");
        if (assumed_supervars().empty()) {
            p.print_cstr(" None");
        } else {
            for (size_t index = 0; index < m_assumed_supervars.size(); index++) {
                Var* assumed_supervar = m_assumed_supervars[index];
                p.print_cstr("- ");
                assumed_supervar->help_print_title(p);
                if (index+1 != m_assumed_supervars.size()) {
                    p.print_newline();
                }
            }
        }
    }
    void Var::help_print_opt_client_ast_node(printer::Printer& p) const {
        if (m_opt_client_ast_node != nullptr) {
            p.print_cstr("client: ");
            p.print_cstr(ast::kind_as_text(m_opt_client_ast_node->kind()));
            p.print_cstr(" @ ");
            p.print_uint_hex(reinterpret_cast<u64>(m_opt_client_ast_node));
            p.print_newline();
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
        assume_invariant_holds__override_fixed_to_init(new KindInvariant(nullptr, VarKind::Class, static_cast<u64>(TypeKind::SignedInt)));
    }
    UnsignedIntFixedClassVar::UnsignedIntFixedClassVar()
    :   FixedClassVar(std::move(std::string("FixedClass:UnsignedInt")))
    {
        assume_invariant_holds__override_fixed_to_init(new KindInvariant(nullptr, VarKind::Class, static_cast<u64>(TypeKind::UnsignedInt)));
    }
    IntFixedClassVar::IntFixedClassVar()
    :   FixedClassVar(std::move(std::string("FixedClass:Int")))
    {
        assume_invariant_holds__override_fixed_to_init(new KindInvariant(nullptr, VarKind::Class, static_cast<u64>(TypeKind::SignedInt) | static_cast<u64>(TypeKind::UnsignedInt)));
    }
    FloatFixedClassVar::FloatFixedClassVar()
    :   FixedClassVar(std::move(std::string("FixedClass:Float")))
    {
        assume_invariant_holds__override_fixed_to_init(new KindInvariant(nullptr, VarKind::Class, static_cast<u64>(TypeKind::Float)));
    }
    NumberFixedClassVar::NumberFixedClassVar()
    :   FixedClassVar(std::move(std::string("FixedClass:Number")))
    {
        assume_invariant_holds__override_fixed_to_init(
            new KindInvariant(
                nullptr, 
                VarKind::Class, 
                static_cast<u64>(TypeKind::SignedInt) | static_cast<u64>(TypeKind::UnsignedInt) | static_cast<u64>(TypeKind::Float)
            )
        );
    }
}