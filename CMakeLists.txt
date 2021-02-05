cmake_minimum_required(VERSION 3.16)

#
# Initializing the project:
#

# initializing the vcpkg builtsystem:
set(CMAKE_TOOLCHAIN_FILE
    ${CMAKE_CURRENT_SOURCE_DIR}/dev/vcpkg/scripts/buildsystems/vcpkg.cmake
    CACHE STRING "Vcpkg toolchain file"
)

# creating project, setting langs:
project(pandemonium C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)

# configuring VCPkg, dependencies:
# from https://github.com/microsoft/vcpkg/README.md
# from http://cpptruths.blogspot.com/2019/03/bootstrapping-vcpkg-based-cmake-project.html
set(PDM_DEPENDENCIES llvm)
# set(PDM_DEPENDENCIES llvm clang)

# load vcpkg toolchain:
if(NOT DEFINED ${CMAKE_TOOLCHAIN_FILE})
    set(VCPKG_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/dev/vcpkg)

    if(WIN32)
        set(VCPKG_EXEC ${VCPKG_ROOT}/vcpkg.exe)
        set(VCPKG_BOOTSTRAP ${VCPKG_ROOT}/bootstrap-vcpkg.bat)
    else()
        set(VCPKG_EXEC ${VCPKG_ROOT}/vcpkg)
        set(VCPKG_BOOTSTRAP ${VCPKG_ROOT}/bootstrap-vcpkg.sh)
    endif()

    if(NOT EXISTS ${VCPKG_EXEC})
        message("Bootstrapping vcpkg in ${VCPKG_ROOT}")
        execute_process(COMMAND ${VCPKG_BOOTSTRAP} WORKING_DIRECTORY ${VCPKG_ROOT})
    endif()

    if(NOT EXISTS ${VCPKG_EXEC})
        message(FATAL_ERROR "*** FATAL ERROR: Could not bootstrap vcpkg")
    endif()

    message(STATUS "Installing Clang,LLVM in ${VCPKG_ROOT}")
    execute_process(COMMAND ${VCPKG_EXEC} install ${PDM_DEPENDENCIES} WORKING_DIRECTORY ${VCPKG_ROOT})
endif()

# finding dependencies: libclang, llvm
find_package(LLVM CONFIG REQUIRED)
# find_package(Clang CONFIG REQUIRED)
message(STATUS "Found LLVM version (${LLVM_PACKAGE_VERSION})")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g")

# including directories:
include_directories(
    "${LLVM_INCLUDE_DIR}"
)
include_directories(
    src
    dep
)

# adding 'pdm': core library for compiler, other tools:
add_library(
    pdm

    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/manager.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/manager.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/kind.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/kind.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/node.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/node.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/visitor.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/visitor.hh

    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/exp/array.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/exp/binary.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/exp/chain.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/exp/dot.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/exp/exp.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/exp/float.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/exp/id.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/exp/if.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/exp/int.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/exp/lambda.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/exp/paren.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/exp/string.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/exp/struct.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/exp/tcall.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/exp/tuple.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/exp/type_query.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/exp/unary.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/exp/unit.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/exp/vcall.hh

    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/pattern/base_field.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/pattern/lpattern.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/pattern/tpattern.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/pattern/vpattern.hh

    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/script/script.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/script/script.hh

    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/stmt/stmt.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/stmt/builtin.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/stmt/builtin.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/stmt/const.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/stmt/discard.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/stmt/extern.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/stmt/import.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/stmt/import.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/stmt/mod.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/stmt/mod.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/stmt/set.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/stmt/mod_val.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/stmt/mod_enum.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/stmt/mod_type.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/stmt/mod_typeclass.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/stmt/using.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/stmt/val.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/stmt/var.hh

    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/arg/targ.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/arg/varg.hh

    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/setspec/setspec.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/setspec/type_spec.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/setspec/type_spec.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/setspec/class_spec.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/setspec/class_spec.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/setspec/dot.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/setspec/fn.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/setspec/id_type_spec.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/setspec/id_class_spec.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/setspec/struct.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/ast/setspec/tcall.hh

    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/compiler/compiler.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/compiler/compiler.hh

    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/core/bitsets.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/core/integer.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/core/intern.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/core/intern.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/core/utf8.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/core/utf8.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/core/units.hh

    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/scoper/context.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/scoper/context.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/scoper/defn.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/scoper/defn.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/scoper/scoper.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/scoper/scoper.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/scoper/frame.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/scoper/frame.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/scoper/root_frame.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/scoper/root_frame.hh

    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/source/loc.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/source/loc.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/source/pos.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/source/pos.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/source/source.hh

    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/types/manager.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/types/manager.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/types/typeop_result.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/types/var_invariant.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/types/var_invariant.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/types/type.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/types/type.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/types/kind.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/types/var.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/types/var.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/types/var_archetype.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/types/relation.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/types/relation.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/types/solve_result.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/types/kdvs.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/types/kdvs.hh

    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/typer/typer.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/typer/typer.hh
   
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/feedback/feedback.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/feedback/feedback.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/feedback/manager.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/feedback/manager.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/feedback/letter.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/feedback/letter.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/feedback/note.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/feedback/note.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/feedback/severity.hh

    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/parser/lexer.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/parser/lexer.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/parser/parser.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/parser/parser.tab.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/parser/parser.tab.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/parser/reader.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/parser/reader.hh

    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/printer/printer.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/printer/printer.hh

    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/dependency_dispatcher/dependency_dispatcher.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pdm/dependency_dispatcher/dependency_dispatcher.hh
)

# link pdm <- llvm
# - see: https://github.com/MWGuy/llvm-hello/blob/master/CMakeLists.txt
llvm_map_components_to_libnames(llvm_libs Core ExecutionEngine Interpreter MCJIT Support nativecodegen IRReader)
add_definitions(${LLVM_DEFINITIONS})
target_link_libraries(pdm ${llvm_libs})

# link pdm <- intern :- C lib for interned string support
add_subdirectory(dep/intern)
target_link_libraries(pdm intern)

# link pdm <- utf8proc :- C lib for Unicode support
add_library(utf8proc
    dep/utf8proc/utf8proc.c
    dep/utf8proc/utf8proc.h
)
target_link_libraries(pdm utf8proc)

# PDM Sandbox: toy driver for PDM
add_executable(
    pdm_sandbox
    src/pdm_sandbox/main.cc
    src/pdm_sandbox/typer_demo.cc
    src/pdm_sandbox/typer_demo.hh
    src/pdm_sandbox/feedback_demo.cc
    src/pdm_sandbox/feedback_demo.hh
)
target_link_libraries(pdm_sandbox pdm)

#
#
# Other Resources:
#
#

# - https://lowlevelbits.org/building-an-llvm-based-tool.-lessons-learned/
# - https://llvm.org/docs/CMake.html#embedding-llvm-in-your-project
