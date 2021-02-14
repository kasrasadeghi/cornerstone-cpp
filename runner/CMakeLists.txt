set(TARGET_NAME runner)
set(EXEC_NAME "${TARGET_NAME}")

# collect sources
set("${TARGET_NAME}_src" "")
aux_source_directory(${CMAKE_CURRENT_LIST_DIR} "${TARGET_NAME}_src")

# create exec
add_executable(${EXEC_NAME} "${${TARGET_NAME}_src}")

# add cornerstone lib
target_link_libraries(${EXEC_NAME} cornerstonelib_debug)
target_include_directories(${EXEC_NAME} PUBLIC ${PROJECT_ROOT}/lib)

# add backbone lib
target_link_libraries(${EXEC_NAME} backbone_debug)
target_include_directories(${EXEC_NAME} PUBLIC ${PROJECT_ROOT}/backbone)
