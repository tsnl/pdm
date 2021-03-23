#include <iostream>
#include <filesystem>

#include "pdm/compiler/compiler.hh"
#include "pdm/compiler/platform.hh"

#include "pdm/feedback/feedback.hh"

#include "pdm/printer/printer.hh"

#include "pdm/core/intern.hh"

// #include "typer_demo.hh"
// #include "feedback_demo.hh"

int main(int argc, char const* argv[]) {
    std::cout << "pdm-cli v0.0" << std::endl;
    if (argc != 3) {
        std::cout << "Invalid arguments, expected 2, received " << argc - 1 << std::endl
                  << "Usage:\t" << argv[0] << " <entry-point-path>  <platform-string>" << std::endl
                  << "Please try again."    << std::endl;
    } else {
        std::string entry_point_path {argv[1]};
        pdm::intern::String::ensure_init();

        pdm::intern::String platform_string {argv[2]};
        if (pdm::validate_platform_string(platform_string)) {
            pdm::Compiler compiler {
                std::move(std::filesystem::current_path().string()),
                entry_point_path,
                platform_string
            };
            bool compiled_ok = compiler.finish();
            int return_code = (compiled_ok ? 0 : 1);
            pdm::feedback::print_all(std::cout);
            return return_code;
        } else {
            std::cout << "Invalid target string: must be one of..." << std::endl;
            for (auto platform_int_str: pdm::platform_strings()) {
                std::cout << "- " << platform_int_str.cpp_str() << std::endl;
            }
            return 0;
        }
    }
    return 0;
}