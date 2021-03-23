#ifndef INCLUDED__PDM__AST__SOURCE_NODE__PACKAGE_HH
#define INCLUDED__PDM__AST__SOURCE_NODE__PACKAGE_HH

#include <map>
#include <vector>
#include <string>

#include "../node.hh"
#include "i_source_node.hh"

namespace pdm::ast {

    class Package;

    class Package: public ISourceNode {
      public:
        class ExportField: public ast::Node {
          protected:
            ExportField(source::Loc loc, Kind field_kind);
        };
        class ExportField_ExternModuleInC: public ExportField {
          public:
            struct CompilerArgs {
                std::vector<std::string> include;
                std::vector<std::string> src;
                std::vector<std::string> lib;
            };

            using CoreCompilerArgs = CompilerArgs;
            using PlatformCompilerArgs = std::map<intern::String, CompilerArgs>;

          private:
            CoreCompilerArgs m_core_compiler_args;
            PlatformCompilerArgs m_platform_compiler_args;

          public:
            ExportField_ExternModuleInC(
                source::Loc loc,
                CoreCompilerArgs&& core_compiler_args,
                PlatformCompilerArgs&& platform_compiler_args
            );

          public:
            CoreCompilerArgs const& core_compiler_args() const;
            PlatformCompilerArgs const& platform_compiler_args() const;
        };
        class ExportField_ImportAllModulesFrom: public ExportField {
          public:
            std::string m_path;

          public:
            ExportField_ImportAllModulesFrom(source::Loc loc, std::string&& path);
        };

      private:
        std::vector<ExportField*> m_exports_fields;

      public:
        Package(
            source::ISource* package_source, source::Loc loc,
            std::vector<ExportField*>&& exports_fields
        );

      public:
        [[nodiscard]] std::vector<ExportField*> const& exports_fields() const;
    };

    inline Package::ExportField::ExportField(source::Loc loc, Kind field_kind)
    :   Node{loc, field_kind}
    {}

    inline Package::ExportField_ExternModuleInC::ExportField_ExternModuleInC(
        source::Loc loc,
        CompilerArgs &&core_compiler_args, PlatformCompilerArgs &&platform_compiler_args
    )
    :   ExportField(loc, ast::Kind::PackageExportField_ExternModuleInC),
        m_core_compiler_args(std::move(core_compiler_args)),
        m_platform_compiler_args(std::move(platform_compiler_args))
    {}

    inline
    Package::ExportField_ExternModuleInC::CoreCompilerArgs const&
    Package::ExportField_ExternModuleInC::core_compiler_args() const {
        return m_core_compiler_args;
    }

    inline
    Package::ExportField_ExternModuleInC::PlatformCompilerArgs const&
    Package::ExportField_ExternModuleInC::platform_compiler_args() const {
        return m_platform_compiler_args;
    }

    inline Package::Package(
        source::ISource* package_source, source::Loc loc,
        std::vector<ExportField*>&& exports_fields
    )
    :   ISourceNode(package_source, loc, ast::Kind::Package),
        m_exports_fields(std::move(exports_fields))
    {}

    inline Package::ExportField_ImportAllModulesFrom::ExportField_ImportAllModulesFrom(
        source::Loc loc,
        std::string&& path
    )
    :   Package::ExportField(loc, ast::Kind::PackageExportField_ImportAllModulesFrom),
        m_path(std::move(path))
    {}

    inline
    std::vector<Package::ExportField*> const&
    Package::exports_fields() const {
        return m_exports_fields;
    }

}

#endif  // INCLUDED__PDM__AST__SOURCE_NODE__PACKAGE_HH