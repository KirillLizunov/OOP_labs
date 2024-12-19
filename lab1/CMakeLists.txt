cmake_minimum_required(VERSION 3.10)

project(Replacer)

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

# Проверка наличия Google Test
if(NOT gtest_SOURCE_DIR)
  message(FATAL_ERROR "Google Test not found")
endif()

# Добавление основной программы
add_executable(replacer sol.cpp main.cpp)

# Добавление тестов
enable_testing()
add_executable(tests test/test01.cpp sol.cpp)
target_link_libraries(tests gtest gtest_main)

# Добавление тестов в тестовый набор
add_test(NAME ReplacerTests COMMAND tests)
