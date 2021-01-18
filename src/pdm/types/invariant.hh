#ifndef INCLUDED__PDM__TYPES__INVARIANT_HH
#define INCLUDED__PDM__TYPES__INVARIANT_HH

#include <string>
#include <vector>
#include <map>
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
    
    // Invariant is a function mapping a value to a boolean result that always returns true.
    // Thus, Invariants partition the set of all values, and are used to identify sets of values.
    class Invariant {
      private:
        Relation*   m_parent_relation;
        VarKind     m_domain_var_kind;
        std::string m_name;
        Var*        m_supermost_arg_var;

      protected:
        Invariant(Relation* parent_relation, VarKind domain_var_kind, std::string name);
        virtual ~Invariant() = default;

      public:
        Relation* parent_relation() const;
        VarKind domain_var_kind() const;
        std::string const& name() const;
        Var* opt_supermost_arg_var() const;
        void supermost_arg(Var* supermost_arg);

      public:
        virtual bool implies(Invariant const& other) = 0;
    };
    inline Invariant::Invariant(Relation* parent_relation, VarKind domain_var_kind, std::string name)
    :   m_parent_relation(parent_relation),
        m_domain_var_kind(domain_var_kind),
        m_name(name),
        m_supermost_arg_var(nullptr)
    {}
    inline Relation* Invariant::parent_relation() const {
        return m_parent_relation;
    }
    inline VarKind Invariant::domain_var_kind() const {
        return m_domain_var_kind;
    }
    inline std::string const& Invariant::name() const {
        return m_name;
    }
    inline Var* Invariant::opt_supermost_arg_var() const {
        return m_supermost_arg_var;
    }
    inline void Invariant::supermost_arg(Var* supermost_arg_var) {
        if (DEBUG) {
            assert(supermost_arg_var != nullptr && "Cannot set nullptr supermost-arg");
        }
        m_supermost_arg_var = supermost_arg_var;
    }

    //
    // Common invariants:
    //

    class CommonInvariant: public Invariant {
      protected:
        CommonInvariant(Relation* parent_relation, VarKind domain_var_kind, std::string name);
    };
    inline CommonInvariant::CommonInvariant(Relation* parent_relation, VarKind domain_var_kind, std::string name)
    :   Invariant(parent_relation, domain_var_kind, "Common:" + name)
    {}
    
    class KindInvariant: public CommonInvariant {
      private:
        pdm::u64 m_allowed_type_kinds_bitset;

      public:
        KindInvariant(Relation* parent_relation, VarKind domain_var_kind, pdm::u64 allowed_type_kinds_bitset);

      public:
        pdm::u64 allowed_type_kinds_bitset() const;
        bool type_kind_allowed(TypeKind type_kind) const;

      public:
        virtual bool implies(Invariant const& other) override;
    };

    inline KindInvariant::KindInvariant(Relation* parent_relation, VarKind domain_var_kind, pdm::u64 allowed_kinds_bitset)
    :   CommonInvariant(parent_relation, domain_var_kind, "KindInvariant"),
        m_allowed_type_kinds_bitset(allowed_kinds_bitset)
    {}
    inline pdm::u64 KindInvariant::allowed_type_kinds_bitset() const {
        return m_allowed_type_kinds_bitset;
    }
    inline bool KindInvariant::type_kind_allowed(TypeKind type_kind) const {
        return m_allowed_type_kinds_bitset & static_cast<pdm::u64>(type_kind);
    }

    class SubtypeOfInvariant: public CommonInvariant {
      private:
        TypeVar* m_supertype_tv;

      public:
        SubtypeOfInvariant(Relation* parent_relation, TypeVar* supertype_tv);

      public:
        TypeVar* supertype_tv() const;

      public:
        virtual bool implies(Invariant const& other) override;
    };

    inline SubtypeOfInvariant::SubtypeOfInvariant(Relation* parent_relation, TypeVar* supertype_tv)
    :   CommonInvariant(parent_relation, VarKind::Type, "SubtypeOfInvariant"),
        m_supertype_tv(supertype_tv)
    {}
    inline TypeVar* SubtypeOfInvariant::supertype_tv() const {
        return m_supertype_tv;
    }

    class SubclassOfInvariant: public CommonInvariant {
      private:
        ClassVar* m_superclass_cv;
      
      public:
        SubclassOfInvariant(Relation* parent_relation, ClassVar* superclass_cv);

      public:
        ClassVar* superclass_cv() const;

      public:
        virtual bool implies(Invariant const& other) override;
    };

    inline SubclassOfInvariant::SubclassOfInvariant(Relation* parent_relation, ClassVar* superclass_cv)
    :   CommonInvariant(parent_relation, VarKind::Class, "SubclassOfInvariant"),
        m_superclass_cv(superclass_cv)
    {}
    inline ClassVar* SubclassOfInvariant::superclass_cv() const {
        return m_superclass_cv;
    }

    class ClassOfInvariant: public CommonInvariant {
      private:
        TypeVar* m_member_tv;

      public:
        ClassOfInvariant(Relation* parent_relation, TypeVar* member_tv);

      public:
        TypeVar* member_tv() const;

      public:
        virtual bool implies(Invariant const& other) override;
    };
    inline ClassOfInvariant::ClassOfInvariant(Relation* parent_relation, TypeVar* member_tv)
    :   CommonInvariant(parent_relation, VarKind::Class, "ClassOfInvariant"),
        m_member_tv(member_tv)
    {}
    inline TypeVar* ClassOfInvariant::member_tv() const {
        return m_member_tv;
    }

    //
    // Kind-dependent invariants:
    //

    class KindDependentInvariant: public Invariant {
      private:
        TypeKind m_required_type_kind;

      protected:
        KindDependentInvariant(Relation* parent_relation, VarKind domain_var_kind, TypeKind required_type_kind, std::string name);

      public:
        TypeKind required_type_kind() const;
    };
    inline KindDependentInvariant::KindDependentInvariant(Relation* parent_relation, VarKind domain_var_kind, TypeKind required_type_kind, std::string name)
    :   Invariant(parent_relation, domain_var_kind, "KindDependent:" + name),
        m_required_type_kind(required_type_kind)
    {}
    inline TypeKind KindDependentInvariant::required_type_kind() const {
        return m_required_type_kind;
    }

    // void:
    class VoidInvariant: public KindDependentInvariant {
      public:
        VoidInvariant(Relation* parent_relation, VarKind domain_var_kind);

      public:
        virtual bool implies(Invariant const& other) override;
    };
    inline VoidInvariant::VoidInvariant(Relation* parent_relation, VarKind domain_var_kind)
    :   KindDependentInvariant(parent_relation, domain_var_kind, TypeKind::Void, "IsVoid")
    {}

    // string:
    class StringInvariant: public KindDependentInvariant {
      public:
        StringInvariant(Relation* parent_relation, VarKind domain_var_kind);

      public:
        virtual bool implies(Invariant const& other) override;
    };
    inline StringInvariant::StringInvariant(Relation* parent_relation, VarKind domain_var_kind)
    :   KindDependentInvariant(parent_relation, domain_var_kind, TypeKind::String, "IsString")
    {}

    // int:
    class IntInvariant: public KindDependentInvariant {
      private:
        int m_min_width_in_bits;
        int m_max_width_in_bits;
        bool m_uses_sign_extension;

      public:
        IntInvariant(Relation* parent_relation, VarKind domain_var_kind, int opt_min_width_in_bits, int opt_max_width_in_bits, bool uses_sign_extension);

      public:
        inline bool uses_sign_extension() const;
        inline int min_width_in_bits() const;
        inline int max_width_in_bits() const;

      public:
        virtual bool implies(Invariant const& other) override;
    };
    inline IntInvariant::IntInvariant(Relation* parent_relation, VarKind domain_var_kind, int min_width_in_bits, int max_width_in_bits, bool uses_sign_extension)
    :   KindDependentInvariant(
            parent_relation, domain_var_kind, 
            (uses_sign_extension ? TypeKind::SignedInt : TypeKind::UnsignedInt), 
            std::string("Is") + (uses_sign_extension ? "Signed" : "Unsigned") + (
                std::string("Int[") +
                std::to_string(min_width_in_bits) + ":" + 
                std::to_string(max_width_in_bits) + "]"
            )
        ),
        m_min_width_in_bits(min_width_in_bits),
        m_max_width_in_bits(max_width_in_bits),
        m_uses_sign_extension(uses_sign_extension)
    {}
    inline bool IntInvariant::uses_sign_extension() const {
        return m_uses_sign_extension;
    }
    inline int IntInvariant::min_width_in_bits() const {
        return m_min_width_in_bits;
    }
    inline int IntInvariant::max_width_in_bits() const {
        return m_max_width_in_bits;
    }

    // float:
    class FloatInvariant: public KindDependentInvariant {
      private:
        int m_min_width_in_bits;
        int m_max_width_in_bits;

      public:
        FloatInvariant(Relation* parent_relation, VarKind domain_var_kind, int opt_min_width_in_bits, int opt_max_width_in_bits);

      public:
        inline int min_width_in_bits() const;
        inline int max_width_in_bits() const;

      public:
        virtual bool implies(Invariant const& other) override;
    };
    inline FloatInvariant::FloatInvariant(Relation* parent_relation, VarKind domain_var_kind, int opt_min_width_in_bits, int opt_max_width_in_bits)
    :   KindDependentInvariant(
            parent_relation, domain_var_kind, TypeKind::Float, 
            "IsFloat[" + 
            std::to_string(opt_min_width_in_bits) + ":" + 
            std::to_string(opt_max_width_in_bits) + "]"
        ),
        m_min_width_in_bits(opt_min_width_in_bits),
        m_max_width_in_bits(opt_max_width_in_bits)
    {}
    inline int FloatInvariant::min_width_in_bits() const {
        return m_min_width_in_bits;
    }
    inline int FloatInvariant::max_width_in_bits() const {
        return m_max_width_in_bits;
    }
    
    // tuple:
    class TupleInvariant: public KindDependentInvariant {
      private:
        std::vector<TypeVar*> m_typeof_items_tvs;

      public:
        inline TupleInvariant(Relation* parent_relation, VarKind domain_var_kind, std::vector<TypeVar*>&& typeof_items_tvs);

      public:
        inline std::vector<TypeVar*> const& typeof_items_tvs() const;
        
      public:
        virtual bool implies(Invariant const& other) override;
    };
    inline TupleInvariant::TupleInvariant(Relation* parent_relation, VarKind domain_var_kind, std::vector<TypeVar*>&& typeof_items_tvs)
    :   KindDependentInvariant(parent_relation, domain_var_kind, TypeKind::Tuple, "IsTuple"),
        m_typeof_items_tvs(std::move(typeof_items_tvs))
    {}
    inline std::vector<TypeVar*> const& TupleInvariant::typeof_items_tvs() const {
        return m_typeof_items_tvs;
    }
    
    // struct, enum, module:
    class FieldCollectionInvariant: public KindDependentInvariant {
      private:
        std::map<intern::String, Var*> m_fields;

      public:
        FieldCollectionInvariant(Relation* parent_relation, VarKind domain_var_kind, TypeKind required_type_kind, std::string name);
  
      public:
        inline std::map<intern::String, Var*> const& fields() const;

      // todo: implement amend_field as a get_cached/create func

      public:
        virtual bool implies(Invariant const& other) override;
    };
    inline std::map<intern::String, Var*> const& FieldCollectionInvariant::fields() const {
        return m_fields;
    }

    class StructInvariant: public FieldCollectionInvariant {
      public:
        StructInvariant(Relation* parent_relation, VarKind domain_var_kind, std::string opt_name_suffix = "");
    };
    class EnumInvariant: public FieldCollectionInvariant {
      public:
        EnumInvariant(Relation* parent_relation, VarKind domain_var_kind, std::string opt_name_suffix = "");
    };
    class ModuleInvariant: public FieldCollectionInvariant {
      public:
        ModuleInvariant(Relation* parent_relation, VarKind domain_var_kind);
    };
    
    // array
    class ArrayInvariant: public KindDependentInvariant {
      private:
        TypeVar* m_item_tv;

      public:
        ArrayInvariant(Relation* parent_relation, VarKind domain_var_kind, TypeVar* item_tv);

      public:
        inline TypeVar* item_tv() const;

      public:
        virtual bool implies(Invariant const& other) override;
    };
    inline ArrayInvariant::ArrayInvariant(Relation* parent_relation, VarKind domain_var_kind, TypeVar* field_tv)
    :   KindDependentInvariant(parent_relation, domain_var_kind, TypeKind::Tuple, "Array")
    {}
    inline TypeVar* ArrayInvariant::item_tv() const {
        return m_item_tv;
    }
    
    // func
    struct FnInvariant_FnArg {
        ast::VArgAccessSpec varg_access_spec; 
        TypeVar*            typeof_arg_tv;

      public:
        bool operator== (FnInvariant_FnArg const& other) const = default;
    };
    enum class FnInvariant_Strength {
        Formal,
        Actual
    };
    class FnInvariant: public KindDependentInvariant {
      private:
        FnInvariant_Strength m_strength;
        std::vector<FnInvariant_FnArg>&& m_formal_args;
        TypeVar* m_typeof_ret_tv;

      public:
        FnInvariant(FnInvariant_Strength strength, Relation* parent_relation, VarKind domain_var_kind, std::vector<FnInvariant_FnArg>&& formal_args_tvs, TypeVar* ret_tv);

      public:
        FnInvariant_Strength strength() const;
        std::vector<FnInvariant_FnArg> const& formal_args() const;
        TypeVar* typeof_ret_tv() const;

      public:
        virtual bool implies(Invariant const& other) override;
    };
    inline FnInvariant::FnInvariant(FnInvariant_Strength strength, Relation* parent_relation, VarKind domain_var_kind, std::vector<FnInvariant_FnArg>&& formal_args, TypeVar* typeof_ret_tv)
    :   KindDependentInvariant(parent_relation, domain_var_kind, TypeKind::Fn, "Fn"),
        m_strength(strength),
        m_formal_args(std::move(formal_args)),
        m_typeof_ret_tv(typeof_ret_tv)
    {}
    inline FnInvariant_Strength FnInvariant::strength() const {
        return m_strength;
    }
    inline std::vector<FnInvariant_FnArg> const& FnInvariant::formal_args() const {
        return m_formal_args;
    }
    inline TypeVar* FnInvariant::typeof_ret_tv() const {
        return m_typeof_ret_tv;
    }

}

#endif  // INCLUDED_PDM_TYPES_INVARIANT_HH

