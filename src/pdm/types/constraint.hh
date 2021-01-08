#ifndef INCLUDED_PDM_TYPES_TYPE_CONSTRAINT_HH
#define INCLUDED_PDM_TYPES_TYPE_CONSTRAINT_HH

#include "pdm/core/integer.hh"
#include "pdm/core/intern.hh"

#include "pdm/ast/arg/varg.hh"

#include "var_kind.hh"
#include "type_kind.hh"

//
// Forward Declarations:
//

namespace pdm::typer {
    class Rule;
}
namespace pdm::types {
    class TypeVar;
    class ClassVar;
}


//
// Implementation:
//

namespace pdm::types {
    
    // a constraint is a function mapping a **type** to **a boolean result.**
    // - Constraint.test(tv) checks if a constraint is true without altering the TV.
    // - if a constraint is 'assumed' on a Var, it means that all types in that set 
    class Constraint {
      private:
        typer::Rule* m_parent_rule;
        VarKind      m_domain_var_kind;

      protected:
        Constraint(typer::Rule* parent_rule, VarKind domain_var_kind);

      public:
        virtual bool test(TypeVar const* arg);
        virtual bool apply(TypeVar* arg);
    };
    inline Constraint::Constraint(typer::Rule* parent_rule, VarKind domain_var_kind)
    :   m_parent_rule(parent_rule),
        m_domain_var_kind(domain_var_kind) 
    {}

    //
    // Core constraints:
    //
    
    class KindConstraint: public Constraint {
      private:
        pdm::u64 m_allowed_type_kinds_bitset;

      public:
        KindConstraint(typer::Rule* parent_rule, VarKind domain_var_kind, pdm::u64 allowed_type_kinds_bitset);

      public:
        pdm::u64 allowed_type_kinds_bitset() const;
        bool type_kind_allowed(TypeKind type_kind) const;
    };
    inline pdm::u64 KindConstraint::allowed_type_kinds_bitset() const {
        return m_allowed_type_kinds_bitset;
    }
    inline bool KindConstraint::type_kind_allowed(TypeKind type_kind) const {
        return m_allowed_type_kinds_bitset & static_cast<pdm::u64>(type_kind);
    }

    class SubtypeOfConstraint: public Constraint {
      private:
        TypeVar* m_supertype_tv;

      public:
        SubtypeOfConstraint(typer::Rule* parent_rule, TypeVar* supertype_tv);

      public:
        TypeVar* supertype_tv() const {
            return m_supertype_tv;
        }
    };

    class SubclassOfConstraint: public Constraint {
      private:
        ClassVar* m_superclass_cv;
      
      public:
        SubclassOfConstraint(typer::Rule* parent_rule, ClassVar* superclass_cv);

      public:
        ClassVar* superclass_cv() const {
            return m_superclass_cv;
        }
    };

    class ClassOfConstraint: public Constraint {
      private:
        TypeVar* m_member_tv;

      public:
        ClassOfConstraint(typer::Rule* parent_rule, TypeVar* member_tv);

      public:
        TypeVar* member_tv() const {
            return m_member_tv;
        }
    };

    //
    // Kind-dependent constraints:
    //

    class KindDependentConstraint: public Constraint {
      private:
        TypeKind m_required_type_kind;

      protected:
        KindDependentConstraint(typer::Rule* parent_rule, VarKind domain_var_kind, TypeKind required_type_kind);
    };

    // void:
    class VoidConstraint: public KindDependentConstraint {
      public:
        VoidConstraint(typer::Rule* parent_rule, VarKind domain_var_kind);
    };

    // int:
    class IntConstraint: public KindDependentConstraint {
      public:
        IntConstraint(typer::Rule* parent_rule, VarKind domain_var_kind, int min_width = -1, int max_width = -1);
    };

    // float:
    class FloatConstraint: public KindDependentConstraint {
      public:
        FloatConstraint(typer::Rule* parent_rule, VarKind domain_var_kind, int min_width = -1, int max_width = -1);
    };
    
    // string:
    class StringConstraint: public KindDependentConstraint {
      public:
        StringConstraint(typer::Rule* parent_rule, VarKind domain_var_kind);
    };
    
    // tuple:
    class TupleConstraint: public KindDependentConstraint {
      public:
        TupleConstraint(typer::Rule* parent_rule, VarKind domain_var_kind);
    };
    class TupleWithFieldConstraint: public TupleConstraint {
      public:
        TupleWithFieldConstraint(typer::Rule* parent_rule, VarKind domain_var_kind, int index, TypeVar* field_tv);
    };
    
    // array:
    class ArrayConstraint: public KindDependentConstraint {
      public:
        ArrayConstraint(typer::Rule* parent_rule, VarKind domain_var_kind, TypeVar* field_tv);
    };
    
    // struct:
    class StructConstraint: public KindDependentConstraint {
      public:
        StructConstraint(typer::Rule* parent_rule, VarKind domain_var_kind);
    };
    class StructWithFieldConstraint: public StructConstraint {
      public:
        StructWithFieldConstraint(typer::Rule* parent_rule, VarKind domain_var_kind, intern::String field_name, TypeVar* field_tv);
    };

    // ref
    class RefConstraint: public KindDependentConstraint {
      public:
        RefConstraint(typer::Rule* parent_rule, VarKind domain_var_kind);
    };

    // func
    class FuncConstraint: public KindDependentConstraint {
      public:
        FuncConstraint(typer::Rule* parent_rule, VarKind domain_var_kind);
    };
    struct FuncConstraint_Arg {
        ast::VArgAccessSpec varg_access_spec; 
        TypeVar*            typeof_arg_tv;
    };
    class FormalSignatureFuncConstraint: public FuncConstraint {
      public:
        FormalSignatureFuncConstraint(
            typer::Rule* parent_rule, 
            VarKind domain_var_kind, 
            std::vector<FuncConstraint_Arg>&& formal_args_tvs,
            TypeVar* ret_tv
        );
    };
    class ActualSignatureFuncConstraint: public FuncConstraint {
      public:
        ActualSignatureFuncConstraint(
            typer::Rule* parent_rule, 
            VarKind domain_var_kind, 
            std::vector<FuncConstraint_Arg>&& actual_args_tvs,
            TypeVar* ret_tv
        );
    };

    // module
    class ModuleConstraint: public KindDependentConstraint {
      public:
        ModuleConstraint(typer::Rule* parent_rule, VarKind domain_var_kind);
    };
    class ModuleWithValueFieldConstraint: public ModuleConstraint {
      public:
        ModuleWithValueFieldConstraint(typer::Rule* parent_rule, VarKind domain_var_kind, intern::String field_name, TypeVar* typeof_field_tv);
    };
    class ModuleWithTypeFieldConstraint: public ModuleConstraint {
      public:
        ModuleWithTypeFieldConstraint(typer::Rule* parent_rule, VarKind domain_var_kind, intern::String field_name, TypeVar* field_tv);
    };
    
    // todo: subclass KindDependentConstraint to implement 'per-typekind' constraints,
    //       such that we can qualify a concrete type (and then dial constraints back for classes)
}

#endif  // INCLUDED_PDM_TYPES_TYPE_CONSTRAINT_HH

