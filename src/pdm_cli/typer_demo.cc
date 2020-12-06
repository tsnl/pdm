#include <iostream>

#include "typer_demo.hh"

#include <pdm/core/intern.hh>
#include <pdm/typer/typer.hh>

#include "pdm/ast/exp/array.hh"
#include "pdm/ast/exp/binary.hh"
#include "pdm/ast/exp/chain.hh"
#include "pdm/ast/exp/dot.hh"
#include "pdm/ast/exp/exp.hh"
#include "pdm/ast/exp/float.hh"
#include "pdm/ast/exp/id.hh"
#include "pdm/ast/exp/if.hh"
#include "pdm/ast/exp/int.hh"
#include "pdm/ast/exp/lambda.hh"
#include "pdm/ast/exp/paren.hh"
#include "pdm/ast/exp/string.hh"
#include "pdm/ast/exp/struct.hh"
#include "pdm/ast/exp/tcall.hh"
#include "pdm/ast/exp/tuple.hh"
#include "pdm/ast/exp/type_query.hh"
#include "pdm/ast/exp/unary.hh"
#include "pdm/ast/exp/unit.hh"
#include "pdm/ast/exp/vcall.hh"
#include "pdm/ast/pattern/lpattern.hh"
#include "pdm/ast/pattern/tpattern.hh"
#include "pdm/ast/pattern/vpattern.hh"
#include "pdm/ast/script/script.cc"
#include "pdm/ast/script/script.hh"
#include "pdm/ast/stmt/const.hh"
#include "pdm/ast/stmt/def.hh"
#include "pdm/ast/stmt/enum.hh"
#include "pdm/ast/stmt/let.hh"
#include "pdm/ast/stmt/module.cc"
#include "pdm/ast/stmt/module.hh"
#include "pdm/ast/stmt/stmt.hh"
#include "pdm/ast/stmt/type.hh"
#include "pdm/ast/stmt/typeclass.hh"
#include "pdm/ast/typespec/dot.hh"
#include "pdm/ast/typespec/id.hh"
#include "pdm/ast/typespec/mut.hh"
#include "pdm/ast/typespec/ptr.hh"
#include "pdm/ast/typespec/struct.hh"
#include "pdm/ast/typespec/tcall.hh"
#include "pdm/ast/typespec/typespec.hh"

namespace pdm_cli::typer_demo {

    void demo1() {
        pdm::intern::Manager sm;
        pdm::intern::String lhs_name = sm.new_str("x");
        
        pdm::typer::Typer typer{};
        
        // todo: freevar (monomorph): 'x'
        // todo: y: i32
        // todo: x :subtype: y (typespec rule)
        // todo: x :subtype: z (let binding rule)
        // todo: z :subtype: int__ (int/numeric literal rule)
        
        // let x I32;
        auto lhs_tv = typer.new_monomorphic_var_tv("x");
        auto rhs_tv = typer.get_i32_tv();
        typer.apply_vid_typespec_rule(NULL, lhs_name, lhs_tv, rhs_tv);

        std::cout << "rule applied!" << std::endl;
    }
    

}