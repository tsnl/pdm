#ifndef INCLUDED_PDM_TYPER_RULE_HH
#define INCLUDED_PDM_TYPER_RULE_HH

#include <string>

#include <pdm/source/source.hh>
#include <pdm/ast/node.hh>

#include "tv.hh"

//
// forward declarations:
//

namespace pdm::typer {
    class Constraint;
}


//
// implementation:
//

namespace pdm::typer {
    
    class Rule {
      // private data members:
      private:
        ast::Node*  m_who;
        std::string m_why;

      // protected constructor => pure abstract
      protected:
        Rule(ast::Node* ast_node, std::string&& why);

      // interface:
      public:
        virtual void apply() = 0;
    };

    // todo: implement various rules to handle each typing case in the language.
    //       each typing should add one or more rules to the typer

    // AssignRule is used for let, def, type, enum, class, typeclass, module:
    class AssignRule: public Rule {
      private:
        TV* m_lhs;
        TV* m_rhs;
      public:
        AssignRule(ast::Node* ast_node, std::string const& assign_kind, TV* lhs, TV* rhs)
        : Rule(ast_node, "assign<" + assign_kind + ">"),
          m_lhs(lhs),
          m_rhs(rhs) {}
    };

    // '.' and '->' accessors:
    class LhsArrowNameRule: public Rule {
      private:
        TV* m_lhs;
        intern::String m_rhs;
      public:
        LhsArrowNameRule(ast::Node* ast_node, TV* lhs, intern::String rhs)
        : Rule(ast_node, "a -> b"),
          m_lhs(lhs), 
          m_rhs(rhs) {}
    };
    class LhsDotNameRule: public Rule {
      private:
        TV* m_lhs;
        intern::String m_rhs_name;
      public:
        LhsDotNameRule(ast::Node* ast_node, TV* lhs, intern::String rhs_name)
        : Rule(ast_node, "a . b"),
          m_lhs(lhs),
          m_rhs_name(rhs_name) {}
    };
    class LhsDotIndexRule: public Rule {
      private:
        TV* m_lhs;
        int m_rhs_index;
      public:
        LhsDotIndexRule(ast::Node* ast_node, TV* lhs, int rhs_index)
        : Rule(ast_node, "a .(b)"),
          m_lhs(lhs),
          m_rhs_index(rhs_index) {};
    };
    
    // () and <> substitutions:
    class VCallRule: public Rule {
      private:
        TV*              m_lhs;
        std::vector<TV*> m_args;
        TV*              m_ret;
      public:
        VCallRule(ast::Node* ast_node, TV* lhs, std::vector<TV*>&& args, TV* ret)
        : Rule(ast_node, "a(b...)"),
          m_lhs(lhs),
          m_args(std::move(args)),
          m_ret(ret) {}
    };
    class TCallRule: public Rule {
      private:
        TV*              m_lhs;
        std::vector<TV*> m_formal_args;
        TV*              m_ret;
        bool             m_output_value_not_type;
      public:
        TCallRule(ast::Node* ast_node, TV* lhs, std::vector<TV*>&& formal_args, TV* ret, bool output_value_not_type)
        : Rule(ast_node, "a<(B|b)...>"),
          m_lhs(lhs),
          m_formal_args(formal_args),
          m_ret(ret),
          m_output_value_not_type(output_value_not_type) {}
    };

    // if-then, if-then-else:
    class IfThenRule: public Rule {
      private:
        TV* m_cond;
        TV* m_then;
      public:
        IfThenRule(ast::Node* ast_node, TV* cond, TV* then)
        : Rule(ast_node, "if (a) then (b)"),
          m_cond(cond),
          m_then(then) {}
    };
    class IfThenElseRule: public Rule {
      private:
        TV* m_cond;
        TV* m_then;
        TV* m_else;
      public:
        IfThenElseRule(ast::Node* ast_node, TV* cond_tv, TV* then_tv, TV* else_tv)
        : Rule(ast_node, "if (a) then (b) else (c)"),
          m_cond(cond_tv),
          m_then(then_tv),
          m_else(else_tv) {}
    };

    // cast
    class CastRule: public Rule {
      private:
        TV* m_dst;
        TV* m_src;
      public:
        CastRule(ast::Node* ast_node, TV* dst_tv, TV* src_tv)
        : Rule(ast_node, "cast<A>(b)"),
          m_dst(dst_tv),
          m_src(src_tv) {}
    };

    // convert
    class ConvertRule: public Rule {
      private:
        TV* m_dst;
        TV* m_src;
      public:
        ConvertRule(ast::Node* ast_node, TV* dst_tv, TV* src_tv)
        : Rule(ast_node, "convert<A>(b)") {}
    };
}

#endif  // INCLUDED_PDM_TYPER_RULE_HH