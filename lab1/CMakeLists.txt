project(lab1 VERSION 0.1.0)
add_executable(lab1 ${CMAKE_CURRENT_SOURCE_DIR} src/main.cxx)
target_link_libraries(lab1 PRIVATE goya)
