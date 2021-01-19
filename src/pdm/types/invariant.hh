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
    };
    inline Invariant::Invariant(Relation* parent_relation, VarKind domain_var_kind, std::string name)
    :   m_parent_relation(parent_relation),
        m_domain_var_kind(domain_var_kind),
        m_name(std::move(name)),
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
    class IsVoidInvariant: public KindDependentInvariant {
      public:
        IsVoidInvariant(Relation* parent_relation, VarKind domain_var_kind);
    };
    inline IsVoidInvariant::IsVoidInvariant(Relation* parent_relation, VarKind domain_var_kind)
    :   KindDependentInvariant(parent_relation, domain_var_kind, TypeKind::Void, "IsVoid")
    {}

    // string:
    class IsStringInvariant: public KindDependentInvariant {
      public:
        IsStringInvariant(Relation* parent_relation, VarKind domain_var_kind);
    };
    inline IsStringInvariant::IsStringInvariant(Relation* parent_relation, VarKind domain_var_kind)
    :   KindDependentInvariant(parent_relation, domain_var_kind, TypeKind::String, "IsString")
    {}

    // int:
    class IsIntInvariant: public KindDependentInvariant {
      private:
        int m_min_width_in_bits;
        int m_max_width_in_bits;
        bool m_uses_sign_extension;

      public:
        IsIntInvariant(Relation* parent_relation, VarKind domain_var_kind, int opt_min_width_in_bits, int opt_max_width_in_bits, bool uses_sign_extension);

      public:
        inline bool uses_sign_extension() const;
        inline int min_width_in_bits() const;
        inline int max_width_in_bits() const;
    };
    inline IsIntInvariant::IsIntInvariant(Relation* parent_relation, VarKind domain_var_kind, int min_width_in_bits, int max_width_in_bits, bool uses_sign_extension)
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
    inline bool IsIntInvariant::uses_sign_extension() const {
        return m_uses_sign_extension;
    }
    inline int IsIntInvariant::min_width_in_bits() const {
        return m_min_width_in_bits;
    }
    inline int IsIntInvariant::max_width_in_bits() const {
        return m_max_width_in_bits;
    }

    // float:
    class IsFloatInvariant: public KindDependentInvariant {
      private:
        int m_min_width_in_bits;
        int m_max_width_in_bits;

      public:
        IsFloatInvariant(Relation* parent_relation, VarKind domain_var_kind, int opt_min_width_in_bits, int opt_max_width_in_bits);

      public:
        inline int min_width_in_bits() const;
        inline int max_width_in_bits() const;
    };
    inline IsFloatInvariant::IsFloatInvariant(Relation* parent_relation, VarKind domain_var_kind, int opt_min_width_in_bits, int opt_max_width_in_bits)
    :   KindDependentInvariant(
            parent_relation, domain_var_kind, TypeKind::Float, 
            "IsFloat[" + 
            std::to_string(opt_min_width_in_bits) + ":" + 
            std::to_string(opt_max_width_in_bits) + "]"
        ),
        m_min_width_in_bits(opt_min_width_in_bits),
        m_max_width_in_bits(opt_max_width_in_bits)
    {}
    inline int IsFloatInvariant::min_width_in_bits() const {
        return m_min_width_in_bits;
    }
    inline int IsFloatInvariant::max_width_in_bits() const {
        return m_max_width_in_bits;
    }
    
    // tuple:
    class IsTupleInvariant: public KindDependentInvariant {
      private:
        std::vector<TypeVar*> m_typeof_items_tvs;

      public:
        inline IsTupleInvariant(Relation* parent_relation, VarKind domain_var_kind, std::vector<TypeVar*>&& typeof_items_tvs);

      public:
        inline std::vector<TypeVar*> const& typeof_items_tvs() const;
    };
    inline IsTupleInvariant::IsTupleInvariant(Relation* parent_relation, VarKind domain_var_kind, std::vector<TypeVar*>&& typeof_items_tvs)
    :   KindDependentInvariant(parent_relation, domain_var_kind, TypeKind::Tuple, "IsTuple"),
        m_typeof_items_tvs(std::move(typeof_items_tvs))
    {}
    inline std::vector<TypeVar*> const& IsTupleInvariant::typeof_items_tvs() const {
        return m_typeof_items_tvs;
    }
    
    // struct, enum, module:
    class IsFieldCollectionInvariant: public KindDependentInvariant {
      private:
        std::map<intern::String, Var*> m_fields;

      public:
        IsFieldCollectionInvariant(Relation* parent_relation, VarKind domain_var_kind, TypeKind required_type_kind, std::string name, std::map<intern::String, Var*>&& fields);
  
      public:
        inline std::map<intern::String, Var*> const& fields() const;
    };
    inline std::map<intern::String, Var*> const& IsFieldCollectionInvariant::fields() const {
        return m_fields;
    }

    class IsStructInvariant: public IsFieldCollectionInvariant {
      public:
        IsStructInvariant(Relation* parent_relation, VarKind domain_var_kind, std::string opt_name_suffix = "");
    };
    class IsEnumInvariant: public IsFieldCollectionInvariant {
      public:
        IsEnumInvariant(Relation* parent_relation, VarKind domain_var_kind, std::string opt_name_suffix = "");
    };
    class IsModuleInvariant: public IsFieldCollectionInvariant {
      public:
        IsModuleInvariant(Relation* parent_relation, VarKind domain_var_kind);
    };
    
    // array
    class IsArrayInvariant: public KindDependentInvariant {
      private:
        TypeVar* m_item_tv;

      public:
        IsArrayInvariant(Relation* parent_relation, VarKind domain_var_kind, TypeVar* item_tv);

      public:
        inline TypeVar* item_tv() const;
    };
    inline IsArrayInvariant::IsArrayInvariant(Relation* parent_relation, VarKind domain_var_kind, TypeVar* field_tv)
    :   KindDependentInvariant(parent_relation, domain_var_kind, TypeKind::Tuple, "Array")
    {}
    inline TypeVar* IsArrayInvariant::item_tv() const {
        return m_item_tv;
    }
    
    // func/vcall:
    struct VCallArg {
        ast::VArgAccessSpec varg_access_spec; 
        TypeVar*            typeof_arg_tv;

      public:
        bool operator== (VCallArg const& other) const = default;
    };
    enum class VCallInvariantStrength {
        Formal,
        Actual
    };
    class IsVCallableInvariant: public KindDependentInvariant {
      private:
        VCallInvariantStrength m_strength;
        std::vector<VCallArg>&& m_formal_args;
        TypeVar* m_typeof_ret_tv;

      public:
        IsVCallableInvariant(
            VCallInvariantStrength strength,
            Relation* parent_relation,
            VarKind domain_var_kind,
            std::vector<VCallArg>&& formal_args_tvs,
            TypeVar* ret_tv
        );

      public:
        VCallInvariantStrength strength() const;
        std::vector<VCallArg> const& formal_args() const;
        TypeVar* typeof_ret_tv() const;
    };
    inline IsVCallableInvariant::IsVCallableInvariant(VCallInvariantStrength strength, Relation* parent_relation, VarKind domain_var_kind, std::vector<VCallArg>&& formal_args, TypeVar* typeof_ret_tv)
    :   KindDependentInvariant(parent_relation, domain_var_kind, TypeKind::Fn, "Fn"),
        m_strength(strength),
        m_formal_args(std::move(formal_args)),
        m_typeof_ret_tv(typeof_ret_tv)
    {}
    inline VCallInvariantStrength IsVCallableInvariant::strength() const {
        return m_strength;
    }
    inline std::vector<VCallArg> const& IsVCallableInvariant::formal_args() const {
        return m_formal_args;
    }
    inline TypeVar* IsVCallableInvariant::typeof_ret_tv() const {
        return m_typeof_ret_tv;
    }

    // todo: implement
    // - template in value context (as exp)
    // - template in type context
    //   - template -> class context
    //   - template -> type
    //   * totally determined from grammar!

}

#endif  // INCLUDED_PDM_TYPES_INVARIANT_HH

