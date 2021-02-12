#ifndef INCLUDED__PDM__TYPES__INVARIANT_HH
#define INCLUDED__PDM__TYPES__INVARIANT_HH

#include <string>
#include <vector>
#include <map>
#include <cassert>
#include <optional>

#include "pdm/core/config.hh"
#include "pdm/core/integer.hh"
#include "pdm/core/intern.hh"
#include "pdm/printer/printer.hh"
#include "pdm/ast/arg/varg.hh"

#include "var_archetype.hh"
#include "kind.hh"

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
    class VarInvariant {
      private:
        Relation*   m_parent_relation;
        VarArchetype     m_domain_var_kind;
        std::string m_name;
        Var*        m_supermost_arg_var;

      protected:
        VarInvariant(Relation* parent_relation, VarArchetype domain_var_kind, std::string name);
        virtual ~VarInvariant() = default;

      public:
        [[nodiscard]] Relation* parent_relation() const;
        [[nodiscard]] VarArchetype domain_var_archetype() const;
        [[nodiscard]] std::string const& name() const;
        [[nodiscard]] Var* opt_supermost_arg_var() const;
        void supermost_arg(Var* supermost_arg);

      public:
        virtual void print(printer::Printer& printer) const = 0;
    };
    inline VarInvariant::VarInvariant(Relation* parent_relation, VarArchetype domain_var_kind, std::string name)
    :   m_parent_relation(parent_relation),
        m_domain_var_kind(domain_var_kind),
        m_name(std::move(name)),
        m_supermost_arg_var(nullptr)
    {}
    inline Relation* VarInvariant::parent_relation() const {
        return m_parent_relation;
    }
    inline VarArchetype VarInvariant::domain_var_archetype() const {
        return m_domain_var_kind;
    }
    inline std::string const& VarInvariant::name() const {
        return m_name;
    }
    inline Var* VarInvariant::opt_supermost_arg_var() const {
        return m_supermost_arg_var;
    }
    inline void VarInvariant::supermost_arg(Var* supermost_arg_var) {
        if (DEBUG) {
            assert(supermost_arg_var != nullptr && "Cannot set nullptr supermost-arg");
        }
        m_supermost_arg_var = supermost_arg_var;
    }

    //
    // Kind-independent invariants:
    //

    class KindIndependentVarInvariant: public VarInvariant {
      protected:
        KindIndependentVarInvariant(Relation* parent_relation, VarArchetype domain_var_kind, std::string name);
    };
    inline KindIndependentVarInvariant::KindIndependentVarInvariant(Relation* parent_relation, VarArchetype domain_var_kind, std::string name)
    : VarInvariant(parent_relation, domain_var_kind, "Common:" + name)
    {}

    class SubtypeOfInvariant: public KindIndependentVarInvariant {
      private:
        TypeVar* m_supertype_tv;

      public:
        SubtypeOfInvariant(Relation* parent_relation, TypeVar* supertype_tv);

      public:
        [[nodiscard]] TypeVar* supertype_tv() const;

      public:
        void print(printer::Printer& printer) const override;
    };

    inline SubtypeOfInvariant::SubtypeOfInvariant(Relation* parent_relation, TypeVar* supertype_tv)
    : KindIndependentVarInvariant(parent_relation, VarArchetype::Type, "SubtypeOfInvariant"),
      m_supertype_tv(supertype_tv)
    {}
    inline TypeVar* SubtypeOfInvariant::supertype_tv() const {
        return m_supertype_tv;
    }

    class SubclassOfInvariant: public KindIndependentVarInvariant {
      private:
        ClassVar* m_superclass_cv;
      
      public:
        SubclassOfInvariant(Relation* parent_relation, ClassVar* superclass_cv);

      public:
        [[nodiscard]] ClassVar* superclass_cv() const;

      public:
        void print(printer::Printer& printer) const override;
    };

    inline SubclassOfInvariant::SubclassOfInvariant(Relation* parent_relation, ClassVar* superclass_cv)
    : KindIndependentVarInvariant(parent_relation, VarArchetype::Class, "SubclassOfInvariant"),
      m_superclass_cv(superclass_cv)
    {}
    inline ClassVar* SubclassOfInvariant::superclass_cv() const {
        return m_superclass_cv;
    }

    class ClassOfInvariant: public KindIndependentVarInvariant {
      private:
        TypeVar* m_member_tv;

      public:
        ClassOfInvariant(Relation* parent_relation, TypeVar* member_tv);

      public:
        [[nodiscard]] TypeVar* member_tv() const;

      public:
        void print(printer::Printer& printer) const override;
    };
    inline ClassOfInvariant::ClassOfInvariant(Relation* parent_relation, TypeVar* member_tv)
    : KindIndependentVarInvariant(parent_relation, VarArchetype::Class, "ClassOfInvariant"),
      m_member_tv(member_tv)
    {}
    inline TypeVar* ClassOfInvariant::member_tv() const {
        return m_member_tv;
    }

    // select overloaded operators (e.g. arithmetic) can be solved by a few different classes that all include
    // 'numbers'.
    class IsNumberVarInvariant: public KindIndependentVarInvariant {
      public:
        explicit inline IsNumberVarInvariant(Relation* parent_relation);

      public:
        void print(printer::Printer& printer) const override;
    };

    inline IsNumberVarInvariant::IsNumberVarInvariant(Relation *parent_relation)
    : KindIndependentVarInvariant(parent_relation, VarArchetype::Type, "IsNumberInvariant")
    {}

    //
    // Kind-dependent invariants:
    //

    class KindDependentInvariant: public VarInvariant {
      private:
        Kind m_required_type_kind;

      protected:
        KindDependentInvariant(Relation* parent_relation, VarArchetype domain_var_kind, Kind required_type_kind, std::string name);

      public:
        Kind required_type_kind() const;
    };
    inline KindDependentInvariant::KindDependentInvariant(Relation* parent_relation, VarArchetype domain_var_kind, Kind required_type_kind, std::string name)
    : VarInvariant(parent_relation, domain_var_kind, "KindDependent:" + name),
      m_required_type_kind(required_type_kind)
    {}
    inline Kind KindDependentInvariant::required_type_kind() const {
        return m_required_type_kind;
    }

    // void:
    class IsVoidInvariant: public KindDependentInvariant {
      public:
        IsVoidInvariant(Relation* parent_relation, VarArchetype domain_var_kind);

      public:
        void print(printer::Printer& printer) const override;
    };
    inline IsVoidInvariant::IsVoidInvariant(Relation* parent_relation, VarArchetype domain_var_kind)
    :   KindDependentInvariant(parent_relation, domain_var_kind, Kind::Void, "IsVoid")
    {}

    // string:
    class IsStringInvariant: public KindDependentInvariant {
      public:
        IsStringInvariant(Relation* parent_relation, VarArchetype domain_var_kind);

      public:
        void print(printer::Printer& printer) const override;
    };
    inline IsStringInvariant::IsStringInvariant(Relation* parent_relation, VarArchetype domain_var_kind)
    :   KindDependentInvariant(parent_relation, domain_var_kind, Kind::String, "IsString")
    {}

    // int:
    class IsIntInvariant: public KindDependentInvariant {
      private:
        int m_min_width_in_bits;
        int m_max_width_in_bits;
        bool m_uses_sign_extension;

      public:
        IsIntInvariant(Relation* parent_relation, VarArchetype domain_var_kind, int opt_min_width_in_bits, int opt_max_width_in_bits, bool uses_sign_extension);

      public:
        inline bool uses_sign_extension() const;
        inline int min_width_in_bits() const;
        inline int max_width_in_bits() const;

      public:
        void print(printer::Printer& printer) const override;
    };
    inline IsIntInvariant::IsIntInvariant(Relation* parent_relation, VarArchetype domain_var_kind, int min_width_in_bits, int max_width_in_bits, bool uses_sign_extension)
    :   KindDependentInvariant(
            parent_relation, domain_var_kind, 
            (uses_sign_extension ? Kind::SignedInt : Kind::UnsignedInt),
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
        IsFloatInvariant(Relation* parent_relation, VarArchetype domain_var_kind, int opt_min_width_in_bits, int opt_max_width_in_bits);

      public:
        inline int min_width_in_bits() const;
        inline int max_width_in_bits() const;

      public:
        void print(printer::Printer& printer) const override;
    };
    inline IsFloatInvariant::IsFloatInvariant(Relation* parent_relation, VarArchetype domain_var_kind, int opt_min_width_in_bits, int opt_max_width_in_bits)
    :   KindDependentInvariant(
        parent_relation, domain_var_kind, Kind::Float,
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
        inline IsTupleInvariant(Relation* parent_relation, VarArchetype domain_var_kind, std::vector<TypeVar*>&& typeof_items_tvs);

      public:
        inline std::vector<TypeVar*> const& typeof_items_tvs() const;

      public:
        void print(printer::Printer& printer) const override;
    };
    inline IsTupleInvariant::IsTupleInvariant(Relation* parent_relation, VarArchetype domain_var_kind, std::vector<TypeVar*>&& typeof_items_tvs)
    :   KindDependentInvariant(parent_relation, domain_var_kind, Kind::Tuple, "IsTuple"),
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
        IsFieldCollectionInvariant(
            Relation* parent_relation,
            VarArchetype domain_var_kind,
            Kind required_type_kind,
            std::string name,
            std::map<intern::String, Var*>&& fields
        );
  
      public:
        [[nodiscard]] inline std::map<intern::String, Var*> const& fields() const;
    };
    inline std::map<intern::String, Var*> const& IsFieldCollectionInvariant::fields() const {
        return m_fields;
    }

    class IsStructInvariant: public IsFieldCollectionInvariant {
      public:
        IsStructInvariant(
            Relation* parent_relation, VarArchetype domain_var_kind,
            std::map<intern::String, Var*> fields,
            std::string opt_name_suffix = ""
        );

      public:
        void print(printer::Printer& printer) const override;
    };
    class IsEnumInvariant: public IsFieldCollectionInvariant {
      public:
        IsEnumInvariant(
            Relation* parent_relation,
            VarArchetype domain_var_kind,
            std::map<intern::String, Var*> fields,
            std::string opt_name_suffix = ""
        );

      public:
        void print(printer::Printer& printer) const override;
    };
    class IsModuleInvariant: public IsFieldCollectionInvariant {
      public:
        IsModuleInvariant(
            Relation* parent_relation,
            VarArchetype domain_var_kind,
            std::map<intern::String, Var*> fields,
            std::string opt_name_suffix = ""
        );

      public:
        void print(printer::Printer& printer) const override;
    };
    
    // array
    class IsArrayInvariant: public KindDependentInvariant {
      private:
        TypeVar* m_item_tv;

      public:
        IsArrayInvariant(
            Relation* parent_relation,
            VarArchetype domain_var_kind,
            TypeVar* item_tv,
            std::string array_name
        );

      public:
        [[nodiscard]] inline TypeVar* item_tv() const;

      public:
        void print(printer::Printer& printer) const override;
    };

    inline TypeVar* IsArrayInvariant::item_tv() const {
        return m_item_tv;
    }
    
    // func/vcall:
    struct VCallArg {
        std::optional<intern::String> name;
        ast::VArgAccessSpec varg_access_spec;
        TypeVar* typeof_arg_tv;

      public:
        bool operator== (VCallArg const& other) const;
    };
    inline bool VCallArg::operator==(const VCallArg &other) const {
        // if either arg is missing a name, we don't check if names match.
        // only if both args have a name do we check they must match.
        bool ignore_name_match = !name.has_value() || !other.name.has_value();
        if (!ignore_name_match) {
            if (name.value() != other.name.value()) {
                return false;
            }
        }
        return (
            (varg_access_spec == other.varg_access_spec) &&
            (typeof_arg_tv == other.typeof_arg_tv)
        );
    }

    enum class VCallInvariantStrength {
        Formal,
        Actual
    };
    class IsVCallableInvariant: public KindDependentInvariant {
      private:
        VCallInvariantStrength m_strength;
        std::vector<VCallArg> m_formal_args;
        TypeVar* m_typeof_ret_tv;

      public:
        IsVCallableInvariant(
            VCallInvariantStrength strength,
            Relation* parent_relation,
            VarArchetype domain_var_kind,
            std::vector<VCallArg>&& formal_args_tvs,
            TypeVar* ret_tv
        );

      public:
        [[nodiscard]] VCallInvariantStrength strength() const;
        [[nodiscard]] std::vector<VCallArg> const& formal_args() const;
        [[nodiscard]] TypeVar* typeof_ret_tv() const;

      public:
        void print(printer::Printer &printer) const override;
    };
    inline IsVCallableInvariant::IsVCallableInvariant(
        VCallInvariantStrength strength,
        Relation* parent_relation,
        VarArchetype domain_var_kind,
        std::vector<VCallArg>&& formal_args,
        TypeVar* typeof_ret_tv
    )
    :   KindDependentInvariant(parent_relation, domain_var_kind, Kind::Fn, "Fn"),
        m_strength(strength),
        m_formal_args(std::move(formal_args)),
        m_typeof_ret_tv(typeof_ret_tv)
    {
        if (pdm::DEBUG) {
            if (m_strength == VCallInvariantStrength::Formal) {
                for (VCallArg const& arg: m_formal_args) {
                    assert(arg.name.has_value() && "Cannot pass unnamed arg with Formal strength.");
                }
            }
        }
    }
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

