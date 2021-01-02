#ifndef INCLUDED_PDM_COMPILER_COMPILER_HH
#define INCLUDED_PDM_COMPILER_COMPILER_HH

#include <string>
#include <algorithm>
#include <unordered_map>
#include <filesystem>
#include <vector>

#include "pdm/core/intern.hh"
#include "pdm/ast/manager.hh"
#include "pdm/ast/script/script.hh"

#include "pdm/types/manager.hh"
#include "pdm/scoper/scoper.hh"
#include "pdm/scoper/root_frame.hh"

namespace pdm::compiler {

    // helper
    namespace aux {
        struct Key {
            std::filesystem::path import_from_path;
            std::string import_type_str;

            bool operator==(Key const k) const {
                return (
                    import_from_path == k.import_from_path &&
                    import_type_str == k.import_type_str
                );
            }
        };
        struct Hash {
            Hash() {}

            std::size_t operator() (Key const it) const {
                size_t lt = std::hash<std::string>{}(it.import_from_path.native());
                size_t rt = std::hash<std::string>{}(it.import_type_str);
                return lt ^ rt;
            }
        };
        using ImportMap = std::unordered_map<Key, ast::Script*, Hash>;
    }

    // 'Compiler' instances transform input files into output files.
    class Compiler {
      public:
        enum class PrintFlag: u64 {
            SourceCode  = 0x1,
            Scopes      = 0x2,
            Types       = 0x4,
            Llvm        = 0x8,
            Wasm        = 0x10
        };

      private:
        std::filesystem::path m_cwd;
        std::filesystem::path m_entry_point_path;
        
        aux::ImportMap            m_cached_imports;
        std::vector<ast::Script*> m_all_scripts;
        
        types::Manager   m_typer;
        ast::Manager   m_manager;
        scoper::Scoper m_scoper;

        u64 m_print_flags;

      // builtin type stmts:
      private:
        ast::BuiltinTypeStmt* m_void_tv_client_astn;
        ast::BuiltinTypeStmt* m_string_tv_client_astn;
        ast::BuiltinTypeStmt* m_i8_tv_client_astn;
        ast::BuiltinTypeStmt* m_i16_tv_client_astn;
        ast::BuiltinTypeStmt* m_i32_tv_client_astn;
        ast::BuiltinTypeStmt* m_i64_tv_client_astn;
        ast::BuiltinTypeStmt* m_i128_tv_client_astn;
        ast::BuiltinTypeStmt* m_u1_tv_client_astn;
        ast::BuiltinTypeStmt* m_u8_tv_client_astn;
        ast::BuiltinTypeStmt* m_u16_tv_client_astn;
        ast::BuiltinTypeStmt* m_u32_tv_client_astn;
        ast::BuiltinTypeStmt* m_u64_tv_client_astn;
        ast::BuiltinTypeStmt* m_u128_tv_client_astn;
        ast::BuiltinTypeStmt* m_f16_tv_client_astn;
        ast::BuiltinTypeStmt* m_f32_tv_client_astn;
        ast::BuiltinTypeStmt* m_f64_tv_client_astn;

      public:
        Compiler(std::string&& cwd, std::string&& entry_point_path, u64 print_flags = 0);
        
      public:
        ast::Script* import(std::string const& from_path, std::string const& type, std::string const& reason);

      private:
        // help_define_builtin_type is called during the constructor, post initialization to define
        // universal types.
        ast::BuiltinTypeStmt* help_define_builtin_type(intern::String name, types::Var* typer_var);
        
        // help_import_script_1 is called for every imported function, regardless of whether imported before or not.
        ast::Script* help_import_script_1(std::string const& from_path, std::string const& type);

        // help_import_script_2 is used to perform first-time initialization of freshly loaded Scripts.
        void help_import_script_2(ast::Script* script);

      private:
        bool pass1_import_all();
        bool pass2_typecheck_all();
        bool pass3_emit_all();

      private:
        void postpass1_print1_code();
        void postpass1_print2_scopes();
        void postpass2_print1_types();
        void postpass3_print1_llvm();
        void postpass3_print2_wasm();

      public:
        bool finish();

      public:
        std::string abspath(std::string const& str) const;

      public:
        types::Manager* typer() {
            return &m_typer;
        }
        ast::Manager* ast_manager() {
            return &m_manager;
        }
        std::vector<ast::Script*> const& all_scripts() const {
            return m_all_scripts;
        }
    };

}

#endif  // INCLUDED_PDM_COMPILER_COMPILER_HH