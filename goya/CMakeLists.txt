cmake_minimum_required(VERSION 3.19)
project(goya LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

include(cmake/Warnings.cmake)

find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)
find_package(GLEW REQUIRED)

set(${PROJECT_NAME}_SOURCES
  src/goya/b_spline.cxx
  src/goya/camera.cxx
  src/goya/drawable.cxx
  src/goya/engine.cxx
  src/goya/events.cxx
  src/goya/mesh_loader.cxx
  src/goya/mesh_obj_data.cxx
  src/goya/mesh.cxx
  src/goya/model.cxx
  src/goya/particles.cxx
  src/goya/primitives.cxx
  src/goya/shader.cxx
  src/goya/window.cxx
)

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC include)

set_default_warnings(${PROJECT_NAME} PRIVATE FALSE)
target_link_libraries(${PROJECT_NAME} 
  PUBLIC 
    OpenGL::GL Threads::Threads GLEW::GLEW glfw glm)
