#ifndef INCLUDED_PDM_TYPES_RELATION_HH
#define INCLUDED_PDM_TYPES_RELATION_HH

#include <vector>
#include <string>
#include <map>

#include "pdm/source/i-source.hh"
#include "pdm/ast/node.hh"
#include "pdm/ast/exp/id.hh"
#include "pdm/ast/arg/targ.hh"
#include "pdm/ast/pattern/tpattern.hh"

#include "var.hh"
#include "typeop_result.hh"
#include "var_invariant.hh"

//
// forward declarations:
//

namespace pdm::types {
    class Manager;
    class VarInvariant;
    class Var;
    class TypeVar;
    class ClassVar;
}

//
// implementation:
//

namespace pdm::types {

    class Relation {
      private:
        enum class ApplyState {
            NotApplied,
            Applied_OK,
            Applied_Fail
        };
        
      // private data members:
      private:
        ast::Node*  m_who;
        std::string m_why;
        ApplyState  m_apply_state;

      // protected constructor => pure abstract
      protected:
        inline Relation(ast::Node* ast_node, std::string&& why);

      // 'apply' interface:
      public:
        // apply returns 'true' if any change was made to the system, otherwise 'false'
        // when all relations apply false, the invariant set is at a fixed point
        void on_assume(types::Manager* manager);

      protected:
        virtual bool on_assume_impl(types::Manager* manager) = 0;
    };

    Relation::Relation(ast::Node* ast_node, std::string&& why)
    :   m_who(ast_node),
        m_why(std::move(why)),
        m_apply_state(ApplyState::NotApplied)
    {}

    //
    // subtype, subclass, class-of, and equality
    //

    class SubtypeOfRelation;
    class SubclassOfRelation;
    class ClassOfRelation;

    class TypeEqualsRelation;
    class ClassEqualsRelation;

    class SubtypeOfRelation: public Relation {
        friend TypeEqualsRelation;

      private:
        TypeVar* m_subtype_tv;
        TypeVar* m_supertype_tv;
      public:
        SubtypeOfRelation(ast::Node* node, TypeVar* subtype_tv, TypeVar* supertype_tv);
      protected:
        bool on_assume_impl(types::Manager* manager) override;
    };
    inline SubtypeOfRelation::SubtypeOfRelation(ast::Node* node, TypeVar* subtype_tv, TypeVar* supertype_tv)
    :   Relation(node, "SubtypeOf"),
        m_subtype_tv(subtype_tv),
        m_supertype_tv(supertype_tv)
    {}

    class SubclassOfRelation: public Relation {
        friend ClassEqualsRelation;

      private:
        ClassVar* m_subclass_cv;
        ClassVar* m_superclass_cv;
      public:
        SubclassOfRelation(ast::Node* node, ClassVar* subclass_cv, ClassVar* superclass_cv);
      protected:
        bool on_assume_impl(types::Manager* manager) override;
    };
    inline SubclassOfRelation::SubclassOfRelation(ast::Node* node, ClassVar* subclass_cv, ClassVar* superclass_cv)
    :   Relation(node, std::move(std::string("SubclassOf"))),
        m_subclass_cv(subclass_cv),
        m_superclass_cv(superclass_cv)
    {}

    class ClassOfRelation: public Relation {
      private:
        ClassVar* m_class_cv;
        TypeVar* m_member_tv;
      public:
        inline ClassOfRelation(ast::Node* node, ClassVar* class_cv, TypeVar* member_tv);
      protected:
        bool on_assume_impl(types::Manager* manager) override;
    };
    inline ClassOfRelation::ClassOfRelation(ast::Node* node, ClassVar* class_cv, TypeVar* member_tv)
    :   Relation(node, std::move(std::string("ClassOf"))),
        m_class_cv(class_cv),
        m_member_tv(member_tv)
    {}
  
    // forced equality relations:
    class TypeEqualsRelation: public Relation {
      private:
        TypeVar* m_lhs_tv;
        TypeVar* m_rhs_tv;
        SubtypeOfRelation m_lhs_subtype_of_rhs_relation;
        SubtypeOfRelation m_rhs_subtype_of_lhs_relation;
      public:
        TypeEqualsRelation(ast::Node* node, TypeVar* lhs_tv, TypeVar* rhs_tv);
      protected:
        bool on_assume_impl(types::Manager* manager) override;
    };
    inline TypeEqualsRelation::TypeEqualsRelation(ast::Node* node, TypeVar* lhs_tv, TypeVar* rhs_tv)
    :   Relation(node, "TypeEquals"),
        m_lhs_tv(lhs_tv),
        m_rhs_tv(rhs_tv),
        m_lhs_subtype_of_rhs_relation(node, lhs_tv, rhs_tv),
        m_rhs_subtype_of_lhs_relation(node, rhs_tv, lhs_tv)
    {}
    class ClassEqualsRelation: public Relation {
      private:
        ClassVar* m_lhs_cv;
        ClassVar* m_rhs_cv;
        SubclassOfRelation m_lhs_subclass_of_rhs_relation;
        SubclassOfRelation m_rhs_subclass_of_lhs_relation;
      public:
        ClassEqualsRelation(ast::Node* node, ClassVar* lhs_cv, ClassVar* rhs_cv);
      protected:
        bool on_assume_impl(types::Manager* manager) override;
    };
    inline ClassEqualsRelation::ClassEqualsRelation(ast::Node* node, ClassVar* lhs_cv, ClassVar* rhs_cv)
    :   Relation(node, "ClassEquals"),
        m_lhs_cv(lhs_cv),
        m_rhs_cv(rhs_cv),
        m_lhs_subclass_of_rhs_relation(node, lhs_cv, rhs_cv),
        m_rhs_subclass_of_lhs_relation(node, rhs_cv, lhs_cv)
    {}

    // LetValueRelation is used for const, val, var, and fn statements
    class LetValueRelation: public Relation {
      private:
        TypeVar* m_typeof_lhs_tv;
        TypeVar* m_typeof_rhs_tv;

      public:
        LetValueRelation(ast::Node* ast_node, TypeVar* typeof_lhs_tv, TypeVar* typeof_rhs_tv)
        : Relation(ast_node, "LetValueRelation"),
          m_typeof_lhs_tv(typeof_lhs_tv),
          m_typeof_rhs_tv(typeof_rhs_tv) {}

      public:
        TypeVar* typeof_lhs_tv() const {
            return m_typeof_lhs_tv;
        }
        TypeVar* typeof_rhs_tv() const {
            return m_typeof_rhs_tv;
        }

      protected:
        bool on_assume_impl(types::Manager* manager) override;
    };

    // LetTypeRelation is used for type statements
    class LetTypeRelation: public Relation {
      private:
        TypeVar* m_lhs_tv;
        TypeVar* m_rhs_tv;

      public:
        LetTypeRelation(ast::Node* ast_node, TypeVar* lhs_tv, TypeVar* rhs_tv)
        : Relation(ast_node, "LetTypeRelation"),
          m_lhs_tv(lhs_tv),
          m_rhs_tv(rhs_tv) {}

      public:
        TypeVar* lhs_tv() const {
            return m_lhs_tv;
        }
        TypeVar* rhs_tv() const {
            return m_rhs_tv;
        }

      protected:
        bool on_assume_impl(types::Manager* manager) override;
    };

    // LetClassRelation is used for typeclass statements
    class LetClassRelation: public Relation {
      private:
        ClassVar* m_lhs_cv;
        ClassVar* m_rhs_cv;

      public:
        LetClassRelation(ast::Node* ast_node, ClassVar* lhs_cv, ClassVar* rhs_cv)
        : Relation(ast_node, "LetClassRelation"),
          m_lhs_cv(lhs_cv),
          m_rhs_cv(rhs_cv) {}

      public:
        ClassVar* lhs_cv() const {
            return m_lhs_cv;
        }
        ClassVar* rhs_cv() const {
            return m_rhs_cv;
        }

      protected:
        virtual bool on_assume_impl(types::Manager* manager) override;
    };

    // '.' accessors:
    enum class DotNameRelationKind {
        ModuleTypeField,                 // a:T
        ModuleValueField,                // a:v
        StructValueField,                // a.v
        EnumValueField,                  // T.E (...)
        StructTypeField              // T.e
    };
    class DotNameRelation: public Relation {
      private:
        TypeVar*            m_lhs;
        intern::String      m_rhs_name;
        TypeVar*            m_eval_type;
        DotNameRelationKind m_dot_name_relation_kind;

      protected:
        inline DotNameRelation(ast::Node* ast_node, TypeVar* lhs, TypeVar* eval_type, intern::String rhs_name, DotNameRelationKind dot_name_relation_kind);

      public:
        TypeVar* lhs() const;
        intern::String rhs_name() const;
        TypeVar* eval_type() const;
        DotNameRelationKind dot_name_relation_kind() const;

      protected:
        virtual bool on_assume_impl(types::Manager* manager) override;
    };
    inline DotNameRelation::DotNameRelation(ast::Node* ast_node, TypeVar* lhs, TypeVar* eval_type, intern::String rhs_name, DotNameRelationKind dot_name_relation_kind)
    :   Relation(ast_node, "DotNameRelation"),
        m_lhs(lhs),
        m_eval_type(eval_type),
        m_rhs_name(rhs_name),
        m_dot_name_relation_kind(dot_name_relation_kind)
    {}
    inline TypeVar* DotNameRelation::lhs() const {
        return m_lhs;
    }
    inline intern::String DotNameRelation::rhs_name() const {
        return m_rhs_name;
    }
    inline TypeVar* DotNameRelation::eval_type() const {
        return m_eval_type;
    }
    inline DotNameRelationKind DotNameRelation::dot_name_relation_kind() const {
        return m_dot_name_relation_kind;
    }
    
    struct ModuleDotTypeRelation: public DotNameRelation {
        inline ModuleDotTypeRelation(ast::Node* ast_node, TypeVar* lhs, TypeVar* eval_type, intern::String rhs_name);
    };
    inline ModuleDotTypeRelation::ModuleDotTypeRelation(ast::Node* ast_node, TypeVar* lhs, TypeVar* eval_type, intern::String rhs_name)
    :   DotNameRelation(ast_node, lhs, eval_type, rhs_name, DotNameRelationKind::ModuleTypeField)
    {}
    
    struct ModuleDotValueRelation: public DotNameRelation {
        inline ModuleDotValueRelation(ast::Node* ast_node, TypeVar* lhs, TypeVar* eval_type, intern::String rhs_name);
    };
    inline ModuleDotValueRelation::ModuleDotValueRelation(ast::Node* ast_node, TypeVar* lhs, TypeVar* eval_type, intern::String rhs_name)
    :   DotNameRelation(ast_node, lhs, eval_type, rhs_name, DotNameRelationKind::ModuleValueField)
    {}

    struct StructDotValueRelation: public DotNameRelation {
        inline StructDotValueRelation(ast::Node* ast_node, TypeVar* lhs, TypeVar* eval_type, intern::String rhs_name);
    };
    inline StructDotValueRelation::StructDotValueRelation(ast::Node* ast_node, TypeVar* lhs, TypeVar* eval_type, intern::String rhs_name)
    :   DotNameRelation(ast_node, lhs, eval_type, rhs_name, DotNameRelationKind::StructValueField)
    {}

    class DotIndexRelation: public Relation {
      private:
        TypeVar* m_typeof_lhs_tv;
        TypeVar* m_typeof_rhs_index_tv;

      public:
        DotIndexRelation(ast::Node* ast_node, TypeVar* typeof_lhs_tv, TypeVar* typeof_rhs_tv);

      public:
        TypeVar* typeof_lhs_tv() const;
        TypeVar* typeof_rhs_index_tv() const;

      protected:
        bool on_assume_impl(types::Manager* manager) override;
    };
    inline DotIndexRelation::DotIndexRelation(ast::Node* ast_node, TypeVar* typeof_lhs_tv, TypeVar* typeof_rhs_index_tv)
    :   Relation(ast_node, "DotIndexRelation"),
        m_typeof_lhs_tv(typeof_lhs_tv),
        m_typeof_rhs_index_tv(typeof_rhs_index_tv) 
    {}
    inline TypeVar* DotIndexRelation::typeof_lhs_tv() const {
        return m_typeof_lhs_tv;
    }
    inline TypeVar* DotIndexRelation::typeof_rhs_index_tv() const {
        return m_typeof_rhs_index_tv;
    }

    class EnumDotNameRelation: public DotNameRelation {
      private:
        std::vector<TypeVar*> m_args;
      public:
        inline EnumDotNameRelation(ast::Node* ast_node, TypeVar* lhs, TypeVar* eval_type, intern::String rhs_name, std::vector<TypeVar*>&& typeof_args_tvs);
      public:
        [[nodiscard]] std::vector<TypeVar*> const& args() const {
            return m_args;
        }
    };
    inline EnumDotNameRelation::EnumDotNameRelation(ast::Node* ast_node, TypeVar* lhs, TypeVar* eval_type, intern::String rhs_name, std::vector<TypeVar*>&& typeof_args_tvs)
    :   DotNameRelation(ast_node, lhs, eval_type, rhs_name, DotNameRelationKind::EnumValueField)
    {}

    //
    // Bulk tuple, struct, enum:
    //

    class IsTupleRelation: public Relation {
      private:
        TypeVar* m_tuple_tv;
        std::vector<TypeVar*> m_fields_tvs;

      public:
        inline IsTupleRelation(std::string&& why, ast::Node* node, TypeVar* tuple_tv, std::vector<TypeVar*>&& fields_tvs);

      protected:
        bool on_assume_impl(types::Manager* types_mgr) override;
    };
    inline IsTupleRelation::IsTupleRelation(std::string&& why, ast::Node* node, TypeVar* tuple_tv, std::vector<TypeVar*>&& fields_tvs)
    :   Relation(node, "TupleOf:" + std::move(why)),
        m_tuple_tv(tuple_tv),
        m_fields_tvs(std::move(fields_tvs))
    {}

    class IsFieldCollectionRelation: public Relation {
      protected:
        enum class FieldCollectionKind {
            Struct,
            Enum,
            Module
        };

      private:
        TypeVar* m_collection_tv;
        std::map<intern::String, Var*> m_fields;
        FieldCollectionKind m_field_collection_kind;

      protected:
        inline IsFieldCollectionRelation(
            FieldCollectionKind field_collection_kind,
            std::string&& why,
            ast::Node* node,
            TypeVar* collection_tv,
            std::map<intern::String, Var*>&& fields_tvs
        );

      protected:
        bool on_assume_impl(types::Manager* manager) override;

      protected:
        [[nodiscard]] inline TypeVar* collection_tv() const;
        [[nodiscard]] inline FieldCollectionKind field_collection_kind() const;
    };
    inline IsFieldCollectionRelation::IsFieldCollectionRelation(
        FieldCollectionKind field_collection_kind,
        std::string&& why,
        ast::Node* node,
        TypeVar* collection_tv,
        std::map<intern::String, Var*>&& fields_tvs
    )
    :   Relation(node, std::move(why)),
        m_collection_tv(collection_tv),
        m_fields(std::move(fields_tvs)),
        m_field_collection_kind(field_collection_kind)
    {}
    inline TypeVar* 
    IsFieldCollectionRelation::collection_tv() const {
        return m_collection_tv;
    }
    inline IsFieldCollectionRelation::FieldCollectionKind
    IsFieldCollectionRelation::field_collection_kind() const {
        return m_field_collection_kind;
    }

    class IsStructRelation: public IsFieldCollectionRelation {
      public:
        IsStructRelation(
            std::string&& why,
            ast::Node* node,
            TypeVar* struct_tv,
            std::map<intern::String, Var*> fields_tvs
        );

      public:
        [[nodiscard]] inline TypeVar* struct_tv() const;
    };

    inline TypeVar* IsStructRelation::struct_tv() const {
        return collection_tv();
    }

    class IsEnumRelation: public IsFieldCollectionRelation {
      public:
        IsEnumRelation(
            std::string&& why,
            ast::Node* node,
            TypeVar* enum_tv,
            std::map<intern::String, Var*> fields_tvs
        );

      public:
        [[nodiscard]] inline TypeVar* enum_tv() const;
    };
    inline TypeVar* IsEnumRelation::enum_tv() const {
        return collection_tv();
    }

    class IsModuleRelation: public IsFieldCollectionRelation {
      public:
        IsModuleRelation(
            std::string&& why,
            ast::Node* node,
            TypeVar* module_tv,
            std::map<intern::String, Var*> fields_tvs
        );

      public:
        [[nodiscard]] inline TypeVar* module_tv() const;
    };
    inline TypeVar* IsModuleRelation::module_tv() const {
        return collection_tv();
    }

    //
    // vcall (func()): definition and use
    //

    enum class VCallableRelationStrength {
        Formal,   // in this call, formal arguments are equal to actual arguments
        Actual    // in this call, formal arguments are supertypes of actual arguments
    };
    class VCallableRelation: public Relation {
      private:
        VCallableRelationStrength m_strength;
        TypeVar*                  m_fn_tv;
        std::vector<VCallArg>     m_args;
        TypeVar*                  m_ret_tv;

      protected:
        VCallableRelation(VCallableRelationStrength strength, ast::Node* ast_node, TypeVar* fn_tv, std::vector<VCallArg>&& args, TypeVar* ret_tv)
        :   Relation(ast_node, "VCallableRelation"),
            m_strength(strength),
            m_fn_tv(fn_tv),
            m_args(std::move(args)),
            m_ret_tv(ret_tv)
        {}

      public:
        VCallableRelationStrength strength() const {
            return m_strength;
        }
        TypeVar* fn_tv() const {
            return m_fn_tv;
        }
        std::vector<VCallArg> const& args() const {
            return m_args;
        }
        TypeVar* ret_tv() const {
            return m_ret_tv;
        }
    };
    class FormalVCallableRelation: public VCallableRelation {
      public:
        FormalVCallableRelation(ast::Node* ast_node, TypeVar* fn_tv, std::vector<VCallArg>&& args_tvs, TypeVar* ret_tv);

      protected:
        bool on_assume_impl(types::Manager* manager) override;
    };
    class ActualVCallableRelation: public VCallableRelation {
      public:
        ActualVCallableRelation(ast::Node* ast_node, TypeVar* fn_tv, std::vector<VCallArg>&& args_tvs, TypeVar* ret_tv);

      protected:
        bool on_assume_impl(types::Manager* manager) override;
    };
    inline FormalVCallableRelation::FormalVCallableRelation(ast::Node* ast_node, TypeVar* fn_tv, std::vector<VCallArg>&& args_tvs, TypeVar* ret_tv)
    :   VCallableRelation(VCallableRelationStrength::Formal, ast_node, fn_tv, std::move(args_tvs), ret_tv)
    {}
    inline ActualVCallableRelation::ActualVCallableRelation(ast::Node* ast_node, TypeVar* fn_tv, std::vector<VCallArg>&& args_tvs, TypeVar* ret_tv)
    :   VCallableRelation(VCallableRelationStrength::Actual, ast_node, fn_tv, std::move(args_tvs), ret_tv)
    {}

    // if-then, if-then-else:
    class IfThenRelation: public Relation {
      private:
        TypeVar* m_output_tv;
        TypeVar* m_cond;
        TypeVar* m_then;

      public:
        IfThenRelation(ast::Node* ast_node, TypeVar* output_tv, TypeVar* cond, TypeVar* then)
        :   Relation(ast_node, "IfThenRelation"),
            m_output_tv(output_tv),
            m_cond(cond),
            m_then(then)
        {}

      protected:
        bool on_assume_impl(types::Manager* manager) override;
    };
    class IfThenElseRelation: public Relation {
      private:
        TypeVar* m_output;
        TypeVar* m_cond;
        TypeVar* m_then;
        TypeVar* m_else;

      public:
        IfThenElseRelation(ast::Node* ast_node, TypeVar* output_tv, TypeVar* cond_tv, TypeVar* then_tv, TypeVar* else_tv)
        : Relation(ast_node, "IfThenElseRelation"),
          m_output(output_tv),
          m_cond(cond_tv),
          m_then(then_tv),
          m_else(else_tv) {}

      protected:
        bool on_assume_impl(types::Manager* manager) override;
    };

    // cast
    class BitcastableRelation: public Relation {
      private:
        TypeVar* m_dst;
        TypeVar* m_src;

      public:
        BitcastableRelation(ast::Node* ast_node, TypeVar* dst_tv, TypeVar* src_tv)
        : Relation(ast_node, "BitcastableRelation"),
          m_dst(dst_tv),
          m_src(src_tv) {}

      protected:
        bool on_assume_impl(types::Manager* manager) override;
    };

    // convert
    class ConvertibleRelation: public Relation {
      private:
        TypeVar* m_dst;
        TypeVar* m_src;

      public:
        ConvertibleRelation(ast::Node* ast_node, TypeVar* dst_tv, TypeVar* src_tv)
        : Relation(ast_node, "ConvertableRelation") {}

      protected:
        bool on_assume_impl(types::Manager* manager) override;
    };

    // IsNumberRelation used to ensure numeric values resolve to a numeric class only (such that an assembler impl is
    // available)
    class IsNumberRelation: public Relation {
      private:
        TypeVar* m_number_tv;

      public:
        inline IsNumberRelation(ast::Node* ast_node, TypeVar* number_tv);

      protected:
        bool on_assume_impl(types::Manager* manager) override;
    };

    inline IsNumberRelation::IsNumberRelation(ast::Node* ast_node, TypeVar* number_tv)
    :   Relation(ast_node, "IsNumberRelation"),
        m_number_tv(number_tv)
    {}
}

#endif  // INCLUDED_PDM_TYPES_RELATION_HH
