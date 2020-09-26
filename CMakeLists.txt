cmake_minimum_required(VERSION 3.18)
project(pandemonium)

#
# Adding LLVM and Clang as dependencies:
#

# RESOURCES:
# - https://lowlevelbits.org/building-an-llvm-based-tool.-lessons-learned/
# - https://llvm.org/docs/CMake.html#embedding-llvm-in-your-project

# set (LLVM_DIR ${PATH_TO_LLVM_PROJECT}/llvm/cmake/modules)
# find_package(
#     LLVM REQUIRED CONFIG
#     NO_DEFAULT_PATH
# )

find_package(LLVM REQUIRED CONFIG)
# find_package(Clang REQUIRED CONFIG)

message(STATUS "... Found LLVM version (${LLVM_PACKAGE_VERSION})")
message(STATUS "... Using LLVMConfig.cmake in: ${LLVM_DIR}")

# message(STATUS "... Found LLVM ${LLVM_PACKAGE_VERSION}")
# message(STATUS "... Using LLVMConfig.cmake in: ${LLVM_DIR}")

# set (LLVM_ENABLE_PROJECTS "clang;clang-tools-extra;compiler-rt;libc")
# set (CMAKE_CURRENT_BINARY_DIR "build")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g")

include_directories("/usr/local/Cellar/llvm/10.0.1_1/include/")
add_definitions(${LLVM_DEFINITIONS})
add_executable(pc
    src/ast.c
    src/ast.h
    src/cgen.c
    src/cgen.h
    src/checker.c
    src/checker.h
    src/code-printer.c
    src/code-printer.h
    src/config.h
    src/debugger.c
    src/debugger.h
    src/interp.c
    src/interp.h
    src/lexer.c
    src/lexer.h
    src/main.c
    src/parser.c
    src/parser.h
    src/primer.c
    src/primer.h
    src/source.c
    src/source.h
    src/symbols.c
    src/symbols.h
    src/typer.c
    src/typer.h
    src/useful.h
)

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
target_link_libraries(pc
    intern
)
