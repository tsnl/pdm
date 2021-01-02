#include "manager.hh"

namespace pdm::types {

    Manager::Manager()
    :   m_void_tv("BuiltinType:Void", VoidTypeSoln::get(), nullptr),
        m_string_tv("BuiltinType:String", StringTypeSoln::get(), nullptr),
        m_i8_tv("BuiltinType:I8", IntTypeSoln::get_i8(), nullptr),
        m_i16_tv("BuiltinType:I16", IntTypeSoln::get_i16(), nullptr),
        m_i32_tv("BuiltinType:I32", IntTypeSoln::get_i32(), nullptr),
        m_i64_tv("BuiltinType:I64", IntTypeSoln::get_i64(), nullptr),
        m_i128_tv("BuiltinType:I128", IntTypeSoln::get_i128(), nullptr),
        m_u1_tv("BuiltinType:U1", IntTypeSoln::get_u1(), nullptr),
        m_u8_tv("BuiltinType:U8", IntTypeSoln::get_u8(), nullptr),
        m_u16_tv("BuiltinType:U16", IntTypeSoln::get_u16(), nullptr),
        m_u32_tv("BuiltinType:U32", IntTypeSoln::get_u32(), nullptr),
        m_u64_tv("BuiltinType:U64", IntTypeSoln::get_u64(), nullptr),
        m_u128_tv("BuiltinType:U128", IntTypeSoln::get_u128(), nullptr),
        m_f16_tv("BuiltinType:F16", FloatTypeSoln::get_f16(), nullptr),
        m_f32_tv("BuiltinType:F32", FloatTypeSoln::get_f32(), nullptr),
        m_f64_tv("BuiltinType:F64", FloatTypeSoln::get_f64(), nullptr) 
    {}

    void Manager::print(printer::Printer& p) const {
        p.print_cstr("Manager Dump:");
        p.print_newline_indent();
        {
            
        }
        p.print_newline_deindent();
    }

}