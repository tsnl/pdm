#include "typer.hh"

#include <iostream>

#include "pdm/scoper/defn.hh"

#include "pdm/types/manager.hh"
#include "pdm/types/var.hh"
#include "pdm/types/relation.hh"

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
        virtual bool on_visit__module_dot_exp(ast::ModuleDotExp* node, VisitOrder visit_order) override;
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

    TyperVisitor::TyperVisitor(types::Manager* types_mgr, ast::Script* script)
    :   m_types_mgr(types_mgr),
        m_script(script)
    {}

    // script:
    bool TyperVisitor::on_visit__script(ast::Script* script, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }

    // statements:
    bool TyperVisitor::on_visit__mod_stmt(ast::ModStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            types::TypeVar* module_tv = node->x_module_tv();
        } else {

        }
        // todo: implement this typer.
        // - require is_kind(module)
        // - require has_vid_field for each const/fn defn
        // - require has_tid_field for each type/enum/typeclass type defn
        return true;
    }
    bool TyperVisitor::on_visit__typeclass_stmt(ast::TypeclassStmt* node, VisitOrder visit_order) {
        // todo: implement this typer.
        // - if template, set up formal args, use return for following steps.
        // - otherwise,
        //   - require is_kind(typeclass)
        //   - require eqconstraint (fixed) with those provided.
        // leave typeclasses, templates for last.
        return true;
    }
    bool TyperVisitor::on_visit__type_stmt(ast::TypeStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            if (!node->lhs_tpatterns().empty()) {

            }
        }
        return true;
    }
    bool TyperVisitor::on_visit__enum_stmt(ast::EnumStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            
        } else {

        }
        return true;
    }
    bool TyperVisitor::on_visit__fn_stmt(ast::FnStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Post) {
            types::TypeVar* fn_tv = nullptr;
            if (node->tpatterns().empty()) {
                fn_tv = dynamic_cast<types::TypeVar*>(node->x_defn_var());
            } else {
                types::ValueTemplateVar* fn_template_var = dynamic_cast<types::ValueTemplateVar*>(node->x_defn_var());
                // todo: set fn_tv based on formal args.
                assert(0 && "NotImplemented: fn statements with template args.");
            }

            // set fn_tv type relationships based on vpattern, return.
            types::TypeVar* ret_tv = m_types_mgr->new_unknown_tv("Return", node); {
                // todo: need a type equality relation
            }
            std::vector<types::TypeVar*> args_tvs; {
                size_t formal_arg_count = node->vpattern()->fields().size();
                args_tvs.reserve(formal_arg_count);
                for (size_t formal_arg_index = 0; formal_arg_index < formal_arg_count; formal_arg_index++) {
                    ast::VPattern::Field* field = node->vpattern()->fields()[formal_arg_index];
                    args_tvs.push_back(field->x_defn_tv());
                }
            }
            m_types_mgr->assume(
                new types::FormalFnRelation(
                    node,
                    fn_tv,
                    std::move(args_tvs),
                    ret_tv
                )
            );
        }
        return true;
    }
    bool TyperVisitor::on_visit__const_stmt(ast::ConstStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            // todo ;-;
        } else {

        }
        return true;
    }
    bool TyperVisitor::on_visit__val_stmt(ast::ValStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Post) {
            // type-relating each defined symbol to the RHS.
            ast::LPattern* lpattern = node->lhs_lpattern();
            types::TypeVar* typeof_rhs_tv = node->rhs_exp()->x_typeof_tv();
            if (lpattern->destructure()) {
                // destructure as a tuple
                assert(0 && "NotImplemented: tuple-lpattern destructuring");
            } else {
                
            }
        }
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
        if (visit_order == VisitOrder::Pre) {
            // todo: replace with fresh TV
            types::TypeVar* int_tv = m_types_mgr->get_u32_tv();
            node->x_typeof_tv(int_tv);
        } else {
            // todo: classify tv as int, let inference figure out width
            // node->x_typeof_tv()
        }
        return true;
    }
    bool TyperVisitor::on_visit__float_exp(ast::FloatExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            // todo: replace with fresh TV
            types::TypeVar* float_tv = m_types_mgr->get_f32_tv();
            node->x_typeof_tv(float_tv);
        } else {
            // todo: classify tv as float, let inference figure out width
        }
        return true;
    }
    bool TyperVisitor::on_visit__string_exp(ast::StringExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            types::TypeVar* string_tv = m_types_mgr->get_string_tv();
            node->x_typeof_tv(string_tv);
        }
        return true;
    }
    bool TyperVisitor::on_visit__id_exp(ast::IdExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            types::TypeVar* id_tv = dynamic_cast<types::TypeVar*>(node->x_defn()->var());
            assert(id_tv != nullptr && "Scoper failed!");
            node->x_typeof_tv(id_tv);
        }
        return true;
    }
    bool TyperVisitor::on_visit__paren_exp(ast::ParenExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "ParenExp";
            types::TypeVar* paren_tv = m_types_mgr->new_unknown_tv(std::move(tv_name), node);
            node->x_typeof_tv(paren_tv);
        } else {
            // todo: set type equality between paren and item contained.
        }
        return true;
    }
    bool TyperVisitor::on_visit__tuple_exp(ast::TupleExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "TupleExp(" + std::to_string(node->items().size()) + ")";
            types::TypeVar* tuple_tv = m_types_mgr->new_unknown_tv(std::move(tv_name), node);
            node->x_typeof_tv(tuple_tv);
        } else {
            // todo: set tuple field requirements here by equating to a TupleTV
        }
        return true;
    }
    bool TyperVisitor::on_visit__array_exp(ast::ArrayExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "ArrayExp(" + std::to_string(node->items().size()) + ")";
            types::TypeVar* array_tv = m_types_mgr->new_unknown_tv(std::move(tv_name), node);
            node->x_typeof_tv(array_tv);
        } else {
            // todo: set array exp requirements here by equating to an ArrayTV
        }
        return true;
    }
    bool TyperVisitor::on_visit__struct_exp(ast::StructExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "StructExp(" + std::to_string(node->fields().size()) + ")";
            types::TypeVar* struct_exp_tv = m_types_mgr->new_unknown_tv(std::move(tv_name), node);
            node->x_typeof_tv(struct_exp_tv);
        } else {
            // todo: set struct exp requirements here by equating to a StructTV
        }
        return true;
    }
    bool TyperVisitor::on_visit__type_query_exp(ast::TypeQueryExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "TypeQueryExp";
            types::TypeVar* type_query_exp_tv = m_types_mgr->new_unknown_tv(std::move(tv_name), node);
            node->x_typeof_tv(type_query_exp_tv);
        } else {
            // todo: implement this typer.
        }
        return true;
    }
    bool TyperVisitor::on_visit__chain_exp(ast::ChainExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "ChainExp";
            types::TypeVar* chain_exp_tv = m_types_mgr->new_unknown_tv(std::move(tv_name), node);
            node->x_typeof_tv(chain_exp_tv);
        } else {

        }
        return true;
    }
    bool TyperVisitor::on_visit__lambda_exp(ast::LambdaExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "LambdaExp";
            types::TypeVar* lambda_exp_tv = m_types_mgr->new_unknown_tv(std::move(tv_name), node);
            node->x_typeof_tv(lambda_exp_tv);
        } else {

        }
        return true;
    }
    bool TyperVisitor::on_visit__if_exp(ast::IfExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "IfExp";
            types::TypeVar* if_exp_tv = m_types_mgr->new_unknown_tv(std::move(tv_name), node);
            node->x_typeof_tv(if_exp_tv);
        } else {

        }
        return true;
    }
    bool TyperVisitor::on_visit__dot_index_exp(ast::DotIndexExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "DotIndexExp";
            types::TypeVar* dot_index_exp_tv = m_types_mgr->new_unknown_tv(std::move(tv_name), node);
            node->x_typeof_tv(dot_index_exp_tv);
        } else {

        }
        return true;
    }
    bool TyperVisitor::on_visit__dot_name_exp(ast::DotNameExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "DotNameExp";
            types::TypeVar* dot_name_exp_tv = m_types_mgr->new_unknown_tv(std::move(tv_name), node);
            node->x_typeof_tv(dot_name_exp_tv);
        } else {

        }
        return true;
    }
    bool TyperVisitor::on_visit__module_dot_exp(ast::ModuleDotExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            // todo
        }
        return true;
    }
    bool TyperVisitor::on_visit__unary_exp(ast::UnaryExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "UnaryExp";
            types::TypeVar* unary_exp_tv = m_types_mgr->new_unknown_tv(std::move(tv_name), node);
            node->x_typeof_tv(unary_exp_tv);
        } else {

        }
        return true;
    }
    bool TyperVisitor::on_visit__binary_exp(ast::BinaryExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "BinaryExp";
            types::TypeVar* binary_exp_tv = m_types_mgr->new_unknown_tv(std::move(tv_name), node);
            node->x_typeof_tv(binary_exp_tv);
        } else {

        }
        return true;
    }
    bool TyperVisitor::on_visit__vcall_exp(ast::VCallExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "VCallExp";
            types::TypeVar* vcall_exp_tv = m_types_mgr->new_unknown_tv(std::move(tv_name), node);
            node->x_typeof_tv(vcall_exp_tv);
        } else {

        }
        return true;
    }
    bool TyperVisitor::on_visit__tcall_exp(ast::TCallExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "TCallExp";
            types::TypeVar* tcall_exp_tv = m_types_mgr->new_unknown_tv(std::move(tv_name), node);
            node->x_typeof_tv(tcall_exp_tv);
        } else {

        }
        return true;
    }

    // patterns:
    bool TyperVisitor::on_visit__vpattern(ast::VPattern* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Post) {
            for (ast::VPattern::Field* field: node->fields()) {
                types::TypeVar* tv = field->x_defn_tv();
                // todo: equate tv to typespec
            }
        }
        return true;
    }
    bool TyperVisitor::on_visit__tpattern(ast::TPattern* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Post) {
            for (ast::TPattern::Field* field: node->fields()) {
                types::Var* tv = field->x_defn_var();
                if (field->kind() == ast::TPattern::FieldKind::Value) {
                    // todo: apply typing
                } else if (field->kind() == ast::TPattern::FieldKind::Type) {
                    // todo: apply typing
                }
            }
        }
        return true;
    }
    bool TyperVisitor::on_visit__lpattern(ast::LPattern* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Post) {
            for (ast::LPattern::Field* field: node->fields()) {
                types::TypeVar* tv = field->x_defn_tv();
                if (field->opt_rhs_typespec()) {
                    // todo: equate tv to typespec
                }
            }
        }
        return true;
    }
    
    // typespecs:
    bool TyperVisitor::on_visit__id_typespec(ast::IdTypespec* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            node->x_spectype_var(node->x_defn()->var());
        }
        return true;
    }
    bool TyperVisitor::on_visit__fn_typespec(ast::FnTypespec* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            // node->x_spectype_var(m_types_mgr->new_func_tv()) ...
        }
        return true;
    }
    bool TyperVisitor::on_visit__tcall_typespec(ast::TCallTypespec* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {

        }
        return true;
    }
    bool TyperVisitor::on_visit__tuple_typespec(ast::TupleTypespec* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {

        }
        return true;
    }
    bool TyperVisitor::on_visit__dot_name_typespec_type_prefix(ast::DotNameTypespec_TypePrefix* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {

        }
        return true;
    }
    bool TyperVisitor::on_visit__dot_name_typespec_mod_prefix(ast::DotNameTypespec_ModPrefix* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {

        }
        return true;
    }
    bool TyperVisitor::on_visit__struct_typespec(ast::StructTypespec* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {

        } else {
            
        }
        return true;
    }
    bool TyperVisitor::on_visit__paren_typespec(ast::ParenTypespec* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {

        } else {

        }
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
