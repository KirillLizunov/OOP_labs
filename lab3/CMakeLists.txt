cmake_minimum_required(VERSION 3.10)
project(Lab_3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавление опций компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

# Установка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  TLS_VERIFY false
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Добавление библиотеки с реализацией классов фигур
add_library(${CMAKE_PROJECT_NAME}_lib
    src/Square.cpp
    src/Rectangle.cpp
    src/Trapezoid.cpp
    src/Figure.cpp
    src/ShapeArray.cpp
)

# Главный исполняемый файл
add_executable(${CMAKE_PROJECT_NAME}.exe main.cpp)

# Линковка библиотеки с фигурами к главному файлу
target_link_libraries(${CMAKE_PROJECT_NAME}.exe PRIVATE ${CMAKE_PROJECT_NAME}_lib)

# Добавление тестов
enable_testing()

# tests - команда в терминал для запуска тестов, а далее имя файла и папки  
add_executable(tests test/FiguresTest.cpp)

# Линковка библиотеки с фигурами и Google Test
target_link_libraries(tests PRIVATE ${CMAKE_PROJECT_NAME}_lib gtest_main)

# Добавление тестов в тестовый набор
add_test(NAME MyProjectTests COMMAND tests)

# cmake ..
# make
# ./tests
# ./Lab_3.exe