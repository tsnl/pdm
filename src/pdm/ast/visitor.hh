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

#include "pdm/ast/source-node/script.hh"

#include "pdm/ast/stmt/stmt.hh"
#include "pdm/ast/stmt/const.hh"
#include "pdm/ast/stmt/mod_val.hh"
#include "pdm/ast/stmt/mod_enum.hh"
// #include "pdm/ast/stmt/mod.hh"
// #include "pdm/ast/stmt/import.hh"
#include "pdm/ast/stmt/mod_type.hh"
#include "pdm/ast/stmt/mod_typeclass.hh"
#include "pdm/ast/header/extern_stmt.hh"
#include "pdm/ast/stmt/builtin.hh"
#include "pdm/ast/stmt/discard.hh"
#include "pdm/ast/stmt/set.hh"
#include "pdm/ast/stmt/using.hh"
#include "pdm/ast/stmt/var.hh"
#include "pdm/ast/stmt/val.hh"

#include "pdm/ast/module/mod_exp.hh"
#include "pdm/ast/module/mod_address.hh"

#include "pdm/ast/header/import_stmt.hh"

#include "pdm/ast/class_spec/class_exp.hh"
#include "pdm/ast/class_spec/id.hh"
#include "pdm/ast/class_spec/mai.hh"

#include "pdm/ast/type_spec/type_spec.hh"
#include "pdm/ast/type_spec/mai.hh"
#include "pdm/ast/type_spec/id.hh"
#include "pdm/ast/type_spec/struct.hh"
#include "pdm/ast/type_spec/enum.hh"
#include "pdm/ast/type_spec/tuple.hh"
#include "pdm/ast/type_spec/fn.hh"
#include "pdm/ast/type_spec/type_spec.hh"

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
        virtual bool on_visit_script_field(Script::Field* field, VisitOrder visit_order) = 0;

        // modules:
        virtual bool on_visit_mod_exp(ModExp* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_value_mod_field(ModExp::ValueField* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_type_mod_field(ModExp::TypeField* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_class_mod_field(ModExp::ClassField* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_mod_mod_field(ModExp::ModuleField* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_mod_address(ModAddress* node, VisitOrder visit_order) = 0;

        // statements:
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

        // type specs:
        virtual bool on_visit_id_type_spec(IdTypeSpec* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_fn_type_spec(FnTypeSpec* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_tuple_type_spec(TupleTypeSpec* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_ma_type_spec(ModAddressIdTypeSpec* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_struct_type_spec(StructTypeSpec* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_enum_type_spec(EnumTypeSpec* node, VisitOrder visit_order) = 0;

        // class specs:
        virtual bool on_visit_id_class_spec(IdClassSpec* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_class_exp_class_spec(ClassExpClassSpec* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_ma_class_spec(ModAddressIdClassSpec* node, VisitOrder visit_order) = 0;

        // templates/shared:
        virtual bool on_visit_t_arg(TArg* node, VisitOrder visit_order) = 0;
        virtual bool on_visit_v_arg(VArg* node, VisitOrder visit_order) = 0;

        // non-syntactic elements:
        virtual bool on_visit_builtin_type_stmt(BuiltinStmt* node, VisitOrder visit_order) = 0;
    };


    class TinyVisitor: public Visitor {
      protected:
        // scripts:
        bool on_visit_script(Script* script, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_script_field(Script::Field* field, VisitOrder visit_order) override {
            return true;
        }

        // modules:
        bool on_visit_mod_exp(ModExp* mod_exp, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_value_mod_field(ModExp::ValueField* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_type_mod_field(ModExp::TypeField* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_class_mod_field(ModExp::ClassField* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_mod_mod_field(ast::ModExp::ModuleField* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_mod_address(ModAddress* node, VisitOrder visit_order) override {
            return true;
        }

        // statements:
        bool on_visit_const_stmt(ConstStmt* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_val_stmt(ValStmt* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_var_stmt(VarStmt* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_set_stmt(SetStmt* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_discard_stmt(DiscardStmt* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_extern_stmt(ExternStmt* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_import_stmt(ImportStmt* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_using_stmt(UsingStmt* node, VisitOrder visit_order) override {
            return true;
        }

        // expressions:
        bool on_visit_unit_exp(UnitExp* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_int_exp(IntExp* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_float_exp(FloatExp* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_string_exp(StringExp* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_id_exp(IdExp* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_paren_exp(ParenExp* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_tuple_exp(TupleExp* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_array_exp(ArrayExp* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_struct_exp(StructExp* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_type_query_exp(TypeQueryExp* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_chain_exp(ChainExp* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_lambda_exp(LambdaExp* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_if_exp(IfExp* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_dot_index_exp(DotIndexExp* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_dot_name_exp(DotNameExp* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_module_dot_exp(ModuleDotExp* node, VisitOrder visit_order) override {
            return true;
        };
        bool on_visit_unary_exp(UnaryExp* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_binary_exp(BinaryExp* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_v_call_exp(VCallExp* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_t_call_exp(TCallExp* node, VisitOrder visit_order) override {
            return true;
        }
        
        // patterns:
        bool on_visit_v_pattern(VPattern* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_t_pattern(TPattern* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_l_pattern(LPattern* node, VisitOrder visit_order) override {
            return true;
        }

        // type specs:
        bool on_visit_id_type_spec(IdTypeSpec* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_fn_type_spec(FnTypeSpec* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_tuple_type_spec(TupleTypeSpec* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_ma_type_spec(ModAddressIdTypeSpec* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_struct_type_spec(StructTypeSpec* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_enum_type_spec(EnumTypeSpec* node, VisitOrder visit_order) override {
            return true;
        }

        // class specs:
        bool on_visit_id_class_spec(IdClassSpec* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_class_exp_class_spec(ClassExpClassSpec* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_ma_class_spec(ModAddressIdClassSpec* node, VisitOrder visit_order) override {
            return true;
        }

        // templates/shared:
        bool on_visit_t_arg(TArg* node, VisitOrder visit_order) override {
            return true;
        }
        bool on_visit_v_arg(VArg* node, VisitOrder visit_order) override {
            return true;
        }

        // non-syntactic elements:
        bool on_visit_builtin_type_stmt(BuiltinStmt* node, VisitOrder visit_order) override {
            return true;
        }
    };

}   // namespace pdm::ast

#endif  // INCLUDED_PDM_AST_VISITOR_HH
