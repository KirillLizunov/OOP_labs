cmake_minimum_required(VERSION 3.10)

project(lab5)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключение Google Test через FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(lab5 
    main.cpp
    include/memory_resource.h
    include/list.h
    src/memory_resource.cpp
)
add_library(${CMAKE_PROJECT_NAME}_lib
    src/memory_resource.cpp
)

target_include_directories(lab5 PRIVATE include)
# Добавление тестов
enable_testing()

add_executable(tests test/test01.cpp)
target_link_libraries(tests ${CMAKE_PROJECT_NAME}_lib gtest_main)


# Добавление тестов в тестовый набор
add_test(NAME FiguresTests COMMAND tests)