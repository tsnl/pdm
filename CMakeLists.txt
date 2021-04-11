cmake_minimum_required(VERSION 3.16)

#
# Initializing the project:
#

# creating project, setting langs:
project(pandemonium C CXX)

# finding LLVM's package:
# see: https://llvm.org/docs/CMake.html#embedding-llvm-in-your-project
# set(PDM_LLVM_CMAKE_DIR "dep/llvm-project/llvm/cmake/modules/")
# list(APPEND CMAKE_MODULE_PATH $"{PDM_LLVM_CMAKE_DIR}")
# find_package(LLVM REQUIRED CONFIG PATHS "${PDM_LLVM_CMAKE_DIR}")
# set(LLVM_ENABLE_PROJECTS "clang;clang-tools-extra;compiler-rt")
set(LLVM_ENABLE_ASSERTIONS ON)

set(PDM_LLVM_INSTALL_DIR "./build/llvm/install/")
list(APPEND CMAKE_PREFIX_PATH "${PDM_LLVM_INSTALL_DIR}/lib/cmake/clang")
list(APPEND CMAKE_PREFIX_PATH "${PDM_LLVM_INSTALL_DIR}/lib/cmake/llvm")

find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED)
# include("${CMAKE_BINARY_DIR}/dep/llvm-project/llvm/lib/cmake/llvm/LLVM-Config.cmake")
# set(PDM_LLVM_BINARY_DIR ${CMAKE_BINARY_DIR}/build-llvm)
# set(PDM_LLVM_INSTALL_DIR ${CMAKE_BINARY_DIR}/install-llvm)

message(STATUS "Enable string: '${LLVM_ENABLE_PROJECTS}'")

# set(CMAKE_INSTALL_PREFIX "${PDM_LLVM_INSTALL_DIR}")

# add_subdirectory(
#     dep/llvm-project/llvm
#     "${PDM_LLVM_BINARY_DIR}"
# )

message(STATUS "find_package @ LLVM: ${LLVM_FOUND}")
message(STATUS "    - LLVM_DIR: ${LLVM_DIR}")
message(STATUS "find_package @ Clang: ${Clang_FOUND}")
message(STATUS "    - Clang_DIR: ${Clang_DIR}")
message(STATUS "Found LLVM version '${LLVM_PACKAGE_VERSION}'")
message(STATUS "Using LLVM-Config.cmake in: ${LLVM_DIR}")

# including directories:
include_directories(
    src
    dep
)
link_directories("${PDM_LLVM_INSTALL_DIR}/lib/")

# preparing to link llvm
# - see: https://github.com/MWGuy/llvm-hello/blob/master/CMakeLists.txt
add_definitions(${LLVM_DEFINITIONS})
add_definitions(${CLANG_DEFINITIONS})

# set(LLVM_ENABLE_PROJECTS "clang;clang-tools-extra;compiler-rt")
llvm_map_components_to_libnames(
    llvm_libs
    Core ExecutionEngine Interpreter MCJIT Support nativecodegen IRReader
)

# adding 'pdm': core library for compiler, other tools:
add_library(pdm STATIC
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

        src/pdm/ast/pattern/base-field.hh
    src/pdm/ast/pattern/lpattern.hh
    src/pdm/ast/pattern/tpattern.hh
    src/pdm/ast/pattern/vpattern.hh

    src/pdm/ast/source-node/i-source-node.hh
    src/pdm/ast/source-node/script.cc
    src/pdm/ast/source-node/script.hh
    src/pdm/ast/source-node/package.hh

    src/pdm/ast/stmt/stmt.hh
    src/pdm/ast/stmt/builtin.cc
    src/pdm/ast/stmt/builtin.hh
    src/pdm/ast/stmt/const.hh
    src/pdm/ast/stmt/discard.hh
    src/pdm/ast/header/extern_stmt.hh
    src/pdm/ast/stmt/set.hh
    src/pdm/ast/stmt/mod_val.hh
    src/pdm/ast/stmt/mod_enum.hh
    src/pdm/ast/stmt/mod_type.hh
    src/pdm/ast/stmt/mod_typeclass.hh
    src/pdm/ast/stmt/using.hh
    src/pdm/ast/stmt/val.hh
    src/pdm/ast/stmt/var.hh
    src/pdm/ast/stmt/vax.hh

    src/pdm/ast/arg/targ.hh
    src/pdm/ast/arg/varg.hh

    src/pdm/ast/header/import_stmt.hh
    src/pdm/ast/header/import_stmt.cc

    src/pdm/ast/type_spec/type_spec.cc
    src/pdm/ast/type_spec/type_spec.hh
    src/pdm/ast/class_spec/class_spec.cc
    src/pdm/ast/class_spec/class_spec.hh
    src/pdm/ast/type_spec/fn.hh
    src/pdm/ast/type_spec/id.hh
    src/pdm/ast/class_spec/id.hh
    src/pdm/ast/type_spec/struct.hh

    src/pdm/ast/module/native-mod-exp.hh
    src/pdm/ast/module/mod-address.hh
    src/pdm/ast/module/base-mod-exp.hh
    src/pdm/ast/module/extern-c-mod-exp.hh
    src/pdm/ast/module/pkg-bundle-mod-exp.hh

    src/pdm/compiler/compiler.cc
    src/pdm/compiler/compiler.hh
    src/pdm/compiler/platform.hh
    src/pdm/compiler/platform.cc

    src/pdm/core/bitsets.hh
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
    src/pdm/source/i-source.hh
    src/pdm/source/local-script-source.hh
    src/pdm/source/local-package-source.hh
    src/pdm/source/source-kind.hh

    src/pdm/types/manager.cc
    src/pdm/types/manager.hh
    src/pdm/types/typeop-result.hh
    src/pdm/types/var-invariant.cc
    src/pdm/types/var-invariant.hh
    src/pdm/types/type.cc
    src/pdm/types/type.hh
    src/pdm/types/kind.hh
    src/pdm/types/var.cc
    src/pdm/types/var.hh
    src/pdm/types/var-archetype.hh
    src/pdm/types/relation.hh
    src/pdm/types/relation.cc
    src/pdm/types/solve_result.hh
    src/pdm/types/kdvs.cc
    src/pdm/types/kdvs.hh
    src/pdm/types/type-trie.hh

    src/pdm/typer/typer.cc
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
    src/pdm/parser/package-parser.cc

    src/pdm/printer/printer.cc
    src/pdm/printer/printer.hh

    src/pdm/dependency-dispatcher/dependency-dispatcher.cc
    src/pdm/dependency-dispatcher/dependency-dispatcher.hh

    src/pdm/emitter/llvm-emitter.hh

    src/pdm/ast/type_spec/mai.hh
    src/pdm/ast/type_spec/enum.hh
    src/pdm/ast/type_spec/struct.hh
    src/pdm/ast/class_spec/class_exp.hh
    src/pdm/ast/class_spec/mai.hh
    src/pdm/ast/type_spec/array.hh

    src/pdm/emitter/llvm-emitter.cc

    # adding utf8proc as a source-level dependency
    # WARNING: volatile! may change as utf8proc changes,
    #   we should eliminate this dependency ASAP.
    dep/utf8proc/utf8proc.c
    dep/utf8proc/utf8proc.h
        src/pdm/ast/pattern/lpattern.cc src/pdm/ast/pattern/vpattern.cc src/pdm/ast/pattern/tpattern.cc src/pdm/ast/module/base-mod-exp.cc src/pdm/ast/exp/binary.cc src/pdm/ast/exp/unary.cc)

target_link_libraries(pdm PUBLIC
    ${llvm_libs} 
    libclang
)
target_include_directories(pdm PRIVATE
    "${LLVM_INCLUDE_DIRS}"
    "${CLANG_INCLUDE_DIRS}"
)
# WARNING: C++20 introduces reversed comparison operators that create a compile-time
# error in LLVM.
# see: https://stackoverflow.com/questions/60386792/c20-comparison-warning-about-ambiguous-reversed-operator
# thus, CXX standard must be set ONLY for our source code.
set_property(TARGET pdm PROPERTY CXX_STANDARD 20)
set_property(TARGET pdm PROPERTY C_STANDARD   11)
# set_property(TARGET pdm PROPERTY CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g")

# target_link_libraries(pdm PRIVATE utf8proc)

# 'porch' => *Pdm Orch*estrator.
# connotes an entryway to a larger building/home.
add_executable(
    porch
    src/porch/main.cc
    src/porch/typer_demo.cc
    src/porch/typer_demo.hh
    src/porch/feedback_demo.cc
    src/porch/feedback_demo.hh
)
add_definitions(
    ${LLVM_DEFINITIONS}
    ${CLANG_DEFINITIONS}
)
target_link_libraries(porch PRIVATE
    pdm
)
set_property(TARGET porch PROPERTY CXX_STANDARD 20)
set_property(TARGET porch PROPERTY C_STANDARD   11)

#
#
# Other Resources:
#
#

# - https://lowlevelbits.org/building-an-llvm-based-tool.-lessons-learned/
# - https://llvm.org/docs/CMake.html#embedding-llvm-in-your-project
