cmake_minimum_required(VERSION 3.16)
project(mycrt)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(Mycrt)

#add_compile_options(-m32 -Wall -fno-builtin -nostdlib -fno-stack-protector -ggdb)
#
#add_custom_command(OUTPUT main.o COMMAND gcc -c main.c -m32 -Wall -fno-builtin -nostdlib -fno-stack-protector -ggdb )
#
#add_custom_command(OUTPUT main COMMAND gcc main.o -o main)
#
#
##set(CMAKE_EXE_LINKER_FLAGS  "-m elf_i386 -e my_crt_entry")
##SET (CMAKE_LINKER  "/usr/bin/ld")
##
##add_executable(main main.c)
##
##target_link_options(main PUBLIC -static -m32)
##
##target_link_libraries(main PUBLIC Mycrt)
#
#
#
##target_include_directories(main PUBLIC ${PROJECT_SOURCE_DIR}/Mycrt)
