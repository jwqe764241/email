set(SOURCES 
main.cpp 
server.cpp 
connection.cpp)

set(CMAKE_CXX_STANDARD 14)

add_definitions(-DASIO_STANDALONE)

add_executable(email ${SOURCES})


if(WIN32)
  target_link_libraries(email wsock32 ws2_32)
endif()