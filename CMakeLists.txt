cmake_minimum_required(VERSION 3.16)

#
# Initializing the project:
#

# creating project, setting langs:
project(pandemonium C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g")

# finding LLVM's package:
# see: https://llvm.org/docs/CMake.html
list(APPEND CMAKE_PREFIX_PATH "dep/build-llvm/cmake/modules/CMakeFiles")
find_package(LLVM REQUIRED)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# we build llvm & clang from source in the driver script.
# the following paths are hard-coded:
set(PDM_LLVM_INCLUDE_DIR  "dep/llvm-project/llvm/include")
set(PDM_LLVM_BUILD_INCLUDE_DIR "dep/build-llvm/include")
set(PDM_CLANG_INCLUDE_DIR "dep/llvm-project/clang/include")
message("include (1): ${PDM_LLVM_INCLUDE_DIR}")

# including directories:
include_directories(
    src
    dep
)

# adding 'pdm': core library for compiler, other tools:
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

    src/pdm/ast/pattern/base_field.hh
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
)

# link pdm <- llvm
# - see: https://github.com/MWGuy/llvm-hello/blob/master/CMakeLists.txt
llvm_map_components_to_libnames(
    llvm_libs 
    Core ExecutionEngine Interpreter MCJIT Support nativecodegen IRReader
)
add_definitions(
    ${LLVM_DEFINITIONS}
    ${CLANG_DEFINITIONS}
)
target_link_libraries(pdm PRIVATE 
    ${llvm_libs} clang
)
include_directories(
    "${PDM_LLVM_INCLUDE_DIR}"
    "${PDM_LLVM_BUILD_INCLUDE_DIR}"
    "${PDM_CLANG_INCLUDE_DIR}"
    "${LLVM_INCLUDE_DIRS}"
)

message(
    "debug:\n"
    "- '${llvm_libs}'"
)

# link pdm <- intern :- C lib for interned string support
set(BUILD_STATIC ON)
add_subdirectory(dep/intern)
target_link_libraries(pdm PRIVATE intern)

# link pdm <- utf8proc :- C lib for Unicode support
add_library(utf8proc
    dep/utf8proc/utf8proc.c
    dep/utf8proc/utf8proc.h
)
target_link_libraries(pdm PRIVATE utf8proc)

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
