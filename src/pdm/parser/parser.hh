#ifndef INCLUDED_PDM_PARSER_PARSER_HH
#define INCLUDED_PDM_PARSER_PARSER_HH

#include "lexer.hh"
#include "pdm/ast/source-node/script.hh"
#include "pdm/ast/source-node/package.hh"
#include "pdm/source/i-source.hh"
#include "pdm/source/local-script-source.hh"
#include "pdm/source/local-package-source.hh"

namespace pdm::parser {

    ast::Script* parse_script(ast::Manager* manager, source::LocalScriptSource* source);
    ast::Package* parse_package(ast::Manager* manager, source::LocalPackageSource* source);

}

#endif  // INCLUDED_PDM_PARSER_PARSER_HH
