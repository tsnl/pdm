#include "typer.hh"

#include "pdm/types/manager.hh"
#include "pdm/types/var.hh"

//
// TypeVisitor helps apply typing rules for each AST node (without forgetting any).
//

namespace pdm::typer {

    //
    // TypeVisitor declaration:
    //

    class TyperVisitor: public ast::Visitor {
      private:
        types::Manager* m_types_mgr;
        ast::Script*    m_script;

      public:
        TyperVisitor(types::Manager* types_mgr, ast::Script* script);

      protected:
        // script:
        virtual bool on_visit__script(ast::Script* script, VisitOrder visit_order) override;

        // statements:
        virtual bool on_visit__mod_stmt(ast::ModStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__typeclass_stmt(ast::TypeclassStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__type_stmt(ast::TypeStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__enum_stmt(ast::EnumStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__fn_stmt(ast::FnStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__const_stmt(ast::ConstStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__val_stmt(ast::ValStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__var_stmt(ast::VarStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__set_stmt(ast::SetStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__discard_stmt(ast::DiscardStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__extern_stmt(ast::ExternStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__import_stmt(ast::ImportStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__using_stmt(ast::UsingStmt* node, VisitOrder visit_order) override;
        
        // expressions:
        virtual bool on_visit__unit_exp(ast::UnitExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__int_exp(ast::IntExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__float_exp(ast::FloatExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__string_exp(ast::StringExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__id_exp(ast::IdExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__paren_exp(ast::ParenExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__tuple_exp(ast::TupleExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__array_exp(ast::ArrayExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__struct_exp(ast::StructExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__type_query_exp(ast::TypeQueryExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__chain_exp(ast::ChainExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__lambda_exp(ast::LambdaExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__if_exp(ast::IfExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__dot_index_exp(ast::DotIndexExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__dot_name_exp(ast::DotNameExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__unary_exp(ast::UnaryExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__binary_exp(ast::BinaryExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__vcall_exp(ast::VCallExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__tcall_exp(ast::TCallExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__vpattern(ast::VPattern* node, VisitOrder visit_order) override;
        virtual bool on_visit__tpattern(ast::TPattern* node, VisitOrder visit_order) override;
        virtual bool on_visit__lpattern(ast::LPattern* node, VisitOrder visit_order) override;
        
        // typespecs:
        virtual bool on_visit__id_typespec(ast::IdTypespec* node, VisitOrder visit_order) override;
        virtual bool on_visit__fn_typespec(ast::FnTypespec* node, VisitOrder visit_order) override;
        virtual bool on_visit__tcall_typespec(ast::TCallTypespec* node, VisitOrder visit_order) override;
        virtual bool on_visit__tuple_typespec(ast::TupleTypespec* node, VisitOrder visit_order) override;
        virtual bool on_visit__dot_name_typespec_type_prefix(ast::DotNameTypespec_TypePrefix* node, VisitOrder visit_order) override;
        virtual bool on_visit__dot_name_typespec_mod_prefix(ast::DotNameTypespec_ModPrefix* node, VisitOrder visit_order) override;
        virtual bool on_visit__struct_typespec(ast::StructTypespec* node, VisitOrder visit_order) override;
        virtual bool on_visit__paren_typespec(ast::ParenTypespec* node, VisitOrder visit_order) override;
        
        // args:
        virtual bool on_visit__targ(ast::TArg* node, VisitOrder visit_order) override;
        virtual bool on_visit__varg(ast::VArg* node, VisitOrder visit_order) override;
        
        // non-syntactic:
        virtual bool on_visit__builtin_type_stmt(ast::BuiltinTypeStmt* node, VisitOrder visit_order) override;
    };

    //
    // TypeVisitor Definitions:
    //

    TyperVisitor::TyperVisitor(types::Manager* types_mgr)
    :   m_types_mgr(types_mgr)
    {}

    // script:
    bool TyperVisitor::on_visit__script(ast::Script* script, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }

    // statements:
    bool TyperVisitor::on_visit__mod_stmt(ast::ModStmt* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__typeclass_stmt(ast::TypeclassStmt* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__type_stmt(ast::TypeStmt* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__enum_stmt(ast::EnumStmt* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__fn_stmt(ast::FnStmt* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__const_stmt(ast::ConstStmt* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__val_stmt(ast::ValStmt* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__var_stmt(ast::VarStmt* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__set_stmt(ast::SetStmt* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__discard_stmt(ast::DiscardStmt* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__extern_stmt(ast::ExternStmt* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__import_stmt(ast::ImportStmt* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__using_stmt(ast::UsingStmt* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    
    // expressions:
    bool TyperVisitor::on_visit__unit_exp(ast::UnitExp* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__int_exp(ast::IntExp* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__float_exp(ast::FloatExp* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__string_exp(ast::StringExp* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__id_exp(ast::IdExp* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__paren_exp(ast::ParenExp* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__tuple_exp(ast::TupleExp* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__array_exp(ast::ArrayExp* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__struct_exp(ast::StructExp* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__type_query_exp(ast::TypeQueryExp* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__chain_exp(ast::ChainExp* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__lambda_exp(ast::LambdaExp* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__if_exp(ast::IfExp* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__dot_index_exp(ast::DotIndexExp* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__dot_name_exp(ast::DotNameExp* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__unary_exp(ast::UnaryExp* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__binary_exp(ast::BinaryExp* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__vcall_exp(ast::VCallExp* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__tcall_exp(ast::TCallExp* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__vpattern(ast::VPattern* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__tpattern(ast::TPattern* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__lpattern(ast::LPattern* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    
    // typespecs:
    bool TyperVisitor::on_visit__id_typespec(ast::IdTypespec* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__fn_typespec(ast::FnTypespec* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__tcall_typespec(ast::TCallTypespec* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__tuple_typespec(ast::TupleTypespec* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__dot_name_typespec_type_prefix(ast::DotNameTypespec_TypePrefix* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__dot_name_typespec_mod_prefix(ast::DotNameTypespec_ModPrefix* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__struct_typespec(ast::StructTypespec* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__paren_typespec(ast::ParenTypespec* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    
    // args:
    bool TyperVisitor::on_visit__targ(ast::TArg* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit__varg(ast::VArg* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    
    // non-syntactic:
    bool TyperVisitor::on_visit__builtin_type_stmt(ast::BuiltinTypeStmt* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
}

//
// Public interface implementation:
//

namespace pdm::typer {

    bool type(types::Manager* types_mgr, ast::Script* script) {
        TyperVisitor typer_visitor {types_mgr, script};
        return typer_visitor.visit(script);
    }

}
