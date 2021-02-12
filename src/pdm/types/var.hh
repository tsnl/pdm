#ifndef INCLUDED_PDM_TYPES_VAR_HH
#define INCLUDED_PDM_TYPES_VAR_HH

#include <vector>
#include <string>

#include "pdm/ast/arg/targ.hh"
#include "pdm/printer/printer.hh"

#include "type.hh"
#include "var_archetype.hh"
#include "typeop_result.hh"
#include "solve_result.hh"
#include "var_invariant.hh"
#include "kdvs.hh"

namespace pdm::types {
    class Manager;

    class Var;
    class TypeVar;
    class ClassVar;
    class TemplateVar_RetValue;
    class TemplateVar_RetType;
    class TemplateVar_RetClass;

    class Relation;
    class VarInvariant;
}
namespace pdm::ast {
    class Node;
}

namespace pdm::types {

    // A 'Var' is a bag of invariants that identifies a type, typeclass, or specific value.
    // A value is in a Var if it satisfies all invariants.
    // - each Var only has kd-invariants of one kind <=> each Var has exactly one kind.
    // - no Var (even typeclass) may span kinds.
    class Var {
      public:
        struct Edge {
            Var* var;
            bool is_induced_by_solver;
        };

      private:
        std::string m_name;
        ast::Node* m_opt_client_ast_node;
        VarArchetype m_var_archetype;

        std::vector<KindIndependentVarInvariant*> m_assumed_common_invariants;
        std::vector<KindDependentInvariant*> m_assumed_kind_dependent_invariants;
        std::vector<KindDependentInvariant*> m_invalid_assumed_kind_dependent_invariants;
        std::vector<IsNumberVarInvariant*> m_opt_force_number_invariants;
        Kind m_assumed_kind;
        std::vector<Edge> m_assumed_sub_var_edges;
        std::vector<Edge> m_assumed_super_var_edges;
        size_t m_sp1_checked_sub_var_count;
        size_t m_sp1_checked_super_var_count;
        size_t m_sp2_last_flushed_sub_var_count;
        size_t m_sp2_last_flushed_super_var_count;
        size_t m_sp2_last_flushed_kd_invariant_count;
        KindDependentVarSolver* m_kdvs;

        // for each solution iter, we cache the previous iter's result:
        SolveResult m_initial_solve_iter_result;
        SolveResult m_prev_solve_iter_result;

      // the solution:
      protected:
        Type* m_opt_type_soln;
        FinishResult m_finish_result;

      // constructor/dtor:
      protected:
        Var(std::string&& name, ast::Node* opt_client_ast_node, VarArchetype var_kind,
            SolveResult initial_solve_iter_result);

        virtual ~Var() = default;

      // public getters:
      public:
        [[nodiscard]] std::string const& name() const;
        [[nodiscard]] VarArchetype var_archetype() const;
        [[nodiscard]] ast::Node* opt_client_ast_node() const;
        [[nodiscard]] std::vector<KindIndependentVarInvariant*> const& assumed_common_invariants() const;
        [[nodiscard]] std::vector<KindDependentInvariant*> const& assumed_kind_dependent_invariants() const;
        [[nodiscard]] std::vector<Edge> const& assumed_sub_var_edges() const;
        [[nodiscard]] std::vector<Edge> const& assumed_super_var_edges() const;
        [[nodiscard]] bool is_constant() const;

      // Assuming: setting up type invariants.
      // - assume updates the IntervalSet representation
      // - solve (called after all 'assume')
      public:
        SolveResult assume_invariant_holds(VarInvariant* invariant);
        SolveResult assume_invariant_holds_overwrite_fixed(VarInvariant* invariant);
        SolveResult equals_by_induction(Var* var);
        SolveResult sub_var_by_induction(Var* var);
      private:
        SolveResult assume_invariant_holds_impl(VarInvariant* invariant, bool override_fixed);

      // Solving:
      public:
        SolveResult solve_iter();

      // Accessing available solution:
      public:
        [[nodiscard]] Type* get_type_soln();

      private:
        SolveResult solve_iter_impl();
        SolveResult solve_iter_phase1();
        static Kind get_kind_from_edges(std::vector<Var::Edge> const& edges);
        SolveResult solve_iter_phase2();
        bool finish();
        bool finish_impl();

      private:
        static SolveResult help_assume_sub_var(Var* sub_var, Var* super_var, bool is_second_order_invariant);

      // debug printing:
      public:
        void print(printer::Printer& p) const;
        void print_title(printer::Printer& p) const;
      private:
        void help_print_assumed_kind_bitset(printer::Printer& p) const;
        void help_print_assumed_common_invariants(printer::Printer& p) const;
        void help_print_assumed_kind_dependent_invariants(printer::Printer& p) const;
        void help_print_assumed_sub_vars(printer::Printer& p) const;
        void help_print_assumed_super_vars(printer::Printer& p) const;
        void help_print_opt_client_ast_node(printer::Printer& p) const;
        void help_print_kdvs(printer::Printer& p) const;
        void help_print_soln(printer::Printer& p) const;
    };

    inline std::string const& Var::name() const {
        return m_name;
    }
    inline VarArchetype Var::var_archetype() const {
        return m_var_archetype;
    }
    inline ast::Node* Var::opt_client_ast_node() const {
        return m_opt_client_ast_node;
    }
    inline std::vector<KindIndependentVarInvariant*> const& Var::assumed_common_invariants() const {
        return m_assumed_common_invariants;
    }
    inline std::vector<KindDependentInvariant*> const& Var::assumed_kind_dependent_invariants() const {
        return m_assumed_kind_dependent_invariants;
    }
    inline std::vector<Var::Edge> const& Var::assumed_sub_var_edges() const {
        return m_assumed_sub_var_edges;
    }
    inline std::vector<Var::Edge> const& Var::assumed_super_var_edges() const {
        return m_assumed_super_var_edges;
    }
    inline bool Var::is_constant() const {
        return m_initial_solve_iter_result == SolveResult::NoChange;
    }

    // typevar:
    enum class TypeVarSolnBill {
        Fixed,          // do not solve, use provided solution
        Monotype        // solve for a unique solution
    };
    class TypeVar: public Var {
      private:
        Type*           m_newest_soln;
        TypeVarSolnBill m_soln_bill;

      protected:
        inline TypeVar(std::string&& name, Type* opt_fixed_soln, ast::Node* opt_client_ast_node, TypeVarSolnBill soln_bill);

      private:
        static SolveResult initial_sp2_result_for_soln_bill(TypeVarSolnBill soln_bill);

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
    };
    inline TypeVar::TypeVar(std::string&& name, Type* opt_fixed_soln, ast::Node* opt_client_ast_node, TypeVarSolnBill soln_bill)
    :   Var(std::move(name), opt_client_ast_node, VarArchetype::Type, initial_sp2_result_for_soln_bill(soln_bill)),
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
        inline ClassVar(std::string&& name, ast::Node* client_ast_node, SolveResult sp2_result);
    };
    inline ClassVar::ClassVar(std::string&& name, ast::Node* client_ast_node, SolveResult sp2_result)
    :   Var(std::move(name), client_ast_node, VarArchetype::Class, sp2_result)
    {}

    class UnknownClassVar: public ClassVar {
      public:
        inline UnknownClassVar(std::string&& name, ast::Node* client_ast_node);
    };
    inline UnknownClassVar::UnknownClassVar(std::string&& name, ast::Node* client_ast_node)
    :   ClassVar(std::move(name), client_ast_node, SolveResult::UpdatedOrFresh)
    {}

    class FixedClassVar: public ClassVar {
      public:
        inline FixedClassVar(std::string&& name);
    };
    inline FixedClassVar::FixedClassVar(std::string&& name)
    :   ClassVar(std::move(name), nullptr, SolveResult::NoChange)
    {}
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

    //
    // templates:
    //
    
    class TemplateVar: public Var {
      private:
        std::vector<TemplateFormalArg> m_formal_args;
      protected:
        inline TemplateVar(std::string&& name, ast::Node* client_ast_node, VarArchetype var_kind);

      public:
        std::vector<TemplateFormalArg> const& formal_args() const;
    };
    inline TemplateVar::TemplateVar(std::string&& name, ast::Node* client_ast_node, VarArchetype var_kind)
    :   Var(std::move(name), client_ast_node, var_kind, SolveResult::UpdatedOrFresh),
        m_formal_args()
    {}
    inline std::vector<TemplateFormalArg> const& TemplateVar::formal_args() const {
        return m_formal_args;
    }
    
    class TemplateVar_RetValue: public TemplateVar {
      public:
        inline TemplateVar_RetValue(std::string&& name, ast::Node* client_ast_node);
    };
    inline TemplateVar_RetValue::TemplateVar_RetValue(std::string&& name, ast::Node* client_ast_node)
    :   TemplateVar(std::move(name), client_ast_node, VarArchetype::Template_RetValue)
    {}

    class TemplateVar_RetType: public TemplateVar {
      public:
        inline TemplateVar_RetType(std::string&& name, ast::Node* client_ast_node);
    };
    inline TemplateVar_RetType::TemplateVar_RetType(std::string&& name, ast::Node* client_ast_node)
    :   TemplateVar(std::move(name), client_ast_node, VarArchetype::Template_RetType)
    {}
    
    class TemplateVar_RetClass: public TemplateVar {
      public:
        inline TemplateVar_RetClass(std::string&& name, ast::Node* client_ast_node);
    };
    inline TemplateVar_RetClass::TemplateVar_RetClass(std::string&& name, ast::Node* client_ast_node)
    :   TemplateVar(std::move(name), client_ast_node, VarArchetype::Template_RetClass)
    {}

}   // namespace pdm::typer

#endif  // INCLUDED_PDM_TYPES_VAR_HH