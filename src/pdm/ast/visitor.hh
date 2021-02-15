#ifndef INCLUDED_PDM_AST_VISITOR_HH
#define INCLUDED_PDM_AST_VISITOR_HH

#include "pdm/ast/exp/exp.hh"
#include "pdm/ast/exp/array.hh"
#include "pdm/ast/exp/binary.hh"
#include "pdm/ast/exp/chain.hh"
#include "pdm/ast/exp/dot.hh"
#include "pdm/ast/exp/float.hh"
#include "pdm/ast/exp/id.hh"
#include "pdm/ast/exp/if.hh"
#include "pdm/ast/exp/int.hh"
#include "pdm/ast/exp/lambda.hh"
#include "pdm/ast/exp/paren.hh"
#include "pdm/ast/exp/string.hh"
#include "pdm/ast/exp/struct.hh"
#include "pdm/ast/exp/tcall.hh"
#include "pdm/ast/exp/tuple.hh"
#include "pdm/ast/exp/type_query.hh"
#include "pdm/ast/exp/unary.hh"
#include "pdm/ast/exp/unit.hh"
#include "pdm/ast/exp/vcall.hh"

#include "pdm/ast/pattern/lpattern.hh"
#include "pdm/ast/pattern/tpattern.hh"
#include "pdm/ast/pattern/vpattern.hh"

#include "pdm/ast/script/script.hh"

#include "pdm/ast/stmt/stmt.hh"
#include "pdm/ast/stmt/const.hh"
#include "pdm/ast/stmt/mod_val.hh"
#include "pdm/ast/stmt/mod_enum.hh"
#include "pdm/ast/stmt/mod.hh"
#include "pdm/ast/stmt/mod_type.hh"
#include "pdm/ast/stmt/mod_typeclass.hh"
#include "pdm/ast/stmt/import.hh"
#include "pdm/ast/stmt/extern.hh"
#include "pdm/ast/stmt/builtin.hh"
#include "pdm/ast/stmt/discard.hh"
#include "pdm/ast/stmt/set.hh"
#include "pdm/ast/stmt/using.hh"
#include "pdm/ast/stmt/var.hh"
#include "pdm/ast/stmt/val.hh"

#include "pdm/ast/setspec/type_spec.hh"
#include "pdm/ast/setspec/class_spec.hh"
#include "pdm/ast/setspec/dot.hh"
#include "pdm/ast/setspec/id_type_spec.hh"
#include "pdm/ast/setspec/id_class_spec.hh"
#include "pdm/ast/setspec/struct.hh"
#include "pdm/ast/setspec/tcall.hh"
#include "pdm/ast/setspec/tuple.hh"
#include "pdm/ast/setspec/fn.hh"
#include "pdm/ast/setspec/type_spec.hh"
#include "pdm/ast/setspec/paren.hh"

#include "pdm/ast/arg/targ.hh"
#include "pdm/ast/arg/varg.hh"

//
// implementations:
//

namespace pdm::ast {

    // Visitor recursively applies a pure-virtual method 'on_visit'
    // to each node in an AST.
    class Visitor {

      // visit is the outward-facing endpoint:
      public:
        bool visit(Node* node);

      // on_visit calls on_visit__X based on node->kind()
      // on_visit__X is a pure virtual callback called by 'visit' for each node
      // of that kind.
      // on_visit__X should not recurse on children. Instead, it should just
      // perform the necessary processing for that node in pre/post and wait 
      // for the visitor to apply other functions to children nodes.

      public:
        enum class VisitOrder {
            Pre,
            Post
        };

      protected:
        virtual bool on_visit(Node* node, VisitOrder visit_order);
      
      protected:
        // scripts:
        virtual bool on_visit_script(Script* script, VisitOrder visit_order) = 0;

        // statements:
        virtual bool on_visit_mod_stmt(ModStmt* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_mod_typeclass_stmt(ModTypeclassStmt* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_mod_type_stmt(ModTypeStmt* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_mod_enum_stmt(ModEnumStmt* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_mod_val_stmt(ModValStmt* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_const_stmt(ConstStmt* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_val_stmt(ValStmt* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_var_stmt(VarStmt* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_set_stmt(SetStmt* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_discard_stmt(DiscardStmt* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_extern_stmt(ExternStmt* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_import_stmt(ImportStmt* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_using_stmt(UsingStmt* node, VisitOrder visit_order) = 0;

        // expressions:
        virtual bool on_visit_unit_exp(UnitExp* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_int_exp(IntExp* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_float_exp(FloatExp* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_string_exp(StringExp* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_id_exp(IdExp* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_paren_exp(ParenExp* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_tuple_exp(TupleExp* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_array_exp(ArrayExp* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_struct_exp(StructExp* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_type_query_exp(TypeQueryExp* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_chain_exp(ChainExp* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_lambda_exp(LambdaExp* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_if_exp(IfExp* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_dot_index_exp(DotIndexExp* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_dot_name_exp(DotNameExp* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_module_dot_exp(ModuleDotExp* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_unary_exp(UnaryExp* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_binary_exp(BinaryExp* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_v_call_exp(VCallExp* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_t_call_exp(TCallExp* node, VisitOrder visit_order) = 0;
        
        // patterns:
        virtual bool on_visit_v_pattern(VPattern* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_t_pattern(TPattern* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_l_pattern(LPattern* node, VisitOrder visit_order) = 0;

        // typespecs:
        virtual bool on_visit_id_type_spec(IdTypeSpec* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_id_class_spec(IdClassSpec* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_fn_type_spec(FnTypeSpec* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_t_call_type_spec(TCallTypeSpec* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_t_call_class_spec(TCallClassSpec* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_tuple_type_spec(TupleTypeSpec* node, VisitOrder visit_order) = 0;
        // virtual bool on_visit__dot_name_typespec_type_prefix(DotNameTypeSpec_TypePrefix* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_dot_name_type_spec_mod_prefix(DotNameTypeSpec_ModPrefix* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_struct_type_spec(StructTypeSpec* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_paren_type_spec(ParenTypeSpec* node, VisitOrder visit_order) = 0;

        // templates/shared:
        virtual bool on_visit_targ(TArg* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_varg(VArg* node, VisitOrder visit_order) = 0;

        // non-syntactic elements:
        virtual bool on_visit_builtin_type_stmt(BuiltinStmt* node, VisitOrder visit_order) = 0;
    };

    class TinyVisitor: public Visitor {
      protected:
        // scripts:
        virtual bool on_visit_script(Script* script, VisitOrder visit_order) override {
            return true;
        }

        // statements:
        virtual bool on_visit_mod_stmt(ModStmt* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_mod_typeclass_stmt(ModTypeclassStmt* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_mod_type_stmt(ModTypeStmt* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_mod_enum_stmt(ModEnumStmt* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_mod_val_stmt(ModValStmt* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_const_stmt(ConstStmt* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_val_stmt(ValStmt* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_var_stmt(VarStmt* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_set_stmt(SetStmt* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_discard_stmt(DiscardStmt* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_extern_stmt(ExternStmt* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_import_stmt(ImportStmt* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_using_stmt(UsingStmt* node, VisitOrder visit_order) override {
            return true;
        }

        // expressions:
        virtual bool on_visit_unit_exp(UnitExp* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_int_exp(IntExp* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_float_exp(FloatExp* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_string_exp(StringExp* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_id_exp(IdExp* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_paren_exp(ParenExp* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_tuple_exp(TupleExp* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_array_exp(ArrayExp* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_struct_exp(StructExp* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_type_query_exp(TypeQueryExp* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_chain_exp(ChainExp* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_lambda_exp(LambdaExp* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_if_exp(IfExp* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_dot_index_exp(DotIndexExp* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_dot_name_exp(DotNameExp* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_module_dot_exp(ModuleDotExp* node, VisitOrder visit_order) override {
            return true;
        };
        virtual bool on_visit_unary_exp(UnaryExp* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_binary_exp(BinaryExp* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_v_call_exp(VCallExp* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_t_call_exp(TCallExp* node, VisitOrder visit_order) override {
            return true;
        }
        
        // patterns:
        virtual bool on_visit_v_pattern(VPattern* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_t_pattern(TPattern* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_l_pattern(LPattern* node, VisitOrder visit_order) override {
            return true;
        }

        // typespecs:
        virtual bool on_visit_id_type_spec(IdTypeSpec* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_id_class_spec(IdClassSpec* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_fn_type_spec(FnTypeSpec* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_t_call_type_spec(TCallTypeSpec* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_t_call_class_spec(TCallClassSpec* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_tuple_type_spec(TupleTypeSpec* node, VisitOrder visit_order) override {
            return true;
        }
        // virtual bool on_visit__dot_name_typespec_type_prefix(DotNameTypeSpec_TypePrefix* node, VisitOrder visit_order) override {
        //     return true;
        // }
        virtual bool on_visit_dot_name_type_spec_mod_prefix(DotNameTypeSpec_ModPrefix* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_struct_type_spec(StructTypeSpec* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_paren_type_spec(ParenTypeSpec* node, VisitOrder visit_order) override {
            return true;
        }

        // templates/shared:
        virtual bool on_visit_targ(TArg* node, VisitOrder visit_order) override {
            return true;
        }
        virtual bool on_visit_varg(VArg* node, VisitOrder visit_order) override {
            return true;
        }

        // non-syntactic elements:
        virtual bool on_visit_builtin_type_stmt(BuiltinStmt* node, VisitOrder visit_order) override {
            return true;
        }
    };

}   // namespace pdm::ast

#endif  // INCLUDED_PDM_AST_VISITOR_HH
