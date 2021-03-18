#include <iostream>
#include <filesystem>

#include "pdm/compiler/compiler.hh"
#include "pdm/feedback/feedback.hh"

#include "pdm/printer/printer.hh"

// #include "typer_demo.hh"
// #include "feedback_demo.hh"

int main(int argc, char const* argv[]) {
    std::cout << "pdm-cli v0.0" << std::endl;
    if (argc != 2) {
        std::cout << "Invalid #args, expected 2, received " << argc << std::endl
                  << "Usage:\t" << argv[0] << " <entry_point_path>" << std::endl
                  << "Please try again."    << std::endl;
    } else {
        std::string entry_point_path {argv[1]};
        pdm::Compiler compiler {
            std::move(std::filesystem::current_path().string()),
            entry_point_path,
            pdm::Compiler::PrintFlags_PrintEverything
        };
        bool compiled_ok = compiler.finish();
        int return_code = (compiled_ok ? 0 : 1);
        pdm::feedback::print_all(std::cout);
        return return_code;
    }
    return 0;
}