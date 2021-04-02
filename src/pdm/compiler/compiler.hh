#ifndef INCLUDED_PDM_COMPILER_COMPILER_HH
#define INCLUDED_PDM_COMPILER_COMPILER_HH

#include <string>
#include <algorithm>
#include <unordered_map>
#include <filesystem>
#include <vector>

#include "pdm/core/intern.hh"
#include "pdm/ast/manager.hh"
#include "pdm/ast/source-node/i-source-node.hh"

#include "pdm/types/manager.hh"
#include "pdm/scoper/scoper.hh"
#include "pdm/scoper/root_frame.hh"

namespace pdm {

    // helper
    namespace aux {
        struct Key {
            std::filesystem::path import_from_path;
            // std::string import_type_str;

            bool operator==(Key const& k) const {
                return (
                    import_from_path == k.import_from_path
                );
            }
        };
        struct Hash {
            Hash() = default;

            std::size_t operator() (Key const& it) const {
                return std::hash<std::string>{}(it.import_from_path.native());
            }
        };
        using ImportMap = std::unordered_map<Key, ast::ISourceNode*, Hash>;
    }

    // 'Compiler' instances transform input files into output files.
    class Compiler {
      private:
        std::filesystem::path m_cwd;
        std::filesystem::path m_entry_point_path;
        
        aux::ImportMap m_cached_imports;
        std::vector<ast::ISourceNode*> m_all_source_nodes;
        
        types::Manager m_types_mgr;
        ast::Manager   m_ast_mgr;

        intern::String m_target_name;
        LLVMBuilderRef m_llvm_builder;

      // builtin type stmts:
      private:
        ast::BuiltinStmt* m_void_tv_client_astn;
        ast::BuiltinStmt* m_string_tv_client_astn;
        ast::BuiltinStmt* m_i8_tv_client_astn;
        ast::BuiltinStmt* m_i16_tv_client_astn;
        ast::BuiltinStmt* m_i32_tv_client_astn;
        ast::BuiltinStmt* m_i64_tv_client_astn;
        ast::BuiltinStmt* m_i128_tv_client_astn;
        ast::BuiltinStmt* m_u1_tv_client_astn;
        ast::BuiltinStmt* m_u8_tv_client_astn;
        ast::BuiltinStmt* m_u16_tv_client_astn;
        ast::BuiltinStmt* m_u32_tv_client_astn;
        ast::BuiltinStmt* m_u64_tv_client_astn;
        ast::BuiltinStmt* m_u128_tv_client_astn;
        ast::BuiltinStmt* m_f16_tv_client_astn;
        ast::BuiltinStmt* m_f32_tv_client_astn;
        ast::BuiltinStmt* m_f64_tv_client_astn;

      public:
        Compiler(std::string&& cwd, std::string const& entry_point_path, intern::String target_name);
        ~Compiler();

      public:
        ast::ISourceNode* import(std::string const& abs_from_path, std::string const& reason);

      private:
        // help_define_builtin_type is called during the constructor, post initialization to define
        // universal types.
        ast::BuiltinStmt* help_define_builtin_type(scoper::Scoper& scoper, intern::String name, types::Var* typer_var);

        ast::ISourceNode* check_cache_or_import(std::string const& from_path, std::string const& reason);
        ast::ISourceNode* import_new(std::string const& raw_from_path_string, std::string const& abs_from_path_string, std::string const& reason);
        ast::Script* import_new_script(std::string const& raw_from_path_string, std::string const& abs_from_path_string, std::string const& reason);
        ast::Package* import_new_package(std::string const& raw_from_path_string, std::string const& abs_from_path_string, std::string const& reason);
        // void setup_fresh_script(ast::Script* script);
        // void setup_fresh_package(ast::Package* package-content);

      private:
        bool pass1_import_all(scoper::Scoper& scoper);
        bool pass2_type_check_all();
        bool pass3_emit_all();

      private:
        void postpass1_print1_code();
        void postpass1_print2_scopes(scoper::Scoper& scoper);
        void postpass2_print1_types();

      public:
        bool finish();

      public:
        [[nodiscard]] std::string abspath(std::string const& str) const;

      public:
        types::Manager* types_mgr() {
            return &m_types_mgr;
        }
        ast::Manager* ast_mgr() {
            return &m_ast_mgr;
        }
        [[nodiscard]] std::vector<ast::ISourceNode*> const& all_source_nodes() const {
            return m_all_source_nodes;
        }
        [[nodiscard]] intern::String target_name() const {
            return m_target_name;
        }

      public:
        [[nodiscard]] LLVMBuilderRef llvm_builder() const;
    };

    inline LLVMBuilderRef Compiler::llvm_builder() const {
        return m_llvm_builder;
    }

}

#endif  // INCLUDED_PDM_COMPILER_COMPILER_HH