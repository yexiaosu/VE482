cmake_minimum_required(VERSION 2.7)
project(ve482p1)

set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-g -Wall -Wextra -Wconversion -Werror -pedantic -Wno-unused-result")
file(GLOB SOURCE_FILES "*.c")
add_executable(mumsh P1.c builtin.c buildin.h pipe.c functions.h readline.c redirection.h constant.h execute.c signal.c var.h error.c)
add_executable(mumsh_memory_check P1.c builtin.c buildin.h pipe.c functions.h readline.c redirection.h constant.h execute.c signal.c var.h error.c)

target_compile_options(mumsh_memory_check PUBLIC -fsanitize=address,undefined,integer -fno-omit-frame-pointer)
target_link_libraries(mumsh_memory_check -fsanitize=address,undefined,integer)