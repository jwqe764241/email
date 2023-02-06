set(SOURCES main.cpp)

set(CMAKE_CXX_STANDARD 14)

add_definitions(-DASIO_STANDALONE)

add_executable(email ${SOURCES})
