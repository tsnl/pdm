#ifndef INCLUDED_PDM_TYPES_RULE_HH
#define INCLUDED_PDM_TYPES_RULE_HH

namespace pdm::ast {
    class Node;
}

namespace pdm::types {

    //
    // Base Rule:
    //

    class Rule {
      private:
        ast::Node* m_applied_at_astn;

      protected:
        Rule(ast::Node* applied_at_astn);
        virtual ~Rule();

      public:
        ast::Node* applied_at_astn() const;
    };

    inline        
    Rule::Rule(ast::Node* applied_at_astn)
    :   m_applied_at_astn(applied_at_astn)
    {}

    inline 
    ast::Node* Rule::applied_at_astn() const {
        return m_applied_at_astn;
    }

    //
    // Rule subclasses:
    //

}

#endif  // INCLUDED_PDM_TYPES_RULE_HH