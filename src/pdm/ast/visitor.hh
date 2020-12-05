#ifndef INCLUDED_PDM_AST_VISITOR_HH
#define INCLUDED_PDM_AST_VISITOR_HH

//
// forward declarations:
//

namespace pdm::ast {
    
    // base node:
    class Node;

    // script:
    class Script;

    // statements:
    class ModuleStmt;
    class ClassStmt;
    class EnumStmt;
    class TypeStmt;
    class DefStmt;
    class LetStmt;

    // expressions:
    class UnitExp;
    class IntExp;
    class FloatExp;
    class StringExp;
    class VIdExp;
    class TIdExp;
    class ParenExp;
    class TupleExp;
    class ArrayExp;
    class StructExp;
    class ChainExp;
    class LambdaExp;
    class IfExp;
    class MatchExp;
    class DotIndexExp;
    class DotNameExp;
    class UnaryExp;
    class BinaryExp;
    class VCallExp;
    class TCallExp;
    class CastExp;
    
    // patterns:
    class VPattern;     // used in def() and struct-typespec
    class TPattern;     // used in def<>/[], type<>/[], class<>/[]4
    class LPattern;     // used in let, lambda, match

    // todo: typespecs
    // todo: vfield, tfield

}   // namespace pdm::ast


//
// implementations:
//

namespace pdm::ast {

    class BaseVisitor {
        // BaseVisitor takes a pure-virtual method 'on_visit'
        // and applies it to each node in an AST recursively
      protected:
        virtual bool on_visit(Node* node, bool pre_not_post) = 0;
    };

    class BaseVisitor_Factored: public BaseVisitor {
      // dummy implementations of visitors per-kind.
      protected:
        // scripts:
        virtual bool on_visit__script(Node* node, bool pre_not_post) {
            return true;
        };

        // statements:
        virtual bool on_visit__module_stmt(ModuleStmt* node, bool pre_not_post) { 
            return true;
        };
        virtual bool on_visit__class_stmt(ClassStmt* node, bool pre_not_post) { 
            return true;
        };
        virtual bool on_visit__type_stmt(TypeStmt* node, bool pre_not_post) { 
            return true;
        };
        virtual bool on_visit__enum_stmt(EnumStmt* node, bool pre_not_post) {
            return true;
        }
        virtual bool on_visit__def_stmt(DefStmt* node, bool pre_not_post) { 
            return true;
        };
        virtual bool on_visit__let_stmt(LetStmt* node, bool pre_not_post) { 
            return true;
        };

        // expressions:
        virtual bool on_visit__unit_exp(UnitExp* node, bool pre_not_post) {
            return true;
        }
        virtual bool on_visit__int_exp(IntExp* node, bool pre_not_post) {
            return true;
        }
        virtual bool on_visit__float_exp(FloatExp* node, bool pre_not_post) {
            return true;
        }
        virtual bool on_visit__string_exp(StringExp* node, bool pre_not_post) {
            return true;
        }
        virtual bool on_visit__vid_exp(VIdExp* node, bool pre_not_post) {
            return true;
        }
        virtual bool on_visit__tid_exp(TIdExp* node, bool pre_not_post) {
            return true;
        }
        virtual bool on_visit__paren_exp(ParenExp* node, bool pre_not_post) {
            return true;
        }
        virtual bool on_visit__tuple_exp(TupleExp* node, bool pre_not_post) {
            return true;
        }
        virtual bool on_visit__array_exp(ArrayExp* node, bool pre_not_post) {
            return true;
        }
        virtual bool on_visit__struct_exp(StructExp* node, bool pre_not_post) {
            return true;
        }
        virtual bool on_visit__chain_exp(ChainExp* node, bool pre_not_post) {
            return true;
        }
        virtual bool on_visit__lambda_exp(LambdaExp* node, bool pre_not_post) {
            return true;
        }
        virtual bool on_visit__if_exp(IfExp* node, bool pre_not_post) {
            return true;
        }
        virtual bool on_visit__match_exp(MatchExp* node, bool pre_not_post) {
            return true;
        }
        virtual bool on_visit__dot_index_exp(DotIndexExp* node, bool pre_not_post) {
            return true;
        }
        virtual bool on_visit__dot_name_exp(DotNameExp* node, bool pre_not_post) {
            return true;
        }
        virtual bool on_visit__unary_exp(UnaryExp* node, bool pre_not_post) {
            return true;
        }
        virtual bool on_visit__binary_exp(BinaryExp* node, bool pre_not_post) {
            return true;
        }
        virtual bool on_visit__v_call_exp(VCallExp* node, bool pre_not_post) {
            return true;
        }
        virtual bool on_visit__t_call_exp(TCallExp* node, bool pre_not_post) {
            return true;
        }
        virtual bool on_visit__cast_exp(CastExp* node, bool pre_not_post) {
            return true;
        }

        // patterns:
        virtual bool on_visit__v_pattern(VPattern* node, bool pre_not_post) {
            return true;
        }
        virtual bool on_visit__t_pattern(TPattern* node, bool pre_not_post) {
            return true;
        }
        virtual bool on_visit__l_pattern(LPattern* node, bool pre_not_post) {
            return true;
        }

      // implementation of BaseVisitor's on_visit
      protected:
        // todo: add more virtual overloads per node-type
        // todo: implement 'on_visit', delegating to on_visit__...
        virtual bool on_visit(Node* node, bool pre_not_post) override;
    };

}   // namespace pdm::ast

#endif  // INCLUDED_PDM_AST_VISITOR_HH
