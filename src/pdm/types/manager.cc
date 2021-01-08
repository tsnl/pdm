#include "manager.hh"

#include <iostream>

namespace pdm::types {

    Manager::Manager(Compiler* opt_compiler_ptr)
    :   m_opt_compiler_ptr(opt_compiler_ptr),
        m_void_tv("BuiltinType:Void", VoidType::get(), nullptr, TypeVarSolnBill::Fixed),
        m_string_tv("BuiltinType:String", StringType::get(), nullptr, TypeVarSolnBill::Fixed),
        m_i8_tv("BuiltinType:I8", IntType::get_i8(), nullptr, TypeVarSolnBill::Fixed),
        m_i16_tv("BuiltinType:I16", IntType::get_i16(), nullptr, TypeVarSolnBill::Fixed),
        m_i32_tv("BuiltinType:I32", IntType::get_i32(), nullptr, TypeVarSolnBill::Fixed),
        m_i64_tv("BuiltinType:I64", IntType::get_i64(), nullptr, TypeVarSolnBill::Fixed),
        m_i128_tv("BuiltinType:I128", IntType::get_i128(), nullptr, TypeVarSolnBill::Fixed),
        m_u1_tv("BuiltinType:U1", IntType::get_u1(), nullptr, TypeVarSolnBill::Fixed),
        m_u8_tv("BuiltinType:U8", IntType::get_u8(), nullptr, TypeVarSolnBill::Fixed),
        m_u16_tv("BuiltinType:U16", IntType::get_u16(), nullptr, TypeVarSolnBill::Fixed),
        m_u32_tv("BuiltinType:U32", IntType::get_u32(), nullptr, TypeVarSolnBill::Fixed),
        m_u64_tv("BuiltinType:U64", IntType::get_u64(), nullptr, TypeVarSolnBill::Fixed),
        m_u128_tv("BuiltinType:U128", IntType::get_u128(), nullptr, TypeVarSolnBill::Fixed),
        m_f16_tv("BuiltinType:F16", FloatType::get_f16(), nullptr, TypeVarSolnBill::Fixed),
        m_f32_tv("BuiltinType:F32", FloatType::get_f32(), nullptr, TypeVarSolnBill::Fixed),
        m_f64_tv("BuiltinType:F64", FloatType::get_f64(), nullptr, TypeVarSolnBill::Fixed) 
    {}

    void Manager::print(printer::Printer& p, std::string const& title) const {
        p.print_cstr("-- Type Manager Dump: ");
        p.print_str(title);
        p.print_newline_indent();
        {
            // print all vars:
            for (TypeVar const& tv: m_all_tvs) {
                tv.print(p);
            }
            for (ClassVar const& cv: m_all_cvs) {
                cv.print(p);
            }
            for (ValueTemplateVar const& vtv: m_all_value_template_vars) {
                vtv.print(p);
            }
            for (TypeTemplateVar const& ttv: m_all_type_template_vars) {
                ttv.print(p);
            }
            for (ClassTemplateVar const& ctv: m_all_class_template_vars) {
                ctv.print(p);
            }
            
            // todo: print all 'relations' with pointers to referenced TVs.
        }
        p.print_newline_deindent();
    }

    TypeVar* Manager::new_fixed_tv(std::string&& name, Type* soln, ast::Node* opt_client_ast_node) {
        m_all_tvs.emplace_back(std::move(name), soln, opt_client_ast_node, TypeVarSolnBill::Fixed);
        return &m_all_tvs.back();
    }
    TypeVar* Manager::new_tv(std::string&& name, ast::Node* opt_client_ast_node) {
        m_all_tvs.emplace_back(std::move(name), nullptr, opt_client_ast_node, TypeVarSolnBill::Monotype);
        return &m_all_tvs.back();
    }
    TypeVar* Manager::new_proxy_tv(std::string&& name, ast::Node* opt_client_ast_node) {
        m_all_tvs.emplace_back(std::move(name), nullptr, opt_client_ast_node, TypeVarSolnBill::ProxyForMany);
        return &m_all_tvs.back();
    }
    ClassVar* Manager::new_cv(std::string&& name, ast::Node* opt_client_ast_node) {
        m_all_cvs.emplace_back(std::move(name), opt_client_ast_node);
        return &m_all_cvs.back();
    }
    ValueTemplateVar* Manager::new_value_template_var(std::string&& name, ast::Node* opt_client_ast_node) {
        m_all_value_template_vars.emplace_back(std::move(name), opt_client_ast_node);
        return &m_all_value_template_vars.back();
    }
    TypeTemplateVar* Manager::new_type_template_var(std::string&& name, ast::Node* opt_client_ast_node) {
        m_all_type_template_vars.emplace_back(std::move(name), opt_client_ast_node);
        return &m_all_type_template_vars.back();
    }
    ClassTemplateVar* Manager::new_class_template_var(std::string&& name, ast::Node* opt_client_ast_node) {
        m_all_class_template_vars.emplace_back(std::move(name), opt_client_ast_node);
        return &m_all_class_template_vars.back();
    }

    AssumeOpResult Manager::assume(Relation* relation) {
        m_all_relations.push_back(relation);
        // todo: apply the relation to argument variables in terms of component constraints.
        return AssumeOpResult::Applied;
    }
    TestOpResult Manager::test(Relation* relation) {
        std::cout << "NotImplemented: typer::Manager::test" << std::endl;
        // todo: test if the relation is true given argument variables using 'test_constraint'
        return TestOpResult::ErrorOccurred;
    }
}