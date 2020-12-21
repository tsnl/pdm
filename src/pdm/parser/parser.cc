#include "parser.hh"

#include "parser.tab.hh"

namespace pdm::parser {

    ast::Script* parse_script(source::Source* source) {
        Lexer lexer;
        if (!lexer.setup(source)) {
            return nullptr;
        }

        // todo: call function in parser.tab.cc/parser.tab.hh to parse this source file.
    }
}
