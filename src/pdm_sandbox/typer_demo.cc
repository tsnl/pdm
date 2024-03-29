#include <iostream>

#include "typer_demo.hh"

#include "pdm/ast/visitor.hh"
#include "pdm/core/intern.hh"
#include "pdm/types/manager.hh"

namespace pdm_cli::typer_demo {

    void demo1() {
        pdm::intern::String lhs_name("x");
        
        pdm::types::Manager types_mgr{nullptr};
        
        // todo: freevar (monomorph): 'x'
        // todo: y: i32
        // todo: x :subtype: y (typespec rule)
        // todo: x :subtype: z (let binding rule)
        // todo: z :subtype: int__ (int/numeric literal rule)
        
        // let x I32;
        auto lhs_tv = types_mgr.new_unknown_type_var("x");
        auto rhs_tv = types_mgr.get_i32_tv();
        // typer.apply_vid_typespec_rule(NULL, lhs_name, lhs_tv, rhs_tv);

        std::cout << "rule applied!" << std::endl;
    }

}
