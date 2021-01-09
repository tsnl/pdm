#ifndef INCLUDED_PDM_TYPES_VAR_HH
#define INCLUDED_PDM_TYPES_VAR_HH

#include <vector>
#include <string>

#include "pdm/ast/arg/targ.hh"
#include "pdm/printer/printer.hh"

#include "type.hh"
#include "var_kind.hh"
#include "typeop_result.hh"

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
        friend Relation;

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
        SolveIterResult m_zeroth_solve_iter_result;
        SolveIterResult m_prev_solve_iter_result;

      protected:
        Var(std::string&& name, ast::Node* opt_client_ast_node, VarKind var_kind, SolveIterResult default_solve_iter_result);

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

      // Relation interface
      // - assume updates the IntervalSet representation
      // - solve (called after all 'assume')
      public:
        AssumeOpResult assume(Constraint* constraint);
        SolveIterResult solve_iter();
      private:
        SolveIterResult help_solve_iter();

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
    inline Var::Var(std::string&& name, ast::Node* opt_client_ast_node, VarKind var_kind, SolveIterResult zeroth_solve_iter_result)
    :   m_name(std::move(name)),
        m_opt_client_ast_node(opt_client_ast_node),
        m_var_kind(var_kind),
        m_assumed_common_constraints(),
        m_assumed_kind_dependent_constraints(),
        m_assumed_kind_bitset(0),
        m_assumed_subvars(),
        m_assumed_supervars(),
        m_assumed_interval_set(),
        m_zeroth_solve_iter_result(zeroth_solve_iter_result),
        m_prev_solve_iter_result(zeroth_solve_iter_result)
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

      public:
        TypeVar(std::string&& name, Type* opt_fixed_soln, ast::Node* opt_client_ast_node, TypeVarSolnBill soln_bill);

      private:
        static SolveIterResult zeroth_solve_iter_result_for_soln_bill(TypeVarSolnBill soln_bill);

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

    inline
    TypeVar::TypeVar(std::string&& name, Type* opt_fixed_soln, ast::Node* opt_client_ast_node, TypeVarSolnBill soln_bill)
    :   Var(std::move(name), opt_client_ast_node, VarKind::Type, zeroth_solve_iter_result_for_soln_bill(soln_bill)),
        m_newest_soln(opt_fixed_soln),
        m_soln_bill(soln_bill) 
    {
        if (this->soln_bill() == TypeVarSolnBill::Fixed) {
            assert(opt_fixed_soln != nullptr && "Cannot create 'Fixed' TypeVar with null solution.");
        }
    }

    // classvar:
    class ClassVar: public Var {
      public:
        ClassVar(std::string&& name, ast::Node* client_ast_node)
        : Var(std::move(name), client_ast_node, VarKind::Class, SolveIterResult::UpdatedOrFresh) {}

      public:
        void assume_constraint(Constraint* constraint);
        void assume_subclass_of(ClassVar* superclass_cv);
        void assume_superclass_of(ClassVar* subclass_cv);

        void test_constraint(Constraint* constraint);
        void test_subclass_of(ClassVar* superclass_cv);
        void test_superclass_of(ClassVar* subclass_cv);
    };

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
        TemplateVar(std::string&& name, ast::Node* client_ast_node, VarKind var_kind);

      public:
        std::vector<TemplateFormalArg> const& formal_args() const;
    };
    class ValueTemplateVar: public TemplateVar {
      public:
        ValueTemplateVar(std::string&& name, ast::Node* client_ast_node);
    };
    class TypeTemplateVar: public TemplateVar {
      public:
        TypeTemplateVar(std::string&& name, ast::Node* client_ast_node);
    };
    class ClassTemplateVar: public TemplateVar {
      public:
        ClassTemplateVar(std::string&& name, ast::Node* client_ast_node);
    };

    inline
    TemplateVar::TemplateVar(std::string&& name, ast::Node* client_ast_node, VarKind var_kind)
    :   Var(std::move(name), client_ast_node, var_kind, SolveIterResult::UpdatedOrFresh),
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