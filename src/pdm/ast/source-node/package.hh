#ifndef INCLUDED__PDM__AST__SOURCE_NODE__PACKAGE_HH
#define INCLUDED__PDM__AST__SOURCE_NODE__PACKAGE_HH

#include <map>
#include <vector>
#include <string>

#include "../node.hh"
#include "../module/base-mod-exp.hh"
#include "../module/extern-c-mod-exp.hh"
#include "../module/pkg-bundle-mod-exp.hh"
#include "i-source-node.hh"

namespace pdm::ast {

    // Package is a source node that is a collection of 2 kinds of modules:
    // - ExternModExps: link a static binary and expose a module interface
    // - PkgBundleModExp: import * from X
    // NOTE: the package also exports 1 PkgBundleModExp representing its contents.
    class Package: public ISourceNode {
      // Fields:
      public:
        class ExportField: public ast::Node {
          private:
            intern::String m_name;
            BaseModExp* m_mod_exp;

          protected:
            ExportField(source::Loc loc, intern::String name, Kind field_kind);

          public:
            [[nodiscard]] intern::String name() const;

            [[nodiscard]] BaseModExp* mod_exp() const;
            void mod_exp(BaseModExp* mod_exp);
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
                intern::String name,
                CoreCompilerArgs&& core_compiler_args,
                PlatformCompilerArgs&& platform_compiler_args
            );

          public:
            [[nodiscard]] CoreCompilerArgs const& core_compiler_args() const;
            [[nodiscard]] PlatformCompilerArgs const& platform_compiler_args() const;

          public:
            [[nodiscard]] ExternCModExp* x_extern_mod_exp() const;
            void x_extern_mod_exp(ExternCModExp* extern_c_mod_exp);
        };
        class ExportField_ImportAllModulesFrom: public ExportField {
          private:
            std::string m_path;
            ISourceNode* m_x_origin_source_node;

          public:
            ExportField_ImportAllModulesFrom(source::Loc loc, intern::String name, std::string&& path);

          public:
            [[nodiscard]] std::string const& path() const;

          public:
            [[nodiscard]] ISourceNode* x_origin_source_node() const;
            void x_origin_source_node(ISourceNode* x_origin_source_node);
        };

      // Package data members:
      private:
        std::vector<ExportField*> m_exports_fields;

      // Constructors:
      public:
        Package(
            source::ISource* package_source, source::Loc loc,
            std::vector<ExportField*>&& exports_fields
        );

      // Properties:
      public:
        [[nodiscard]] std::vector<ExportField*> const& exports_fields() const;
    };

    inline Package::ExportField::ExportField(source::Loc loc, intern::String name, Kind field_kind)
    :   Node{loc, field_kind},
        m_name(name),
        m_mod_exp(nullptr)
    {}

    inline Package::ExportField_ExternModuleInC::ExportField_ExternModuleInC(
        source::Loc loc, intern::String name,
        CompilerArgs &&core_compiler_args, PlatformCompilerArgs &&platform_compiler_args
    )
    :   ExportField(loc, name, ast::Kind::PackageExportField_ExternModuleInC),
        m_core_compiler_args(std::move(core_compiler_args)),
        m_platform_compiler_args(std::move(platform_compiler_args))
    {}

    inline
    intern::String
    Package::ExportField::name() const {
        return m_name;
    }

    inline
    BaseModExp* Package::ExportField::mod_exp() const {
        return m_mod_exp;
    }

    inline
    void Package::ExportField::mod_exp(BaseModExp* mod_exp) {
        m_mod_exp = mod_exp;
    }

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

    inline
    ExternCModExp*
    Package::ExportField_ExternModuleInC::x_extern_mod_exp() const {
        auto extern_c_mod_exp = dynamic_cast<ExternCModExp*>(mod_exp());
        assert(extern_c_mod_exp && "Failed to up-cast a ModExp to an ExternCModExp.");
        return extern_c_mod_exp;
    }

    inline
    void
    Package::ExportField_ExternModuleInC::x_extern_mod_exp(ExternCModExp* extern_c_mod_exp) {
        mod_exp(extern_c_mod_exp);
    }

    inline Package::Package(
        source::ISource* package_source, source::Loc loc,
        std::vector<ExportField*>&& exports_fields
    )
    :   ISourceNode(package_source, loc, ast::Kind::Package),
        m_exports_fields(std::move(exports_fields))
    {}

    inline
    Package::ExportField_ImportAllModulesFrom::ExportField_ImportAllModulesFrom(
        source::Loc loc,
        intern::String name,
        std::string&& path
    )
    :   Package::ExportField(loc, name, ast::Kind::PackageExportField_ImportAllModulesFrom),
        m_path(std::move(path))
    {}

    inline
    std::string const&
    Package::ExportField_ImportAllModulesFrom::path() const {
        return m_path;
    }

    inline
    ISourceNode*
    Package::ExportField_ImportAllModulesFrom::x_origin_source_node() const {
        return m_x_origin_source_node;
    }

    inline
    void
    Package::ExportField_ImportAllModulesFrom::x_origin_source_node(ISourceNode* x_origin_source_node) {
        m_x_origin_source_node = x_origin_source_node;
    }

    inline
    std::vector<Package::ExportField*> const&
    Package::exports_fields() const {
        return m_exports_fields;
    }

}

#endif  // INCLUDED__PDM__AST__SOURCE_NODE__PACKAGE_HH