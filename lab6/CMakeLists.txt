cmake_minimum_required(VERSION 3.10)
project(Lab_6)

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
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Подключение всех файлов в src и include
file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.h)

# Главный исполняемый файл
add_executable(${CMAKE_PROJECT_NAME}.exe main.cpp ${SOURCES} ${HEADERS})

# Линковка библиотеки к главному файлу
target_sources(${CMAKE_PROJECT_NAME}.exe PRIVATE ${HEADERS})

# Добавление тестов
enable_testing()

# tests - команда в терминал для запуска тестов, а далее имя файла и папки  
add_executable(tests tests/tests.cpp ${SOURCES} ${HEADERS})

# Линковка с Google Test
target_link_libraries(tests PRIVATE gtest_main)

# Добавление тестов в тестовый набор
add_test(NAME Lab_6_Tests COMMAND tests)

# cmake ..
# make
# ./tests
# ./Lab_6.exe