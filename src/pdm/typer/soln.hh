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
        std::string m_name;
        
      // public getters:
      public:
        RoughClass rough_class() const {
            return m_rough_class;
        }
        std::string const& name() const {
            return m_name;
        }
        
      // protected constructors:
      protected:
        Soln(std::string&& name, RoughClass rough_class)
        : m_name(std::move(name)),
          m_rough_class(rough_class) {}

      // public: solution update methods:
      public:
        // todo: enable this when ready
        // virtual ApplyConstraintResult apply_constraint(Constraint* constraint) = 0;

      // public abstract properties:
      public:
        virtual TvKind tv_kind() const = 0;
        virtual bool is_concrete() const = 0;
    };

    //
    //
    // 2. Concrete Solns:
    //
    //

    class ConcreteSoln: public Soln {
      public:
        ConcreteSoln(std::string&& name, RoughClass rough_class)
        : Soln(std::move(name), rough_class) {}

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
        ConcreteTypeSoln(std::string&& name, RoughClass rough_class)
        : ConcreteSoln(std::move(name), rough_class) {}

      public:
        virtual TvKind tv_kind() const override {
            return TvKind::Type;
        }
    };
    class VoidSoln: public ConcreteTypeSoln {
      // shared singletons:
      private:
        static VoidSoln s_singleton;
      public:
        static VoidSoln* get() { return &s_singleton; }

      // protected constructor:
      protected:
        VoidSoln()
        : ConcreteTypeSoln("Unit", RoughClass::Void) {}
    };
    class IntSoln: public ConcreteTypeSoln {
      private:
        int  m_width_in_bits;
        bool m_using_sign_ext;

      // shared singletons:
      private:
        static IntSoln s_i8_singleton;
        static IntSoln s_i16_singleton;
        static IntSoln s_i32_singleton;
        static IntSoln s_i64_singleton;
        static IntSoln s_i128_singleton;
        static IntSoln s_u1_singleton;
        static IntSoln s_u8_singleton;
        static IntSoln s_u16_singleton;
        static IntSoln s_u32_singleton;
        static IntSoln s_u64_singleton;
        static IntSoln s_u128_singleton;
      public:
        static IntSoln* get_i8() { return &s_i8_singleton; }
        static IntSoln* get_i16() { return &s_i16_singleton; }
        static IntSoln* get_i32() { return &s_i32_singleton; }
        static IntSoln* get_i64() { return &s_i64_singleton; }
        static IntSoln* get_i128() { return &s_i128_singleton; }
        static IntSoln* get_u1() { return &s_u8_singleton; }
        static IntSoln* get_u8() { return &s_u8_singleton; }
        static IntSoln* get_u16() { return &s_u16_singleton; }
        static IntSoln* get_u32() { return &s_u32_singleton; }
        static IntSoln* get_u64() { return &s_u64_singleton; }
        static IntSoln* get_u128() { return &s_u128_singleton; }

      // protected constructor:
      protected:
        IntSoln(std::string&& name, int width_in_bits, bool using_sign_ext)
        : ConcreteTypeSoln(std::move(name), RoughClass::Int), 
          m_width_in_bits(width_in_bits),
          m_using_sign_ext(using_sign_ext) {}
    };
    class FloatSoln: public ConcreteTypeSoln {
      private:
        int m_width_in_bits;

      private:
        static FloatSoln s_float16_singleton;
        static FloatSoln s_float32_singleton;
        static FloatSoln s_float64_singleton;
      public:
        static FloatSoln* get_f16() { return &s_float16_singleton; }
        static FloatSoln* get_f32() { return &s_float32_singleton; }
        static FloatSoln* get_f64() { return &s_float64_singleton; }

      protected:
        FloatSoln(std::string&& name, int width_in_bits)
        : ConcreteTypeSoln(std::move(name), RoughClass::Float),
          m_width_in_bits(width_in_bits) {}
    };
    class PtrSoln: public ConcreteTypeSoln {
      private:
        ConcreteTypeSoln* m_pointee_soln;
      public:
        PtrSoln(ConcreteTypeSoln* pointee_soln)
        : ConcreteTypeSoln("^" + pointee_soln->name(), RoughClass::Ptr),
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
        : ConcreteTypeSoln("Struct{}", RoughClass::Struct),
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
        : ConcreteTypeSoln("Enum{}", RoughClass::Enum),
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
        : ConcreteTypeSoln("Module{}", RoughClass::Module),
          m_fields(std::move(fields)) {}
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
        : ConcreteSoln("TemplateFunc<>", RoughClass::TFunc), 
          m_formal_args(std::move(mov_formal_args)),
          m_actual_args(m_formal_args.size()),
          m_returns_val_not_type(returns_val_not_type) {}
    };
    class TypeclassSoln: public ConcreteSoln {
      private:
        std::vector<Constraint*> m_constraints;
      public:
        TypeclassSoln(std::vector<Constraint*>&& constraints)
        : ConcreteSoln("Typeclass{}", RoughClass::Typeclass),
          m_constraints(std::move(constraints)) {}
    };

    //
    //
    // 3. Non-concrete Type Soln: MonomorphicVarSoln, PolymorphicVarSoln
    //
    //

    class VarSoln: public Soln {
      protected:
        VarSoln(std::string&& name, RoughClass rough_class)
        : Soln(std::move(name), rough_class) {}
      public:
        virtual bool is_concrete() const override {
            return false;
        }
        virtual TvKind tv_kind() const override {
            // todo: what about value solutions for tcalls?
            return TvKind::Type;
        }
    };
    class MonomorphicVarSoln: public VarSoln {
      private:
        ConcreteSoln* m_concrete_substitute;
      public:
        MonomorphicVarSoln(std::string&& name)
        : VarSoln(std::move(name), RoughClass::MonomorphicVar) {}
    };
    class PolymorphicVarSoln: public VarSoln {
      private:
        std::vector<ConcreteSoln*> m_concrete_substitutes;
      public:
        PolymorphicVarSoln(std::string&& name)
        : VarSoln(std::move(name), RoughClass::PolymorphicVar) {}
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
