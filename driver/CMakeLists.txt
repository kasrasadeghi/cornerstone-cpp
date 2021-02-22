set(TARGET_NAME driver)
set(EXEC_NAME "${PROJECT_NAME}")

# collect sources
set("${TARGET_NAME}_src" "")
aux_source_directory(${CMAKE_CURRENT_LIST_DIR} "${TARGET_NAME}_src")


# create release
add_executable(${EXEC_NAME} "${${TARGET_NAME}_src}")
target_compile_options(${EXEC_NAME} PRIVATE -O3)

#   add cornerstone lib
target_link_libraries(${EXEC_NAME} cornerstonelib)
target_include_directories(${EXEC_NAME} PUBLIC ${PROJECT_ROOT}/lib)

#   add backbone lib
target_link_libraries(${EXEC_NAME} backbone)
target_include_directories(${EXEC_NAME} PUBLIC ${PROJECT_ROOT}/backbone)


# switch to debug
set(EXEC_NAME "${EXEC_NAME}_debug")

# create debug exec
add_executable(${EXEC_NAME} "${${TARGET_NAME}_src}")
target_compile_options(${EXEC_NAME} PRIVATE -g -O0)

#   add cornerstone lib
target_link_libraries(${EXEC_NAME} cornerstonelib_debug)
target_include_directories(${EXEC_NAME} PUBLIC ${PROJECT_ROOT}/lib)

#   add backbone lib
target_link_libraries(${EXEC_NAME} backbone_debug)
target_include_directories(${EXEC_NAME} PUBLIC ${PROJECT_ROOT}/backbone)
