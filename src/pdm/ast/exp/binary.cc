#include "binary.hh"

namespace pdm::ast {

    char const* binary_operator_name(BinaryOperator binary_operator) {
        switch (binary_operator) {
            case ast::BinaryOperator::Mul: return "multiply";
            case ast::BinaryOperator::Div: return "divide";
            case ast::BinaryOperator::Rem: return "modulo";
            case ast::BinaryOperator::Add: return "add";
            case ast::BinaryOperator::Subtract: return "subtract";
            case ast::BinaryOperator::Less: return "less";
            case ast::BinaryOperator::Greater: return "greater";
            case ast::BinaryOperator::LessOrEq: return "less_or_eq";
            case ast::BinaryOperator::GreaterOrEq: return "greater_or_eq";
            case ast::BinaryOperator::Equals: return "equals";
            case ast::BinaryOperator::NotEquals: return "not_equals";
            case ast::BinaryOperator::And: return "and";
            case ast::BinaryOperator::XOr: return "xor";
            case ast::BinaryOperator::Or: return "or";
            case ast::BinaryOperator::META_Count: return "META_Count";
        }
    }

}