cmake_minimum_required(VERSION 3.16)
project(pandemonium)

#
# Adding LLVM and Clang as dependencies:
#

# RESOURCES:
# - https://lowlevelbits.org/building-an-llvm-based-tool.-lessons-learned/
# - https://llvm.org/docs/CMake.html#embedding-llvm-in-your-project
# - todo: load source by adding dirs to 'CMAKE_MODULE_PATH' http://wiki.icub.org/wiki/CMake_and_FIND_PACKAGE

find_package(LLVM REQUIRED CONFIG)
# find_package(Clang REQUIRED CONFIG)

message(STATUS "... Found LLVM version (${LLVM_PACKAGE_VERSION})")
message(STATUS "... Using LLVMConfig.cmake in: ${LLVM_DIR}")
message(STATUS "... Add '/usr/local/Cellar/llvm/10.0.1_1/include/' to your IDE include path list for LLVM C API auto-complete.")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g")

# todo: change this path for different platforms
include_directories("/usr/local/Cellar/llvm/10.0.1_1/include/")
add_definitions(${LLVM_DEFINITIONS})
add_executable(pc
    src/ast.c
    src/ast.h
    src/checker.c
    src/checker.h
    src/code-printer.c
    src/code-printer.h
    src/config.h
    src/debugger.c
    src/debugger.h
    src/extra-tokens.h
    src/interp.c
    src/interp.h
    src/lexer.c
    src/lexer.h
    src/llvm-emitter.c
    src/llvm-emitter.h
    src/main.c
    src/parser.h
    src/parser.tab.c
    src/parser.tab.h
    src/primer.c
    src/primer.h
    src/source.c
    src/source.h
    src/symbols.c
    src/symbols.h
    src/typer.c
    src/typer.h
    src/unicoder.c
    src/unicoder.h
    src/useful.c
    src/useful.h
    src/values.h
)

#
# WIP C++ rewrite
#
include_directories(
    "src"
)
add_library(
    pdm
    src/pdm/ast/ast.cc
    src/pdm/ast/ast.hh
    src/pdm/ast/kind.hh
    src/pdm/ast/node.hh
    src/pdm/ast/visitor.cc
    src/pdm/ast/visitor.hh
    src/pdm/common/ints.hh
    src/pdm/source/loc.hh
    src/pdm/source/source.hh
    src/pdm/source/span.hh
    src/pdm/typer/constraint.hh
    src/pdm/typer/rule.hh
    src/pdm/typer/soln.cc
    src/pdm/typer/soln.hh
    src/pdm/typer/type.cc
    src/pdm/typer/type.hh
    src/pdm/typer/typer.cc
    src/pdm/typer/typer.hh
)
add_executable(
    pdm_cli
    src/pdm_cli/main.cc
)
target_link_libraries(pdm_cli pdm)

#
# LLVM
# - see: https://github.com/MWGuy/llvm-hello/blob/master/CMakeLists.txt
#

# target_link_libraries(pc LLVM)
# target_include_directories(pc PUBLIC "${LLVM_INCLUDE_DIRS}")
# target_link_libraries(pc LLVMSupport clangTooling)

# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs Core ExecutionEngine Interpreter MCJIT Support nativecodegen IRReader)

# Link against LLVM libraries
target_link_libraries(pc ${llvm_libs})

#
# Intern library:
#

add_subdirectory(src/intern)
target_link_libraries(pc intern)

#
# utf8proc - Unicode support
#

add_library(utf8proc
    src/utf8proc/utf8proc.c
    src/utf8proc/utf8proc.h
)
target_link_libraries(pc utf8proc)

set_property(TARGET pdm PROPERTY CXX_STANDARD 20)
