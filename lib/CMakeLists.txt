include_directories(${CMAKE_CURRENT_LIST_DIR})

set(LIB_NAME "${PROJECT_NAME}lib")

# gather sources
set(lib_src "")
aux_source_directory(${CMAKE_CURRENT_LIST_DIR} lib_src)

# release library
add_library(${LIB_NAME} STATIC ${lib_src})
target_compile_options(${LIB_NAME} PRIVATE -O3)

# switch to debug
set(LIB_NAME "${LIB_NAME}_debug")

# debug library
add_library(${LIB_NAME} STATIC ${lib_src})
target_compile_options(${LIB_NAME} PRIVATE -g -O0)
