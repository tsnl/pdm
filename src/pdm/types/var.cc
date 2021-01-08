#include "var.hh"

#include <string>

#include "pdm/ast/node.hh"
#include "pdm/printer/printer.hh"

#include "var_kind.hh"
#include "constraint.hh"


namespace pdm::types {

    AssumeOpResult Var::assume(Constraint* constraint) {
        // Kind constraints update the assumed_kind_bitset:
        KindConstraint* kind_constraint = dynamic_cast<KindConstraint*>(constraint);
        if (kind_constraint != nullptr) {
            m_assumed_kind_constraints.push_back(kind_constraint);
            m_assumed_kind_bitset |= kind_constraint->allowed_type_kinds_bitset();
            return AssumeOpResult::Applied;
        } 

        // Subtype, subclass, class membership boil down to subvar:
        {   // subtype:
            SubtypeOfConstraint* subtype_of_constraint = dynamic_cast<SubtypeOfConstraint*>(constraint);
            if (subtype_of_constraint != nullptr) {
                help_assume_subvar(this, subtype_of_constraint->supertype_tv());
                return AssumeOpResult::Applied;
            }
        }
        {   // subclass:
            SubclassOfConstraint* subclass_of_constraint = dynamic_cast<SubclassOfConstraint*>(constraint);
            if (subclass_of_constraint != nullptr) {
                help_assume_subvar(this, subclass_of_constraint->superclass_cv());
                return AssumeOpResult::Applied;
            }
        }
        {   // class instanceship:
            ClassOfConstraint* classof_constraint = dynamic_cast<ClassOfConstraint*>(constraint);
            if (classof_constraint != nullptr) {
                help_assume_subvar(classof_constraint->member_tv(), this);
                return AssumeOpResult::Applied;
            }
        }

        {   // All kind-dependent constraints go into a list for later.
            KindDependentConstraint* kd_constraint = dynamic_cast<KindDependentConstraint*>(constraint);
            if (kd_constraint != nullptr) {
                m_assumed_kind_dependent_constraints.push_back(kd_constraint);
                return AssumeOpResult::Applied;
            }
        }

        return AssumeOpResult::ErrorOccurred;
    }
    TestOpResult Var::test(Constraint* constraint) {
        // todo: implement me!
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
            help_print_assumed_kind_constraints(p);
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
            if (m_assumed_kind_bitset & static_cast<u64>(TypeKind::Func))   { p.print_cstr("| Func "); }
        } else {
            p.print_cstr(": None");
        }
    }
    void Var::help_print_assumed_kind_constraints(printer::Printer& p) const {
        p.print_cstr("assume KindConstraints:");
        if (assumed_kind_constraints().empty()) {
            p.print_cstr(" None");
        } else {
            for (Constraint* constraint: assumed_kind_constraints()) {
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
}