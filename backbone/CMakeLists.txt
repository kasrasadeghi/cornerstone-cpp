set(TARGET_NAME backbone)
set(LIB_NAME ${TARGET_NAME})

# collect sources
set("${TARGET_NAME}_src" "")
aux_source_directory(${CMAKE_CURRENT_LIST_DIR} "${TARGET_NAME}_src")

# add library target
add_library(${LIB_NAME} STATIC "${${TARGET_NAME}_src}")
target_link_libraries(${LIB_NAME} cornerstonelib)
target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_ROOT}/lib)
target_compile_options(${LIB_NAME} PRIVATE -O3)

# switch to debug
set(LIB_NAME "${LIB_NAME}_debug")

# add debug library target
add_library(${LIB_NAME} STATIC "${${TARGET_NAME}_src}")
target_link_libraries(${LIB_NAME} cornerstonelib_debug)
target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_ROOT}/lib)
target_compile_options(${LIB_NAME} PRIVATE -g -O0)
