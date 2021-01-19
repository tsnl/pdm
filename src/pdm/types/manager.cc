#include "manager.hh"

#include <iostream>

#include "solving.hh"

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
            for (TypeVar const& tv: m_all_monotype_tvs) {
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

    TypeVar* Manager::new_unknown_tv(std::string&& name, ast::Node* opt_client_ast_node) {
        m_all_monotype_tvs.emplace_back(std::move(name), opt_client_ast_node);
        return &m_all_monotype_tvs.back();
    }
    TypeVar* Manager::new_proxy_tv(std::string&& name, ast::Node* opt_client_ast_node) {
        m_all_proxy_tvs.emplace_back(std::move(name), opt_client_ast_node);
        return &m_all_proxy_tvs.back();
    }
    ClassVar* Manager::new_unknown_cv(std::string&& name, ast::Node* opt_client_ast_node) {
        m_all_unknown_cvs.emplace_back(std::move(name), opt_client_ast_node);
        return &m_all_unknown_cvs.back();
    }
    TemplateVar_RetValue* Manager::new_value_template_var(std::string&& name, ast::Node* opt_client_ast_node) {
        m_all_value_template_vars.emplace_back(std::move(name), opt_client_ast_node);
        return &m_all_value_template_vars.back();
    }
    TemplateVar_RetType* Manager::new_type_template_var(std::string&& name, ast::Node* opt_client_ast_node) {
        m_all_type_template_vars.emplace_back(std::move(name), opt_client_ast_node);
        return &m_all_type_template_vars.back();
    }
    TemplateVar_ClassType* Manager::new_class_template_var(std::string&& name, ast::Node* opt_client_ast_node) {
        m_all_class_template_vars.emplace_back(std::move(name), opt_client_ast_node);
        return &m_all_class_template_vars.back();
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
}