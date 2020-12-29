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

#include "pdm/dependency_dispatcher/dependency_dispatcher.hh"
#include "pdm/typer/typer.hh"
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
      private:
        std::filesystem::path m_cwd;
        std::filesystem::path m_entry_point_path;
        
        aux::ImportMap            m_cached_imports;
        std::vector<ast::Script*> m_all_scripts;
        
        dependency_dispatcher::DependencyDispatcher m_dependency_dispatcher;

        typer::Typer      m_typer;
        ast::Manager      m_manager;
        scoper::RootFrame m_root_frame;
        scoper::Scoper    m_scoper;

      public:
        Compiler(std::string&& cwd, std::string&& entry_point_path)
        : m_cwd(std::move(cwd)),
          m_entry_point_path(abspath(std::move(entry_point_path))),
          m_cached_imports(),
          m_all_scripts(),
          m_dependency_dispatcher(this),
          m_typer(),
          m_manager(&m_typer),
          m_root_frame(&m_typer),
          m_scoper(&m_typer, &m_root_frame) {
            m_all_scripts.reserve(8);
        }

      public:
        ast::Script* import(std::string const& from_path, std::string const& type, std::string const& reason);

      private:
        // help_import_script_1 is called for every imported function, regardless of whether imported before or not.
        ast::Script* help_import_script_1(std::string const& from_path, std::string const& type);

        // help_import_script_2 is used to perform first-time initialization of freshly loaded Scripts.
        void         help_import_script_2(ast::Script* script);

      public:
        bool import_all();
        bool typecheck_all();

      public:
        std::string abspath(std::string const& str) const;

      public:
        typer::Typer* typer() {
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