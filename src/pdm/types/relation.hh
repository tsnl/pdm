#ifndef INCLUDED_PDM_TYPES_RELATION_HH
#define INCLUDED_PDM_TYPES_RELATION_HH

#include <vector>
#include <string>

#include "pdm/source/source.hh"
#include "pdm/ast/node.hh"
#include "pdm/ast/exp/id.hh"
#include "pdm/ast/arg/targ.hh"

#include "var.hh"

//
// forward declarations:
//

namespace pdm::types {
    class Constraint;
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
        Relation(ast::Node* ast_node, std::string&& why)
        : m_who(ast_node),
          m_why(std::move(why)),
          m_apply_state(ApplyState::NotApplied) {}

      // 'apply' interface:
      // todo: enable and implement for type solution.
      public:
        // apply returns 'true' if any change was made to the system, otherwise 'false'
        // when all relations apply false, the constraint set is at a fixed point
        bool apply();
    };

    // IdTypingRelation for (x T) or <T Cls>
    class IdTypingRelation: public Relation {
      private:
        intern::String m_lhs_name;
        Var*           m_lhs_tv;
        Var*           m_rhs_typespec;

      protected:
        IdTypingRelation(ast::Node* ast_node, intern::String lhs_name, Var* lhs_tv, Var* rhs_typespec)
        : Relation(ast_node, "IdTypingRelation:" + std::string(lhs_name.content())),
          m_lhs_name(lhs_name), 
          m_lhs_tv(lhs_tv),
          m_rhs_typespec(rhs_typespec) {}
    };
    class ValueIdTypingRelation: public IdTypingRelation {
      public:
        ValueIdTypingRelation(ast::Node* ast_node, intern::String lhs_vid_name, TypeVar* lhs_tv, TypeVar* rhs_typespec_tv)
        : IdTypingRelation(ast_node, lhs_vid_name, lhs_tv, rhs_typespec_tv) {}
    };
    class TypeIdTypingRelation: public IdTypingRelation {
      public:
        TypeIdTypingRelation(ast::Node* ast_node, intern::String lhs_tid_name, ClassVar* lhs_cv, ClassVar* rhs_typespec_cv)
        : IdTypingRelation(ast_node, lhs_tid_name, lhs_cv, rhs_typespec_cv) {}
    };

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
    };

    // '.' accessors:
    enum class DotNameRelationHint {
        ModuleType,                 // a.T
        StructFieldOrModuleField,   // a.v
        EnumField,                  // T.E
        TypeField                   // T.e
    };
    class DotNameRelation: public Relation {
      private:
        TypeVar*            m_lhs;
        intern::String      m_rhs_name;
        DotNameRelationHint m_hint;
      public:
        DotNameRelation(ast::Node* ast_node, TypeVar* lhs, intern::String rhs_name, DotNameRelationHint hint);

      public:
        TypeVar* lhs() const;
        intern::String rhs_name() const;
        DotNameRelationHint hint() const;
    };
    inline DotNameRelation::DotNameRelation(ast::Node* ast_node, TypeVar* lhs, intern::String rhs_name, DotNameRelationHint hint)
    :   Relation(ast_node, "DotNameRelation"),
        m_lhs(lhs),
        m_rhs_name(rhs_name),
        m_hint(hint) 
    {}
    inline TypeVar* DotNameRelation::lhs() const {
        return m_lhs;
    }
    inline intern::String DotNameRelation::rhs_name() const {
        return m_rhs_name;
    }
    inline DotNameRelationHint DotNameRelation::hint() const {
        return m_hint;
    }

    class DotIndexRelation: public Relation {
      private:
        TypeVar* m_lhs;
        int      m_rhs_index;

      public:
        DotIndexRelation(ast::Node* ast_node, TypeVar* lhs, int rhs_index);

      public:
        TypeVar* lhs() const;
        int rhs_index() const;
    };
    inline DotIndexRelation::DotIndexRelation(ast::Node* ast_node, TypeVar* lhs, int rhs_index)
    :   Relation(ast_node, "DotIndexRelation"),
        m_lhs(lhs),
        m_rhs_index(rhs_index) {};
    inline TypeVar* DotIndexRelation::lhs() const {
        return m_lhs;
    }
    inline int DotIndexRelation::rhs_index() const {
        return m_rhs_index;
    }

    // vcall (func()): definition and use
    enum class FnRelationKind {
        Formal,   // in this call, formal arguments are equal to actual arguments
        Actual    // in this call, formal arguments are supertypes of actual arguments
    };
    class FnRelation: public Relation {
      private:
        FnRelationKind        m_fn_relation_kind;
        TypeVar*              m_fn_tv;
        std::vector<TypeVar*> m_args_tvs;
        TypeVar*              m_ret_tv;
      
      protected:
        FnRelation(FnRelationKind func_relation_kind, ast::Node* ast_node, TypeVar* fn_tv, std::vector<TypeVar*>&& args_tvs, TypeVar* ret_tv)
        :   Relation(ast_node, "FnRelation"),
            m_fn_relation_kind(func_relation_kind),
            m_fn_tv(fn_tv),
            m_args_tvs(std::move(args_tvs)),
            m_ret_tv(ret_tv) 
        {}

      public:
        FnRelationKind fn_relation_kind() const {
            return m_fn_relation_kind;
        }
        TypeVar* fn_tv() const {
            return m_fn_tv;
        }
        std::vector<TypeVar*> const& args_tvs() const {
            return m_args_tvs;
        }
        TypeVar* ret_tv() const {
            return m_ret_tv;
        }
    };
    class FormalFnRelation: public FnRelation {
      public:
        FormalFnRelation(ast::Node* ast_node, TypeVar* fn_tv, std::vector<TypeVar*>&& args_tvs, TypeVar* ret_tv)
        :   FnRelation(FnRelationKind::Formal, ast_node, fn_tv, std::move(args_tvs), ret_tv)
        {}
    };
    class ActualFnRelation: public FnRelation {
      public:
        ActualFnRelation(ast::Node* ast_node, TypeVar* fn_tv, std::vector<TypeVar*>&& args_tvs, TypeVar* ret_tv)
        :   FnRelation(FnRelationKind::Actual, ast_node, fn_tv, std::move(args_tvs), ret_tv)
        {}
    };

    // if-then, if-then-else:
    class IfThenRelation: public Relation {
      private:
        TypeVar* m_cond;
        TypeVar* m_then;
      public:
        IfThenRelation(ast::Node* ast_node, TypeVar* cond, TypeVar* then)
        : Relation(ast_node, "IfThenRelation"),
          m_cond(cond),
          m_then(then) {}
    };
    class IfThenElseRelation: public Relation {
      private:
        TypeVar* m_cond;
        TypeVar* m_then;
        TypeVar* m_else;
      public:
        IfThenElseRelation(ast::Node* ast_node, TypeVar* cond_tv, TypeVar* then_tv, TypeVar* else_tv)
        : Relation(ast_node, "IfThenElseRelation"),
          m_cond(cond_tv),
          m_then(then_tv),
          m_else(else_tv) {}
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
    };

    // convert
    class ConvertableRelation: public Relation {
      private:
        TypeVar* m_dst;
        TypeVar* m_src;
      public:
        ConvertableRelation(ast::Node* ast_node, TypeVar* dst_tv, TypeVar* src_tv)
        : Relation(ast_node, "ConvertableRelation") {}
    };

    // todo: tcalls need more work; separate formal and actual like fun.
    // tcall: definition and use
    class TemplateCallRelation: public Relation {
      private:
        TemplateVar*                   m_lhs_template_var;
        std::vector<ast::TArg*> const& m_actual_targs;
        
      protected:
        TemplateCallRelation(
            ast::Node* ast_node,
            TemplateVar* lhs_template_var,
            std::vector<ast::TArg*> const& actual_targs
        );
    };
    class ValueTemplateCallRelation: public TemplateCallRelation {
      private:
        TypeVar* m_typeof_ret_tv;

      public:
        ValueTemplateCallRelation(
            ast::Node* ast_node,
            TemplateVar* lhs_template_var,
            std::vector<ast::TArg*> const& actual_targs,
            TypeVar* typeof_ret_tv
        );
    };
    class TypeTemplateCallRelation: public TemplateCallRelation {
      private:
        TypeVar* m_ret_tv;

      public:
        TypeTemplateCallRelation(
            ast::Node* ast_node,
            TemplateVar* lhs_template_var,
            std::vector<ast::TArg*> const& actual_targs,
            TypeVar* ret_tv
        );
    };
    class TypeclassTemplateCallRelation: public TemplateCallRelation {
      private:
        ClassVar* m_ret_cv;

      public:
        TypeclassTemplateCallRelation(
            ast::Node* ast_node,
            TemplateVar* lhs_template_var,
            std::vector<ast::TArg*> const& actual_targs,
            ClassVar* ret_cv
        );
    };

}

#endif  // INCLUDED_PDM_TYPES_RELATION_HH