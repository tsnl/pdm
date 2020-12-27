#ifndef INCLUDED_PDM_PARSER_PARSER_HH
#define INCLUDED_PDM_PARSER_PARSER_HH

#include "lexer.hh"
#include "pdm/ast/script/script.hh"
#include "pdm/source/source.hh"

namespace pdm::parser {

    ast::Script* parse_script(ast::Manager* manager, source::Source* source);

}

#endif  // INCLUDED_PDM_PARSER_PARSER_HH
