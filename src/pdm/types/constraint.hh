#ifndef INCLUDED_PDM_TYPES_TYPE_CONSTRAINT_HH
#define INCLUDED_PDM_TYPES_TYPE_CONSTRAINT_HH

#include <string>
#include <vector>
#include <cassert>

#include "pdm/core/config.hh"
#include "pdm/core/integer.hh"
#include "pdm/core/intern.hh"

#include "pdm/ast/arg/varg.hh"

#include "var_kind.hh"
#include "type_kind.hh"

//
// Forward Declarations:
//

namespace pdm::types {
    class Var;
    class TypeVar;
    class ClassVar;
    class Relation;
}


//
// Implementation:
//

namespace pdm::types {
    
    // a Constraint is a function mapping a **type** to **a boolean result.**
    // Constraints are 'assumed', which means they are held to be true for the argument 'Var'.
    class Constraint {
      private:
        Relation*   m_parent_relation;
        VarKind     m_domain_var_kind;
        std::string m_name;
        Var*        m_supermost_arg_var;

      protected:
        Constraint(Relation* parent_relation, VarKind domain_var_kind, std::string name);
        virtual ~Constraint() = default;

      public:
        Relation* parent_relation() const;
        VarKind domain_var_kind() const;
        std::string const& name() const;
        Var* opt_supermost_arg_var() const;
        void supermost_arg(Var* supermost_arg);
    };
    inline Constraint::Constraint(Relation* parent_relation, VarKind domain_var_kind, std::string name)
    :   m_parent_relation(parent_relation),
        m_domain_var_kind(domain_var_kind),
        m_name(name),
        m_supermost_arg_var(nullptr)
    {}
    inline Relation* Constraint::parent_relation() const {
        return m_parent_relation;
    }
    inline VarKind Constraint::domain_var_kind() const {
        return m_domain_var_kind;
    }
    inline std::string const& Constraint::name() const {
        return m_name;
    }
    inline Var* Constraint::opt_supermost_arg_var() const {
        return m_supermost_arg_var;
    }
    inline void Constraint::supermost_arg(Var* supermost_arg_var) {
        if (DEBUG) {
            assert(supermost_arg_var != nullptr && "Cannot set nullptr supermost-arg");
        }
        m_supermost_arg_var = supermost_arg_var;
    }

    //
    // Common constraints:
    //

    class CommonConstraint: public Constraint {
      protected:
        CommonConstraint(Relation* parent_relation, VarKind domain_var_kind, std::string name);
    };
    inline CommonConstraint::CommonConstraint(Relation* parent_relation, VarKind domain_var_kind, std::string name)
    :   Constraint(parent_relation, domain_var_kind, "Common:" + name)
    {}
    
    class KindConstraint: public CommonConstraint {
      private:
        pdm::u64 m_allowed_type_kinds_bitset;

      public:
        KindConstraint(Relation* parent_relation, VarKind domain_var_kind, pdm::u64 allowed_type_kinds_bitset);

      public:
        pdm::u64 allowed_type_kinds_bitset() const;
        bool type_kind_allowed(TypeKind type_kind) const;
    };

    inline KindConstraint::KindConstraint(Relation* parent_relation, VarKind domain_var_kind, pdm::u64 allowed_kinds_bitset)
    :   CommonConstraint(parent_relation, domain_var_kind, "KindConstraint"),
        m_allowed_type_kinds_bitset(allowed_kinds_bitset)
    {}
    inline pdm::u64 KindConstraint::allowed_type_kinds_bitset() const {
        return m_allowed_type_kinds_bitset;
    }
    inline bool KindConstraint::type_kind_allowed(TypeKind type_kind) const {
        return m_allowed_type_kinds_bitset & static_cast<pdm::u64>(type_kind);
    }

    class SubtypeOfConstraint: public CommonConstraint {
      private:
        TypeVar* m_supertype_tv;

      public:
        SubtypeOfConstraint(Relation* parent_relation, TypeVar* supertype_tv);

      public:
        TypeVar* supertype_tv() const;
    };

    inline SubtypeOfConstraint::SubtypeOfConstraint(Relation* parent_relation, TypeVar* supertype_tv)
    :   CommonConstraint(parent_relation, VarKind::Type, "SubtypeOfConstraint"),
        m_supertype_tv(supertype_tv)
    {}
    inline TypeVar* SubtypeOfConstraint::supertype_tv() const {
        return m_supertype_tv;
    }

    class SubclassOfConstraint: public CommonConstraint {
      private:
        ClassVar* m_superclass_cv;
      
      public:
        SubclassOfConstraint(Relation* parent_relation, ClassVar* superclass_cv);

      public:
        ClassVar* superclass_cv() const;
    };

    inline SubclassOfConstraint::SubclassOfConstraint(Relation* parent_relation, ClassVar* superclass_cv)
    :   CommonConstraint(parent_relation, VarKind::Class, "SubclassOfConstraint"),
        m_superclass_cv(superclass_cv)
    {}
    inline ClassVar* SubclassOfConstraint::superclass_cv() const {
        return m_superclass_cv;
    }

    class ClassOfConstraint: public CommonConstraint {
      private:
        TypeVar* m_member_tv;

      public:
        ClassOfConstraint(Relation* parent_relation, TypeVar* member_tv);

      public:
        TypeVar* member_tv() const;
    };
    inline ClassOfConstraint::ClassOfConstraint(Relation* parent_relation, TypeVar* member_tv)
    :   CommonConstraint(parent_relation, VarKind::Class, "ClassOfConstraint"),
        m_member_tv(member_tv)
    {}
    inline TypeVar* ClassOfConstraint::member_tv() const {
        return m_member_tv;
    }

    //
    // Kind-dependent constraints:
    //

    class KindDependentConstraint: public Constraint {
      private:
        TypeKind m_required_type_kind;

      protected:
        KindDependentConstraint(Relation* parent_relation, VarKind domain_var_kind, TypeKind required_type_kind, std::string name);

      public:
        TypeKind required_type_kind() const;
    };
    inline KindDependentConstraint::KindDependentConstraint(Relation* parent_relation, VarKind domain_var_kind, TypeKind required_type_kind, std::string name)
    :   Constraint(parent_relation, domain_var_kind, "KindDependent:" + name),
        m_required_type_kind(required_type_kind)
    {}
    inline TypeKind KindDependentConstraint::required_type_kind() const {
        return m_required_type_kind;
    }

    // void:
    class VoidConstraint: public KindDependentConstraint {
      public:
        VoidConstraint(Relation* parent_relation, VarKind domain_var_kind, std::string name);
    };
    inline VoidConstraint::VoidConstraint(Relation* parent_relation, VarKind domain_var_kind, std::string name)
    :   KindDependentConstraint(parent_relation, domain_var_kind, TypeKind::Void, name)
    {}

    // int:
    class IntConstraint: public KindDependentConstraint {
      public:
        IntConstraint(Relation* parent_relation, VarKind domain_var_kind, int min_width = -1, int max_width = -1);
    };
    inline IntConstraint::IntConstraint(Relation* parent_relation, VarKind domain_var_kind, int min_width, int max_width)
    :   KindDependentConstraint(parent_relation, domain_var_kind, TypeKind::Int, "Int[" + std::to_string(min_width) + ":" + std::to_string(max_width) + "]")
    {}

    // float:
    class FloatConstraint: public KindDependentConstraint {
      public:
        FloatConstraint(Relation* parent_relation, VarKind domain_var_kind, int min_width = -1, int max_width = -1);
    };
    inline FloatConstraint::FloatConstraint(Relation* parent_relation, VarKind domain_var_kind, int min_width, int max_width)
    :   KindDependentConstraint(parent_relation, domain_var_kind, TypeKind::Float, "Float[" + std::to_string(min_width) + ":" + std::to_string(max_width) + "]")
    {}

    // string:
    class StringConstraint: public KindDependentConstraint {
      public:
        StringConstraint(Relation* parent_relation, VarKind domain_var_kind);
    };
    inline StringConstraint::StringConstraint(Relation* parent_relation, VarKind domain_var_kind)
    :   KindDependentConstraint(parent_relation, domain_var_kind, TypeKind::String, "String")
    {}
    
    // tuple:
    class TupleConstraint: public KindDependentConstraint {
      public:
        TupleConstraint(Relation* parent_relation, VarKind domain_var_kind);
    };
    class TupleWithFieldConstraint: public TupleConstraint {
      public:
        TupleWithFieldConstraint(Relation* parent_relation, VarKind domain_var_kind, int index, TypeVar* field_tv);
    };
    inline TupleConstraint::TupleConstraint(Relation* parent_relation, VarKind domain_var_kind)
    :   KindDependentConstraint(parent_relation, domain_var_kind, TypeKind::Tuple, "Tuple")
    {}
    
    // array:
    class ArrayConstraint: public KindDependentConstraint {
      public:
        ArrayConstraint(Relation* parent_relation, VarKind domain_var_kind, TypeVar* field_tv);
    };
    inline ArrayConstraint::ArrayConstraint(Relation* parent_relation, VarKind domain_var_kind, TypeVar* field_tv)
    :   KindDependentConstraint(parent_relation, domain_var_kind, TypeKind::Tuple, "Array")
    {}
    
    // struct:
    class StructConstraint: public KindDependentConstraint {
      public:
        StructConstraint(Relation* parent_relation, VarKind domain_var_kind, std::string opt_name_suffix = "");
    };
    class StructWithFieldConstraint: public StructConstraint {
      private:
        intern::String m_field_name;
        TypeVar*       m_typeOf_field_tv;
      public:
        StructWithFieldConstraint(Relation* parent_relation, VarKind domain_var_kind, intern::String field_name, TypeVar* typeOf_field_tv);
    };
    inline StructConstraint::StructConstraint(Relation* parent_relation, VarKind domain_var_kind, std::string opt_name_suffix)
    :   KindDependentConstraint(parent_relation, domain_var_kind, TypeKind::Struct, "Struct" + opt_name_suffix)
    {}
    inline StructWithFieldConstraint::StructWithFieldConstraint(Relation* parent_relation, VarKind domain_var_kind, intern::String field_name, TypeVar* typeOf_field_tv)
    :   StructConstraint(parent_relation, domain_var_kind, "WithFieldConstraint"),
        m_field_name(field_name),
        m_typeOf_field_tv(typeOf_field_tv)
    {}

    // enum:
    class EnumConstraint: public KindDependentConstraint {
      public:
        EnumConstraint(Relation* parent_relation, VarKind domain_var_kind, std::string opt_name_suffix = "");
    };
    class EnumWithFieldConstraint: public EnumConstraint {
      private:
        intern::String        m_field_name;
        int                   m_vpattern_len;
        std::vector<TypeVar*> m_vpattern_types_tvs;
      public:
        EnumWithFieldConstraint(Relation* parent_relation, VarKind domain_var_kind, intern::String field_name, int tvs_count, TypeVar** typeOf_field_pattern_tvs);
    };
    inline EnumConstraint::EnumConstraint(Relation* parent_relation, VarKind domain_var_kind, std::string opt_name_suffix)
    :   KindDependentConstraint(parent_relation, domain_var_kind, TypeKind::Struct, "Struct" + opt_name_suffix)
    {}
    inline EnumWithFieldConstraint::EnumWithFieldConstraint(Relation* parent_relation, VarKind domain_var_kind, intern::String field_name, int vpattern_len, TypeVar** vpattern_types_tvs)
    :   EnumConstraint(parent_relation, domain_var_kind),
        m_field_name(field_name),
        m_vpattern_len()
    {}

    // ref
    class RefConstraint: public KindDependentConstraint {
      private:
        bool m_ref_readable;
        bool m_ref_writable;
      public:
        RefConstraint(Relation* parent_relation, VarKind domain_var_kind, bool ref_readable, bool ref_writable);
    };
    inline RefConstraint::RefConstraint(Relation* parent_relation, VarKind domain_var_kind, bool ref_readable, bool ref_writable)
    :   KindDependentConstraint(parent_relation, domain_var_kind, TypeKind::Ref, "Ref"),
        m_ref_readable(ref_readable),
        m_ref_writable(ref_writable)
    {}

    // func
    struct FnConstraint_FnArg {
        ast::VArgAccessSpec varg_access_spec; 
        TypeVar*            typeof_arg_tv;
    };
    enum class FnConstraint_Strength {
        Formal,
        Actual
    };
    class FnConstraint: public KindDependentConstraint {
      private:
        FnConstraint_Strength m_strength;
        std::vector<FnConstraint_FnArg>&& m_formal_args_tvs;
        TypeVar* m_ret_tv;

      public:
        FnConstraint(FnConstraint_Strength strength, Relation* parent_relation, VarKind domain_var_kind, std::vector<FnConstraint_FnArg>&& formal_args_tvs, TypeVar* ret_tv);

      public:
        FnConstraint_Strength strength() const;
        std::vector<FnConstraint_FnArg> const& formal_args_tvs() const;
        TypeVar* ret_tv() const;
    };
    inline FnConstraint::FnConstraint(FnConstraint_Strength strength, Relation* parent_relation, VarKind domain_var_kind, std::vector<FnConstraint_FnArg>&& formal_args_tvs, TypeVar* ret_tv)
    :   KindDependentConstraint(parent_relation, domain_var_kind, TypeKind::Fn, "Fn"),
        m_strength(strength),
        m_formal_args_tvs(std::move(formal_args_tvs)),
        m_ret_tv(ret_tv)
    {}
    inline FnConstraint_Strength FnConstraint::strength() const {
        return m_strength;
    }
    inline std::vector<FnConstraint_FnArg> const& FnConstraint::formal_args_tvs() const {
        return m_formal_args_tvs;
    }
    inline TypeVar* FnConstraint::ret_tv() const {
        return m_ret_tv;
    }

    // module
    class ModuleConstraint: public KindDependentConstraint {
      public:
        ModuleConstraint(Relation* parent_relation, VarKind domain_var_kind);
    };
    class ModuleWithValueFieldConstraint: public ModuleConstraint {
      private:
        intern::String m_field_name;
        TypeVar* m_typeof_field_tv;
      public:
        ModuleWithValueFieldConstraint(Relation* parent_relation, VarKind domain_var_kind, intern::String field_name, TypeVar* typeof_field_tv);
    };
    class ModuleWithTypeFieldConstraint: public ModuleConstraint {
      private:
        intern::String m_field_name;
        TypeVar* m_field_tv;
      public:
        ModuleWithTypeFieldConstraint(Relation* parent_relation, VarKind domain_var_kind, intern::String field_name, TypeVar* field_tv);
    };
    inline ModuleConstraint::ModuleConstraint(Relation* parent_relation, VarKind domain_var_kind)
    :   KindDependentConstraint(parent_relation, domain_var_kind, TypeKind::Module, "Module")
    {}
    inline ModuleWithValueFieldConstraint::ModuleWithValueFieldConstraint(Relation* parent_relation, VarKind domain_var_kind, intern::String field_name, TypeVar* typeof_field_tv)
    :   ModuleConstraint(parent_relation, domain_var_kind),
        m_field_name(field_name),
        m_typeof_field_tv(typeof_field_tv)
    {}
    inline ModuleWithTypeFieldConstraint::ModuleWithTypeFieldConstraint(Relation* parent_relation, VarKind domain_var_kind, intern::String field_name, TypeVar* field_tv)
    :   ModuleConstraint(parent_relation, domain_var_kind),
        m_field_name(field_name),
        m_field_tv(field_tv) 
    {}
}

#endif  // INCLUDED_PDM_TYPES_TYPE_CONSTRAINT_HH

