#ifndef INCLUDED_PDM_TYPER_VAR_HH
#define INCLUDED_PDM_TYPER_VAR_HH

#include <vector>

#include "type_soln.hh"
#include "type_constraint.hh"

namespace pdm::typer {
    class Typer;
}
namespace pdm::ast {
    class Node;
}

namespace pdm::typer {

    class Var;
    class TypeVar;
    class ClassVar;

    enum class VarKind {
        Type,
        Class
    };
    class Var {
      private:
        std::vector<TypeConstraint*> m_assumed_constraints;
        std::vector<Var*>            m_assumed_subclasses;
        std::vector<Var*>            m_assumed_superclasses;
        ast::Node*                   m_client_ast_node;
        VarKind                      m_var_kind;

      protected:
        Var(ast::Node* client_ast_node, VarKind var_kind)
        : m_assumed_constraints(),
          m_assumed_subclasses(),
          m_assumed_superclasses(),
          m_client_ast_node(client_ast_node),
          m_var_kind(var_kind) {}

      // public getters:
      public:
        VarKind var_kind() const {
            return m_var_kind;
        }
        ast::Node* client_ast_node() const {
            return m_client_ast_node;
        }
        std::vector<TypeConstraint*> const& assumed_constraints() {
            return m_assumed_constraints;
        }
        std::vector<Var*> const& assumed_subclasses() {
            return m_assumed_subclasses;
        }
        std::vector<Var*> const& assumed_superclasses() {
            return m_assumed_superclasses;
        }

      
      // solving interface:
      protected:
        void assume_var_constraint(TypeConstraint* constraint);
        void assume_var_subclass_of(Var* var);
        void assume_var_superclass_of(Var* var);

        void test_var_constraint(TypeConstraint* constraint);
        void test_var_subclass_of(Var* var);
        void test_var_superclass_of(Var* var);
    };

    class TypeVar: public Var {
      private:
        TypeSoln* m_soln_newest;
        bool      m_soln_fixed;

      public:
        TypeVar(ast::Node* client_ast_node, TypeSoln* opt_fixed_soln)
        : Var(client_ast_node, VarKind::Type),
          m_soln_newest(opt_fixed_soln),
          m_soln_fixed(opt_fixed_soln != nullptr) {}

      // public getters:
      public:
        TypeSoln* soln_newest() const {
            return m_soln_newest;
        }
        bool soln_fixed() const {
            return m_soln_fixed;
        }

      // solving interface:
      public:
        void assume_constraint(TypeConstraint* constraint);
        void assume_subtype_of(TypeVar* supertype_tv);
        void assume_supertype_of(TypeVar* subtype_tv);

        void test_constraint(TypeConstraint* constraint);
        void test_subtype_of(TypeVar* supertype_tv);
        void test_supertype_of(TypeVar* subtype_tv);
    };

    class ClassVar: public Var {
      public:
        ClassVar(ast::Node* client_ast_node)
        : Var(client_ast_node, VarKind::Class) {}

      public:
        void assume_constraint(TypeConstraint* constraint);
        void assume_subclass_of(ClassVar* superclass_cv);
        void assume_superclass_of(ClassVar* subclass_cv);

        void test_constraint(TypeConstraint* constraint);
        void test_subclass_of(ClassVar* superclass_cv);
        void test_superclass_of(ClassVar* subclass_cv);
    };

}   // namespace pdm::typer

#endif  // INCLUDED_PDM_TYPER_VAR_HH