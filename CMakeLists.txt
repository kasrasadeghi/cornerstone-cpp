cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME "cornerstone")
set(PROJECT_ROOT ${CMAKE_CURRENT_LIST_DIR})

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wfatal-errors")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(lib)
add_subdirectory(backbone)

if (GTEST)
  add_subdirectory(test)
else (GTEST)
  add_subdirectory(driver)
  add_subdirectory(matcher)
  add_subdirectory(parser)
  add_subdirectory(select)
  add_subdirectory(runner)
  add_subdirectory(bbfmt)
  add_subdirectory(plumber)
endif (GTEST)

add_subdirectory(tester)
