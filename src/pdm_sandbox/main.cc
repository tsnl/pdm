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
        pdm::compiler::Compiler compiler {
            std::move(std::filesystem::current_path().string()),
            std::move(entry_point_path)
        };
        if (!compiler.import_all()) {
            std::cout << "A fatal error occurred while loading source files." << std::endl;
            pdm::feedback::print_all(std::cout);
            return 1;
        }

        // debug only
        bool const print_scripts = true;
        if (print_scripts) {
            for (pdm::ast::Script* script: compiler.all_scripts()) {
                pdm::printer::Printer printer{std::cout};
                printer.print_node(script);
            }
        }

        if (!compiler.typecheck_all()) {
            std::cout << "A fatal typechecking occurred." << std::endl;
            pdm::feedback::print_all(std::cout);
            return 1;
        }

        // from here, we have a verdant, typechecked AST.
        // todo: emit an LLVM IR bundle, resolving dependencies as required
        // todo: emit a WASM bundle, resolving dependencies as required.

        // pdm_cli::typer_demo::demo1();
        // pdm_cli::feedback_demo::demo1();
    }
    return 0;
}