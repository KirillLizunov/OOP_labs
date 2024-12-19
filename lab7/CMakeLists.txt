cmake_minimum_required(VERSION 3.10)
project(Lab_7)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Проверка компилятора и включение корутин
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines -Werror=maybe-uninitialized")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -fcoroutines-ts")
endif()

# Настройка флагов для Windows, если требуется
if (WIN32)
    set(THREADS_PREFER_PTHREAD_FLAG OFF)
endif()

# Подключение Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Включение директорий для поиска заголовочных файлов
include_directories(${GTEST_INCLUDE_DIRS} include)

# Создание библиотеки проекта из исходных файлов
add_library(${CMAKE_PROJECT_NAME}_lib
    src/npc.cpp
    src/npcfactory.cpp
    src/observer.cpp
    src/orc.cpp
    src/robber.cpp
    src/visitor.cpp
    src/werewolf.cpp
    src/logger.cpp
    src/scheduler.cpp
)

# Убедитесь, что библиотека проекта поддерживает корутины
target_compile_options(${CMAKE_PROJECT_NAME}_lib PRIVATE -fcoroutines)

# Создание основного исполняемого файла
add_executable(${CMAKE_PROJECT_NAME}.exe main.cpp)

# Связывание основного исполняемого файла с библиотекой проекта и pthread
target_link_libraries(${CMAKE_PROJECT_NAME}.exe PRIVATE ${CMAKE_PROJECT_NAME}_lib pthread)

# Создание исполняемого файла для тестов
add_executable(tests tests/tests.cpp)

# Связывание тестового исполняемого файла с библиотекой проекта и Google Test
target_link_libraries(tests PRIVATE ${CMAKE_PROJECT_NAME}_lib gtest_main pthread)

# Включение тестирования
enable_testing()

# Добавление тестов в тестовый набор
add_test(NAME MyProjectTests COMMAND tests)

# cmake ..
# make
# ./tests
# ./Lab_7.exe