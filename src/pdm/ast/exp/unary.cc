#include "unary.hh"


namespace pdm::ast {

    char const* unary_operator_name(UnaryOperator unary_operator) {
        switch (unary_operator) {
            case UnaryOperator::Not: return "not";
            case UnaryOperator::Plus: return "plus";
            case UnaryOperator::Minus: return "minus";
            case UnaryOperator::META_Count: return "META_Count";
        }
    }

}