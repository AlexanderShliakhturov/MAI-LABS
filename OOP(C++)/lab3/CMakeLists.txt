cmake_minimum_required(VERSION 3.10)
project(Lab3)

add_compile_options(-Wall -g)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

file(GLOB_RECURSE INCLUDES LIST_DIRECTORIES false ${INCLUDE_DIR}/*.hpp)
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false ${SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false ${TEST_DIR}/*.cpp)

#
#LIBRARY WITH COMMON FUNCTIONS
#

add_library(${PROJECT_NAME}_lib
            ${SOURCES}
            ${INCLUDES})            

set_target_properties(${PROJECT_NAME}_lib PROPERTIES
                      CXX_STANDARD 20
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)

#
#PROJECT ITSELF
#

add_executable(${PROJECT_NAME}_exe
                ${CMAKE_CURRENT_SOURCE_DIR}/run.cpp)

set_target_properties(${PROJECT_NAME}_exe PROPERTIES
                CXX_STANDARD 20
                CXX_STANDARD_REQUIRED YES
                CXX_EXTENSIONS NO)

add_dependencies(${PROJECT_NAME}_exe ${PROJECT_NAME}_lib)
target_link_libraries(${PROJECT_NAME}_exe ${PROJECT_NAME}_lib)

#
#DOWNLOAD AND ADD GOOGLETEST TO BUILD
#

configure_file(configs/CMakeLists.txt.gtest.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
          RESULT_VARIABLE result
          WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if(result)
message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
          RESULT_VARIABLE result
          WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if(result)
message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
           ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
           EXCLUDE_FROM_ALL)

#POINT TESTS

add_executable(${PROJECT_NAME}_point_tests
               ${CMAKE_CURRENT_SOURCE_DIR}/tests/point_tests.cpp)

set_target_properties(${PROJECT_NAME}_point_tests PROPERTIES
                      CXX_STANDARD 20
                      CXX_STANDARD_REQUIRED YES)

target_include_directories(${PROJECT_NAME}_point_tests PRIVATE
                           "${PROJECT_SOURCE_DIR}/src"
                           "${CMAKE_CURRENT_BINARY_DIR}/googletest-src"
                           "${CMAKE_CURRENT_BINARY_DIR}/googletest-src/include")

add_dependencies(${PROJECT_NAME}_point_tests ${PROJECT_NAME}_lib)
target_link_libraries(${PROJECT_NAME}_point_tests ${PROJECT_NAME}_lib gtest_main)

#
#RECTANGLE TESTS
#

add_executable(${PROJECT_NAME}_rectangle_tests
               ${CMAKE_CURRENT_SOURCE_DIR}/tests/rectangle_tests.cpp)

set_target_properties(${PROJECT_NAME}_rectangle_tests PROPERTIES
                      CXX_STANDARD 20
                      CXX_STANDARD_REQUIRED YES)

target_include_directories(${PROJECT_NAME}_rectangle_tests PRIVATE
                           "${PROJECT_SOURCE_DIR}/src"
                           "${CMAKE_CURRENT_BINARY_DIR}/googletest-src"
                           "${CMAKE_CURRENT_BINARY_DIR}/googletest-src/include")

add_dependencies(${PROJECT_NAME}_rectangle_tests ${PROJECT_NAME}_lib)
target_link_libraries(${PROJECT_NAME}_rectangle_tests ${PROJECT_NAME}_lib gtest_main)

#
#SQUARE TESTS
#

add_executable(${PROJECT_NAME}_square_tests
               ${CMAKE_CURRENT_SOURCE_DIR}/tests/square_tests.cpp)

set_target_properties(${PROJECT_NAME}_square_tests PROPERTIES
                      CXX_STANDARD 20
                      CXX_STANDARD_REQUIRED YES)

target_include_directories(${PROJECT_NAME}_square_tests PRIVATE
                           "${PROJECT_SOURCE_DIR}/src"
                           "${CMAKE_CURRENT_BINARY_DIR}/googletest-src"
                           "${CMAKE_CURRENT_BINARY_DIR}/googletest-src/include")

add_dependencies(${PROJECT_NAME}_square_tests ${PROJECT_NAME}_lib)
target_link_libraries(${PROJECT_NAME}_square_tests ${PROJECT_NAME}_lib gtest_main)

#

#
#VECTOR TESTS
#

add_executable(${PROJECT_NAME}_vector_tests
               ${CMAKE_CURRENT_SOURCE_DIR}/tests/vector_tests.cpp)

set_target_properties(${PROJECT_NAME}_vector_tests PROPERTIES
                      CXX_STANDARD 20
                      CXX_STANDARD_REQUIRED YES)

target_include_directories(${PROJECT_NAME}_vector_tests PRIVATE
                           "${PROJECT_SOURCE_DIR}/src"
                           "${CMAKE_CURRENT_BINARY_DIR}/googletest-src"
                           "${CMAKE_CURRENT_BINARY_DIR}/googletest-src/include")

add_dependencies(${PROJECT_NAME}_vector_tests ${PROJECT_NAME}_lib)
target_link_libraries(${PROJECT_NAME}_vector_tests ${PROJECT_NAME}_lib gtest_main)