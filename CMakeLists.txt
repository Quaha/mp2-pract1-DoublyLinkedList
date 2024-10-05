cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME DoublyLinkedList)
project(${PROJECT_NAME})

set(MP2_LIBRARY "${PROJECT_NAME}")
set(MP2_TESTS   "test_${PROJECT_NAME}")
set(MP2_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")

include_directories("${MP2_INCLUDE}" gtest)

# BUILD
add_subdirectory(src)
add_subdirectory(gtest)
add_subdirectory(test)
