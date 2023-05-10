cmake_minimum_required(VERSION 3.0.0)
project(email VERSION 0.1.0)

include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/lib/asio/include
)

add_subdirectory(src)
add_subdirectory(lib/catch)
add_subdirectory(test)