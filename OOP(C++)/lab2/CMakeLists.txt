#указываю минимальную версию cmake, необходимую для сборки 
cmake_minimum_required(VERSION 3.0)  
# задаю имя своей сборки/проекта
project(lab2)
# устанавливаю стандарт с++ для компиляции исходников
set(CMAKE_CXX_STANDARD 17)
# требую, чтобы стандарт указанный в CMAKE_CXX_STANDARD был обязательным
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# добавление опций компилятору; -g добавляю отладочную информацию; -rdynamic опция для линкера, не знаю зачем;
# add_compile_options(-g -rdynamic)

add_subdirectory(lib/googletest)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

include_directories(${INCLUDE_DIR})



# GLOB_RECURSE - мы хотим выполнить поиск файлов с рекурсивным обходом подкаталогов;
# SOURCES - переменная;
# LIST_DIRECTORIES false - показывает, что в SOURCES не должны включаться каталоги, в которых были найдены файлы;
# /*.cpp - шаблон для поиска всех файлов с расширением .cpp;

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false ${SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false ${TEST_DIR}/*.cpp)

# создает библиотеку из исходников, находящихся в src
add_library(${CMAKE_PROJECT_NAME}_lib ${SOURCES})

# создаю исполняемый файл на основе main.cpp
add_executable(${CMAKE_PROJECT_NAME}_exe task.cpp)

# создаю исполняемый файл для тестов
add_executable(${CMAKE_PROJECT_NAME}_test ${TEST_SOURCES})

# установка зависимостей, в данном случае показываю, что исполняемый файл зависит от библиотеки(PRIVATE-библиотеки видимы только для цели)
target_link_libraries(${CMAKE_PROJECT_NAME}_exe PRIVATE ${CMAKE_PROJECT_NAME}_lib)
# показываю, где искать заголовочные файлы при компиляции цели
target_include_directories(${CMAKE_PROJECT_NAME}_test PRIVATE ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
# добавляю библиотеки в зависимости цели, то есть исполняемого файла юнит тестов
target_link_libraries(${CMAKE_PROJECT_NAME}_test PRIVATE ${CMAKE_PROJECT_NAME}_lib gtest gtest_main)

add_test(NAME BASIC COMMAND tests2)