cmake_minimum_required(VERSION 3.0.0)
project(email VERSION 0.1.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/lib/catch")
include(CTest)
include(Catch)

include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/lib/asio/include
)

add_subdirectory(lib/catch)
add_subdirectory(src)
add_subdirectory(test)