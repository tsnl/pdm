#ifndef INCLUDED_PDM_COMPILER_COMPILER_HH
#define INCLUDED_PDM_COMPILER_COMPILER_HH

#include <string>
#include <algorithm>
#include <unordered_map>
#include <filesystem>

#include "pdm/core/intern.hh"
#include "pdm/ast/manager.hh"
#include "pdm/ast/script/script.hh"

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
        aux::ImportMap m_cached_imports;
        
        typer::Typer m_typer;
        ast::Manager m_manager;
        scoper::RootFrame m_root_frame;
        scoper::Scoper m_scoper;

      public:
        Compiler(std::string&& cwd, std::string&& entry_point_path)
        : m_cwd(std::move(cwd)),
          m_entry_point_path(abspath(std::move(entry_point_path))),
          m_typer(),
          m_manager(&m_typer),
          m_root_frame(&m_typer),
          m_scoper(&m_typer, &m_root_frame) {}

      private:
        ast::Script* import(std::string&& from_path, std::string&& type);

      public:
        bool import_all();
        bool typecheck_all();

      public:
        std::string abspath(std::string&& str) const;
    };

}

#endif  // INCLUDED_PDM_COMPILER_COMPILER_HH