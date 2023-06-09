project(catch)

add_library(catch catch_amalgamated.hpp catch_amalgamated.cpp)
add_library(Catch2::Catch2 ALIAS catch)

target_include_directories(catch PUBLIC
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)