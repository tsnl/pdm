#include "var.hh"

#include <string>
#include <iostream>

#include "pdm/ast/node.hh"
#include "pdm/printer/printer.hh"

#include "var_kind.hh"
#include "constraint.hh"


namespace pdm::types {

    AssumeOpResult Var::assume_constraint_holds(Constraint* constraint) {
        return assume_constraint_holds_impl(constraint, false);
    }
    AssumeOpResult Var::assume_constraint_holds__override_fixed_to_init(Constraint* constraint) {
        return assume_constraint_holds_impl(constraint, true);
    }

    AssumeOpResult Var::assume_constraint_holds_impl(Constraint* constraint, bool override_fixed) {
        // if this constraint was not intended for a Var of this VarKind,
        // typer's meta-type error:
        if (var_kind() != constraint->domain_var_kind()) {
            return AssumeOpResult::ErrorOccurred;
        }

        // unless NotImplemented, AssumeOp will return 'Applied' from here.
        
        if (!override_fixed) {
            if (is_constant()) {
                // just ignoring extra constraints on constants-- 
                // constants are constraint sinks upon propagation!
                return AssumeOpResult::Applied;
            }
        }
        
        // if a common constraint, adding and applying immediately.
        CommonConstraint* common_constraint = nullptr;
        if ((common_constraint = dynamic_cast<CommonConstraint*>(constraint)) != nullptr) {
            m_assumed_common_constraints.push_back(common_constraint);

            // Kind constraints update the assumed_kind_bitset:
            KindConstraint* kind_constraint = dynamic_cast<KindConstraint*>(constraint);
            if (kind_constraint != nullptr) {
                m_assumed_kind_bitset |= kind_constraint->allowed_type_kinds_bitset();
                return AssumeOpResult::Applied;
            } 

            // subtype:
            SubtypeOfConstraint* subtype_of_constraint = dynamic_cast<SubtypeOfConstraint*>(constraint);
            if (subtype_of_constraint != nullptr) {
                help_assume_subvar(this, subtype_of_constraint->supertype_tv());
                return AssumeOpResult::Applied;
            }

            // subclass:
            SubclassOfConstraint* subclass_of_constraint = dynamic_cast<SubclassOfConstraint*>(constraint);
            if (subclass_of_constraint != nullptr) {
                help_assume_subvar(this, subclass_of_constraint->superclass_cv());
                return AssumeOpResult::Applied;
            }
        
            // class instanceship:
            ClassOfConstraint* classof_constraint = dynamic_cast<ClassOfConstraint*>(constraint);
            if (classof_constraint != nullptr) {
                help_assume_subvar(classof_constraint->member_tv(), this);
                return AssumeOpResult::Applied;
            }

            // Unknown CommonConstraint kind...
            assert(0 && "Unknown CommonConstraint.");
        }

        // if a kind-dependent constraint, adding to a list and deferring for later.
        // - we defer because if a TypeVar is multi-kind, we already have an error, so we can halt with the simplest error message.
        // - before KindDependentConstraint
        // also adding a kind-constraint corresponding to the assumed kind.
        KindDependentConstraint* kind_dependent_constraint = nullptr;
        if ((kind_dependent_constraint = dynamic_cast<KindDependentConstraint*>(constraint)) != nullptr) {
            // *sweats in bad memory management*
            AssumeOpResult result = assume_constraint_holds_impl(new KindConstraint(
                constraint->parent_relation(), 
                constraint->domain_var_kind(), 
                static_cast<u64>(kind_dependent_constraint->required_type_kind())
            ), override_fixed);
            
            // kind-dependent constraints deferred for later.
            m_assumed_kind_dependent_constraints.push_back(kind_dependent_constraint);

            // returning the result of just the kind application:
            return result;
        }

        return AssumeOpResult::ErrorOccurred;
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
            case VarKind::ValueTemplate:
            case VarKind::TypeTemplate:
            {
                return help_check_phase1_type_bitset_for_mixed_kinds();
            }
            case VarKind::Class:
            case VarKind::ClassTemplate:
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
        u64 bitset = m_assumed_kind_bitset;
        if (bitset == 0) {
            return SolvePhase1_Result::InsufficientInfo;
        } else if (!(bitset & (bitset-1))) {
            return SolvePhase1_Result::Ok;
        } else {
            return SolvePhase1_Result::Error_MixedKind;
        }
    }

    SolvePhase2_Result Var::solve_phase2_iter() {
        SolvePhase2_Result iter_sir = solve_phase2_iter_impl();
        m_prev_solve_iter_result = iter_sir;
        return iter_sir;
    }
    SolvePhase2_Result Var::solve_phase2_iter_impl() {
        if (m_prev_solve_iter_result == SolvePhase2_Result::AtFixedPoint) {
            return SolvePhase2_Result::AtFixedPoint;
        }
        if (m_prev_solve_iter_result == SolvePhase2_Result::AtError) {
            return SolvePhase2_Result::AtError;
        }
        
        assert(m_prev_solve_iter_result == SolvePhase2_Result::UpdatedOrFresh);

        // todo: compare kind bitset against all subvars
        // todo: implement rest of `typing.dot`...

        std::cout << "NotImplemented: solve_phase2_iter_impl" << std::endl;
        return SolvePhase2_Result::AtError;
    }

    TestOpResult Var::test(Constraint* constraint) {
        std::cout << "NotImplemented: Var::test." << std::endl;
        return TestOpResult::ErrorOccurred;
    }
    
    void Var::help_assume_subvar(Var* subvar, Var* supervar) {
        // todo: update to 1-way when not in DEBUG mode:
        subvar->m_assumed_supervars.push_back(supervar);
        supervar->m_assumed_subvars.push_back(subvar);
    }

    SolvePhase2_Result TypeVar::initial_sp2_result_for_soln_bill(TypeVarSolnBill soln_bill) {
        switch (soln_bill) {
            case TypeVarSolnBill::Fixed: 
            {
                return SolvePhase2_Result::AtFixedPoint;
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
            help_print_assumed_common_constraints(p);
            p.print_newline();
            help_print_assumed_kind_dependent_constraints(p);
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
            case VarKind::ValueTemplate:
            {
                p.print_cstr("ValueTemplate");
                break;
            }
            case VarKind::TypeTemplate:
            {
                p.print_cstr("TypeTemplate");
                break;
            }
            case VarKind::ClassTemplate:
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
            if (m_assumed_kind_bitset & static_cast<u64>(TypeKind::Void))   { p.print_cstr("| Void "); }
            if (m_assumed_kind_bitset & static_cast<u64>(TypeKind::String)) { p.print_cstr("| String "); }
            if (m_assumed_kind_bitset & static_cast<u64>(TypeKind::Int))    { p.print_cstr("| Int "); }
            if (m_assumed_kind_bitset & static_cast<u64>(TypeKind::Float))  { p.print_cstr("| Float "); }
            if (m_assumed_kind_bitset & static_cast<u64>(TypeKind::Ref))    { p.print_cstr("| Ref "); }
            if (m_assumed_kind_bitset & static_cast<u64>(TypeKind::Struct)) { p.print_cstr("| Struct "); }
            if (m_assumed_kind_bitset & static_cast<u64>(TypeKind::Enum))   { p.print_cstr("| Enum "); }
            if (m_assumed_kind_bitset & static_cast<u64>(TypeKind::Module)) { p.print_cstr("| Module "); }
            if (m_assumed_kind_bitset & static_cast<u64>(TypeKind::Fn))   { p.print_cstr("| Fn "); }
        } else {
            p.print_cstr(": None");
        }
    }
    void Var::help_print_assumed_common_constraints(printer::Printer& p) const {
        p.print_cstr("assume CommonConstraints:");
        if (assumed_common_constraints().empty()) {
            p.print_cstr(" None");
        } else {
            for (Constraint* constraint: assumed_common_constraints()) {
                p.print_newline();
                p.print_cstr("- ");
                p.print_str(constraint->name());
            }
        }
    }
    void Var::help_print_assumed_kind_dependent_constraints(printer::Printer& p) const {
        p.print_cstr("assume KindDependentConstraints:");
        if (assumed_kind_dependent_constraints().empty()) {
            p.print_cstr(" None");
        } else {
            for (Constraint* constraint: assumed_kind_dependent_constraints()) {
                p.print_newline();
                p.print_cstr("- ");
                p.print_str(constraint->name());
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
    // todo: implement constant Relations for these constraints to be applied from.

    FixedTypeVar::FixedTypeVar(std::string&& name, Type* fixed_soln)
    :   TypeVar("FixedType:" + std::move(name), fixed_soln, nullptr, TypeVarSolnBill::Fixed)
    {}
    
    VoidFixedTypeVar::VoidFixedTypeVar()
    :   FixedTypeVar(std::move(std::string("Void")), VoidType::get()) 
    { 
        assume_constraint_holds__override_fixed_to_init(new VoidConstraint(nullptr, VarKind::Type)); 
    }
    StringFixedTypeVar::StringFixedTypeVar()
    :   FixedTypeVar(std::move(std::string("String")), StringType::get())
    {
        assume_constraint_holds__override_fixed_to_init(new StringConstraint(nullptr, VarKind::Type));
    }
    
    Int8FixedTypeVar::Int8FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("Int8")), IntType::get_i8())
    {
        assume_constraint_holds__override_fixed_to_init(new IntConstraint(nullptr, VarKind::Type, 8, 8, true));
    }
    Int16FixedTypeVar::Int16FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("Int16")), IntType::get_i16())
    {
        assume_constraint_holds__override_fixed_to_init(new IntConstraint(nullptr, VarKind::Type, 16, 16, true));
    }
    Int32FixedTypeVar::Int32FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("Int32")), IntType::get_i32())
    {
        assume_constraint_holds__override_fixed_to_init(new IntConstraint(nullptr, VarKind::Type, 32, 32, true));
    }
    Int64FixedTypeVar::Int64FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("Int64")), IntType::get_i64())
    {
        assume_constraint_holds__override_fixed_to_init(new IntConstraint(nullptr, VarKind::Type, 64, 64, true));
    }
    Int128FixedTypeVar::Int128FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("Int128")), IntType::get_i128())
    {
        assume_constraint_holds__override_fixed_to_init(new IntConstraint(nullptr, VarKind::Type, 128, 128, true));
    }

    UInt1FixedTypeVar::UInt1FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("UInt1")), IntType::get_u8())
    {
        assume_constraint_holds__override_fixed_to_init(new IntConstraint(nullptr, VarKind::Type, 1, 1, false));
    }
    UInt8FixedTypeVar::UInt8FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("UInt8")), IntType::get_u8())
    {
        assume_constraint_holds__override_fixed_to_init(new IntConstraint(nullptr, VarKind::Type, 8, 8, false));
    }
    UInt16FixedTypeVar::UInt16FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("UInt16")), IntType::get_u16())
    {
        assume_constraint_holds__override_fixed_to_init(new IntConstraint(nullptr, VarKind::Type, 16, 16, false));
    }
    UInt32FixedTypeVar::UInt32FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("UInt32")), IntType::get_u32())
    {
        assume_constraint_holds__override_fixed_to_init(new IntConstraint(nullptr, VarKind::Type, 32, 32, false));
    }
    UInt64FixedTypeVar::UInt64FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("UInt64")), IntType::get_u64())
    {
        assume_constraint_holds__override_fixed_to_init(new IntConstraint(nullptr, VarKind::Type, 64, 64, false));
    }
    UInt128FixedTypeVar::UInt128FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("UInt128")), IntType::get_u128())
    {
        assume_constraint_holds__override_fixed_to_init(new IntConstraint(nullptr, VarKind::Type, 128, 128, false));
    }

    Float16FixedTypeVar::Float16FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("Float16")), FloatType::get_f16())
    {
        assume_constraint_holds__override_fixed_to_init(new FloatConstraint(nullptr, VarKind::Type, 16, 16));
    }
    Float32FixedTypeVar::Float32FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("Float32")), FloatType::get_f32())
    {
        assume_constraint_holds__override_fixed_to_init(new FloatConstraint(nullptr, VarKind::Type, 32, 32));
    }
    Float64FixedTypeVar::Float64FixedTypeVar()
    :   FixedTypeVar(std::move(std::string("Float64")), FloatType::get_f32())
    {
        assume_constraint_holds__override_fixed_to_init(new FloatConstraint(nullptr, VarKind::Type, 64, 64));
    }
    
    //
    // Constant classes:
    //
    // todo: implement constant Relations for these constraints to be applied from.

    NumberFixedClassVar::NumberFixedClassVar()
    :   FixedClassVar(std::move(std::string("FixedClass:Number")))
    {
        // Int?
        assume_constraint_holds__override_fixed_to_init(new IntConstraint(nullptr, VarKind::Class, 0, 0, true));

        // UInt?
        assume_constraint_holds__override_fixed_to_init(new IntConstraint(nullptr, VarKind::Class, 0, 0, false));

        // Float?
        assume_constraint_holds__override_fixed_to_init(new FloatConstraint(nullptr, VarKind::Class, 0, 0));
    }
    SignedIntFixedClassVar::SignedIntFixedClassVar()
    :   FixedClassVar(std::move(std::string("FixedClass:SignedInt")))
    {
        assume_constraint_holds__override_fixed_to_init(new IntConstraint(nullptr, VarKind::Class, 0, 0, true));
    }
    UnsignedIntFixedClassVar::UnsignedIntFixedClassVar()
    :   FixedClassVar(std::move(std::string("FixedClass:UnsignedInt")))
    {
        assume_constraint_holds__override_fixed_to_init(new IntConstraint(nullptr, VarKind::Class, 0, 0, false));
    }
    FloatFixedClassVar::FloatFixedClassVar()
    :   FixedClassVar(std::move(std::string("FixedClass:Float")))
    {
        assume_constraint_holds__override_fixed_to_init(new FloatConstraint(nullptr, VarKind::Class, 0, 0));
    }
    
}