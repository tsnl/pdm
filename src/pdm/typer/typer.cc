#include "typer.hh"

#include <iostream>
#include <iomanip>
#include <map>

#include "pdm/source/loc.hh"

#include "pdm/feedback/feedback.hh"
#include "pdm/feedback/severity.hh"
#include "pdm/feedback/letter.hh"
#include "pdm/feedback/note.hh"

#include "pdm/scoper/defn.hh"

#include "pdm/ast/source-node/script.hh"
#include "pdm/ast/type_spec/struct.hh"

#include "pdm/types/manager.hh"
#include "pdm/types/var.hh"
#include "pdm/types/relation.hh"
#include "pdm/types/solve_result.hh"

//
// TypeVisitor helps apply typing rules for each AST node (without forgetting any).
//

// TODO:
// - script fields
// - module fields:
//   - module, type, class, value
// - type specs (enum, dot)
// - class specs (totally redesigned, class-exp, dot, id)
// - templates/mod-address

// helper in 'types' namespace:
namespace pdm::types {

    //
    // TypeVisitor declaration:
    //

    class TyperVisitor: public ast::Visitor {
      private:
        Manager*     m_types_mgr;
        ast::Script* m_script;

      public:
        TyperVisitor(Manager* types_mgr, ast::Script* script);

      private:
        bool post_feedback_from_first_kd_res(SolveResult kd_res, std::string&& source_desc, source::Loc loc);
      
      protected:
        // script:
        bool on_visit_script(ast::Script* script, VisitOrder visit_order) override;
        bool on_visit_script_field(ast::Script::Field* script_field, VisitOrder visit_order) override;

        // module:
        bool on_visit_native_mod_exp(ast::NativeModExp* mod_exp, VisitOrder visit_order) override;
        bool on_visit_mod_mod_field(ast::NativeModExp::ModuleField* module_field, VisitOrder visit_order) override;
        bool on_visit_value_mod_field(ast::NativeModExp::ValueField* value_field, VisitOrder visit_order) override;
        bool on_visit_type_mod_field(ast::NativeModExp::TypeField* type_field, VisitOrder visit_order) override;
        bool on_visit_class_mod_field(ast::NativeModExp::ClassField* class_field, VisitOrder visit_order) override;
        bool on_visit_mod_address(ast::ModAddress* mod_address, VisitOrder visit_order) override;

        // statements:
        bool on_visit_const_stmt(ast::ConstStmt* node, VisitOrder visit_order) override;
        bool on_visit_val_stmt(ast::ValStmt* node, VisitOrder visit_order) override;
        bool on_visit_var_stmt(ast::VarStmt* node, VisitOrder visit_order) override;
        bool on_visit_set_stmt(ast::SetStmt* node, VisitOrder visit_order) override;
        bool on_visit_discard_stmt(ast::DiscardStmt* node, VisitOrder visit_order) override;
        bool on_visit_extern_stmt(ast::ExternStmt* node, VisitOrder visit_order) override;
        bool on_visit_import_stmt(ast::ImportStmt* node, VisitOrder visit_order) override;
        bool on_visit_using_stmt(ast::UsingStmt* node, VisitOrder visit_order) override;
        
        // expressions:
        bool on_visit_unit_exp(ast::UnitExp* node, VisitOrder visit_order) override;
        bool on_visit_int_exp(ast::IntExp* node, VisitOrder visit_order) override;
        bool on_visit_float_exp(ast::FloatExp* node, VisitOrder visit_order) override;
        bool on_visit_string_exp(ast::StringExp* node, VisitOrder visit_order) override;
        bool on_visit_id_exp(ast::IdExp* node, VisitOrder visit_order) override;
        bool on_visit_paren_exp(ast::ParenExp* node, VisitOrder visit_order) override;
        bool on_visit_tuple_exp(ast::TupleExp* node, VisitOrder visit_order) override;
        bool on_visit_array_exp(ast::ArrayExp* node, VisitOrder visit_order) override;
        bool on_visit_struct_exp(ast::StructExp* node, VisitOrder visit_order) override;
        bool on_visit_type_query_exp(ast::TypeQueryExp* node, VisitOrder visit_order) override;
        bool on_visit_chain_exp(ast::ChainExp* node, VisitOrder visit_order) override;
        bool on_visit_lambda_exp(ast::LambdaExp* node, VisitOrder visit_order) override;
        bool on_visit_if_exp(ast::IfExp* node, VisitOrder visit_order) override;
        bool on_visit_dot_index_exp(ast::DotIndexExp* node, VisitOrder visit_order) override;
        bool on_visit_dot_name_exp(ast::DotNameExp* node, VisitOrder visit_order) override;
        bool on_visit_module_dot_exp(ast::ModuleDotExp* node, VisitOrder visit_order) override;
        bool on_visit_unary_exp(ast::UnaryExp* node, VisitOrder visit_order) override;
        bool on_visit_binary_exp(ast::BinaryExp* node, VisitOrder visit_order) override;
        bool on_visit_v_call_exp(ast::VCallExp* node, VisitOrder visit_order) override;
        bool on_visit_t_call_exp(ast::TCallExp* node, VisitOrder visit_order) override;
        bool on_visit_v_pattern(ast::VPattern* node, VisitOrder visit_order) override;
        bool on_visit_t_pattern(ast::TPattern* node, VisitOrder visit_order) override;
        bool on_visit_l_pattern(ast::LPattern* node, VisitOrder visit_order) override;
        
        // type specs:
        bool on_visit_id_type_spec(ast::IdTypeSpec* node, VisitOrder visit_order) override;
        bool on_visit_fn_type_spec(ast::FnTypeSpec* node, VisitOrder visit_order) override;
        bool on_visit_tuple_type_spec(ast::TupleTypeSpec* node, VisitOrder visit_order) override;
        bool on_visit_struct_type_spec(ast::StructTypeSpec* node, VisitOrder visit_order) override;
        bool on_visit_ma_type_spec(ast::ModAddressIdTypeSpec* node, VisitOrder visit_order) override;
        bool on_visit_enum_type_spec(ast::EnumTypeSpec* node, VisitOrder visit_order) override;

        // class specs:
        bool on_visit_class_exp_class_spec(ast::ClassExpClassSpec* class_exp, VisitOrder visit_order) override;
        bool on_visit_id_class_spec(ast::IdClassSpec* node, VisitOrder visit_order) override;
        bool on_visit_ma_class_spec(ast::ModAddressIdClassSpec* node, VisitOrder visit_order) override;

        // args:
        bool on_visit_t_arg(ast::TArg* node, VisitOrder visit_order) override;
        bool on_visit_v_arg(ast::VArg* node, VisitOrder visit_order) override;
        
        // non-syntactic:
        bool on_visit_builtin_type_stmt(ast::BuiltinStmt* node, VisitOrder visit_order) override;

      // helpers:
      protected:
        bool help_post_type_const_or_val_or_var_stmt(ast::Node* node, ast::LPattern* lhs, ast::Exp* rhs);

        static TypeVar* expect_type_var(Var* var, std::string&& expected_desc, std::string&& in_desc, source::Loc loc);
        static ClassVar* expect_class_var(Var* var, std::string&& expected_desc, std::string&& in_desc, source::Loc loc);
        static Var* expect_var_check(Var* var, std::string&& expected_desc, std::string&& in_desc, VarArchetype expected_var_kind, source::Loc loc);

        static ast::BaseModExp::Field* get_mod_field_from_addr(ast::ModAddress* lhs_mod_address, intern::String rhs_name);
    };

    //
    // TypeVisitor Definitions:
    //

    TyperVisitor::TyperVisitor(Manager* types_mgr, ast::Script* script)
    :   m_types_mgr(types_mgr),
        m_script(script)
    {}

    bool TyperVisitor::post_feedback_from_first_kd_res(SolveResult kd_res, std::string&& source_desc, source::Loc loc) {
        if (result_is_error(kd_res)) {
            std::string headline = "A typing relation could not be applied";
            std::string more = (
                (kd_res == SolveResult::CompilerError) ?
                "This was caused by a compiler bug, and is not your fault." : ""
            );

            std::vector<feedback::Note*> notes{1}; {
                notes[0] = new feedback::SourceLocNote(std::move(source_desc), loc);
            }
            feedback::post(new feedback::Letter(
                feedback::Severity::Error,
                std::move(headline), 
                std::move(more),
                std::move(notes)
            ));
            return false;
        } else {
            return true;
        }
    }

    // script:
    bool TyperVisitor::on_visit_script(ast::Script* script, VisitOrder visit_order) {
        // do nothing
        return true;
    }
    bool TyperVisitor::on_visit_script_field(ast::Script::Field* script_field, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Post) {
            TypeVar* lhs_defn_tv = script_field->x_defn_var();
            TypeVar* rhs_module_tv = script_field->rhs_mod_exp()->x_module_var();

            auto relation = new TypeEqualsRelation(
                script_field,
                lhs_defn_tv,
                rhs_module_tv
            );
            auto assume_relation_result = m_types_mgr->assume_relation_holds(relation);
            return !result_is_error(assume_relation_result);
        }
        return true;
    }

    // modules:
    bool TyperVisitor::on_visit_native_mod_exp(ast::NativeModExp* mod_exp, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            // TODO: implement typing for templates.
            if (mod_exp->opt_template_pattern()) {
                assert(0 && "NotImplemented: 'TyperVisitor::on_visit_native_mod_exp' with template args.");
            }

            // all ok:
            return true;
        } else {
            // retrieving and typing the TV:
            assert(visit_order == VisitOrder::Post && "Invalid visit order.");
            auto module_tv = dynamic_cast<TypeVar*>(mod_exp->x_module_var());

            std::map<intern::String, Var*> fields_tvs; {
                for (ast::NativeModExp::Field* field: mod_exp->fields()) {
                    fields_tvs[field->name()] = field->x_defn_var();
                }
            }

            std::string relation_why = "IsModuleWithFields";
            auto relation = new IsModuleRelation(
                std::move(relation_why),
                mod_exp,
                module_tv,
                fields_tvs
            );
            auto assume_relation_result = m_types_mgr->assume_relation_holds(relation);
            return !result_is_error(assume_relation_result);
        }
    }
    bool TyperVisitor::on_visit_mod_mod_field(ast::NativeModExp::ModuleField* mod_field, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            return true;
        } else if (visit_order == VisitOrder::Post) {
            // retrieving the TV defined in the scoper/pre-typer:
            auto lhs_tv = dynamic_cast<TypeVar*>(mod_field->x_defn_var());
            auto rhs_tv = dynamic_cast<TypeVar*>(mod_field->rhs_mod_exp()->x_module_var());
            assert(lhs_tv && rhs_tv && "TyperVisitor::on_visit_mod_mod_field: arg TVs were nullptr");

            // equating the LHS type to the RHS type:
            auto relation = new TypeEqualsRelation(mod_field, lhs_tv, rhs_tv);
            auto assume_relation_result = m_types_mgr->assume_relation_holds(relation);
            return !result_is_error(assume_relation_result);
        } else {
            if (pdm::DEBUG) {
                assert(0 && "Invalid VisitOrder");
            }
            return false;
        }
    }
    bool TyperVisitor::on_visit_value_mod_field(ast::NativeModExp::ValueField* mod_field, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            return true;
        } else if (visit_order == VisitOrder::Post) {
            // retrieving the TV defined in the scoper/pre-typer:
            auto value_tv = dynamic_cast<TypeVar*>(mod_field->x_defn_var());
            auto rhs_tv = dynamic_cast<TypeVar*>(mod_field->rhs_exp()->x_type_of_var());
            assert(value_tv && rhs_tv && "TyperVisitor::on_visit_value_mod_field: arg TVs were nullptr");

            // equating the type to the RHS:
            auto relation = new TypeEqualsRelation(mod_field, value_tv, rhs_tv);
            auto assume_relation_result = m_types_mgr->assume_relation_holds(relation);
            auto result = !result_is_error(assume_relation_result);
            return result;
        } else {
            if (pdm::DEBUG) {
                assert(0 && "Invalid VisitOrder");
            }
            return false;
        }
    }
    bool TyperVisitor::on_visit_type_mod_field(ast::NativeModExp::TypeField* mod_field, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            return true;
        } else if (visit_order == VisitOrder::Post) {
            // retrieving the TV defined in the scoper/pre-typer:
            auto lhs_tv = dynamic_cast<TypeVar*>(mod_field->x_defn_var());
            std::string expected_rhs_desc = "a type specifier";
            std::string expected_in_desc = "a 'Type' module-field binding (" + mod_field->name().cpp_str() + ")";
            auto rhs_tv = expect_type_var(
                mod_field->rhs_type_spec()->x_spec_var(),
                std::move(expected_rhs_desc),
                std::move(expected_in_desc),
                mod_field->loc()
            );
            if (!rhs_tv) {
                return false;
            }
            assert(lhs_tv && rhs_tv && "TyperVisitor::on_visit_type_mod_field: arg TVs were nullptr");

            // equating the LHS and RHS types:
            auto relation = new TypeEqualsRelation(mod_field, lhs_tv, rhs_tv);
            auto assume_relation_result = m_types_mgr->assume_relation_holds(relation);
            return !result_is_error(assume_relation_result);
        } else {
            if (pdm::DEBUG) {
                assert(0 && "Invalid VisitOrder");
            }
            return false;
        }
    }
    bool TyperVisitor::on_visit_class_mod_field(ast::NativeModExp::ClassField* mod_field, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            return true;
        } else if (visit_order == VisitOrder::Post) {
            // retrieving the TV defined in the scoper/pre-typer:
            auto lhs_tv = dynamic_cast<TypeVar*>(mod_field->x_defn_var());
            std::string expected_rhs_desc = "a class specifier";
            std::string expected_in_desc = "a 'CLASS' module-field binding (" + mod_field->name().cpp_str() + ")";
            auto rhs_tv = expect_type_var(
                mod_field->rhs_class_spec()->x_spec_var(),
                std::move(expected_rhs_desc),
                std::move(expected_in_desc),
                mod_field->loc()
            );
            if (!rhs_tv) {
                return false;
            }
            assert(lhs_tv && rhs_tv && "TyperVisitor::on_visit_class_mod_field: arg TVs were nullptr");

            // equating the LHS and RHS types:
            auto relation = new TypeEqualsRelation(mod_field, lhs_tv, rhs_tv);
            auto assume_relation_result = m_types_mgr->assume_relation_holds(relation);
            return !result_is_error(assume_relation_result);
        } else {
            if (pdm::DEBUG) {
                assert(0 && "Invalid VisitOrder");
            }
            return false;
        }
    }
    bool TyperVisitor::on_visit_mod_address(ast::ModAddress* mod_address, VisitOrder visit_order) {
        if (!mod_address->template_args().empty()) {
            assert(0 && "NotImplemented: TyperVisitor::on_visit_mod_address for >0 actual template args!");
        }
        
        if (visit_order == VisitOrder::Pre) {
            // retrieving the TV defined in the scoper/pre-typer:
            auto origin_mod_exp = mod_address->x_origin_mod_exp();
            assert(origin_mod_exp && "nullptr origin_mod_exp");
            // ast::ModExp::Field* ref_field = nullptr;
            // for (auto field: origin_mod_exp->fields()) {
            //     if (field->name() == mod_address->rhs_name() && field->kind() == ast::Kind::NativeModExp_ModField) {
            //         ref_field = field;
            //         break;
            //     }
            // }
            if (origin_mod_exp) {
                // lookup succeeded
                return true;
            } else {
                // lookup failed
                std::string headline = "Invalid module address";
                std::string desc = "";
                std::vector<feedback::Note*> notes{1}; {
                    std::string desc0 = "See usage here...";
                    notes[0] = new feedback::SourceLocNote(std::move(desc0), mod_address->loc());
                }
                feedback::post(new feedback::Letter(
                    feedback::Severity::Error,
                    std::move(headline),
                    std::move(desc),
                    std::move(notes)
                ));
                return false;
            }
        } else if (visit_order == VisitOrder::Post) {
            return true;
        } else {
            if (DEBUG) {
                assert(0 && "Invalid VisitOrder.");
            }
            return false;
        }
    }

    // statements:
    bool TyperVisitor::on_visit_const_stmt(ast::ConstStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Post) {
            return help_post_type_const_or_val_or_var_stmt(node, node->lhs_lpattern(), node->rhs_exp());
        }
        return true;
    }
    bool TyperVisitor::on_visit_val_stmt(ast::ValStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Post) {
            return help_post_type_const_or_val_or_var_stmt(node, node->lhs_lpattern(), node->rhs_exp());
        }
        return true;
    }
    bool TyperVisitor::on_visit_var_stmt(ast::VarStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Post) {
            return help_post_type_const_or_val_or_var_stmt(node, node->lhs_lpattern(), node->rhs_exp());
        }
        return true;
    }
    bool TyperVisitor::on_visit_set_stmt(ast::SetStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Post) {
            auto lhs_tv = dynamic_cast<types::TypeVar*>(node->lhs_exp()->x_type_of_var());
            auto rhs_tv = dynamic_cast<types::TypeVar*>(node->rhs_exp()->x_type_of_var());
            assert(lhs_tv && rhs_tv && "Could not type set-stmt: TVs unset");
            auto solve_res = m_types_mgr->assume_relation_holds(new types::TypeEqualsRelation(
                node,
                lhs_tv, rhs_tv
            ));
            return !types::result_is_error(solve_res);
        }
        return true;
    }
    bool TyperVisitor::on_visit_discard_stmt(ast::DiscardStmt* node, VisitOrder visit_order) {
        // do nothing...
        return true;
    }
    bool TyperVisitor::on_visit_extern_stmt(ast::ExternStmt* node, VisitOrder visit_order) {
        // todo: implement this typer.
        assert(0 && "NotImplemented: TyperVisitor::on_visit_extern_stmt");
        return true;
    }
    bool TyperVisitor::on_visit_import_stmt(ast::ImportStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            // from scoper's ImportOrder handler: `origin_tv`
            // from scoper's visitor: `export_tv`

            SolveResult result = SolveResult::NoChange;
            for (auto group: node->field_groups()) {
                for (auto field: group->fields()) {
                    auto origin_mod_exp = field->x_origin_mod_exp();
                    auto origin_tv = origin_mod_exp->x_module_var();
                    auto export_tv = field->x_exported_tv();

                    assert(origin_tv && "ScoperError: expected `origin_tv` from ImportLookupOrder");
                    assert(export_tv && "ScoperError: expected `export_tv` from scoper visitor");

                    SolveResult field_result = m_types_mgr->assume_relation_holds(new TypeEqualsRelation(
                        field,
                        origin_tv, export_tv
                    ));
                    result = result_and(result, field_result);
                }
            }
            return !result_is_error(result);
        } else {
            return true;
        }
    }
    bool TyperVisitor::on_visit_using_stmt(ast::UsingStmt* node, VisitOrder visit_order) {
        // todo: implement this typer.
        assert(0 && "NotImplemented: TyperVisitor::on_visit_using_stmt");
        return true;
    }
    
    // expressions:
    bool TyperVisitor::on_visit_unit_exp(ast::UnitExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string name = "UnitExp";
            TypeVar* type_of_exp_tv = m_types_mgr->new_unknown_type_var(std::move(name), node);
            node->x_type_of_var(type_of_exp_tv);
            return true;
        } else {
            assert(visit_order == VisitOrder::Post);
            auto type_of_exp_tv = dynamic_cast<TypeVar*>(node->x_type_of_var());
            assert(type_of_exp_tv && "Uninitialized type_of_exp_tv");

            SolveResult result = m_types_mgr->assume_relation_holds(new TypeEqualsRelation(
                node,
                type_of_exp_tv, m_types_mgr->get_void_tv()
            ));

            return !result_is_error(result);
        }
    }
    bool TyperVisitor::on_visit_int_exp(ast::IntExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name; {
                if (node->force_unsigned()) {
                    tv_name = "UnsignedIntExp";
                } else {
                    tv_name = "SignedIntExp";
                }
            }
            TypeVar* int_tv = m_types_mgr->new_unknown_type_var(std::move(tv_name), node);
            node->x_type_of_var(int_tv);
        } else {
            assert(visit_order == VisitOrder::Post);
            auto int_tv = dynamic_cast<TypeVar*>(node->x_type_of_var());
            auto inferred_cv = (
                (node->force_unsigned()) ?
                m_types_mgr->get_unsigned_int_cv() :
                m_types_mgr->get_signed_int_cv()
            );
            SolveResult sp2_result = (
                m_types_mgr->assume_relation_holds(new ClassOfRelation(
                    node,
                    inferred_cv,
                    int_tv
                ))
            );
            std::string source_desc = "see integer expression here...";
            return post_feedback_from_first_kd_res(sp2_result, std::move(source_desc), node->loc());
        }
        return true;
    }
    bool TyperVisitor::on_visit_float_exp(ast::FloatExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "FloatExp";
            TypeVar* float_tv = m_types_mgr->new_unknown_type_var(std::move(tv_name), node);
            node->x_type_of_var(float_tv);
        } else {
            assert(visit_order == VisitOrder::Post);
            auto float_tv = dynamic_cast<TypeVar*>(node->x_type_of_var());
            assert(float_tv != nullptr);
            SolveResult sp2_result = m_types_mgr->assume_relation_holds(new ClassOfRelation(
                node,
                m_types_mgr->get_float_cv(), float_tv
            ));

            std::string source_desc = "see float expression here...";
            return post_feedback_from_first_kd_res(sp2_result, std::move(source_desc), node->loc());
        }
        return true;
    }
    bool TyperVisitor::on_visit_string_exp(ast::StringExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            TypeVar* string_tv = m_types_mgr->get_string_tv();
            node->x_type_of_var(string_tv);
        } else {
            auto typeof_string_tv = dynamic_cast<TypeVar*>(node->x_type_of_var());
            SolveResult sp2_result = m_types_mgr->assume_relation_holds(new TypeEqualsRelation(
                node,
                m_types_mgr->get_string_tv(), typeof_string_tv
            ));

            std::string source_desc = "see string expression here...";
            return post_feedback_from_first_kd_res(sp2_result, std::move(source_desc), node->loc());
        }
        return true;
    }
    bool TyperVisitor::on_visit_id_exp(ast::IdExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            auto id_tv = dynamic_cast<TypeVar*>(node->x_defn()->var());
            assert(id_tv != nullptr && "Scoper failed!");
            node->x_type_of_var(id_tv);
        }
        return true;
    }
    bool TyperVisitor::on_visit_paren_exp(ast::ParenExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "ParenExp";
            TypeVar* paren_tv = m_types_mgr->new_unknown_type_var(std::move(tv_name), node);
            node->x_type_of_var(paren_tv);
        } else {
            auto paren_tv = dynamic_cast<TypeVar*>(node->x_type_of_var());
            TypeVar* nested_tv = expect_type_var(
                node->nested_exp()->x_type_of_var(),
                std::move(std::string("an expression")),
                std::move(std::string("a parenthetical expression")),
                node->loc()
            );

            auto relation = new TypeEqualsRelation(node, paren_tv, nested_tv);
            SolveResult kd_res = m_types_mgr->assume_relation_holds(relation);
            
            std::string source_desc = "see paren expression here...";
            return post_feedback_from_first_kd_res(kd_res, std::move(source_desc), node->loc());
        }
        return true;
    }
    bool TyperVisitor::on_visit_tuple_exp(ast::TupleExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "TupleExp(" + std::to_string(node->items().size()) + ")";
            TypeVar* tuple_tv = m_types_mgr->new_unknown_type_var(std::move(tv_name), node);
            node->x_type_of_var(tuple_tv);
            return true;
        } else if (visit_order == VisitOrder::Post) {
            auto tuple_tv = dynamic_cast<TypeVar*>(node->x_type_of_var());
            assert(tuple_tv && "Uninitialized Tuple-TV");

            // assembling + checking field tvs:
            std::vector<TypeVar*> fields_tvs{node->items().size()};
            bool fields_ok = true;
            {
                size_t fields_count = fields_tvs.size();
                auto fields_count_str = std::to_string(fields_count);

                for (size_t i = 0; i < fields_count; i++) {
                    types::Var* field_var = node->items()[i]->x_type_of_var();
                    assert(field_var && "NULL tuple field var");

                    std::string expected_desc = "an expression";
                    std::string in_desc = "a " + fields_count_str + "-tuple expression";
                    types::TypeVar* field_tv = expect_type_var(
                        field_var,
                        std::move(expected_desc), std::move(in_desc),
                        node->items()[i]->loc()
                    );
                    if (field_tv == nullptr) {
                        fields_ok = false;
                    }

                    fields_tvs[i] = field_tv;
                }
            }
            if (!fields_ok) {
                return false;
            }

            // applying relation on all fields & tuple:
            std::string relation_why = "IsTupleExp";
            auto relation = new IsTupleRelation(
                std::move(relation_why),
                node, tuple_tv, std::move(fields_tvs)
            );
            auto assume_relation_result = m_types_mgr->assume_relation_holds(relation);
            return !result_is_error(assume_relation_result);
        } else {
            if (DEBUG) {
                assert(0 && "Invalid visit-order");
            }
            return false;
        }
    }
    bool TyperVisitor::on_visit_array_exp(ast::ArrayExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "ArrayExp(" + std::to_string(node->items().size()) + ")";
            TypeVar* array_tv = m_types_mgr->new_unknown_type_var(std::move(tv_name), node);
            node->x_type_of_var(array_tv);
        } else {
            // todo: set array exp requirements here by equating to an ArrayTV
        }
        return true;
    }
    bool TyperVisitor::on_visit_struct_exp(ast::StructExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "StructExp(" + std::to_string(node->fields().size()) + ")";
            TypeVar* struct_exp_tv = m_types_mgr->new_unknown_type_var(std::move(tv_name), node);
            node->x_type_of_var(struct_exp_tv);
        } else {
            // todo: set struct exp requirements here by equating to a StructTV
        }
        return true;
    }
    bool TyperVisitor::on_visit_type_query_exp(ast::TypeQueryExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "TypeQueryExp";
            TypeVar* type_query_exp_tv = m_types_mgr->new_unknown_type_var(std::move(tv_name), node);
            node->x_type_of_var(type_query_exp_tv);
        } else {
            // todo: implement this typer.
            // note: only used in typeclass_stmt
        }
        return true;
    }
    bool TyperVisitor::on_visit_chain_exp(ast::ChainExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "ChainExp";
            TypeVar* chain_exp_tv = m_types_mgr->new_unknown_type_var(std::move(tv_name), node);
            node->x_type_of_var(chain_exp_tv);
        } else {
            auto chain_tv = dynamic_cast<TypeVar*>(node->x_type_of_var());
            TypeVar* suffix_tv = nullptr;
            if (node->suffix()) {
                suffix_tv = expect_type_var(
                    node->suffix()->x_type_of_var(),
                    std::move(std::string("an expression suffix")),
                    std::move(std::string("a chain-expression")),
                    node->loc()
                );
            } else {
                suffix_tv = m_types_mgr->get_void_tv();
            }
            assert(suffix_tv && "Expected non-nullptr suffix_tv while typing ChainExp");

            auto relation = new TypeEqualsRelation(node, chain_tv, suffix_tv);
            SolveResult kd_res = m_types_mgr->assume_relation_holds(relation);

            std::string source_desc = "see chain expression here...";
            return post_feedback_from_first_kd_res(kd_res, std::move(source_desc), node->loc());
        }
        return true;
    }
    bool TyperVisitor::on_visit_lambda_exp(ast::LambdaExp* node, VisitOrder visit_order) {
        bool ok = true;

        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "LambdaExp";
            TypeVar* lambda_exp_tv = m_types_mgr->new_unknown_type_var(std::move(tv_name), node);
            node->x_type_of_var(lambda_exp_tv);
        } else {
            assert(visit_order == VisitOrder::Post);

            auto lambda_exp_tv = dynamic_cast<TypeVar*>(node->x_type_of_var());
            size_t args_count = node->lhs_vpattern()->fields().size();
            std::vector<VCallArg> args{args_count}; {
                for (size_t index = 0; index < args_count; index++) {
                    ast::VPattern::Field* field = node->lhs_vpattern()->fields()[index];
                    args[index].name = field->lhs_name();
                    args[index].varg_access_spec = field->accepted_varg_kind();
                    args[index].typeof_arg_tv = field->x_defn_tv();
                }
            }

            TypeVar* ret_tv = m_types_mgr->get_void_tv();
            if (node->opt_ret_typespec()) {
                ret_tv = expect_type_var(
                    node->opt_ret_typespec()->x_spec_var(),
                    std::move(std::string("a type specifier")),
                    std::move(std::string("a lambda function's return type-specifier")),
                    node->loc()
                );
            }

            auto body_tv = expect_type_var(
                node->rhs_body()->x_type_of_var(),
                std::move(std::string("an expression")),
                std::move(std::string("a lambda function's return body")),
                node->rhs_body()->loc()
            );
            auto relation1 = new TypeEqualsRelation(node, ret_tv, body_tv);
            SolveResult kd_res1 = m_types_mgr->assume_relation_holds(relation1);

            auto relation2 = new FormalVCallableRelation(node, lambda_exp_tv, std::move(args), ret_tv);
            SolveResult kd_res2 = m_types_mgr->assume_relation_holds(relation2);

            auto kd_res = result_and(kd_res1, kd_res2);
            if (result_is_error(kd_res)) {
                post_feedback_from_first_kd_res(kd_res, "if expression here...", node->loc());
                return false;
            }
        }

        return ok;
    }
    bool TyperVisitor::on_visit_if_exp(ast::IfExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "IfExp";
            TypeVar* if_exp_tv = m_types_mgr->new_unknown_type_var(std::move(tv_name), node);
            node->x_type_of_var(if_exp_tv);
        } else {
            Relation* relation = nullptr;
            if (node->else_exp() == nullptr) {
                relation = new IfThenRelation(
                    node,
                    dynamic_cast<TypeVar*>(node->x_type_of_var()),
                    expect_type_var(
                        node->cond_exp()->x_type_of_var(),
                        std::move(std::string("an expression")),
                        std::move(std::string("the condition of an if-then expression")),
                        node->loc()
                    ),
                    expect_type_var(
                        node->then_exp()->x_type_of_var(),
                        std::move(std::string("an expression")),
                        std::move(std::string("the 'then' branch of an if-then expression")),
                        node->loc()
                    )
                );
            } else {
                relation = new IfThenElseRelation(
                    node,
                    dynamic_cast<TypeVar*>(node->x_type_of_var()),
                    expect_type_var(
                        node->cond_exp()->x_type_of_var(),
                        std::move(std::string("an expression")),
                        std::move(std::string("the condition of an if-then-else expression")),
                        node->loc()
                    ),
                    expect_type_var(
                        node->then_exp()->x_type_of_var(),
                        std::move(std::string("an expression")),
                        std::move(std::string("the 'then' branch of an if-then-else expression")),
                        node->loc()
                    ),
                    expect_type_var(
                        node->else_exp()->x_type_of_var(),
                        std::move(std::string("an expression")),
                        std::move(std::string("the 'else' branch of an if-then-else expression")),
                        node->loc()
                    )
                );
            }
            SolveResult kd_res = m_types_mgr->assume_relation_holds(relation);

            if (result_is_error(kd_res)) {
                post_feedback_from_first_kd_res(kd_res, "if expression here...", node->loc());
                return false;
            }
        }
        return true;
    }
    bool TyperVisitor::on_visit_dot_index_exp(ast::DotIndexExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "DotIndexExp";
            TypeVar* dot_index_exp_tv = m_types_mgr->new_unknown_type_var(std::move(tv_name), node);
            node->x_type_of_var(dot_index_exp_tv);
        } else {
            // todo: require subtype of an array or tuple...
        }
        return true;
    }
    bool TyperVisitor::on_visit_dot_name_exp(ast::DotNameExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name;
            {
                switch (node->rhs_hint())
                {
                    case ast::DotNameExp::RhsHint::LhsEnum:
                    {
                        tv_name = "EnumDotNameExp";
                        break;
                    }
                    case ast::DotNameExp::RhsHint::LhsStruct:
                    {
                        tv_name = "StructDotNameExp";
                        break;
                    }
                    default:
                    {
                        assert(0 && "NotImplemented: typing DotNameExp: unknown DotNameExpLhsHint");
                        return false;
                    }
                }
            }
            TypeVar* dot_name_exp_tv = m_types_mgr->new_unknown_type_var(std::move(tv_name), node);
            node->x_type_of_var(dot_name_exp_tv);
            return true;
        } else {
            auto out_tv = dynamic_cast<TypeVar*>(node->x_type_of_var());

            switch (node->rhs_hint())
            {
                case ast::DotNameExp::RhsHint::LhsEnum:
                {
                    auto lhs_enum_type_spec = dynamic_cast<ast::TypeSpec*>(node->lhs());
                    auto lhs_enum_tv = expect_type_var(
                        lhs_enum_type_spec->x_spec_var(),
                        "an enum type specifier",
                        "an enum-dot-name expression",
                        node->loc()
                    );
                    SolveResult result = m_types_mgr->assume_relation_holds(
                        new TypeEqualsRelation(node, out_tv, lhs_enum_tv)
                    );
                    return !result_is_error(result);
                }
                case ast::DotNameExp::RhsHint::LhsStruct:
                {
                    auto lhs_struct_exp = dynamic_cast<ast::Exp*>(node->lhs());
                    auto lhs_struct_tv = expect_type_var(
                        lhs_struct_exp->x_type_of_var(),
                        "a struct expression",
                        "a struct-dot-name expression",
                        node->loc()
                    );
                    assert(lhs_struct_tv && "Invalid lhs_struct_tv in `TyperVisitor::on_visit_dot_name_exp`");

                    // subtype of single-field struct:
                    TypeVar* min_struct_super_tv = nullptr;
                    {
                        std::string min_struct_super_tv_name = "StructDotNameExp_MinSuperType";
                        min_struct_super_tv = m_types_mgr->new_unknown_type_var(
                            std::move(min_struct_super_tv_name),
                            node
                        );
                    }
                    assert(min_struct_super_tv);


                    std::map<intern::String, Var*> fields_tvs;
                    fields_tvs[node->rhs_name()] = out_tv;

                    return !result_is_error(result_and(
                        m_types_mgr->assume_relation_holds(new SubtypeOfRelation(
                            node, lhs_struct_tv, min_struct_super_tv
                        )),
                        m_types_mgr->assume_relation_holds(new IsStructRelation(
                            std::move(std::string{"StructDotNameExp"}), node,
                            min_struct_super_tv,
                            fields_tvs
                        ))
                    ));
                }
                default:
                {
                    assert(0 && "NotImplemented: typing DotNameExp: unknown DotNameExpLhsHint");
                    return false;
                }
            }
        }
    }
    bool TyperVisitor::on_visit_module_dot_exp(ast::ModuleDotExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            ast::BaseModExp::Field* field = get_mod_field_from_addr(node->lhs_mod_address(), node->rhs_name());
            if (!field) {
                assert(0 && "NotImplemented: could not find field named '?' in module");
            }
            auto defn_tv = dynamic_cast<TypeVar*>(field->x_defn_var());
            assert(defn_tv && "Invalid/malformed ma_type_spec => error in scoper.");
            node->x_type_of_var(defn_tv);
            return true;
        } else if (visit_order == VisitOrder::Post) {
            return true;
        } else {
            if (DEBUG) {
                assert(0 && "NotImplemented: invalid VisitOrder.");
            }
            return false;
        }
    }
    bool TyperVisitor::on_visit_unary_exp(ast::UnaryExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "UnaryExp";
            TypeVar* unary_exp_tv = m_types_mgr->new_unknown_type_var(std::move(tv_name), node);
            node->x_type_of_var(unary_exp_tv);
        } else {
            assert(visit_order == VisitOrder::Post);

            auto ret_tv = dynamic_cast<TypeVar*>(node->x_type_of_var());
            assert(ret_tv != nullptr);

            auto arg_tv = expect_type_var(
                node->operand()->x_type_of_var(),
                std::move(std::string("an expression")),
                std::move(std::string("a unary expression")),
                node->loc()
            );

            bool preserves_type = false;
            ClassVar* arg_class_cv = nullptr;
            ClassVar* ret_class_cv = nullptr;
            switch (node->unary_operator())
            {
                case ast::UnaryOperator::Not:
                {
                    // UnsignedInt -> UnsignedInt
                    arg_class_cv = m_types_mgr->get_unsigned_int_cv();
                    ret_class_cv = m_types_mgr->get_unsigned_int_cv();
                    preserves_type = true;
                    break;
                }
                case ast::UnaryOperator::Plus:
                {
                    // UnsignedInt -> SignedInt
                    arg_class_cv = m_types_mgr->get_unsigned_int_cv();
                    ret_class_cv = m_types_mgr->get_signed_int_cv();
                    preserves_type = false;
                    break;
                }
                case ast::UnaryOperator::Minus:
                {
                    // SignedInt -> SignedInt
                    arg_class_cv = m_types_mgr->get_signed_int_cv();
                    ret_class_cv = m_types_mgr->get_signed_int_cv();
                    preserves_type = true;
                    break;
                }
                default:
                {
                    if (pdm::DEBUG) {
                        assert(0 && "NotImplemented: visit unary exp for unknown operator.");
                    }
                    return false;
                }
            }

            if (arg_class_cv && ret_class_cv) {
                // ret_tv :: arg_tv
                auto res1 = SolveResult::NoChange;
                if (preserves_type) {
                    res1 = m_types_mgr->assume_relation_holds(new TypeEqualsRelation(node, ret_tv, arg_tv));
                }

                // ret_tv ret_class_cv
                // arg_tv arg_class_cv
                auto res2 = result_and(
                    m_types_mgr->assume_relation_holds(
                        new ClassOfRelation(node, arg_class_cv, arg_tv)
                    ),
                    m_types_mgr->assume_relation_holds(
                        new ClassOfRelation(node, ret_class_cv, ret_tv)
                    )
                );

                return !(result_is_error(result_and(res1, res2)));
            }
        }
        return true;
    }
    bool TyperVisitor::on_visit_binary_exp(ast::BinaryExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "BinaryExp";
            TypeVar* binary_exp_tv = m_types_mgr->new_unknown_type_var(std::move(tv_name), node);
            node->x_type_of_var(binary_exp_tv);
        } else {
            auto binary_exp_tv = dynamic_cast<TypeVar*>(node->x_type_of_var());
            assert(binary_exp_tv && "Uninitialized TV");

            auto ret_tv = binary_exp_tv;
            auto type_of_lhs_tv = expect_type_var(
                node->lhs_operand()->x_type_of_var(),
                "an expression",
                "the left argument slot of a binary operator expression",
                node->loc()
            );
            auto type_of_rhs_tv = expect_type_var(
                node->rhs_operand()->x_type_of_var(),
                "an expression",
                "the right argument slot of a binary operator expression",
                node->loc()
            );
            if (!type_of_lhs_tv || !type_of_rhs_tv) {
                return false;
            } else {
                switch (node->binary_operator())
                {
                    case ast::BinaryOperator::Mul:
                    case ast::BinaryOperator::Div:
                    case ast::BinaryOperator::Rem:
                    case ast::BinaryOperator::Add:
                    case ast::BinaryOperator::Subtract:
                    {
                        // (t1, t2) -> t
                        // (t IsNumber)
                        // note t :< t1 and t :< t2, so t1 and t2 are converted (extended) to t before operation.

                        // ensuring return type is a number:
                        auto ret_number_relation = new IsNumberRelation(node, ret_tv);
                        auto res1 = m_types_mgr->assume_relation_holds(ret_number_relation);

                        // relating arg types to return type:
                        // ret_tv :< type_of_lhs_tv
                        // ret_tv :< type_of_rhs_tv
                        auto eq_relation1 = new SubtypeOfRelation(node, ret_tv, type_of_lhs_tv);
                        auto eq_relation2 = new SubtypeOfRelation(node, ret_tv, type_of_rhs_tv);
                        auto res2 = result_and(
                            m_types_mgr->assume_relation_holds(eq_relation1),
                            m_types_mgr->assume_relation_holds(eq_relation2)
                        );

                        return !result_is_error(result_and(res1, res2));
                    }
                    case ast::BinaryOperator::Less:
                    case ast::BinaryOperator::LessOrEq:
                    case ast::BinaryOperator::Greater:
                    case ast::BinaryOperator::GreaterOrEq:
                    {
                        // (t, t) -> UInt1
                        // (t IsNumber)
                        // here, t is explicitly instantiated.

                        // ensuring return type is UInt1 aka Boolean:
                        auto ret_relation = new TypeEqualsRelation(node, ret_tv, m_types_mgr->get_u1_tv());
                        auto ret_result = m_types_mgr->assume_relation_holds(ret_relation);

                        // creating a 't' type that subtypes both arg types:
                        std::string t_name = "BinaryCmpExpArg";
                        TypeVar* t = m_types_mgr->new_unknown_type_var(std::move(t_name), node);
                        auto t_result = result_and(
                            result_and(
                                // t :< lhs
                                m_types_mgr->assume_relation_holds(new SubtypeOfRelation(node, t, type_of_lhs_tv)),

                                // t :< rhs
                                m_types_mgr->assume_relation_holds(new SubtypeOfRelation(node, t, type_of_rhs_tv))
                            ),

                            // t IsNumber
                            m_types_mgr->assume_relation_holds(new IsNumberRelation(node, t))
                        );

                        return !result_is_error(result_and(t_result, ret_result));
                    }
                    case ast::BinaryOperator::Equals:
                    case ast::BinaryOperator::NotEquals:
                    {
                        // (t, t) -> UInt1
                        auto ret_relation = new TypeEqualsRelation(node, ret_tv, m_types_mgr->get_u1_tv());
                        auto ret_result = m_types_mgr->assume_relation_holds(ret_relation);

                        // creating a 't' type that subtypes both arg types:
                        std::string t_name = "BinaryEqExpArg";
                        auto t = m_types_mgr->new_unknown_type_var(std::move(t_name), node);
                        auto t_result = result_and(
                            m_types_mgr->assume_relation_holds(new SubtypeOfRelation(node, t, type_of_lhs_tv)),
                            m_types_mgr->assume_relation_holds(new SubtypeOfRelation(node, t, type_of_rhs_tv))
                        );

                        return !result_is_error(result_and(ret_result, t_result));
                    }
                    case ast::BinaryOperator::And:
                    case ast::BinaryOperator::Or:
                    case ast::BinaryOperator::XOr:
                    {
                        // bitwise operations only defined on unsigned int class:
                        auto res1 = m_types_mgr->assume_relation_holds(
                            new SubtypeOfRelation(node, ret_tv, type_of_lhs_tv)
                        );
                        auto res2 = m_types_mgr->assume_relation_holds(
                            new SubtypeOfRelation(node, ret_tv, type_of_rhs_tv)
                        );
                        auto res3 = m_types_mgr->assume_relation_holds(
                            new ClassOfRelation(node, m_types_mgr->get_unsigned_int_cv(), ret_tv)
                        );
                        return !result_is_error(
                            result_and(
                                result_and(res1, res2),
                                res3
                            )
                        );
                    }
                    default:
                    {
                        assert(0 && "NotImplemented: typing unknown BinaryOperator");
                    }
                }
            }
        }
        return true;
    }
    bool TyperVisitor::on_visit_v_call_exp(ast::VCallExp* node, VisitOrder visit_order) {
        bool ok = true;

        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "VCallExp_Ret";
            TypeVar* vcall_exp_tv = m_types_mgr->new_unknown_type_var(std::move(tv_name), node);
            node->x_type_of_var(vcall_exp_tv);
        } else {
            assert(visit_order == VisitOrder::Post);

            auto ret_tv = dynamic_cast<TypeVar*>(node->x_type_of_var());

            TypeVar* called_tv = expect_type_var(
                node->lhs_called()->x_type_of_var(),
                std::move(std::string("an expression to call")),
                std::move(std::string("a function call expression")),
                node->loc()
            );

            size_t args_count = node->args().size();
            std::vector<VCallArg> args{args_count}; {
                for (size_t index = 0; index < args_count; index++) {
                    ast::VArg* arg = node->args()[index];
                    args[index].name = {};
                    args[index].varg_access_spec = arg->access_spec();

                    Var* arg_var = arg->arg_exp()->x_type_of_var();
                    assert(arg_var != nullptr && "Typer error: expected arg var from pre-visit.");
                    auto arg_tv = dynamic_cast<TypeVar*>(arg_var);
                    if (arg_tv != nullptr) {
                        args[index].typeof_arg_tv = arg_tv;
                    } else {
                        std::string headline = "Expected value VCallExp argument, received template.";
                        std::vector<feedback::Note*> notes{1}; {
                            std::string note_desc = "incorrect arg here...";
                            notes[0] = new feedback::SourceLocNote(std::move(note_desc), arg->arg_exp()->loc());
                        }
                        feedback::post(new feedback::Letter(
                            feedback::Severity::Error,
                            std::move(headline),"",
                            std::move(notes)
                        ));
                        ok = false;
                    }
                }
            }

            auto relation = new ActualVCallableRelation(node, called_tv, std::move(args), ret_tv);
            SolveResult kd_res = m_types_mgr->assume_relation_holds(relation);

            if (result_is_error(kd_res)) {
                post_feedback_from_first_kd_res(kd_res, "if expression here...", node->loc());
                return false;
            }
        }

        return ok;
    }
    bool TyperVisitor::on_visit_t_call_exp(ast::TCallExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "TCallExp";
            TypeVar* tcall_exp_tv = m_types_mgr->new_unknown_type_var(std::move(tv_name), node);
            node->x_type_of_var(tcall_exp_tv);
        } else {
            assert(visit_order == VisitOrder::Post);
            assert(0 && "NotImplemented: typing template call expressions");
        }
        return true;
    }

    // patterns:
    bool TyperVisitor::on_visit_v_pattern(ast::VPattern* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            // wait for post
            return true;
        } else {
            assert(visit_order == VisitOrder::Post);

            bool ok = true;
            for (ast::VPattern::Field* field: node->fields()) {
                TypeVar* field_tv = field->x_defn_tv();
                
                Var* spec_type_var = field->rhs_typespec()->x_spec_var();
                auto spec_type_tv = dynamic_cast<TypeVar*>(spec_type_var);
                if (spec_type_tv != nullptr) {
                    auto spec_relation = new TypeEqualsRelation(field, field_tv, spec_type_tv);
                    SolveResult kd_res = m_types_mgr->assume_relation_holds(spec_relation);
                    std::string source_desc = "see V-Pattern here...";
                    ok = (ok && post_feedback_from_first_kd_res(kd_res, std::move(source_desc), node->loc()));
                } else {
                    std::string headline = "Incorrect set specifier in V-Pattern";
                    std::string desc = "Expected type specifier, instead received class or incomplete template.";
                    std::vector<feedback::Note*> notes{1}; {
                        std::string note_desc = "incorrect set specifier here...";
                        notes[0] = new feedback::SourceLocNote(std::move(note_desc), node->loc());
                    }
                    feedback::post(new feedback::Letter(
                        feedback::Severity::Error,
                        std::move(headline),
                        std::move(desc),
                        std::move(notes)
                    ));
                    ok = false;
                }
            }
            return ok;
        }
    }
    bool TyperVisitor::on_visit_t_pattern(ast::TPattern* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Post) {
            for (ast::TPattern::Field* field: node->fields()) {
                Var* field_var = field->x_defn_var();
                auto field_tv = dynamic_cast<TypeVar*>(field_var);
                assert(field_tv != nullptr);

                Var* field_spec_var = nullptr; {
                    switch (field->field_kind()) {
                        case ast::TPattern::FieldKind::Type:
                            field_spec_var = dynamic_cast<ast::ClassSpec*>(field->rhs_set_spec())->x_spec_var();
                            break;
                        case ast::TPattern::FieldKind::Value:
                            field_spec_var = dynamic_cast<ast::TypeSpec*>(field->rhs_set_spec())->x_spec_var();
                            break;
                    }
                }
                assert(field_spec_var != nullptr);

                if (field->field_kind() == ast::TPattern::FieldKind::Value) {
                    // [value Type]
                    auto field_spec_tv = dynamic_cast<TypeVar*>(field_spec_var);
                    if (field_spec_tv != nullptr && field_tv != nullptr) {
                        SolveResult kd_res = m_types_mgr->assume_relation_holds(new TypeEqualsRelation(node, field_spec_tv, field_tv));
                        std::string source_desc = "In Value T-Pattern Arg here..";
                        return post_feedback_from_first_kd_res(kd_res, std::move(source_desc), node->loc());
                    } else {
                        std::string headline = "Incorrect set specifier";
                        std::string desc = "Expected type specifier, instead received class or incomplete template.";
                        std::vector<feedback::Note*> notes{1}; {
                            std::string note_desc = "incorrect set specifier here...";
                            notes[0] = new feedback::SourceLocNote(std::move(note_desc), node->loc());
                        }
                        feedback::post(new feedback::Letter(
                            feedback::Severity::Error,
                            std::move(headline),
                            std::move(desc),
                            std::move(notes)
                        ));
                    }
                } else if (field->field_kind() == ast::TPattern::FieldKind::Type) {
                    // [Type Class]
                    auto field_spec_cv = dynamic_cast<ClassVar*>(field_spec_var);
                    auto proxy_field_tv = field_tv;
                    if (field_spec_cv != nullptr) {
                        SolveResult kd_res = m_types_mgr->assume_relation_holds(new ClassOfRelation(node, field_spec_cv, field_tv));
                        std::string source_desc = "In Type T-Pattern Arg here..";
                        return post_feedback_from_first_kd_res(kd_res, std::move(source_desc), node->loc());
                    } else {
                        std::string headline = "Incorrect set specifier";
                        std::string desc = "Expected typeclass specifier, instead received type or incomplete template.";
                        std::vector<feedback::Note*> notes{1}; {
                            std::string note_desc = "incorrect set specifier here...";
                            notes[0] = new feedback::SourceLocNote(std::move(note_desc), node->loc());
                        }
                        feedback::post(new feedback::Letter(
                            feedback::Severity::Error,
                            std::move(headline),
                            std::move(desc),
                            std::move(notes)
                        ));
                    }
                }
            }
        }
        return true;
    }
    bool TyperVisitor::on_visit_l_pattern(ast::LPattern* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Post) {
            for (ast::LPattern::Field* field: node->fields()) {
                TypeVar* tv = field->x_defn_tv();
                if (field->opt_rhs_typespec()) {
                    TypeVar* rhs_tv = dynamic_cast<TypeVar*>(field->opt_rhs_typespec()->x_spec_var());
                    if (rhs_tv != nullptr) {
                        SolveResult kd_res = m_types_mgr->assume_relation_holds(new TypeEqualsRelation(node, tv, rhs_tv));
                        
                        std::string source_desc = "see L-Pattern here...";
                        return post_feedback_from_first_kd_res(kd_res, std::move(source_desc), node->loc());
                    } else {
                        std::string headline = "Incorrect set specifier";
                        std::string desc = "Expected type specifier, instead received class or incomplete template.";
                        std::vector<feedback::Note*> notes{1}; {
                            std::string note_desc = "incorrect set specifier here...";
                            notes[0] = new feedback::SourceLocNote(std::move(note_desc), node->loc());
                        }
                        feedback::post(new feedback::Letter(
                            feedback::Severity::Error,
                            std::move(headline),
                            std::move(desc),
                            std::move(notes)
                        ));
                    }
                }
            }
        }
        return true;
    }
    
    // typespecs:
    bool TyperVisitor::on_visit_id_type_spec(ast::IdTypeSpec* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            auto defn = node->x_defn();
            assert(defn && "Undefined/uninitialized ID type spec in typer.");
            auto defn_var = dynamic_cast<TypeVar*>(defn->var());
            node->x_spec_var(defn_var);
        }
        return true;
    }
    bool TyperVisitor::on_visit_fn_type_spec(ast::FnTypeSpec* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string name = "FnTypeSpec";
            node->x_spec_var(m_types_mgr->new_unknown_type_var(std::move(name), node));
        } else {
            assert(visit_order == VisitOrder::Post);
            // node->x_spec_var(m_types_mgr->new_func_tv()) ...
            auto spectype_tv = dynamic_cast<TypeVar*>(node->x_spec_var());

            size_t args_count = node->lhs_vpattern()->fields().size();
            std::vector<VCallArg> args{args_count};
            for (size_t index = 0; index < args.size(); index++) {
                ast::VPattern::Field* vpattern_field = node->lhs_vpattern()->fields()[index];
                args[index].name = vpattern_field->lhs_name();
                args[index].varg_access_spec = vpattern_field->accepted_varg_kind();
                args[index].typeof_arg_tv = vpattern_field->x_defn_tv();
            }

            TypeVar* ret_tv = m_types_mgr->get_void_tv();
            if (node->opt_ret_type_spec() != nullptr) {
                Var* ret_spectype_var = node->opt_ret_type_spec()->x_spec_var();
                auto ret_spectype_tv = dynamic_cast<TypeVar*>(ret_spectype_var);
                if (ret_spectype_tv != nullptr) {
                    ret_tv = ret_spectype_tv;
                } else {
                    std::string headline = "Incorrect set specifier";
                    std::string desc = "Expected type specifier, instead received class or incomplete template.";
                    std::vector<feedback::Note*> notes{1}; {
                        std::string note_desc = "incorrect set specifier here...";
                        notes[0] = new feedback::SourceLocNote(std::move(note_desc), node->loc());
                    }
                    feedback::post(new feedback::Letter(
                        feedback::Severity::Error,
                        std::move(headline),
                        std::move(desc),
                        std::move(notes)
                    ));
                }
            }
            
            SolveResult kd_res = m_types_mgr->assume_relation_holds(new FormalVCallableRelation(
                node, spectype_tv, std::move(args), ret_tv
            ));
            
            // todo: post
        }
        return true;
    }
    bool TyperVisitor::on_visit_tuple_type_spec(ast::TupleTypeSpec* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string name = "Tuple";
            TypeVar* tuple_tv = m_types_mgr->new_unknown_type_var(std::move(name), node);
            node->x_spec_var(tuple_tv);
        } else {
            assert(visit_order == VisitOrder::Post);
            
            // getting the tuple_tv:
            auto tuple_tv = dynamic_cast<TypeVar*>(node->x_spec_var());
            assert(tuple_tv != nullptr);

            // collecting a vector of field tvs:
            size_t num_fields = node->items().size();
            std::vector<TypeVar*> fields_tvs{num_fields};
            for (size_t field_index = 0; field_index < num_fields; field_index++) {
                ast::TypeSpec* field_type_spec = node->items()[field_index];
                assert(field_type_spec != nullptr);

                Var* field_item_var = field_type_spec->x_spec_var();
                auto field_item_tv = dynamic_cast<TypeVar*>(field_item_var);
                if (field_item_tv != nullptr) {
                    fields_tvs[field_index] = field_item_tv;
                } else {
                    std::string headline = "Incorrect set specifier in Tuple type specifier";
                    std::string desc = "Expected type specifier, instead received class or incomplete template.";
                    std::vector<feedback::Note*> notes{1}; {
                        std::string note_desc = "incorrect set specifier here...";
                        notes[0] = new feedback::SourceLocNote(std::move(note_desc), node->loc());
                    }
                    feedback::post(new feedback::Letter(
                        feedback::Severity::Error,
                        std::move(headline),
                        std::move(desc),
                        std::move(notes)
                    ));
                }
            }

            // relating:
            std::string why = "TupleTypeSpec";
            SolveResult kd_res = m_types_mgr->assume_relation_holds(new IsTupleRelation(
                std::move(why),
                node,
                tuple_tv,
                std::move(fields_tvs)
            ));

            std::string source_desc = "See Tuple type specifier here...";
            return post_feedback_from_first_kd_res(kd_res, std::move(source_desc), node->loc());
        }
        return true;
    }
    bool TyperVisitor::on_visit_ma_type_spec(ast::ModAddressIdTypeSpec* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            ast::BaseModExp::Field* field = get_mod_field_from_addr(node->lhs_mod_address(), node->rhs_type_name());
            if (!field) {
                assert(0 && "NotImplemented: could not find field named '?' in module");
            }
            auto defn_tv = dynamic_cast<TypeVar*>(field->x_defn_var());
            assert(defn_tv && "Invalid/malformed ma_type_spec => error in scoper.");
            node->x_spec_var(defn_tv);
        } else {
            assert(visit_order == VisitOrder::Post);
        }
        return true;
    }
    bool TyperVisitor::on_visit_enum_type_spec(ast::EnumTypeSpec* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string enum_type_spec_name = "AnonymousEnumTypeSpec";
            auto enum_tv = m_types_mgr->new_unknown_type_var(std::move(enum_type_spec_name), node);
            node->x_spec_var(enum_tv);
            
            return true;
        } else {
            assert(visit_order == VisitOrder::Post && "Invalid visit order.");

            // obtaining the enum type:
            auto enum_tv = node->x_spec_var();
            assert(enum_tv && "Un-initialized enum_tv (expected in typer pre-pass)");

            // obtaining the field types:
            std::map<intern::String, Var*> fields;
            for (ast::EnumTypeSpec::Field* field: node->fields()) {
                // checking for & reporting duplicate fields:
                auto found_it = fields.find(field->name());
                if (found_it != fields.end()) {
                    std::string headline = (
                        "Field '" + std::string(field->name().cpp_str()) + "' repeated in enum type specifier"
                    );
                    std::string desc = "Each field in an enum must have a unique name.";
                    std::vector<feedback::Note*> notes{2}; {
                        std::string note_desc0 = "first definition here...";
                        source::Loc loc0 = found_it->second->opt_client_ast_node()->loc();
                        notes[0] = new feedback::SourceLocNote(std::move(note_desc0), loc0);

                        std::string note_desc1 = "subsequent definition here...";
                        source::Loc loc1 = field->loc();
                        notes[1] = new feedback::SourceLocNote(std::move(note_desc1), loc1);
                    }
                    feedback::post(new feedback::Letter(
                        feedback::Severity::Error,
                        std::move(headline),
                        std::move(desc)
                    ));
                } else {
                    // inserting the appropriate field as specified:
                    TypeVar* rhs_tv = nullptr; {
                        if (field->opt_type_spec()) {
                            rhs_tv = field->opt_type_spec()->x_spec_var();
                        } else {
                            rhs_tv = m_types_mgr->get_void_tv();
                        }
                    }
                    assert(rhs_tv && "Could not obtain field type in enum type specifier");
                    fields[field->name()] = rhs_tv;
                }
            }
            if (fields.size() != node->fields().size()) {
                std::string headline = "Invalid enum type specifier fields";
                std::string more = (
                    "The provided fields in an enum type specifier cannot be used to construct a real "
                    "enum since doing so would violate typing rules."
                );
                std::vector<feedback::Note*> notes{1}; {
                    std::string desc0 = "See enum type specifier here...";
                    notes[0] = new feedback::AstNodeNote(std::move(desc0), node);
                }
                feedback::post(new feedback::Letter(
                    feedback::Severity::Error,
                    std::move(headline), std::move(more), std::move(notes)
                ));
                return false;
            } else {
                // relating field types with enum type:
                std::string relation_why = "EnumTypeSpec";
                auto relation = new IsEnumRelation(std::move(relation_why), node, enum_tv, fields);
                auto assume_relation_result = m_types_mgr->assume_relation_holds(relation);
                bool ok = !result_is_error(assume_relation_result);
                assert(ok && "Failed to assume validated relation on EnumTypeSpec");
                return true;
            }
        }
    }
    bool TyperVisitor::on_visit_struct_type_spec(ast::StructTypeSpec* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string name = "StructTypeSpec";
            TypeVar* struct_tv = m_types_mgr->new_unknown_type_var(std::move(name), node);
            node->x_spec_var(struct_tv);
            return true;
        } else {
            assert(visit_order == VisitOrder::Post);
            auto struct_tv = dynamic_cast<TypeVar*>(node->x_spec_var());
            assert(struct_tv != nullptr);
            
            // collecting & checking fields_tvs:
            std::map<intern::String, Var*> fields_tvs;
            bool fields_ok = true;
            for (ast::StructTypeSpec::Field* field: node->fields()) {
                Var* field_var = field->rhs_typespec()->x_spec_var();
                assert(field_var != nullptr);

                // verifying the name is unique:
                auto found_it = fields_tvs.find(field->lhs_name());
                if (found_it != fields_tvs.end()) {
                    fields_ok = false;
                    std::string headline = (
                        "Field '" + std::string(field->lhs_name().content()) + "' repeated in struct type specifier"
                    );
                    std::string desc = "Each field in a struct must have a unique name.";
                    std::vector<feedback::Note*> notes{2}; {
                        std::string note_desc0 = "first definition here...";
                        source::Loc loc0 = found_it->second->opt_client_ast_node()->loc();
                        notes[0] = new feedback::SourceLocNote(std::move(note_desc0), loc0);

                        std::string note_desc1 = "subsequent definition here...";
                        source::Loc loc1 = field->loc();
                        notes[1] = new feedback::SourceLocNote(std::move(note_desc1), loc1);
                    }
                    feedback::post(new feedback::Letter(
                        feedback::Severity::Error,
                        std::move(headline),
                        std::move(desc)
                    ));
                    continue;
                }

                // checking the TV:
                auto field_tv = dynamic_cast<TypeVar*>(field_var);
                if (field_tv == nullptr) {
                    fields_ok = false;
                    std::string headline = "Incorrect set specifier in Struct Set Specifier";
                    std::string desc = "Expected type specifier, instead received class or incomplete template.";
                    std::vector<feedback::Note*> notes{1}; {
                        std::string note_desc = "incorrect set specifier here...";
                        notes[0] = new feedback::SourceLocNote(std::move(note_desc), node->loc());
                    }
                    feedback::post(new feedback::Letter(
                        feedback::Severity::Error,
                        std::move(headline),
                        std::move(desc),
                        std::move(notes)
                    ));
                    continue;
                }

                // storing it:
                fields_tvs[field->lhs_name()] = field_tv;
            }

            if (!fields_ok) {
                std::string headline = "Invalid struct type specifier fields";
                std::string more = (
                    "The provided fields in an struct type specifier cannot be used to construct a real "
                    "struct since doing so would violate typing rules."
                );
                std::vector<feedback::Note*> notes{1}; {
                    std::string desc0 = "See struct type specifier here...";
                    notes[0] = new feedback::AstNodeNote(std::move(desc0), node);
                }
                feedback::post(new feedback::Letter(
                    feedback::Severity::Error,
                    std::move(headline), std::move(more), std::move(notes)
                ));
                return false;
            }

            // assuming a StructOf relation to bind struct_tv to fields:
            std::string name = "StructTypeSpec";
            SolveResult kd_res = m_types_mgr->assume_relation_holds(new IsStructRelation(
                std::move(name), node,
                struct_tv, std::move(fields_tvs)
            ));
            assert(!result_is_error(kd_res));
            return true;
        }
    }

    // class specs:
    bool TyperVisitor::on_visit_class_exp_class_spec(ast::ClassExpClassSpec* node, VisitOrder visit_order) {
        assert(0 && "NotImplemented: TyperVisitor::on_visit_class_exp_class_spec");
        return true;
    }
    bool TyperVisitor::on_visit_id_class_spec(ast::IdClassSpec* node, VisitOrder visit_order) {
        // assert(0 && "NotImplemented: ID class specs for templates.");
        if (visit_order == VisitOrder::Pre) {
            auto defn = node->x_defn();
            auto var = defn->var();
            std::string expected_desc = "a CLASS specifier";
            std::string expected_in_desc = "a CLASS ID";
            auto class_var = expect_class_var(
                var,
                std::move(expected_desc),
                std::move(expected_in_desc),
                node->loc()
            );
            node->x_spec_var(class_var);
            return true;
        }
        return true;
    }
    bool TyperVisitor::on_visit_ma_class_spec(ast::ModAddressIdClassSpec* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            ast::BaseModExp::Field* field = get_mod_field_from_addr(node->lhs_mod_address(), node->rhs_type_name());
            if (!field) {
                assert(0 && "NotImplemented: could not find field named '?' in module");
            }
            auto defn_tv = dynamic_cast<ClassVar*>(field->x_defn_var());
            assert(defn_tv && "Invalid/malformed ma_class_spec => error in scoper.");
            node->x_spec_var(defn_tv);
        } else {
            assert(visit_order == VisitOrder::Post);
        }
        return true;
    }
    
    // args:
    bool TyperVisitor::on_visit_t_arg(ast::TArg* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    bool TyperVisitor::on_visit_v_arg(ast::VArg* node, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }
    
    // non-syntactic:
    bool TyperVisitor::on_visit_builtin_type_stmt(ast::BuiltinStmt* node, VisitOrder visit_order) {
        return true;
    }

    //
    // Helpers:
    //

    bool TyperVisitor::help_post_type_const_or_val_or_var_stmt(ast::Node* node, ast::LPattern* lhs, ast::Exp* rhs) {
        TypeVar* typeof_rhs_tv = expect_type_var(
            rhs->x_type_of_var(),
            std::move(std::string("an expression")),
            std::move(std::string("a 'Let' value-id-binding")),
            rhs->loc()
        );
        if (lhs->destructure()) {
            // todo: destructure as a tuple
            std::cout << "NotImplemented: tuple-lpattern destructuring" << std::endl;
        } else {
            assert(lhs->fields().size() == 1);
            ast::LPattern::Field* field = lhs->fields()[0];
            TypeVar* typeof_lhs_tv = field->x_defn_tv();
            
            // "let lhs = rhs" <=> rhs :< lhs
            auto relation = new SubtypeOfRelation(node, typeof_rhs_tv, typeof_lhs_tv);
            SolveResult assume_op_result1 = m_types_mgr->assume_relation_holds(relation);
            
            // if type-spec, ensure exact type equality
            SolveResult assume_op_result2 = SolveResult::NoChange; {
                if (field->opt_rhs_typespec()) {
                    TypeVar* typespec_tv = expect_type_var(
                        field->opt_rhs_typespec()->x_spec_var(),
                        std::move(std::string("a type specifier")),
                        std::move(std::string("an L-pattern field")),
                        node->loc()
                    );
                    if (typespec_tv != nullptr) {
                        // typeof_lhs_tv :: typeof_typespec_tv
                        auto ts_relation = new TypeEqualsRelation(
                            field,
                            typeof_lhs_tv,
                            typespec_tv
                        );
                        assume_op_result2 = m_types_mgr->assume_relation_holds(relation);
                    } else {
                        assume_op_result2 = SolveResult::TypingError;
                    }
                }
            }

            std::string source_desc = "see const/val/var statement here...";
            post_feedback_from_first_kd_res(
                result_and(assume_op_result1, assume_op_result2),
                std::move(source_desc),
                node->loc()
            );
        }
        return true;
    }

    Var* TyperVisitor::expect_var_check(
        Var* var,
        std::string&& expected_desc,
        std::string&& in_desc,
        VarArchetype expected_var_kind,
        source::Loc loc
    ) {
        if (var != nullptr && var->var_archetype() == expected_var_kind) {
            // passes!
            return var;
        } else {
            if (var != nullptr) {
                std::string vk_as_str = var_archetype_as_str(var->var_archetype());

                std::string headline = "Expected " + std::move(expected_desc) + " in " + std::move(in_desc);
                std::string desc = "Instead, the term has a '" + vk_as_str + "' type variable.";
                std::vector<feedback::Note*> notes{1}; {
                    std::string note_desc = "incorrect term here...";
                    notes[0] = new feedback::SourceLocNote(std::move(note_desc), loc);
                }
                feedback::post(new feedback::Letter(
                    feedback::Severity::Error,
                    std::move(headline),
                    std::move(desc),
                    std::move(notes)
                ));
            }
            return nullptr;
        }
    }
    TypeVar* TyperVisitor::expect_type_var(
        Var* var,
        std::string&& expected_desc, std::string&& in_desc,
        source::Loc loc
    ) {
        Var* checked_var = expect_var_check(var, std::move(expected_desc), std::move(in_desc), VarArchetype::Type, loc);
        if (checked_var == nullptr) {
            return nullptr;
        } else {
            return dynamic_cast<TypeVar*>(checked_var);
        }
    }

    ClassVar* TyperVisitor::expect_class_var(
        Var* var,
        std::string&& expected_desc, std::string&& in_desc,
        source::Loc loc
    ) {
        Var* checked_var = expect_var_check(var, std::move(expected_desc), std::move(in_desc), VarArchetype::Class, loc);
        if (checked_var == nullptr) {
            return nullptr;
        } else {
            return dynamic_cast<ClassVar*>(checked_var);
        }
    }

    ast::BaseModExp::Field* TyperVisitor::get_mod_field_from_addr(
        ast::ModAddress* lhs_mod_address,
        intern::String rhs_name
    ) {
        auto lhs_mod_exp = lhs_mod_address->x_origin_mod_exp();
        assert(lhs_mod_exp && "Scoper error: expected lhs mod exp to be non-nullptr");

        // assert(0 && "STUBBED: TyperVisitor::get_mod_field_from_addr-- needs rewrite.");
        // note: consider a more efficient field lookup mechanism if required
        // currently just using a linear scan.
        ast::BaseModExp::Field* found_field = nullptr;
        for (ast::BaseModExp::Field* field: lhs_mod_exp->fields()) {
            if (rhs_name == field->name()) {
                found_field = field;
                break;
            }
        }
        return found_field;
    }
}

//
// Public interface implementation:
//

namespace pdm::typer {

    bool type_script(types::Manager* types_mgr, ast::Script* script) {
        types::TyperVisitor typer_visitor {types_mgr, script};
        return typer_visitor.visit(script);
    }

    bool type_package(types::Manager* manager, ast::Package* package) {
        // assert(0 && "NotImplemented: typer::type_package.");
        std::cout << "NotImplemented: typer::type_package" << std::endl;
        return false;
    }

}
