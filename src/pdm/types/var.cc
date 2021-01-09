#include "var.hh"

#include <string>
#include <iostream>

#include "pdm/ast/node.hh"
#include "pdm/printer/printer.hh"

#include "var_kind.hh"
#include "constraint.hh"


namespace pdm::types {

    AssumeOpResult Var::assume(Constraint* constraint) {
        // if this constraint was not intended for a Var of this VarKind,
        // typer's meta-type error:
        if (var_kind() != constraint->domain_var_kind()) {
            return AssumeOpResult::ErrorOccurred;
        }

        // unless NotImplemented, AssumeOp will return 'Applied' from here.
        
        // if the zeroth solve iter is 'AtFixed', this is a constant type.
        if (m_zeroth_solve_iter_result == SolveIterResult::AtFixedPoint) {
            // just ignoring extra constraints on constants-- 
            // constants are constraint sinks upon propagation!
            return AssumeOpResult::Applied;
        }
        
        // if a common constraint, adding and applying immediately.
        CommonConstraint* common_constraint = nullptr;
        if ((common_constraint = dynamic_cast<CommonConstraint*>(constraint)) != nullptr) {
            m_assumed_common_constraints.push_back(common_constraint);

            // Kind constraints update the assumed_kind_bitset:
            KindConstraint* kind_constraint = dynamic_cast<KindConstraint*>(constraint);
            if (kind_constraint != nullptr) {
                m_assumed_common_constraints.push_back(kind_constraint);
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

            // All kind-dependent constraints go into a list for later.
            KindDependentConstraint* kd_constraint = dynamic_cast<KindDependentConstraint*>(constraint);
            if (kd_constraint != nullptr) {
                m_assumed_kind_dependent_constraints.push_back(kd_constraint);
                return AssumeOpResult::Applied;
            }

            // Unknown CommonConstraint kind...
            assert(0 && "Unknown CommonConstraint.");
        }

        // if a kind-dependent constraint, adding to a list and deferring for later.
        // also adding a kind-constraint corresponding to the assumed kind.
        KindDependentConstraint* kind_dependent_constraint = nullptr;
        if ((kind_dependent_constraint = dynamic_cast<KindDependentConstraint*>(constraint)) != nullptr) {
            // *sweats in bad memory management*
            AssumeOpResult result = assume(new KindConstraint(
                constraint->parent_relation(), 
                constraint->domain_var_kind(), 
                static_cast<u64>(kind_dependent_constraint->required_type_kind())
            ));
            
            // kind-dependent constraints deferred for later.
            m_assumed_kind_dependent_constraints.push_back(kind_dependent_constraint);

            // returning the result of just the kind application:
            return result;
        }

        return AssumeOpResult::ErrorOccurred;
    }

    SolveIterResult Var::solve_iter() {
        SolveIterResult iter_sir = help_solve_iter();
        m_prev_solve_iter_result = iter_sir;
        return iter_sir;
    }
    SolveIterResult Var::help_solve_iter() {
        if (m_prev_solve_iter_result == SolveIterResult::AtFixedPoint) {
            return SolveIterResult::AtFixedPoint;
        }
        if (m_prev_solve_iter_result == SolveIterResult::AtError) {
            return SolveIterResult::AtError;
        }
        
        assert(m_prev_solve_iter_result == SolveIterResult::UpdatedOrFresh);

        // todo: compare kind bitset against all subvars
        // todo: implement rest of `typing.dot`...

        std::cout << "NotImplemented: help_solve_iter" << std::endl;
        return SolveIterResult::AtError;
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
        p.print_cstr(":");

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
                p.print_cstr("- ");
                // todo: print constraint here
                p.print_newline();
            }
        }
    }
    void Var::help_print_assumed_kind_dependent_constraints(printer::Printer& p) const {
        p.print_cstr("assume KindDependentConstraints:");
        if (assumed_kind_dependent_constraints().empty()) {
            p.print_cstr(" None");
        } else {
            for (Constraint* constraint: assumed_kind_dependent_constraints()) {
                p.print_cstr("- ");
                // todo: print constraint here
                p.print_newline();
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
                p.print_cstr("- ");
                assumed_subvar->help_print_title(p);
                if (index+1 != m_assumed_subvars.size()) {
                    p.print_newline();
                }
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

    SolveIterResult TypeVar::zeroth_solve_iter_result_for_soln_bill(TypeVarSolnBill soln_bill) {
        switch (soln_bill) {
            case TypeVarSolnBill::Fixed: 
            {
                return SolveIterResult::AtFixedPoint;
            }
            case TypeVarSolnBill::Monotype:
            case TypeVarSolnBill::ProxyForMany:
            {
                return SolveIterResult::UpdatedOrFresh;
            }
        }
    }
}