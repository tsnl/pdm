#ifndef INCLUDED_PDM_TYPES_VAR_HH
#define INCLUDED_PDM_TYPES_VAR_HH

#include <vector>
#include <string>

#include "pdm/ast/arg/targ.hh"
#include "pdm/printer/printer.hh"

#include "type.hh"
#include "var_kind.hh"
#include "typeop_result.hh"
#include "solving.hh"

#include "interval.hh"

namespace pdm::types {
    class Manager;

    class Var;
    class TypeVar;
    class ClassVar;
    class ValueTemplateVar;
    class TypeTemplateVar;
    class ClassTemplateVar;

    class Relation;
    class Constraint;
}
namespace pdm::ast {
    class Node;
}

namespace pdm::types {

    // A 'Var' is a bag of constraints that identifies a set of types.
    // All types in this set satisfy all assumed constraints.
    // All typing operations boil down to supervar and subvar relationships
    // between Vars and easily unifiable IntervalSets
    // - a type T is in a class C              <=> T \subvar C
    // - a type T is a subtype of a type U     <=> T \subvar U
    // - a class C is a subclass of class D    <=> C \subvar D
    // - a template T is equal to a template U <=> T \subvar U and U \subvar T
    // * use 'VarKind' to determine if a Var is a type, class, or template.
    // * 'equality' is just subtype+supertype or subclass+superclass
    // Once constraints are stored, can later query
    class Var {
      private:
        std::string m_name;
        ast::Node* m_opt_client_ast_node;
        VarKind m_var_kind;

        // all applied constraints stored as common or kind-dependent:
        std::vector<CommonConstraint*> m_assumed_common_constraints;
        std::vector<KindDependentConstraint*> m_assumed_kind_dependent_constraints;

        // common constraints broken into a bitset, subvars, and supervars:
        u64 m_assumed_kind_bitset;
        std::vector<Var*> m_assumed_subvars;
        std::vector<Var*> m_assumed_supervars;

        // after checking all supervar/subvar bitsets, kind-dependent constraints are broken
        // into an 'IntervalSet' that is then iteratively expanded.
        // Finally, the IntervalSet can be checked for validity based on VarKind.
        IntervalSet m_assumed_interval_set;

        // for each solution iter, we cache the previous iter's result:
        SolvePhase2_Result m_initial_solve_iter_result;
        SolvePhase2_Result m_prev_solve_iter_result;

      protected:
        Var(std::string&& name, ast::Node* opt_client_ast_node, VarKind var_kind, SolvePhase2_Result default_solve_iter_result);

        virtual ~Var() {}

      // public getters:
      public:
        std::string const& name() const;
        VarKind var_kind() const;
        ast::Node* opt_client_ast_node() const;
        std::vector<CommonConstraint*> const& assumed_common_constraints() const;
        std::vector<KindDependentConstraint*> const& assumed_kind_dependent_constraints() const;
        std::vector<Var*> const& assumed_subvars() const;
        std::vector<Var*> const& assumed_supervars() const;
        bool is_constant() const;

      // Assuming: setting up type constraints.
      // - assume updates the IntervalSet representation
      // - solve (called after all 'assume')
      public:
        AssumeOpResult assume_constraint_holds(Constraint* constraint);
        AssumeOpResult assume_constraint_holds__override_fixed_to_init(Constraint* constraint);
      private:
        AssumeOpResult assume_constraint_holds_impl(Constraint* constraint, bool override_fixed);

      // Solving: Phase 1 (SP1)
      public:
        SolvePhase1_Result solve_phase1();
      private:
        SolvePhase1_Result help_check_phase1_type_bitset_for_mixed_kinds();

      // Solving: Phase 2 (SP2)
      public:
        SolvePhase2_Result solve_phase2_iter();
      private:
        SolvePhase2_Result solve_phase2_iter_impl();

      public:
        TestOpResult test(Constraint* constraint);

      private:
        static void help_assume_subvar(Var* subvar, Var* supervar);

      // debug printing:
      public:
        void print(printer::Printer& p) const;
      private:
        void help_print_title(printer::Printer& p) const;
        void help_print_assumed_kind_bitset(printer::Printer& p) const;
        void help_print_assumed_common_constraints(printer::Printer& p) const;
        void help_print_assumed_kind_dependent_constraints(printer::Printer& p) const;
        void help_print_assumed_subvars(printer::Printer& p) const;
        void help_print_assumed_supervars(printer::Printer& p) const;
        void help_print_opt_client_ast_node(printer::Printer& p) const;
    };
    inline Var::Var(std::string&& name, ast::Node* opt_client_ast_node, VarKind var_kind, SolvePhase2_Result initial_solve_iter_result)
    :   m_name(std::move(name)),
        m_opt_client_ast_node(opt_client_ast_node),
        m_var_kind(var_kind),
        m_assumed_common_constraints(),
        m_assumed_kind_dependent_constraints(),
        m_assumed_kind_bitset(0),
        m_assumed_subvars(),
        m_assumed_supervars(),
        m_assumed_interval_set(),
        m_initial_solve_iter_result(initial_solve_iter_result),
        m_prev_solve_iter_result(initial_solve_iter_result)
    {}
    inline std::string const& Var::name() const {
        return m_name;
    }
    inline VarKind Var::var_kind() const {
        return m_var_kind;
    }
    inline ast::Node* Var::opt_client_ast_node() const {
        return m_opt_client_ast_node;
    }
    inline std::vector<CommonConstraint*> const& Var::assumed_common_constraints() const {
        return m_assumed_common_constraints;
    }
    inline std::vector<KindDependentConstraint*> const& Var::assumed_kind_dependent_constraints() const {
        return m_assumed_kind_dependent_constraints;
    }
    inline std::vector<Var*> const& Var::assumed_subvars() const {
        return m_assumed_subvars;
    }
    inline std::vector<Var*> const& Var::assumed_supervars() const {
        return m_assumed_supervars;
    }
    inline bool Var::is_constant() const {
        return m_initial_solve_iter_result == SolvePhase2_Result::AtFixedPoint;
    }

    // typevar:
    enum class TypeVarSolnBill {
        Fixed,          // do not solve, use provided solution
        ProxyForMany,   // do not solve, accepts multiple solutions (really a class with a type interface)
        Monotype        // solve for a unique solution
    };
    class TypeVar: public Var {
      private:
        Type*           m_newest_soln;
        TypeVarSolnBill m_soln_bill;

      protected:
        inline TypeVar(std::string&& name, Type* opt_fixed_soln, ast::Node* opt_client_ast_node, TypeVarSolnBill soln_bill);

      private:
        static SolvePhase2_Result initial_sp2_result_for_soln_bill(TypeVarSolnBill soln_bill);

      // public getters:
      public:
        Type* newest_soln() const {
            return m_newest_soln;
        }
        TypeVarSolnBill soln_bill() const {
            return m_soln_bill;
        }
        bool is_soln_fixed() const {
            return soln_bill() == TypeVarSolnBill::Fixed;
        }
        bool is_proxy_for_many() const {
            return soln_bill() == TypeVarSolnBill::ProxyForMany;
        }
    };
    inline TypeVar::TypeVar(std::string&& name, Type* opt_fixed_soln, ast::Node* opt_client_ast_node, TypeVarSolnBill soln_bill)
    :   Var(std::move(name), opt_client_ast_node, VarKind::Type, initial_sp2_result_for_soln_bill(soln_bill)),
        m_newest_soln(opt_fixed_soln),
        m_soln_bill(soln_bill)
    {
        if (this->soln_bill() == TypeVarSolnBill::Fixed) {
            assert(opt_fixed_soln != nullptr && "Cannot create 'Fixed' TypeVar with null solution.");
        }
    }

    // fixed:
    class FixedTypeVar: public TypeVar {
      protected:
        inline FixedTypeVar(std::string&& name, Type* fixed_soln);
    };
    struct VoidFixedTypeVar: public FixedTypeVar { VoidFixedTypeVar(); };
    struct StringFixedTypeVar: public FixedTypeVar { StringFixedTypeVar(); };
    struct Int8FixedTypeVar: public FixedTypeVar { Int8FixedTypeVar(); };
    struct Int16FixedTypeVar: public FixedTypeVar { Int16FixedTypeVar(); };
    struct Int32FixedTypeVar: public FixedTypeVar { Int32FixedTypeVar(); };
    struct Int64FixedTypeVar: public FixedTypeVar { Int64FixedTypeVar(); };
    struct Int128FixedTypeVar: public FixedTypeVar { Int128FixedTypeVar(); };
    struct UInt1FixedTypeVar: public FixedTypeVar { UInt1FixedTypeVar(); };
    struct UInt8FixedTypeVar: public FixedTypeVar { UInt8FixedTypeVar(); };
    struct UInt16FixedTypeVar: public FixedTypeVar { UInt16FixedTypeVar(); };
    struct UInt32FixedTypeVar: public FixedTypeVar { UInt32FixedTypeVar(); };
    struct UInt64FixedTypeVar: public FixedTypeVar { UInt64FixedTypeVar(); };
    struct UInt128FixedTypeVar: public FixedTypeVar { UInt128FixedTypeVar(); };
    struct Float16FixedTypeVar: public FixedTypeVar { Float16FixedTypeVar(); };
    struct Float32FixedTypeVar: public FixedTypeVar { Float32FixedTypeVar(); };
    struct Float64FixedTypeVar: public FixedTypeVar { Float64FixedTypeVar(); };

    // proxy:
    class ProxyTypeVar: public TypeVar {
      public:
        inline ProxyTypeVar(std::string&& name, ast::Node* client_ast_node);
    };
    inline ProxyTypeVar::ProxyTypeVar(std::string&& name, ast::Node* client_ast_node)
    :   TypeVar(std::move(name), nullptr, client_ast_node, TypeVarSolnBill::ProxyForMany)
    {}

    // monotype:
    class MonotypeTypeVar: public TypeVar {
      public:
        inline MonotypeTypeVar(std::string&& name, ast::Node* client_ast_node);
    };
    inline MonotypeTypeVar::MonotypeTypeVar(std::string&& name, ast::Node* client_ast_node)
    :   TypeVar(std::move(name), nullptr, client_ast_node, TypeVarSolnBill::Monotype)
    {}

    // classvar:
    enum class ClassVarSolnBill {
        Fixed,
        Unknown
    };
    class ClassVar: public Var {
      protected:
        inline ClassVar(std::string&& name, ast::Node* client_ast_node, SolvePhase2_Result sp2_result);

      public:
        void assume_constraint(Constraint* constraint);
        void assume_subclass_of(ClassVar* superclass_cv);
        void assume_superclass_of(ClassVar* subclass_cv);

        void test_constraint(Constraint* constraint);
        void test_subclass_of(ClassVar* superclass_cv);
        void test_superclass_of(ClassVar* subclass_cv);
    };
    inline ClassVar::ClassVar(std::string&& name, ast::Node* client_ast_node, SolvePhase2_Result sp2_result)
    :   Var(std::move(name), client_ast_node, VarKind::Class, sp2_result)
    {}

    class UnknownClassVar: public ClassVar {
      public:
        inline UnknownClassVar(std::string&& name, ast::Node* client_ast_node);
    };
    inline UnknownClassVar::UnknownClassVar(std::string&& name, ast::Node* client_ast_node)
    :   ClassVar(std::move(name), client_ast_node, SolvePhase2_Result::UpdatedOrFresh)
    {}

    class FixedClassVar: public ClassVar {
      public:
        inline FixedClassVar(std::string&& name);
    };
    inline FixedClassVar::FixedClassVar(std::string&& name)
    :   ClassVar(std::move(name), nullptr, SolvePhase2_Result::AtFixedPoint)
    {}
    struct NumberFixedClassVar: public FixedClassVar { NumberFixedClassVar(); };
    struct SignedIntFixedClassVar: public FixedClassVar { SignedIntFixedClassVar(); };
    struct UnsignedIntFixedClassVar: public FixedClassVar { UnsignedIntFixedClassVar(); };
    struct FloatFixedClassVar: public FixedClassVar { FloatFixedClassVar(); };
    
    // templates helpers:
    class TemplateFormalArg {
      private:
        ast::TArgKind m_targ_kind;

      protected:
        TemplateFormalArg(ast::TArgKind targ_kind);

      public:
        ast::TArgKind targ_kind() const;
    };
    class TemplateValueFormalArg: public TemplateFormalArg {
      private:
        TypeVar* m_typeof_formal_tv;
      public:
        TemplateValueFormalArg(TypeVar* typeof_formal_tv);
      public:
        TypeVar* typeof_formal_tv() const;
    };
    class TemplateTypeFormalArg: public TemplateFormalArg {
      private:
        TypeVar*  m_proxy_formal_tv;
        ClassVar* m_classof_formal_cv;
      public:
        TemplateTypeFormalArg(TypeVar* proxy_formal_tv, ClassVar* classof_formal_cv);
      public:
        TypeVar* proxy_formal_tv() const;
        ClassVar* classof_formal_tv() const;
    };
    inline TemplateFormalArg::TemplateFormalArg(ast::TArgKind targ_kind)
    :   m_targ_kind(targ_kind)
    {}
    inline TemplateValueFormalArg::TemplateValueFormalArg(TypeVar* typeof_formal_tv)
    :   TemplateFormalArg(ast::TArgKind::Value),
        m_typeof_formal_tv(typeof_formal_tv)
    {}
    inline TemplateTypeFormalArg::TemplateTypeFormalArg(TypeVar* proxy_formal_tv, ClassVar* classof_formal_cv)
    :   TemplateFormalArg(ast::TArgKind::Value),
        m_proxy_formal_tv(proxy_formal_tv),
        m_classof_formal_cv(classof_formal_cv)
    {}
    inline ast::TArgKind TemplateFormalArg::targ_kind() const {
        return m_targ_kind;
    }
    inline TypeVar* TemplateValueFormalArg::typeof_formal_tv() const {
        return m_typeof_formal_tv;
    }
    inline TypeVar* TemplateTypeFormalArg::proxy_formal_tv() const {
        return m_proxy_formal_tv;
    }
    inline ClassVar* TemplateTypeFormalArg::classof_formal_tv() const {
        return m_classof_formal_cv;
    }

    // templates:
    class TemplateVar: public Var {
      private:
        std::vector<TemplateFormalArg> m_formal_args;
      protected:
        inline TemplateVar(std::string&& name, ast::Node* client_ast_node, VarKind var_kind);

      public:
        std::vector<TemplateFormalArg> const& formal_args() const;
    };
    class ValueTemplateVar: public TemplateVar {
      public:
        inline ValueTemplateVar(std::string&& name, ast::Node* client_ast_node);
    };
    class TypeTemplateVar: public TemplateVar {
      public:
        inline TypeTemplateVar(std::string&& name, ast::Node* client_ast_node);
    };
    class ClassTemplateVar: public TemplateVar {
      public:
        inline ClassTemplateVar(std::string&& name, ast::Node* client_ast_node);
    };

    inline TemplateVar::TemplateVar(std::string&& name, ast::Node* client_ast_node, VarKind var_kind)
    :   Var(std::move(name), client_ast_node, var_kind, SolvePhase2_Result::UpdatedOrFresh),
        m_formal_args()
    {}

    inline std::vector<TemplateFormalArg> const& TemplateVar::formal_args() const {
        return m_formal_args;
    }
    inline ValueTemplateVar::ValueTemplateVar(std::string&& name, ast::Node* client_ast_node)
    :   TemplateVar(std::move(name), client_ast_node, VarKind::ValueTemplate)
    {}
    inline TypeTemplateVar::TypeTemplateVar(std::string&& name, ast::Node* client_ast_node)
    :   TemplateVar(std::move(name), client_ast_node, VarKind::TypeTemplate)
    {}
    inline ClassTemplateVar::ClassTemplateVar(std::string&& name, ast::Node* client_ast_node)
    :   TemplateVar(std::move(name), client_ast_node, VarKind::ClassTemplate)
    {}

}   // namespace pdm::typer

#endif  // INCLUDED_PDM_TYPES_VAR_HH