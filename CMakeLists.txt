set(CMAKE_MINIMUM_REQUIRED_VERSION 3.18.2)

project(pandemonium)

add_executable(pc
    src/ast.c
    src/ast.h
    src/config.h
    src/lexer.c
    src/lexer.h
    src/main.c
    src/parser.c
    src/parser.h
    src/scoper.c
    src/scoper.h
    src/source.c
    src/source.h
    src/symbols.c
    src/symbols.h
    src/typer.c
    src/typer.h
    src/useful.h
)

#
# Intern library:
#

add_subdirectory(src/intern)
target_link_libraries(pc 
    intern
)