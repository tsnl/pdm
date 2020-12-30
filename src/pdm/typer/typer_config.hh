#ifndef INCLUDED_PDM_TYPER_TYPER_CFG_HH
#define INCLUDED_PDM_TYPER_TYPER_CFG_HH

namespace pdm::ast {
    class BuiltinTypeStmt;
}

/*
    TypeVar* m_void_tv;
    TypeVar* m_string_tv;
    TypeVar* m_i8_tv;
    TypeVar* m_i16_tv;
    TypeVar* m_i32_tv;
    TypeVar* m_i64_tv;
    TypeVar* m_i128_tv;
    TypeVar* m_u1_tv;
    TypeVar* m_u8_tv;
    TypeVar* m_u16_tv;
    TypeVar* m_u32_tv;
    TypeVar* m_u64_tv;
    TypeVar* m_u128_tv;
    TypeVar* m_f16_tv;
    TypeVar* m_f32_tv;
    TypeVar* m_f64_tv;
 */

namespace pdm::typer {
    struct TyperConfig {
        ast::BuiltinTypeStmt* void_tv_client_astn;
        ast::BuiltinTypeStmt* string_tv_client_astn;
        
        ast::BuiltinTypeStmt* i8_tv_client_astn;
        ast::BuiltinTypeStmt* i16_tv_client_astn;
        ast::BuiltinTypeStmt* i32_tv_client_astn;
        ast::BuiltinTypeStmt* i64_tv_client_astn;
        ast::BuiltinTypeStmt* i128_tv_client_astn;
        
        ast::BuiltinTypeStmt* u1_tv_client_astn;
        ast::BuiltinTypeStmt* u8_tv_client_astn;
        ast::BuiltinTypeStmt* u16_tv_client_astn;
        ast::BuiltinTypeStmt* u32_tv_client_astn;
        ast::BuiltinTypeStmt* u64_tv_client_astn;
        ast::BuiltinTypeStmt* u128_tv_client_astn;
        
        ast::BuiltinTypeStmt* f16_tv_client_astn;
        ast::BuiltinTypeStmt* f32_tv_client_astn;
        ast::BuiltinTypeStmt* f64_tv_client_astn;
    };
}

#endif  // INCLUDED_PDM_TYPER_TYPER_CFG_HH