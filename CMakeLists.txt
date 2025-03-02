cmake_minimum_required(VERSION 3.14)

# Включаем модуль FetchContent
include(FetchContent)

project(MyProject)

# Настройка для Eigen
FetchContent_Declare(Eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
  GIT_TAG origin/master)
FetchContent_GetProperties(Eigen)
FetchContent_MakeAvailable(Eigen)

# Настройка для doctest
FetchContent_Declare(doctest
  GIT_REPOSITORY https://github.com/doctest/doctest.git
  GIT_TAG origin/master)
FetchContent_GetProperties(doctest)
FetchContent_MakeAvailable(doctest)

configure_file(
    ${CMAKE_SOURCE_DIR}/matrix_data.txt
    ${CMAKE_BINARY_DIR}/matrix_data.txt
    COPYONLY
)

configure_file(
    ${CMAKE_SOURCE_DIR}/test_data.txt
    ${CMAKE_BINARY_DIR}/test_data.txt
    COPYONLY
)

add_executable(main ldpc.cpp GF2.hpp functions.h)
add_executable(tests tests.cpp functions.h)

target_include_directories(main PRIVATE ${eigen_SOURCE_DIR})
target_include_directories(tests PRIVATE ${eigen_SOURCE_DIR} ${doctest_SOURCE_DIR})

# Связываем doctest с тестами
target_link_libraries(tests PRIVATE doctest::doctest)