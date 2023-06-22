set(SOURCES 
  main.cpp 
  Server/Server.cpp 
  Server/Connection.cpp 
  Server/ConnectionContext.cpp
  Smtp/SmtpParser.cpp
  Smtp/TokenReader.cpp
  Smtp/Token.cpp
  Smtp/HeloCommand.cpp
  Smtp/MailCommand.cpp
  Smtp/RcptCommand.cpp
  Smtp/DataCommand.cpp
  Smtp/QuitCommand.cpp
  Smtp/NoopCommand.cpp
  Smtp/RsetCommand.cpp
  State/StateMachine.cpp
  State/StateTransition.cpp
  State/State.cpp
  State/StateTable.cpp)

set(CMAKE_CXX_STANDARD 14)

add_definitions(-DASIO_STANDALONE)

add_executable(email ${SOURCES})

if(WIN32)
  target_link_libraries(email wsock32 ws2_32)
endif()

#libraries for tests
add_library(TokenReader STATIC 
  Smtp/TokenReader.cpp 
  Smtp/Token.cpp)

add_library(SmtpParser STATIC 
  Smtp/SmtpParser.cpp 
  Smtp/TokenReader.cpp 
  Smtp/Token.cpp 
  Smtp/HeloCommand.cpp
  Smtp/MailCommand.cpp
  Smtp/RcptCommand.cpp
  Smtp/DataCommand.cpp
  Smtp/QuitCommand.cpp
  Smtp/NoopCommand.cpp
  Smtp/RsetCommand.cpp
  Server/ConnectionContext.cpp)