#include "typer.hh"

#include <iostream>
#include <iomanip>

#include "pdm/source/loc.hh"

#include "pdm/feedback/feedback.hh"
#include "pdm/feedback/severity.hh"
#include "pdm/feedback/letter.hh"
#include "pdm/feedback/note.hh"

#include "pdm/scoper/defn.hh"

#include "pdm/ast/script/script.hh"
#include "pdm/ast/setspec/struct.hh"

#include "pdm/types/manager.hh"
#include "pdm/types/var.hh"
#include "pdm/types/relation.hh"
#include "pdm/types/solving.hh"

//
// TypeVisitor helps apply typing rules for each AST node (without forgetting any).
//

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
        bool post_feedback_from_first_sp2res(SolvePhase2_Result sp2res, std::string&& source_desc, source::Loc loc);
      
      protected:
        // script:
        virtual bool on_visit__script(ast::Script* script, VisitOrder visit_order) override;

        // statements:
        virtual bool on_visit__mod_stmt(ast::ModStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__mod_typeclass_stmt(ast::ModTypeclassStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__mod_type_stmt(ast::ModTypeStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__mod_enum_stmt(ast::ModEnumStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__mod_val_stmt(ast::ModValStmt* node, VisitOrder visit_order) override;
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
        virtual bool on_visit__id_typespec(ast::IdSetSpec* node, VisitOrder visit_order) override;
        virtual bool on_visit__fn_typespec(ast::FnTypeSpec* node, VisitOrder visit_order) override;
        virtual bool on_visit__tcall_typespec(ast::TCallTypeSpec* node, VisitOrder visit_order) override;
        virtual bool on_visit__tuple_typespec(ast::TupleTypeSpec* node, VisitOrder visit_order) override;
        virtual bool on_visit__dot_name_typespec_mod_prefix(ast::DotNameTypeSpec_ModPrefix* node, VisitOrder visit_order) override;
        virtual bool on_visit__struct_typespec(ast::StructTypeSpec* node, VisitOrder visit_order) override;
        virtual bool on_visit__paren_typespec(ast::ParenTypeSpec* node, VisitOrder visit_order) override;
        // virtual bool on_visit__dot_name_typespec_type_prefix(ast::DotNameTypeSpec_TypePrefix* node, VisitOrder visit_order) override;
        
        // args:
        virtual bool on_visit__targ(ast::TArg* node, VisitOrder visit_order) override;
        virtual bool on_visit__varg(ast::VArg* node, VisitOrder visit_order) override;
        
        // non-syntactic:
        virtual bool on_visit__builtin_type_stmt(ast::BuiltinStmt* node, VisitOrder visit_order) override;

      // helpers:
      protected:
        bool help_posttype_const_or_val_or_var_stmt(ast::Node* node, ast::LPattern* lhs, ast::Exp* rhs);
    };

    //
    // TypeVisitor Definitions:
    //

    TyperVisitor::TyperVisitor(Manager* types_mgr, ast::Script* script)
    :   m_types_mgr(types_mgr),
        m_script(script)
    {}

    bool TyperVisitor::post_feedback_from_first_sp2res(SolvePhase2_Result sp2res, std::string&& source_desc, source::Loc loc) {
        if (sp2res_is_error(sp2res)) {
            std::string headline = "A typing relation could not be applied";
            std::string more = (
                (sp2res == SolvePhase2_Result::CompilerError) ?
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
    bool TyperVisitor::on_visit__script(ast::Script* script, VisitOrder visit_order) {
        // todo: implement this typer.
        return true;
    }

    // statements:
    bool TyperVisitor::on_visit__mod_stmt(ast::ModStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            TypeVar* module_tv = node->x_module_tv();
        } else {
            // todo: do nothing? double-check
        }
        return true;
    }
    bool TyperVisitor::on_visit__mod_typeclass_stmt(ast::ModTypeclassStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            
        }
        // todo: implement this typer.
        // - if template, set up formal args, use return for following steps.
        // - otherwise,
        //   - require is_kind(typeclass)
        //   - require eqconstraint (fixed) with those provided.
        // leave typeclasses, templates for last.
        return true;
    }
    bool TyperVisitor::on_visit__mod_type_stmt(ast::ModTypeStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            if (!node->lhs_tpatterns().empty()) {
                
            }
        }
        return true;
    }
    bool TyperVisitor::on_visit__mod_enum_stmt(ast::ModEnumStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            
        } else {

        }
        return true;
    }
    bool TyperVisitor::on_visit__mod_val_stmt(ast::ModValStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Post) {
            TypeVar* mod_val_tv = nullptr;
            if (node->tpatterns().empty()) {
                mod_val_tv = dynamic_cast<TypeVar*>(node->x_defn_var());
            } else {
                assert(0 && "NotImplemented: mod_val statements with template args.");
            }
            
            TypeVar* rhs_tv = nullptr;
            if (node->rhs_kind() == ast::ModValStmt::RhsKind::Internal) {
                rhs_tv = node->opt_rhs_exp()->x_typeof_tv();
            } else if (node->rhs_kind() == ast::ModValStmt::RhsKind::External) {
                assert(0 && "NotImplemented: mod_val statements with external RHS");
                return false;
            }
            assert(rhs_tv != nullptr);
            
            // rhs_tv :< mod_val_tv
            SolvePhase2_Result res = m_types_mgr->assume_relation_holds(new SubtypeOfRelation(
                node,
                rhs_tv,
                mod_val_tv
            ));

            std::string source_desc = "see value field of module here...";
            return post_feedback_from_first_sp2res(res, std::move(source_desc), node->loc());
        }
        return true;
    }
    bool TyperVisitor::on_visit__const_stmt(ast::ConstStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Post) {
            return help_posttype_const_or_val_or_var_stmt(node, node->lhs_lpattern(), node->rhs_exp());
        }
        return true;
    }
    bool TyperVisitor::on_visit__val_stmt(ast::ValStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Post) {
            return help_posttype_const_or_val_or_var_stmt(node, node->lhs_lpattern(), node->rhs_exp());
        }
        return true;
    }
    bool TyperVisitor::on_visit__var_stmt(ast::VarStmt* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Post) {
            return help_posttype_const_or_val_or_var_stmt(node, node->lhs_lpattern(), node->rhs_exp());
        }
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
            TypeVar* int_tv = m_types_mgr->get_u32_tv();
            node->x_typeof_tv(int_tv);
        } else {
            assert(visit_order == VisitOrder::Post);
            TypeVar* int_tv = node->x_typeof_tv();
            SolvePhase2_Result sp2_result = m_types_mgr->assume_relation_holds(new ClassOfRelation(
                node,
                m_types_mgr->get_unsigned_int_cv(), int_tv
            ));
            
            std::string source_desc = "see integer expression here...";
            return post_feedback_from_first_sp2res(sp2_result, std::move(source_desc), node->loc());
        }
        return true;
    }
    bool TyperVisitor::on_visit__float_exp(ast::FloatExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            // todo: replace with fresh TV
            TypeVar* float_tv = m_types_mgr->get_f32_tv();
            node->x_typeof_tv(float_tv);
        } else {
            assert(visit_order == VisitOrder::Post);
            TypeVar* float_tv = node->x_typeof_tv();
            SolvePhase2_Result sp2_result = m_types_mgr->assume_relation_holds(new ClassOfRelation(
                node,
                m_types_mgr->get_float_cv(), float_tv
            ));

            std::string source_desc = "see float expression here...";
            return post_feedback_from_first_sp2res(sp2_result, std::move(source_desc), node->loc());
        }
        return true;
    }
    bool TyperVisitor::on_visit__string_exp(ast::StringExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            TypeVar* string_tv = m_types_mgr->get_string_tv();
            node->x_typeof_tv(string_tv);
        } else {
            TypeVar* typeof_string_tv = node->x_typeof_tv();
            SolvePhase2_Result sp2_result = m_types_mgr->assume_relation_holds(new TypeEqualsRelation(
                node,
                m_types_mgr->get_string_tv(), typeof_string_tv
            ));

            std::string source_desc = "see string expression here...";
            return post_feedback_from_first_sp2res(sp2_result, std::move(source_desc), node->loc());
        }
        return true;
    }
    bool TyperVisitor::on_visit__id_exp(ast::IdExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            TypeVar* id_tv = dynamic_cast<TypeVar*>(node->x_defn()->var());
            assert(id_tv != nullptr && "Scoper failed!");
            node->x_typeof_tv(id_tv);
        }
        return true;
    }
    bool TyperVisitor::on_visit__paren_exp(ast::ParenExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "ParenExp";
            TypeVar* paren_tv = m_types_mgr->new_unknown_tv(std::move(tv_name), node);
            node->x_typeof_tv(paren_tv);
        } else {
            TypeVar* paren_tv = node->x_typeof_tv();
            TypeVar* nested_tv = node->nested_exp()->x_typeof_tv();
            SolvePhase2_Result sp2res = m_types_mgr->assume_relation_holds(new TypeEqualsRelation(node, paren_tv, nested_tv));
            
            std::string source_desc = "see paren expression here...";
            return post_feedback_from_first_sp2res(sp2res, std::move(source_desc), node->loc());
        }
        return true;
    }
    bool TyperVisitor::on_visit__tuple_exp(ast::TupleExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "TupleExp(" + std::to_string(node->items().size()) + ")";
            TypeVar* tuple_tv = m_types_mgr->new_unknown_tv(std::move(tv_name), node);
            node->x_typeof_tv(tuple_tv);
        } else {
            // todo: set tuple field requirements here by equating to a TupleTV
        }
        return true;
    }
    bool TyperVisitor::on_visit__array_exp(ast::ArrayExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "ArrayExp(" + std::to_string(node->items().size()) + ")";
            TypeVar* array_tv = m_types_mgr->new_unknown_tv(std::move(tv_name), node);
            node->x_typeof_tv(array_tv);
        } else {
            // todo: set array exp requirements here by equating to an ArrayTV
        }
        return true;
    }
    bool TyperVisitor::on_visit__struct_exp(ast::StructExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "StructExp(" + std::to_string(node->fields().size()) + ")";
            TypeVar* struct_exp_tv = m_types_mgr->new_unknown_tv(std::move(tv_name), node);
            node->x_typeof_tv(struct_exp_tv);
        } else {
            // todo: set struct exp requirements here by equating to a StructTV
        }
        return true;
    }
    bool TyperVisitor::on_visit__type_query_exp(ast::TypeQueryExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "TypeQueryExp";
            TypeVar* type_query_exp_tv = m_types_mgr->new_unknown_tv(std::move(tv_name), node);
            node->x_typeof_tv(type_query_exp_tv);
        } else {
            // todo: implement this typer.
        }
        return true;
    }
    bool TyperVisitor::on_visit__chain_exp(ast::ChainExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "ChainExp";
            TypeVar* chain_exp_tv = m_types_mgr->new_unknown_tv(std::move(tv_name), node);
            node->x_typeof_tv(chain_exp_tv);
        } else {

        }
        return true;
    }
    bool TyperVisitor::on_visit__lambda_exp(ast::LambdaExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "LambdaExp";
            TypeVar* lambda_exp_tv = m_types_mgr->new_unknown_tv(std::move(tv_name), node);
            node->x_typeof_tv(lambda_exp_tv);
        } else {
            // todo: implement all the function/vcall typing stuff here!
        }
        return true;
    }
    bool TyperVisitor::on_visit__if_exp(ast::IfExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "IfExp";
            TypeVar* if_exp_tv = m_types_mgr->new_unknown_tv(std::move(tv_name), node);
            node->x_typeof_tv(if_exp_tv);
        } else {

        }
        return true;
    }
    bool TyperVisitor::on_visit__dot_index_exp(ast::DotIndexExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "DotIndexExp";
            TypeVar* dot_index_exp_tv = m_types_mgr->new_unknown_tv(std::move(tv_name), node);
            node->x_typeof_tv(dot_index_exp_tv);
        } else {

        }
        return true;
    }
    bool TyperVisitor::on_visit__dot_name_exp(ast::DotNameExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "DotNameExp";
            TypeVar* dot_name_exp_tv = m_types_mgr->new_unknown_tv(std::move(tv_name), node);
            node->x_typeof_tv(dot_name_exp_tv);
        } else {

        }
        return true;
    }
    bool TyperVisitor::on_visit__module_dot_exp(ast::ModuleDotExp* node, VisitOrder visit_order) {
        assert(0 && "NotImplemented: TypeVisitor::on_visit__module_dot_exp");
        
        if (visit_order == VisitOrder::Pre) {
            
        } else {
            // todo
        }
        return true;
    }
    bool TyperVisitor::on_visit__unary_exp(ast::UnaryExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "UnaryExp";
            TypeVar* unary_exp_tv = m_types_mgr->new_unknown_tv(std::move(tv_name), node);
            node->x_typeof_tv(unary_exp_tv);
        } else {

        }
        return true;
    }
    bool TyperVisitor::on_visit__binary_exp(ast::BinaryExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "BinaryExp";
            TypeVar* binary_exp_tv = m_types_mgr->new_unknown_tv(std::move(tv_name), node);
            node->x_typeof_tv(binary_exp_tv);
        } else {

        }
        return true;
    }
    bool TyperVisitor::on_visit__vcall_exp(ast::VCallExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "VCallExp";
            TypeVar* vcall_exp_tv = m_types_mgr->new_unknown_tv(std::move(tv_name), node);
            node->x_typeof_tv(vcall_exp_tv);
        } else {

        }
        return true;
    }
    bool TyperVisitor::on_visit__tcall_exp(ast::TCallExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string tv_name = "TCallExp";
            TypeVar* tcall_exp_tv = m_types_mgr->new_unknown_tv(std::move(tv_name), node);
            node->x_typeof_tv(tcall_exp_tv);
        } else {

        }
        return true;
    }

    // patterns:
    bool TyperVisitor::on_visit__vpattern(ast::VPattern* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Post) {
            for (ast::VPattern::Field* field: node->fields()) {
                TypeVar* tv = field->x_defn_tv();
                
                Var* spectype_var = field->rhs_typespec()->x_spectype_var();
                TypeVar* spectype_tv = dynamic_cast<TypeVar*>(spectype_var);
                if (spectype_tv != nullptr) {
                    SolvePhase2_Result sp2res = m_types_mgr->assume_relation_holds(new TypeEqualsRelation(field, tv, spectype_tv));
                    
                    std::string source_desc = "see V-Pattern here...";
                    return post_feedback_from_first_sp2res(sp2res, std::move(source_desc), node->loc());
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
                }
            }
        }
        return true;
    }
    bool TyperVisitor::on_visit__tpattern(ast::TPattern* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Post) {
            for (ast::TPattern::Field* field: node->fields()) {
                Var* field_var = field->x_defn_var();
                auto field_tv = dynamic_cast<TypeVar*>(field_var);
                assert(field_tv != nullptr);

                Var* field_spec_var = field->rhs_typespec()->x_spectype_var();
                assert(field_spec_var != nullptr);

                if (field->kind() == ast::TPattern::FieldKind::Value) {
                    // [value Type]
                    auto field_spec_tv = dynamic_cast<TypeVar*>(field_spec_var);
                    if (field_spec_tv != nullptr && field_tv != nullptr) {
                        SolvePhase2_Result sp2res = m_types_mgr->assume_relation_holds(new TypeEqualsRelation(node, field_spec_tv, field_tv));
                        std::string source_desc = "In Value T-Pattern Arg here..";
                        return post_feedback_from_first_sp2res(sp2res, std::move(source_desc), node->loc());
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
                } else if (field->kind() == ast::TPattern::FieldKind::Type) {
                    // [Type Class]
                    auto field_spec_cv = dynamic_cast<ClassVar*>(field_spec_var);
                    auto proxy_field_tv = field_tv;
                    if (field_spec_cv != nullptr) {
                        SolvePhase2_Result sp2res = m_types_mgr->assume_relation_holds(new ClassOfRelation(node, field_spec_cv, field_tv));
                        std::string source_desc = "In Type T-Pattern Arg here..";
                        return post_feedback_from_first_sp2res(sp2res, std::move(source_desc), node->loc());
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
    bool TyperVisitor::on_visit__lpattern(ast::LPattern* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Post) {
            for (ast::LPattern::Field* field: node->fields()) {
                TypeVar* tv = field->x_defn_tv();
                if (field->opt_rhs_typespec()) {
                    TypeVar* rhs_tv = dynamic_cast<TypeVar*>(field->opt_rhs_typespec()->x_spectype_var());
                    if (rhs_tv != nullptr) {
                        SolvePhase2_Result sp2res = m_types_mgr->assume_relation_holds(new TypeEqualsRelation(node, tv, rhs_tv));
                        
                        std::string source_desc = "see L-Pattern here...";
                        return post_feedback_from_first_sp2res(sp2res, std::move(source_desc), node->loc());
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
    bool TyperVisitor::on_visit__id_typespec(ast::IdSetSpec* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            node->x_spectype_var(node->x_defn()->var());
        }
        return true;
    }
    bool TyperVisitor::on_visit__fn_typespec(ast::FnTypeSpec* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string name = "FnTypeSpec";
            node->x_spectype_var(m_types_mgr->new_unknown_tv(std::move(name), node));
        } else {
            assert(visit_order == VisitOrder::Post);
            // node->x_spectype_var(m_types_mgr->new_func_tv()) ...
            TypeVar* spectype_tv = dynamic_cast<TypeVar*>(node->x_spectype_var());
            
            std::vector<TypeVar*> args_tvs{node->lhs_vpattern()->fields().size()};
            for (size_t index = 0; index < args_tvs.size(); index++) {
                ast::VPattern::Field* vpattern_field = node->lhs_vpattern()->fields()[index];
                args_tvs[index] = vpattern_field->x_defn_tv();
            }

            TypeVar* ret_tv = m_types_mgr->get_void_tv();
            if (node->opt_ret_typespec() != nullptr) {
                Var* ret_spectype_var = node->opt_ret_typespec()->x_spectype_var();
                TypeVar* ret_spectype_tv = dynamic_cast<TypeVar*>(ret_spectype_var);
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
            
            SolvePhase2_Result sp2res = m_types_mgr->assume_relation_holds(new FormalVCallableRelation(
                node, spectype_tv, std::move(args_tvs), ret_tv
            ));
            
            // todo: post
        }
        return true;
    }
    bool TyperVisitor::on_visit__tcall_typespec(ast::TCallTypeSpec* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string name = "TCallSetSpec";
            
            // todo: we do not know if a class tcall or type tcall.
            //       should be able to tell from grammar, by implementing a separate 'ClassSpec'
            //       branch of rules.
            assert(0 && 
                "NotImplemented: TCallTypeSpec: need to implement separate ClassSpec branch in grammar "
                "to determine if TemplateVar_RetType or TemplateVar_RetClass is required."
            );

            Var* new_var = m_types_mgr->new_class_template_var(std::move(name), node);
            node->x_spectype_var();
        } else {
            assert(visit_order == VisitOrder::Post);
        }
        return true;
    }
    bool TyperVisitor::on_visit__tuple_typespec(ast::TupleTypeSpec* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string name = "Tuple";
            TypeVar* tuple_tv = m_types_mgr->new_unknown_tv(std::move(name), node);
            node->x_spectype_var(tuple_tv);
        } else {
            assert(visit_order == VisitOrder::Post);
            
            // getting the tuple_tv:
            auto tuple_tv = dynamic_cast<TypeVar*>(node->x_spectype_var());
            assert(tuple_tv != nullptr);

            // collecting a vector of field tvs:
            size_t num_fields = node->items().size();
            std::vector<TypeVar*> fields_tvs{num_fields};
            for (size_t field_index = 0; field_index < num_fields; field_index++) {
                ast::TypeSpec* field_type_spec = node->items()[field_index];
                assert(field_type_spec != nullptr);

                Var* field_item_var = field_type_spec->x_spectype_var();
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
            SolvePhase2_Result sp2res = m_types_mgr->assume_relation_holds(new TupleOfRelation(
                std::move(why),
                node,
                tuple_tv,
                std::move(fields_tvs)
            ));

            std::string source_desc = "See Tuple type specifier here...";
            return post_feedback_from_first_sp2res(sp2res, std::move(source_desc), node->loc());
        }
        return true;
    }
    bool TyperVisitor::on_visit__dot_name_typespec_mod_prefix(ast::DotNameTypeSpec_ModPrefix* node, VisitOrder visit_order) {
        assert(0 && "NotImplemented: TypeVisitor::on_visit__dot_name_typespec_mod_prefix");

        if (visit_order == VisitOrder::Pre) {
            // todo: lookup mod prefices
            // node->x_spectype_var(spectype_var);
        } else {
            assert(visit_order == VisitOrder::Post);
        }
        return true;
    }
    bool TyperVisitor::on_visit__struct_typespec(ast::StructTypeSpec* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string name = "StructTypeSpec";
            TypeVar* struct_tv = m_types_mgr->new_unknown_tv(std::move(name), node);
            node->x_spectype_var(struct_tv);
        } else {
            assert(visit_order == VisitOrder::Post);
            auto struct_tv = dynamic_cast<TypeVar*>(node->x_spectype_var());
            assert(struct_tv != nullptr);
            
            // collecting & checking fields_tvs:
            std::map<intern::String, TypeVar*> fields_tvs;
            bool fields_ok = true;
            for (ast::StructTypeSpec::Field* field: node->fields()) {
                Var* field_var = field->rhs_typespec()->x_spectype_var();
                assert(field_var != nullptr);

                // verifying the name is unique:
                auto found_it_by_same_name = fields_tvs.find(field->lhs_name());
                if (found_it_by_same_name != fields_tvs.end()) {
                    fields_ok = false;
                    std::string headline = "Name '" + std::string(field->lhs_name().content()) + "' repeated in struct type specifier";
                    std::string desc = "Each field in a struct must have a unique name.";
                    std::vector<feedback::Note*> notes{2}; {
                        std::string note_desc0 = "first definition here...";
                        source::Loc loc0 = found_it_by_same_name->second->opt_client_ast_node()->loc();
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

            // assuming a StructOf relation to bind struct_tv to fields:
            std::string name = "StructTypeSpec";
            SolvePhase2_Result sp2res = m_types_mgr->assume_relation_holds(new StructOfRelation(
                std::move(name), node,
                struct_tv, std::move(fields_tvs)
            ));
        }
        return true;
    }
    bool TyperVisitor::on_visit__paren_typespec(ast::ParenTypeSpec* node, VisitOrder visit_order) {
        assert(0 && 
            "NotImplemented: ParenSetSpec"
            "need to figure out if class or type var"
        );
        
        if (visit_order == VisitOrder::Pre) {
            std::string name = "ParenSetSpec";
            // todo: need to figure out if class or type var
        } else {
            assert(visit_order == VisitOrder::Post);
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
    bool TyperVisitor::on_visit__builtin_type_stmt(ast::BuiltinStmt* node, VisitOrder visit_order) {
        return true;
    }

    //
    // Helpers:
    //

    bool TyperVisitor::help_posttype_const_or_val_or_var_stmt(ast::Node* node, ast::LPattern* lpattern, ast::Exp* rhs_exp) {
        TypeVar* typeof_rhs_tv = rhs_exp->x_typeof_tv();
        if (lpattern->destructure()) {
            // todo: destructure as a tuple
            std::cout << "NotImplemented: tuple-lpattern destructuring" << std::endl;
        } else {
            assert(lpattern->fields().size() == 1);
            ast::LPattern::Field* field = lpattern->fields()[0];
            TypeVar* typeof_lhs_tv = field->x_defn_tv();
            
            // "let lhs = rhs" <=> rhs :< lhs
            SolvePhase2_Result assume_op_result1 = m_types_mgr->assume_relation_holds(new SubtypeOfRelation(node, typeof_rhs_tv, typeof_lhs_tv));
            
            // if typespec, tie!
            SolvePhase2_Result assume_op_result2 = SolvePhase2_Result::NoChange; {
                if (field->opt_rhs_typespec()) {
                    Var* typespec_var = field->opt_rhs_typespec()->x_spectype_var();
                    if (is_type_var_kind(typespec_var->var_kind())) {
                        // typeof_lhs_tv :: typeof_typespec_tv
                        assume_op_result2 = m_types_mgr->assume_relation_holds(new TypeEqualsRelation(
                            field,
                            typeof_lhs_tv,
                            dynamic_cast<TypeVar*>(typespec_var)
                        ));
                    } else {
                        // todo: post 'expected class, received type' error feedback
                        assume_op_result2 = SolvePhase2_Result::TypingError;
                    }
                }
            }

            std::string source_desc = "see const/val/var statement here...";
            post_feedback_from_first_sp2res(sp2res_and(assume_op_result1, assume_op_result2), std::move(source_desc), node->loc());
        }
        return true;
    }
}

//
// Public interface implementation:
//

namespace pdm::typer {

    bool type(types::Manager* types_mgr, ast::Script* script) {
        types::TyperVisitor typer_visitor {types_mgr, script};
        return typer_visitor.visit(script);
    }

}
