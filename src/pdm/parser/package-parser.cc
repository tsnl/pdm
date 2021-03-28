#include "parser.hh"

// #include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <optional>

#include <json/single_include/nlohmann/json.hpp>

#include "pdm/ast/source-node/package.hh"
#include "pdm/ast/module/extern-c-mod-exp.hh"
#include "pdm/ast/module/pkg-bundle-mod-exp.hh"
#include "pdm/ast/manager.hh"

#include "pdm/compiler/platform.hh"

using json = nlohmann::json;

using Package_ExternModuleInC = pdm::ast::Package::ExportField_ExternModuleInC;
using Package_ImportAllModulesFrom = pdm::ast::Package::ExportField_ImportAllModulesFrom;

namespace pdm::parser {

    struct Parser {
        std::string const kind_str_for_IMPORT_ALL_MODULES_FROM;
        std::string const kind_str_for_EXTERN_MODULE_IN_C;
        std::string const index_file_name;

        Parser();

        ast::Package*
        parse_package(ast::Manager* manager, source::LocalPackageSource* source);

        std::optional<Package_ExternModuleInC::CompilerArgs>
        parse_compiler_args_object(json args_json);
    };

    Parser::Parser()
    : kind_str_for_IMPORT_ALL_MODULES_FROM("IMPORT_ALL_MODULES_FROM"),
      kind_str_for_EXTERN_MODULE_IN_C("EXTERN_MODULE_IN_C"),
      index_file_name("pd-index.json")
    {
        intern::String::ensure_init();
    }

}

namespace pdm::parser {

    ast::Package* Parser::parse_package(ast::Manager* manager, source::LocalPackageSource* source) {
        std::filesystem::path package_dir_path = source->abs_path();
        std::filesystem::path package_index_file_path = package_dir_path / index_file_name;

        std::ifstream input_file{package_index_file_path};
        if (!input_file.is_open()) {
            assert(0 && "NotImplemented: report non-existent pd-index.json file.");
            return nullptr;
        }

        // reading the input file into a string:
        std::string text; {
            std::stringstream buffer;
            buffer << input_file.rdbuf();
            text = buffer.str();
        };

        // parsing into a generic JSON object:
        auto index_json_tree = json::parse(std::move(text), nullptr, false);
        if (index_json_tree.is_discarded()) {
            assert(0 && "NotImplemented: report invalid/malformed pd-index.json file.");
            return nullptr;
        }
        assert(index_json_tree.is_object());

        // 'exports' field:
        std::vector<ast::Package::ExportField*> ast_exports_fields;
        if (index_json_tree.contains("exports")) {
            json exports = index_json_tree["exports"];
            if (!exports.is_object()) {
                assert(0 && "NotImplemented: report non-object 'exports' field.");
            }

            // each kv-pair of the 'exports' object describes a module to load.
            // 'key' => name of module
            // 'value' => object with args to load the module, in particular 'kind'
            ast_exports_fields.reserve(exports.size());
            for (auto const& kv_pair: exports.items()) {
                json lhs = kv_pair.key();
                json rhs = kv_pair.value();

                if (!lhs.is_string()) {
                    assert(0 && "NotImplemented: report non-string module name in package index json.");
                }

                if (!rhs.is_object() || !rhs.contains("kind")) {
                    assert(0 && "NotImplemented: report non-object module body in package index json.");
                }

                auto lhs_str = lhs.get<std::string>();
                intern::String lhs_int_str{lhs_str.c_str()};

                json rhs_kind = rhs["kind"];
                auto rhs_kind_str = rhs_kind.get<std::string>();

                // dispatching to resolve each kind of module:
                ast::Package::ExportField* export_field;
                {
                    if (rhs_kind_str == kind_str_for_IMPORT_ALL_MODULES_FROM) {
                        // std::cout << "IMPORT_ALL_MODULES_FROM" << ' ' << lhs_str << std::endl;
                        // assert(0 && "NotImplemented: parsing IMPORT_ALL_MODULES_FROM");

                        if (!rhs.contains("path")) {
                            assert(0 && "NotImplemented: expected 'path' field in rhs of kind 'IMPORT_ALL_MODULES_FROM'");
                        }
                        json path_json = rhs["path"];
                        if (!path_json.is_string()) {
                            assert(0 && "NotImplemented: expected 'path' field in rhs to be a string.");
                        }
                        auto path_json_str = path_json.get<std::string>();

                        export_field = manager->new_package_export_field_for_import_modules_from(
                            {}, lhs_int_str,
                            std::move(path_json_str)
                        );
                    }
                    else if (rhs_kind_str == kind_str_for_EXTERN_MODULE_IN_C) {
                        // std::cout << "EXTERN_MODULE_IN_C" << ' ' << lhs_str << std::endl;

                        source::Loc loc{};
                        Package_ExternModuleInC::CoreCompilerArgs core_compiler_args;
                        Package_ExternModuleInC::PlatformCompilerArgs platform_compiler_args;

                        if (rhs.contains("core-compiler-args")) {
                            json args_json = rhs["core-compiler-args"];

                            if (!args_json.is_object()) {
                                assert(0 && "NotImplemented: expected an object for 'core-compiler-args");
                            }

                            auto maybe_core_compiler_args = std::move(parse_compiler_args_object(args_json));
                            if (maybe_core_compiler_args.has_value()) {
                                core_compiler_args = maybe_core_compiler_args.value();
                            } else {
                                // error already reported, can return 'nullptr' immediately.
                                return nullptr;
                            }
                        }
                        if (rhs.contains("platform-compiler-args")) {
                            json args_json = rhs["platform-compiler-args"];
                            if (!args_json.is_object()) {
                                assert(0 && "NotImplemented: expected an object for 'platform-compiler-args'");
                            }

                            for (auto const& platform_args_kv_pair: args_json.items()) {
                                json platform_args_lhs = platform_args_kv_pair.key();
                                json platform_args_rhs = platform_args_kv_pair.value();

                                if (!platform_args_lhs.is_string()) {
                                    assert(0 && "NotImplemented: expected a string as a key in 'platform-compiler-args'");
                                }
                                if (!platform_args_rhs.is_object()) {
                                    assert(0 && "NotImplemented: expected an object as an RHS value in "
                                                "'platform-compiler-args'");
                                }

                                auto lhs_name_string = platform_args_lhs.get<std::string>();
                                intern::String lhs_name_int_str{lhs_name_string.c_str()};

                                bool is_valid_platform_name = validate_platform_string(lhs_name_int_str);
                                if (!is_valid_platform_name) {
                                    assert(0 && "NotImplemented: report invalid platform name in 'platform-compiler-args'");
                                }

                                auto maybe_pd_compiler_args = parse_compiler_args_object(platform_args_rhs);
                                if (maybe_pd_compiler_args.has_value()) {
                                    platform_compiler_args[lhs_name_int_str] = maybe_pd_compiler_args.value();
                                } else {
                                    // invalid PD-args => an error occurred.
                                    // for now, return nullptr, but consider scanning all args first?
                                    return nullptr;
                                }
                            }
                        }

                        // creating an export field, and an associated module:
                        export_field = manager->new_package_export_field_for_extern_module_in_c(
                            loc, lhs_int_str,
                            std::move(core_compiler_args),
                            std::move(platform_compiler_args)
                        );
                    }
                }
                ast_exports_fields.push_back(export_field);
            }
        }

        return manager->new_package(source, {}, std::move(ast_exports_fields));
    }

    std::optional<Package_ExternModuleInC::CompilerArgs> Parser::parse_compiler_args_object(json args_json) {
        Package_ExternModuleInC::CompilerArgs parsed_args{};

        if (args_json.contains("src")) {
            json src_array = args_json["src"];
            if (!src_array.is_array()) {
                assert(0 && "NotImplemented: expected an array for 'src'.");
                goto only_upon_failure;
            }

            // std::cout << "src:" << std::endl;
            parsed_args.src.reserve(src_array.size());
            for (auto const& it: src_array) {
                if (!it.is_string()) {
                    assert(0 && "NotImplemented: expected a string file path entry for 'src'.");
                    goto only_upon_failure;
                }
                auto arg_text = it.get<std::string>();
                parsed_args.src.push_back(arg_text);
                // std::cout << "- " << arg_text << std::endl;
            }
        }
        if (args_json.contains("lib")) {
            json lib_array = args_json["lib"];
            if (!lib_array.is_array()) {
                assert(0 && "NotImplemented: expected an array for 'lib'.");
                goto only_upon_failure;
            }

            // std::cout << "lib:" << std::endl;
            for (auto const& it: lib_array) {
                if (!it.is_string()) {
                    assert(0 && "NotImplemented: expected a string file path entry for 'src'.");
                    goto only_upon_failure;
                }
                auto arg_text = it.get<std::string>();
                parsed_args.lib.push_back(arg_text);
                // std::cout << "- " << arg_text << std::endl;
            }
        }
        if (args_json.contains("include")) {
            json include_array = args_json["include"];
            if (!include_array.is_array()) {
                assert(0 && "NotImplemented: expected an array for 'include'.");
                goto only_upon_failure;
            }

            // std::cout << "include:" << std::endl;
            for (auto const& it: include_array) {
                if (!it.is_string()) {
                    assert(0 && "NotImplemented: expected a string file path entry for 'src'.");
                    goto only_upon_failure;
                }
                auto arg_text = it.get<std::string>();
                parsed_args.include.push_back(arg_text);
                // std::cout << "- " << arg_text << std::endl;
            }
        }

        return {parsed_args};

      only_upon_failure:
        return {};
    }

    // convenience type checkers
    // j.is_null();
    // j.is_boolean();
    // j.is_number();
    // j.is_object();
    // j.is_array();
    // j.is_string();

}

namespace pdm::parser {

    ast::Package* parse_package(ast::Manager* manager, source::LocalPackageSource* source) {
        static Parser parser{};
        return parser.parse_package(manager, source);
    }

}