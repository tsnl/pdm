#include "manager.hh"

#include <iostream>
#include <string>

#include "solve_result.hh"
#include "relation.hh"
#include "kdvs.hh"

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
    {
        // adding references to builtin types to the 'all' set:
        size_t builtin_tv_count = 16;
        size_t reserved_tv_count = 128 - builtin_tv_count;
        m_all_var_refs.reserve(builtin_tv_count + reserved_tv_count);
        {
            m_all_var_refs.push_back(get_void_tv());
            m_all_var_refs.push_back(get_string_tv());

            m_all_var_refs.push_back(get_i8_tv());
            m_all_var_refs.push_back(get_i16_tv());
            m_all_var_refs.push_back(get_i32_tv());
            m_all_var_refs.push_back(get_i64_tv());
            m_all_var_refs.push_back(get_i128_tv());

            m_all_var_refs.push_back(get_u1_tv());
            m_all_var_refs.push_back(get_u16_tv());
            m_all_var_refs.push_back(get_u32_tv());
            m_all_var_refs.push_back(get_u64_tv());
            m_all_var_refs.push_back(get_u128_tv());

            m_all_var_refs.push_back(get_f16_tv());
            m_all_var_refs.push_back(get_f32_tv());
            m_all_var_refs.push_back(get_f64_tv());
        }
    }

    void Manager::print(printer::Printer& p, std::string const& title) const {
        p.print_c_str("-- Type Manager Dump: ");
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
            m_float_cv.print(p);

            // holes:
            for (TypeVar const& tv: m_all_unknown_monotype_tvs) {
                tv.print(p);
            }
            for (ClassVar const& cv: m_all_unknown_cvs) {
                cv.print(p);
            }

            // todo: print all Relations with pointers to referenced TVs.
        }
        p.print_newline_exdent();
    }

    TypeVar* Manager::new_unknown_type_var(std::string&& name, ast::Node* opt_client_ast_node) {
        m_all_unknown_monotype_tvs.emplace_back(std::move(name), opt_client_ast_node);
        auto ref = &m_all_unknown_monotype_tvs.back();
        m_all_var_refs.push_back(ref);
        return ref;
    }
    ClassVar* Manager::new_unknown_class_var(std::string&& name, ast::Node* opt_client_ast_node) {
        m_all_unknown_cvs.emplace_back(std::move(name), opt_client_ast_node);
        auto ref = &m_all_unknown_cvs.back();
        m_all_var_refs.push_back(ref);
        return ref;
    }

    SolveResult Manager::assume_relation_holds(Relation* relation) {
        m_all_relations.push_back(relation);
        relation->on_assume(this);
        return SolveResult::UpdatedOrFresh;
    }
    TestOpResult Manager::test(Relation* relation) {
        std::cout << "NotImplemented: typer::Manager::test" << std::endl;
        // todo: test if the relation is true given argument variables using 'test_invariant'
        return TestOpResult::ErrorOccurred;
    }

    bool Manager::typecheck() {

        // todo: use a deferred error reporting system, compare failed vars against Relations
        //       and report failed Relations.
        //       for now, just printing errors per-var-- easier to debug.

        // Running solver iteratively until fixed or a max iteration count is exceeded:
        auto last_iter_solve_res = SolveResult::CompilerError;
        {
            bool debug_print_on_each_iter = false;
            printer::Printer debug_printer{std::cerr};
            bool fixed = false;
            size_t const max_iter_count = 8 * 1024;
            size_t iter_count = 0;
            while (!fixed && iter_count < max_iter_count) {
                // dumping typer for debug:
                {
                    if (debug_print_on_each_iter) {
                        print(debug_printer, "Iter " + std::to_string(iter_count));
                    }
                }

                // fixing the size of all vars considered:
                size_t system_size = m_all_var_refs.size();

                // ... run an sp2 iter for each and every var...
                auto all_vars_sp2res = SolveResult::NoChange;
                for (size_t index = 0; index < system_size; index++) {
                    Var* var = m_all_var_refs[index];
                    SolveResult var_sp2res = var->solve_iter();
                    all_vars_sp2res = result_and(all_vars_sp2res, var_sp2res);
                }

                // ... and thereby determine fixed-ness
                fixed = (
                    (all_vars_sp2res == SolveResult::CompilerError) ||
                    (all_vars_sp2res == SolveResult::TypingError) ||
                    (all_vars_sp2res == SolveResult::NoChange)
                );
                last_iter_solve_res = all_vars_sp2res;
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
        }

        // checking all nodes:
        {
            if (result_is_error(last_iter_solve_res)) {
                feedback::Severity common_severity = feedback::Severity::Error;
                std::string common_headline;
                if (last_iter_solve_res == SolveResult::TypingError) {
                    common_severity = common_severity;
                    common_headline = "Inconsistent type relations detected";
                } else {
                    common_severity = feedback::Severity::CompilerError;
                    common_headline = "Bug-induced typer error";
                }

                for (Var* var: m_all_var_refs) {
                    SolveResult var_sp2res = var->solve_iter();

                    // only filtering the most severe errors:
                    if (var_sp2res == last_iter_solve_res) {
                        std::string headline = common_headline;
                        std::string desc;
                        std::vector<feedback::Note*> notes;
                        if (var->opt_client_ast_node() != nullptr) {
                            std::string desc0 = "see typing variable '" + var->name() + "' here...";
                            notes.push_back(new feedback::AstNodeNote(
                                std::move(desc0),
                                var->opt_client_ast_node()
                            ));
                        }
                        feedback::post(new feedback::Letter(
                            common_severity,
                            std::move(headline),
                            std::move(desc),
                            std::move(notes)
                        ));
                    }
                }
                return false;
            }
        }

        // from here, we can ensure invariants are stable and correct enough to propagate.

        // Checking stabilized kinds:
        {
            // todo: use a deferred error reporting system, compare failed vars against Relations
            //       and report failed Relations.
            //       for now, just printing errors per-var-- easier to debug.

            bool finished_ok = true;
            for (Var* var: m_all_var_refs) {
                Type* type_soln = var->get_type_soln();
                if (!type_soln) {
                    finished_ok = false;
                }
            }
            if (!finished_ok) {
                std::string headline = "Typing Error";
                std::string desc = "Var::finish did not return true for all Vars";
                std::vector<feedback::Note*> notes;
                feedback::post(new feedback::Letter(
                    feedback::Severity::FatalError,
                    std::move(headline),
                    std::move(desc),
                    std::move(notes)
                ));

                return false;
            }
        }

        // even if stable, could still be errors.
        // todo: extract a solution, return false if fails
        // assert(last_iter_sp2res == SolveResult::NoChange);
        // {
        // }

        return true;
    }
}
