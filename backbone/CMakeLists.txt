set(TARGET_NAME backbone)
set(LIB_NAME ${TARGET_NAME})

# collect sources
set("${TARGET_NAME}_src" "")
aux_source_directory(${CMAKE_CURRENT_LIST_DIR} "${TARGET_NAME}_src")

# add library target
add_library(${LIB_NAME} STATIC "${${TARGET_NAME}_src}")
target_link_libraries(${LIB_NAME} cornerstonelib)
target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_ROOT}/lib)

# add debug library target
add_library(${LIB_NAME}_debug STATIC "${${TARGET_NAME}_src}")
target_link_libraries(${LIB_NAME}_debug cornerstonelib_debug)
target_include_directories(${LIB_NAME}_debug PUBLIC ${PROJECT_ROOT}/lib)
target_compile_options(${LIB_NAME}_debug PRIVATE -g)
