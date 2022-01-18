cmake_minimum_required(VERSION 3.19)
project(goya LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(goya)

if (LAB1 OR BUILD_ALL)
  add_subdirectory(lab1)
endif()

if (LAB2 OR BUILD_ALL)
  add_subdirectory(lab2)
endif()

if (LAB3 OR BUILD_ALL)
  add_subdirectory(lab3)
endif()
