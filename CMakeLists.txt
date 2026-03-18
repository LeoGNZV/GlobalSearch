cmake_minimum_required(VERSION 3.5) #Проверка версии CMake.

set(PROJECT_NAME GS1) #Создаем обычную локальную переменную с именем проекта
project(${PROJECT_NAME}) # Название проекта, решения

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE) #Создается переменная CMAKE_CONFIGURATION_TYPES со значением "Debug;Release" и меткой/разделом Configs, переменная сохраниется в специальном файле доступном из всех файлов,

if(NOT CMAKE_BUILD_TYPE) # проверка имеющихся у компилятора вариантов сборки
  set(CMAKE_BUILD_TYPE Release) #Если нет то устанавливаем Release
endif()

# Пути для поизаголовочных файлов
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Поиск MPI
find_package(MPI REQUIRED)

# Вывод информации о найденном MPI для отладки
message(STATUS "MPI_CXX_INCLUDE_PATH: ${MPI_CXX_INCLUDE_PATH}")
message(STATUS "MPI_CXX_LIBRARIES: ${MPI_CXX_LIBRARIES}")

add_subdirectory(Projects/One-dimensional) #Добавляем директорию с под-CMakeList-ом, и выполняем под-CMakeList
add_subdirectory(Projects/Multidimensional)
add_subdirectory(Projects/ParallelMultidimensional)