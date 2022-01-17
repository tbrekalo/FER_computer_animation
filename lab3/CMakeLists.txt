set(${PROJECT_NAME}_LIB_SRC
  src/icarus/camera.cxx
  src/icarus/hit.cxx
  src/icarus/image.cxx
  src/icarus/material.cxx
  src/icarus/ray.cxx
  src/icarus/sphere.cxx
  src/icarus/triangle.cxx
  src/icarus/vector.cxx 
)

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_LIB_SRC})
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

set_default_warnings(${PROJECT_NAME} PRIVATE FALSE)

add_executable(
  lab3
    src/main.cxx
)

target_link_libraries(${PROJECT_NAME}_exe PRIVATE ${PROJECT_NAME})
