cmake_minimum_required(VERSION 3.10)
project(Lab_4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавление опций компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

# Установка Google Test через FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  TLS_VERIFY false
)
# Для Windows: предотвращение переопределения настроек компилятора/линковщика родительского проекта
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Главный исполняемый файл
add_executable(${CMAKE_PROJECT_NAME}.exe main.cpp)

# Линковка библиотеки с фигурами к главному файлу
target_sources(${CMAKE_PROJECT_NAME}.exe PRIVATE ${FIGURES_HEADERS})

# Добавление тестов
enable_testing()

# tests - команда в терминал для запуска тестов, а далее имя файла и папки  
add_executable(tests tests/FigureTest.cpp)

# Линковка библиотеки с фигурами и Google Test
target_sources(tests PRIVATE ${FIGURES_HEADERS})
target_link_libraries(tests PRIVATE gtest_main)

# Добавление тестов в тестовый набор
add_test(NAME MyProjectTests COMMAND tests)

# cmake ..
# make
# ./tests
# ./Lab_4.exe