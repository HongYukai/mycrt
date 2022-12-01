file(GLOB LIB_SOURCES "*.c")

add_library(Mycrt ${LIB_SOURCES})

target_include_directories(Mycrt PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

