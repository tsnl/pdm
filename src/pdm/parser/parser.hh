#ifndef INCLUDED_PDM_PARSER_PARSER_HH
#define INCLUDED_PDM_PARSER_PARSER_HH

#include "lexer.hh"
#include "pdm/ast/source-node/script.hh"
#include "pdm/source/i-source.hh"

namespace pdm::parser {

    ast::Script* parse_script(ast::Manager* manager, source::ISource* source);

}

#endif  // INCLUDED_PDM_PARSER_PARSER_HH
