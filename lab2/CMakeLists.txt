project(lab2 VERSION 0.1.0 LANGUAGES C CXX)
add_executable(lab2 ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cxx)
target_link_libraries(lab2 PRIVATE goya)
