#ifndef INCLUDED_PDM_TYPES_RULE_HH
#define INCLUDED_PDM_TYPES_RULE_HH

#include <vector>
#include <string>

#include "pdm/source/source.hh"
#include "pdm/ast/node.hh"
#include "pdm/ast/exp/id.hh"

//
// forward declarations:
//

namespace pdm::types {
    class Constraint;
    class TypeVar;
}


//
// implementation:
//

namespace pdm::types {
    
    class Rule {
      // private data members:
      private:
        ast::Node*  m_who;
        std::string m_why;

      // protected constructor => pure abstract
      protected:
        Rule(ast::Node* ast_node, std::string&& why)
        : m_who(ast_node),
          m_why(std::move(why)) {}

      // interface:
      public:
        // todo: re-enable once implemented for all subtypes.
        // virtual void apply() = 0;
    };

    // todo: implement various rules to handle each typing case in the language.
    //       each typing should add one or more rules to the typer

    // PatternTypespecRule for (x T) or <T Cls>
    class PatternTypespecRule: public Rule {
      private:
        intern::String m_lhs_name;
        TypeVar* m_lhs_tv;
        TypeVar* m_rhs_typespec;
      protected:
        PatternTypespecRule(ast::Node* ast_node, intern::String lhs_name, TypeVar* lhs_tv, TypeVar* rhs_typespec)
        : Rule(ast_node, "(" + std::string(lhs_name.content()) + " X)"),
          m_lhs_name(lhs_name), 
          m_lhs_tv(lhs_tv),
          m_rhs_typespec(rhs_typespec) {}
    };
    class PatternTypespecRule_VId: public PatternTypespecRule {
      public:
        PatternTypespecRule_VId(ast::Node* ast_node, intern::String lhs_vid_name, TypeVar* lhs_tv, TypeVar* rhs_typespec)
        : PatternTypespecRule(ast_node, lhs_vid_name, lhs_tv, rhs_typespec) {}
    };
    class PatternTypespecRule_TId: public PatternTypespecRule {
      public:
        PatternTypespecRule_TId(ast::Node* ast_node, intern::String lhs_tid_name, TypeVar* lhs_tv, TypeVar* rhs_typespec)
        : PatternTypespecRule(ast_node, lhs_tid_name, lhs_tv, rhs_typespec) {}
    };

    // AssignRule is used for let, def, type, enum, class, typeclass, module:
    class AssignRule: public Rule {
      private:
        TypeVar* m_lhs;
        TypeVar* m_rhs;
      public:
        AssignRule(ast::Node* ast_node, std::string const& assign_kind, TypeVar* lhs, TypeVar* rhs)
        : Rule(ast_node, "assign<" + assign_kind + ">"),
          m_lhs(lhs),
          m_rhs(rhs) {}
    };

    // '.' and '->' accessors:
    class LhsArrowNameRule: public Rule {
      private:
        TypeVar* m_lhs;
        intern::String m_rhs;
      public:
        LhsArrowNameRule(ast::Node* ast_node, TypeVar* lhs, intern::String rhs)
        : Rule(ast_node, "a -> b"),
          m_lhs(lhs), 
          m_rhs(rhs) {}
    };
    class LhsDotNameRule: public Rule {
      private:
        TypeVar* m_lhs;
        intern::String m_rhs_name;
      public:
        LhsDotNameRule(ast::Node* ast_node, TypeVar* lhs, intern::String rhs_name)
        : Rule(ast_node, "a . b"),
          m_lhs(lhs),
          m_rhs_name(rhs_name) {}
    };
    class LhsDotIndexRule: public Rule {
      private:
        TypeVar* m_lhs;
        int m_rhs_index;
      public:
        LhsDotIndexRule(ast::Node* ast_node, TypeVar* lhs, int rhs_index)
        : Rule(ast_node, "a .(b)"),
          m_lhs(lhs),
          m_rhs_index(rhs_index) {};
    };
    
    // () and <> substitutions:
    class VCallRule: public Rule {
      private:
        TypeVar*              m_lhs;
        std::vector<TypeVar*> m_args;
        TypeVar*              m_ret;
      public:
        VCallRule(ast::Node* ast_node, TypeVar* lhs, std::vector<TypeVar*>&& args, TypeVar* ret)
        : Rule(ast_node, "a(b...)"),
          m_lhs(lhs),
          m_args(std::move(args)),
          m_ret(ret) {}
    };
    class TCallRule: public Rule {
      private:
        TypeVar*              m_lhs;
        std::vector<TypeVar*> m_formal_args;
        TypeVar*              m_ret;
        bool             m_output_value_not_type;
      public:
        TCallRule(ast::Node* ast_node, TypeVar* lhs, std::vector<TypeVar*>&& formal_args, TypeVar* ret, bool output_value_not_type)
        : Rule(ast_node, "a<(B|b)...>"),
          m_lhs(lhs),
          m_formal_args(formal_args),
          m_ret(ret),
          m_output_value_not_type(output_value_not_type) {}
    };

    // if-then, if-then-else:
    class IfThenRule: public Rule {
      private:
        TypeVar* m_cond;
        TypeVar* m_then;
      public:
        IfThenRule(ast::Node* ast_node, TypeVar* cond, TypeVar* then)
        : Rule(ast_node, "if (a) then (b)"),
          m_cond(cond),
          m_then(then) {}
    };
    class IfThenElseRule: public Rule {
      private:
        TypeVar* m_cond;
        TypeVar* m_then;
        TypeVar* m_else;
      public:
        IfThenElseRule(ast::Node* ast_node, TypeVar* cond_tv, TypeVar* then_tv, TypeVar* else_tv)
        : Rule(ast_node, "if (a) then (b) else (c)"),
          m_cond(cond_tv),
          m_then(then_tv),
          m_else(else_tv) {}
    };

    // cast
    class BitcastRule: public Rule {
      private:
        TypeVar* m_dst;
        TypeVar* m_src;
      public:
        BitcastRule(ast::Node* ast_node, TypeVar* dst_tv, TypeVar* src_tv)
        : Rule(ast_node, "bitcast<A>(b)"),
          m_dst(dst_tv),
          m_src(src_tv) {}
    };

    // convert
    class ConvertRule: public Rule {
      private:
        TypeVar* m_dst;
        TypeVar* m_src;
      public:
        ConvertRule(ast::Node* ast_node, TypeVar* dst_tv, TypeVar* src_tv)
        : Rule(ast_node, "convert<A>(b)") {}
    };
}

#endif  // INCLUDED_PDM_TYPES_RULE_HH