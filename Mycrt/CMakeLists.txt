file(GLOB LIB_SOURCES "*.c")

add_compile_options(-m32 -fno-builtin -nostdlib -fno-stack-protector -g)

add_library(Mycrt STATIC ${LIB_SOURCES})

target_include_directories(Mycrt PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

