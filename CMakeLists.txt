cmake_minimum_required(VERSION 3.16)
project(pandemonium C CXX)

#
# Adding LLVM and Clang as dependencies:
#

# RESOURCES:
# - https://lowlevelbits.org/building-an-llvm-based-tool.-lessons-learned/
# - https://llvm.org/docs/CMake.html#embedding-llvm-in-your-project
# - todo: load source by adding dirs to 'CMAKE_MODULE_PATH' http://wiki.icub.org/wiki/CMake_and_FIND_PACKAGE

find_package(LLVM REQUIRED CONFIG)
# find_package(Clang REQUIRED CONFIG)

set(PDM_LLVM_INSTALL_DIR CACHE PATH 
    "llvm install dir containing headers ('include' dir) with 'llvm', 'clang', etc.")

message(STATUS "... Found LLVM version (${LLVM_PACKAGE_VERSION})")
message(STATUS "... Using LLVMConfig.cmake in: ${LLVM_DIR}")
message(STATUS "... Add '${PDM_LLVM_INSTALL_DIR}/include' to your IDE include path list for LLVM C API auto-complete.")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g")


include_directories(
    "${PDM_LLVM_INSTALL_DIR}/include/"
)
include_directories(
    src
    dep
)


#
#
# PDM:
#
#

add_library(
    pdm

    src/pdm/ast/manager.cc
    src/pdm/ast/manager.hh
    src/pdm/ast/kind.cc
    src/pdm/ast/kind.hh
    src/pdm/ast/node.cc
    src/pdm/ast/node.hh
    src/pdm/ast/visitor.cc
    src/pdm/ast/visitor.hh

    src/pdm/ast/exp/array.hh
    src/pdm/ast/exp/binary.hh
    src/pdm/ast/exp/chain.hh
    src/pdm/ast/exp/dot.hh
    src/pdm/ast/exp/exp.hh
    src/pdm/ast/exp/float.hh
    src/pdm/ast/exp/id.hh
    src/pdm/ast/exp/if.hh
    src/pdm/ast/exp/int.hh
    src/pdm/ast/exp/lambda.hh
    src/pdm/ast/exp/paren.hh
    src/pdm/ast/exp/string.hh
    src/pdm/ast/exp/struct.hh
    src/pdm/ast/exp/tcall.hh
    src/pdm/ast/exp/tuple.hh
    src/pdm/ast/exp/type_query.hh
    src/pdm/ast/exp/unary.hh
    src/pdm/ast/exp/unit.hh
    src/pdm/ast/exp/vcall.hh

    src/pdm/ast/pattern/lpattern.hh
    src/pdm/ast/pattern/tpattern.hh
    src/pdm/ast/pattern/vpattern.hh

    src/pdm/ast/script/script.cc
    src/pdm/ast/script/script.hh

    src/pdm/ast/stmt/stmt.hh
    src/pdm/ast/stmt/builtin_type.cc
    src/pdm/ast/stmt/builtin_type.hh
    src/pdm/ast/stmt/const.hh
    src/pdm/ast/stmt/discard.hh
    src/pdm/ast/stmt/enum.hh
    src/pdm/ast/stmt/extern.hh
    src/pdm/ast/stmt/fn.hh
    src/pdm/ast/stmt/import.cc
    src/pdm/ast/stmt/import.hh
    src/pdm/ast/stmt/mod.cc
    src/pdm/ast/stmt/mod.hh
    src/pdm/ast/stmt/set.hh
    src/pdm/ast/stmt/type.hh
    src/pdm/ast/stmt/typeclass.hh
    src/pdm/ast/stmt/using.hh
    src/pdm/ast/stmt/val.hh
    src/pdm/ast/stmt/var.hh

    src/pdm/ast/arg/targ.hh
    src/pdm/ast/arg/varg.hh

    src/pdm/ast/typespec/typespec.hh
    src/pdm/ast/typespec/dot.hh
    src/pdm/ast/typespec/fn.hh
    src/pdm/ast/typespec/id.hh
    src/pdm/ast/typespec/struct.hh
    src/pdm/ast/typespec/tcall.hh

    src/pdm/compiler/compiler.cc
    src/pdm/compiler/compiler.hh

    src/pdm/core/integer.hh
    src/pdm/core/intern.cc
    src/pdm/core/intern.hh
    src/pdm/core/utf8.cc
    src/pdm/core/utf8.hh
    src/pdm/core/units.hh

    src/pdm/scoper/context.cc
    src/pdm/scoper/context.hh
    src/pdm/scoper/defn.cc
    src/pdm/scoper/defn.hh
    src/pdm/scoper/scoper.cc
    src/pdm/scoper/scoper.hh
    src/pdm/scoper/frame.cc
    src/pdm/scoper/frame.hh
    src/pdm/scoper/root_frame.cc
    src/pdm/scoper/root_frame.hh

    src/pdm/source/loc.cc
    src/pdm/source/loc.hh
    src/pdm/source/pos.cc
    src/pdm/source/pos.hh
    src/pdm/source/source.hh

    src/pdm/types/manager.cc
    src/pdm/types/manager.hh
    src/pdm/types/type_constraint.hh
    src/pdm/types/type_soln.cc
    src/pdm/types/type_soln.hh
    src/pdm/types/type_kind.hh
    src/pdm/types/var.cc
    src/pdm/types/var.hh
    src/pdm/types/rule.hh
    
    src/pdm/typer/typer.hh
    src/pdm/typer/typer.hh

    src/pdm/feedback/feedback.cc
    src/pdm/feedback/feedback.hh
    src/pdm/feedback/manager.cc
    src/pdm/feedback/manager.hh
    src/pdm/feedback/letter.cc
    src/pdm/feedback/letter.hh
    src/pdm/feedback/note.cc
    src/pdm/feedback/note.hh
    src/pdm/feedback/severity.hh

    src/pdm/parser/lexer.cc
    src/pdm/parser/lexer.hh
    src/pdm/parser/parser.hh
    src/pdm/parser/parser.tab.cc
    src/pdm/parser/parser.tab.hh
    src/pdm/parser/reader.cc
    src/pdm/parser/reader.hh

    src/pdm/printer/printer.cc
    src/pdm/printer/printer.hh

    src/pdm/dependency_dispatcher/dependency_dispatcher.cc
    src/pdm/dependency_dispatcher/dependency_dispatcher.hh
)

#
# LLVM
# - see: https://github.com/MWGuy/llvm-hello/blob/master/CMakeLists.txt
#

# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs Core ExecutionEngine Interpreter MCJIT Support nativecodegen IRReader)
add_definitions(${LLVM_DEFINITIONS})
target_link_libraries(pdm ${llvm_libs})

#
# Intern library:
#

add_subdirectory(dep/intern)
target_link_libraries(pdm intern)

#
# utf8proc - Unicode support
#

add_library(utf8proc
    dep/utf8proc/utf8proc.c
    dep/utf8proc/utf8proc.h
)
target_link_libraries(pdm utf8proc)

#
# CXX Standard:
#

set_property(TARGET pdm PROPERTY CXX_STANDARD 20)


#
#
# PDM Sandbox:
#
#

add_executable(
    pdm_sandbox
    src/pdm_sandbox/main.cc
    src/pdm_sandbox/typer_demo.cc
    src/pdm_sandbox/typer_demo.hh
    src/pdm_sandbox/feedback_demo.cc
    src/pdm_sandbox/feedback_demo.hh
)
target_link_libraries(pdm_sandbox pdm)
set_property(TARGET pdm_sandbox PROPERTY CXX_STANDARD 20)
