#ifndef INCLUDED_KIND_HH
#define INCLUDED_KIND_HH

#include <vector>

#include <pdm/core/intern.hh>

#include "constraint.hh"

namespace pdm::typer {
    
    class TV;

} // namespace pdm::typer

namespace pdm::typer {

    //
    //
    // 1. Abstract Soln:
    //
    //


    class Soln;
    
    // Soln is a minimal record of all valid TV constraints, and thus, identity.
    // - which types are equal?
    // - which types are sup/sub types?
    class Soln {
        RoughClass m_rough_class;
        std::vector<Constraint*> m_accepted_constraints;
        std::vector<Constraint*> m_rejected_constraints;

      // public getters:
      public:
        virtual TvKind tv_kind() const = 0;

        RoughClass rough_class() const {
            return m_rough_class;
        }
        int active_constraint_count() const {
            return m_accepted_constraints.size();
        }
        int inactive_constraint_count() const {
            return m_rejected_constraints.size();
        }
        int total_constraint_count() const {
            return active_constraint_count() + inactive_constraint_count();
        }

      // protected constructors:
      protected:
        Soln(RoughClass rough_cls)
        : m_rough_class(rough_cls) {}

      // protected: solution update methods:
      protected:
        virtual ApplyConstraintResult on_apply_constraint(Constraint* constraint) = 0;

      // public solution update methods:
      public:
        ApplyConstraintResult apply_constraint(Constraint* constraint) {
            ApplyConstraintResult result = on_apply_constraint(constraint);
            if (result == ApplyConstraintResult::Rejected) {
                m_rejected_constraints.push_back(constraint);
            } else {
                m_accepted_constraints.push_back(constraint);
            }
            return result;
        }

      // public abstract properties:
      public:
        virtual bool is_concrete() const = 0;
    };

    //
    //
    // 2. Concrete Solns:
    //
    //

    class ConcreteSoln: public Soln {
      public:
        ConcreteSoln(RoughClass rough_class)
        : Soln(rough_class) {}

      public:
        virtual bool is_concrete() const override {
            return true;
        }
    };
    
    //
    // (a) Types:
    //
    class ConcreteTypeSoln: public ConcreteSoln {
      public:
        ConcreteTypeSoln(RoughClass rough_class)
        : ConcreteSoln(rough_class) {}

      public:
        virtual TvKind tv_kind() const override {
            return TvKind::Type;
        }
    };
    class UnitSoln: public ConcreteTypeSoln {
      public:
        UnitSoln()
        : ConcreteTypeSoln(RoughClass::Unit) {}
    };
    class IntSoln: public ConcreteTypeSoln {
      private:
        int  m_width_in_bits;
        bool m_using_sign_ext;
      public:
        IntSoln(int width_in_bits, bool using_sign_ext)
        : ConcreteTypeSoln(RoughClass::Int), 
          m_width_in_bits(width_in_bits),
          m_using_sign_ext(using_sign_ext) {}
    };
    class FloatSoln: public ConcreteTypeSoln {
      private:
        int m_width_in_bits;
      public:
        FloatSoln(int width_in_bits)
        : ConcreteTypeSoln(RoughClass::Float),
          m_width_in_bits(width_in_bits) {}
    };
    class PtrSoln: public ConcreteTypeSoln {
      private:
        ConcreteTypeSoln* m_pointee_soln;
      public:
        PtrSoln(ConcreteTypeSoln* pointee_soln)
        : ConcreteTypeSoln(RoughClass::Ptr),
          m_pointee_soln(pointee_soln) {}
    };
    class StructSoln: public ConcreteTypeSoln {
      public:
        class Field {
          private:
            bool              m_embed;
            intern::String    m_name;
            ConcreteTypeSoln* m_type;
          public:
            Field(bool embed, intern::String name, ConcreteTypeSoln* type)
            : m_embed(embed),
              m_name(name),
              m_type(type) {}
        };
      private:
        std::vector<StructSoln::Field> m_fields;
      public:
        StructSoln(std::vector<StructSoln::Field>&& fields)
        : ConcreteTypeSoln(RoughClass::Struct),
          m_fields(std::move(fields)) {}
    };
    class EnumSoln: public ConcreteTypeSoln {
      public:
        enum class FieldKind {
            ExplicitTs,
            DefaultTs
        };
        class Field {
          private:
            EnumSoln::FieldKind m_kind;
            intern::String      m_name;
            ConcreteTypeSoln*   m_typepsec_soln;
          public:
            Field(intern::String name)
            : m_kind(EnumSoln::FieldKind::DefaultTs),
              m_name(name),
              m_typepsec_soln(nullptr) {}
            Field(intern::String name, ConcreteTypeSoln* typespec_soln)
            : m_kind(EnumSoln::FieldKind::ExplicitTs),
              m_name(name),
              m_typepsec_soln(typespec_soln) {}
        };
      private:
        std::vector<Field> m_fields;
      public:
        EnumSoln(std::vector<EnumSoln::Field>&& fields)
        : ConcreteTypeSoln(RoughClass::Enum),
          m_fields(std::move(fields)) {}
    };
    
    class ModuleSoln: public ConcreteTypeSoln {
      public:
        enum class FieldKind {
            Value,
            Type,
            Typeclass,
            ConstVal_TFunc,
            Type_TFunc
        };
        class Field {
          private:
            ModuleSoln::FieldKind m_kind;
            intern::String        m_name;
            ConcreteSoln*         m_opt_type_soln;
          public:
            Field(ModuleSoln::FieldKind kind, intern::String name, ConcreteTypeSoln* opt_type_soln)
            : m_kind(kind),
              m_name(name),
              m_opt_type_soln(opt_type_soln) {}
        };
      private:
        std::vector<ModuleSoln::Field> m_fields;
      public:
        ModuleSoln(std::vector<ModuleSoln::Field>&& fields)
        : ConcreteTypeSoln(RoughClass::Module),
          m_fields(std::move(fields)) {}
    };
    class ClassSoln: public ConcreteTypeSoln {
      public:
        enum class Member_Kind {
            Data,
            Message
        };
        enum class Member_Visibility {
            Public,
            Private
        };
        enum class Member_Existence {
            Abstract,
            Defined
        };
        class Member {
          private:
            Member_Kind       m_kind;
            Member_Visibility m_visibility;
            Member_Existence  m_existence;
            ConcreteTypeSoln* m_concrete_type_soln;
          public:
            Member(Member_Kind kind, Member_Visibility visibility, Member_Existence existence, ConcreteTypeSoln* concrete_type_soln)
            : m_kind(kind),
              m_visibility(visibility),
              m_existence(existence),
              m_concrete_type_soln(concrete_type_soln) {}
        };
      private:
        std::vector<ClassSoln::Member> m_members;
      public:
        ClassSoln(std::vector<ClassSoln::Member>&& mov_members)
        : ConcreteTypeSoln(RoughClass::Class),
          m_members(std::move(mov_members)) {}
    };
    class VFuncSoln: public ConcreteTypeSoln {
      public:
        class FormalArg {
          private:
            intern::String    m_name;
            ConcreteTypeSoln* m_arg_type;
          public:
            FormalArg(intern::String name, ConcreteTypeSoln* arg_type)
            : m_name(name),
              m_arg_type(arg_type) {}
        };
      private:
        std::vector<VFuncSoln::FormalArg> m_formal_args;
        TV*                               m_ret_tv;
      public:
        VFuncSoln(std::vector<VFuncSoln::FormalArg>&& mov_formal_args, TV* ret_tv);
    };

    class TFuncSoln: public ConcreteSoln {
      public:
        enum class ArgKind {
            Type,
            Value
        };
        class FormalArg {
          private:
            ArgKind        m_kind;
            intern::String m_name;
            ConcreteSoln*  m_typespec;
          public:
            FormalArg(ArgKind kind, intern::String name, ConcreteSoln* typespec)
            : m_kind(kind),
              m_name(name),
              m_typespec(typespec) {}
        };
        class ActualArg {
          private:
            ArgKind       m_arg_kind;
            ConcreteSoln* m_value;
          public:
            ActualArg(ArgKind arg_kind, ConcreteSoln* value)
            : m_arg_kind(arg_kind),
              m_value(value) {}
        };
      private:
        std::vector<TFuncSoln::FormalArg> m_formal_args;
        std::vector<TV*>                  m_actual_args;
        bool                              m_returns_val_not_type;
      public:
        TFuncSoln(std::vector<TFuncSoln::FormalArg>&& mov_formal_args, TV* ret_tv, bool returns_val_not_type)
        : ConcreteSoln(RoughClass::TFunc), 
          m_formal_args(std::move(mov_formal_args)),
          m_actual_args(m_formal_args.size()),
          m_returns_val_not_type(returns_val_not_type) {}
    };
    class TypeclassSoln: public ConcreteSoln {
      private:
        std::vector<Constraint*> m_constraints;
      public:
        TypeclassSoln(std::vector<Constraint*>&& constraints)
        : ConcreteSoln(RoughClass::Typeclass),
          m_constraints(std::move(constraints)) {}
    };

    //
    //
    // 3. Non-concrete Type Soln: MonomorphicVarSoln, PolymorphicVarSoln
    //
    //

    class VarSoln: public Soln {
      protected:
        VarSoln(RoughClass rough_class)
        : Soln(rough_class) {}
      public:
        virtual bool is_concrete() const override {
            return false;
        }
    };
    class MonomorphicVarSoln: public VarSoln {
      private:
        ConcreteSoln* m_concrete_substitute;
      public:
        MonomorphicVarSoln()
        : VarSoln(RoughClass::MonomorphicVar) {}
    };
    class PolymorphicVarSoln: public VarSoln {
      private:
        std::vector<ConcreteSoln*> m_concrete_substitutes;
      public:
        PolymorphicVarSoln()
        : VarSoln(RoughClass::PolymorphicVar) {}
    };

    //
    //
    // 4. Value Soln: ConstVal
    //
    //

    class ConstVal: public Soln {

    };

    // class VarSoln: Soln {
    //   private:
    //     // SuperRec/SubRec store a super/sub soln and the constraint index 
    //     struct SuperOrSubRec;
    //     using SuperRec = SuperOrSubRec;
    //     using SubRec = SuperOrSubRec;
    //     struct SupOrSubTypingRec {
    //         Soln* m_soln;
    //         Rule* m_rule;
    //     };

    //   private:
    //     std::vector<Constraint*> m_constraints;
    //     std::vector<SuperRec> m_super_recs;
    //     std::vector<SubRec> m_sub_recs;

    //   public:
    //     virtual bool can_satisfy(Constraint const* constraint) const = 0;
    //     virtual bool must_satisfy(Constraint const* constraint)      = 0;

    //   public:
    //     virtual bool is_concrete() const {
    //         return m_
    //     }
    // };


}   // namespace pdm::typer

#endif  // INLCUDED_KIND_HH
