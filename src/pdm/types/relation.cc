#include "relation.hh"

namespace pdm::types {

    bool Relation::apply() {
        if (m_apply_state == ApplyState::NotApplied) {
            // todo: call an abstract virtual method here
            // todo: update m_apply_state based on the above result here.
            // - set Applied_OK if successful
            // - set Applied_Fail if unsuccessful
            return true;
        } else {
            return false;
        }
    }

    TemplateCallRelation::TemplateCallRelation(
        ast::Node* ast_node,
        TemplateVar* lhs_template_var,
        std::vector<ast::TArg*> const& actual_targs
    )
    :   Relation(ast_node, "TemplateCallRelation"),
        m_lhs_template_var(lhs_template_var),
        m_actual_targs(actual_targs)
    {}

    ValueTemplateCallRelation::ValueTemplateCallRelation(
        ast::Node* ast_node,
        TemplateVar* lhs_template_var,
        std::vector<ast::TArg*> const& actual_targs,
        TypeVar* typeof_ret_tv
    )
    :   TemplateCallRelation(ast_node, lhs_template_var, actual_targs),
        m_typeof_ret_tv(typeof_ret_tv)
    {}

    TypeTemplateCallRelation::TypeTemplateCallRelation(
        ast::Node* ast_node,
        TemplateVar* lhs_template_var,
        std::vector<ast::TArg*> const& actual_targs,
        TypeVar* ret_tv
    )
    :   TemplateCallRelation(ast_node, lhs_template_var, actual_targs),
        m_ret_tv(ret_tv)
    {}

    TypeclassTemplateCallRelation::TypeclassTemplateCallRelation(
        ast::Node* ast_node,
        TemplateVar* lhs_template_var,
        std::vector<ast::TArg*> const& actual_targs,
        ClassVar* ret_cv
    )
    :   TemplateCallRelation(ast_node, lhs_template_var, actual_targs),
        m_ret_cv(ret_cv)
    {}
}