#include <iostream>

#include "typer_demo.hh"

#include "pdm/ast/visitor.hh"
#include "pdm/core/intern.hh"
#include "pdm/typer/typer.hh"

namespace pdm_cli::typer_demo {

    void demo1() {
        pdm::intern::String lhs_name("x");
        
        pdm::typer::Typer typer{};
        
        // todo: freevar (monomorph): 'x'
        // todo: y: i32
        // todo: x :subtype: y (typespec rule)
        // todo: x :subtype: z (let binding rule)
        // todo: z :subtype: int__ (int/numeric literal rule)
        
        // let x I32;
        auto lhs_tv = typer.new_tv("x");
        auto rhs_tv = typer.get_i32_tv();
        // typer.apply_vid_typespec_rule(NULL, lhs_name, lhs_tv, rhs_tv);

        std::cout << "rule applied!" << std::endl;
    }
    

}