#include "manager.hh"

#include <iostream>

#include "solving.hh"

#include "pdm/core/config.hh"

#include "pdm/feedback/feedback.hh"
#include "pdm/feedback/severity.hh"
#include "pdm/feedback/letter.hh"
#include "pdm/feedback/note.hh"

namespace pdm::types {

    Manager::Manager(Compiler* opt_compiler_ptr)
    :   m_opt_compiler_ptr(opt_compiler_ptr),
        m_void_tv(), m_string_tv(),
        m_i8_tv(), m_i16_tv(), m_i32_tv(), m_i64_tv(), m_i128_tv(),
        m_u1_tv(), m_u8_tv(), m_u16_tv(), m_u32_tv(), m_u64_tv(), m_u128_tv(),
        m_f16_tv(), m_f32_tv(), m_f64_tv() 
    {}

    void Manager::print(printer::Printer& p, std::string const& title) const {
        p.print_cstr("-- Type Manager Dump: ");
        p.print_str(title);
        p.print_newline_indent();
        {
            // fixed types:
            m_void_tv.print(p);
            m_string_tv.print(p);
            m_i8_tv.print(p);
            m_i16_tv.print(p);
            m_i32_tv.print(p);
            m_i64_tv.print(p);
            m_i128_tv.print(p);
            m_u1_tv.print(p);
            m_u8_tv.print(p);
            m_u16_tv.print(p);
            m_u32_tv.print(p);
            m_u64_tv.print(p);
            m_u128_tv.print(p);
            m_f16_tv.print(p);
            m_f32_tv.print(p);
            m_f64_tv.print(p);

            // fixed classes:
            m_signed_int_cv.print(p);
            m_unsigned_int_cv.print(p);
            m_int_cv.print(p);
            m_float_cv.print(p);
            m_number_cv.print(p);

            // holes:
            for (TypeVar const& tv: m_all_unknown_monotype_tvs) {
                tv.print(p);
            }
            for (ClassVar const& cv: m_all_unknown_cvs) {
                cv.print(p);
            }
            for (TemplateVar_RetValue const& vtv: m_all_value_template_vars) {
                vtv.print(p);
            }
            for (TemplateVar_RetType const& ttv: m_all_type_template_vars) {
                ttv.print(p);
            }
            for (TemplateVar_ClassType const& ctv: m_all_class_template_vars) {
                ctv.print(p);
            }
            
            // todo: print all Relations with pointers to referenced TVs.
        }
        p.print_newline_deindent();
    }

    TypeVar* Manager::new_unknown_monotype_tv(std::string&& name, ast::Node* opt_client_ast_node) {
        m_all_unknown_monotype_tvs.emplace_back(std::move(name), opt_client_ast_node);
        auto ref = &m_all_unknown_monotype_tvs.back();
        m_all_var_refs.push_back(ref);
        return ref;
    }
    TypeVar* Manager::new_unknown_proxy_tv(std::string&& name, ast::Node* opt_client_ast_node) {
        m_all_unknown_proxy_tvs.emplace_back(std::move(name), opt_client_ast_node);
        auto ref = &m_all_unknown_proxy_tvs.back();
        m_all_var_refs.push_back(ref);
        return ref;
    }
    ClassVar* Manager::new_unknown_cv(std::string&& name, ast::Node* opt_client_ast_node) {
        m_all_unknown_cvs.emplace_back(std::move(name), opt_client_ast_node);
        auto ref = &m_all_unknown_cvs.back();
        m_all_var_refs.push_back(ref);
        return ref;
    }
    TemplateVar_RetValue* Manager::new_value_template_var(std::string&& name, ast::Node* opt_client_ast_node) {
        m_all_value_template_vars.emplace_back(std::move(name), opt_client_ast_node);
        auto ref = &m_all_value_template_vars.back();
        m_all_var_refs.push_back(ref);
        return ref;
    }
    TemplateVar_RetType* Manager::new_type_template_var(std::string&& name, ast::Node* opt_client_ast_node) {
        m_all_type_template_vars.emplace_back(std::move(name), opt_client_ast_node);
        auto ref = &m_all_type_template_vars.back();
        m_all_var_refs.push_back(ref);
        return ref;
    }
    TemplateVar_ClassType* Manager::new_class_template_var(std::string&& name, ast::Node* opt_client_ast_node) {
        m_all_class_template_vars.emplace_back(std::move(name), opt_client_ast_node);
        auto ref = &m_all_class_template_vars.back();
        m_all_var_refs.push_back(ref);
        return ref;
    }

    SolvePhase2_Result Manager::assume_relation_holds(Relation* relation) {
        m_all_relations.push_back(relation);
        // todo: apply the relation to argument variables in terms of component invariants.
        return SolvePhase2_Result::UpdatedOrFresh;
    }
    TestOpResult Manager::test(Relation* relation) {
        std::cout << "NotImplemented: typer::Manager::test" << std::endl;
        // todo: test if the relation is true given argument variables using 'test_invariant'
        return TestOpResult::ErrorOccurred;
    }

    bool Manager::typecheck() {
    //     auto const var_in_slice = [&all_vars] (Var* var, size_t min_index, size_t end_index) {
    //         // bounds checks:
    //         assert(
    //             (min_index < all_vars.size()) &&
    //             (end_index <= all_vars.size()) &&
    //             (min_index <= end_index)
    //         );

    //         // scanning:
    //         for (size_t index = min_index; index < end_index; index++) {
    //             if (all_vars[index] == var) {
    //                 return true;
    //             }
    //         }

    //         // not found:
    //         return false;
    //     }

        // Solve Phase 1: runs only once, either passes or fails:
        // iteratively call var solvers...
        bool sp1_pass = true;

        // todo: use a deferred error reporting system, compare failed vars against Relations
        //       and report failed Relations.
        // for now, just printing errors per-var-- easier to debug.

        for (Var* var: m_all_var_refs) {
            // SP2:
            SolvePhase1_Result sp1_res = var->solve_phase1();

            // Parsing status:
            switch (sp1_res) {
                case SolvePhase1_Result::InsufficientInfo:
                {
                    // insufficient info is ok! wait for SP2
                    sp1_pass = true;
                }
                case SolvePhase1_Result::Error_MixedKind:
                {
                    sp1_pass = false;
                    std::string headline = (
                        "Mixed type-kinds in type/class variable."
                    );
                    std::string more = "";
                    std::vector<feedback::Note*> notes;
                    if (var->opt_client_ast_node() != nullptr) {
                        std::string desc0 = "see syntax element here...";
                        notes.push_back(new feedback::AstNodeNote(
                            std::move(desc0), var->opt_client_ast_node()
                        ));
                    }
                    feedback::post(new feedback::Letter(
                        feedback::Severity::Error,
                        std::move(headline),
                        std::move(more),
                        std::move(notes)
                    ));
                    break;
                }
                case SolvePhase1_Result::Ok:
                {
                    break;
                }
            }
        }

        if (!sp1_pass) {
            std::string headline = "Errors detected in typing setup: terminating.";
            std::string desc = "";
            std::vector<feedback::Note*> notes;
            feedback::post(new feedback::Letter(
                feedback::Severity::FatalError,
                std::move(headline),
                std::move(desc),
                std::move(notes)
            ));

            return false;
        }

        // from this point, we can assume that all Vars have a KDVS

        // until fixed...
        bool fixed = false;
        auto last_iter_sp2res = SolvePhase2_Result::CompilerError;
        size_t const max_iter_count = 8 * 1024;
        size_t iter_count = 0;
        while (!fixed && iter_count < max_iter_count) {
            size_t system_size = m_all_var_refs.size();
            
            // ... run an sp2 iter for each and every var...
            auto all_vars_sp2res = SolvePhase2_Result::NoChange;
            for (size_t index = 0; index < system_size; index++) {
                Var* var = m_all_var_refs[index];
                SolvePhase2_Result var_sp2res = var->solve_phase2_iter();
                all_vars_sp2res = sp2res_and(all_vars_sp2res, var_sp2res);
            }

            // ... and thereby determine fixed-ness
            fixed = (
                (all_vars_sp2res == SolvePhase2_Result::CompilerError) ||
                (all_vars_sp2res == SolvePhase2_Result::TypingError) ||
                (all_vars_sp2res == SolvePhase2_Result::NoChange)
            );
            last_iter_sp2res = all_vars_sp2res;
            iter_count++;
        }
        if (iter_count >= max_iter_count) {
            // Compiler error
            feedback::post(new feedback::Letter(
                feedback::Severity::CompilerError,
                "Type solver iterations exceeded safety limit",
                "Your type queries are either too complex, or (more likely) "
                "there is a bug in the type solver."
            ));
            return false;
        }

        if (!sp2res_is_error(last_iter_sp2res)) {
            return true;
        } else {
            for (Var* var: m_all_var_refs) {
                SolvePhase2_Result var_sp2res = var->solve_phase2_iter();
                
                // only filtering the most severe errors:
                if (var_sp2res == last_iter_sp2res) {
                    std::string headline;
                    std::string desc;
                    std::vector<feedback::Note*> notes; 
                    if (var->opt_client_ast_node() != nullptr) {
                        std::string desc0 = "see type here...";
                        notes.push_back(new feedback::AstNodeNote(
                            std::move(desc0),
                            var->opt_client_ast_node()
                        ));
                    }
                    feedback::post(new feedback::Letter(
                        feedback::Severity::Error,
                        std::move(headline),
                        std::move(desc),
                        std::move(notes)
                    ));
                }
            }
            return false;
        }
    }

}
