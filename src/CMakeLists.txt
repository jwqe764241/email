set(SOURCES 
  main.cpp 
  Server/Server.cpp 
  Server/Connection.cpp 
  Server/ConnectionContext.cpp
  Server/SecuredStream.cpp
  Smtp/SmtpParser.cpp
  Smtp/HeloCommand.cpp
  Smtp/EhloCommand.cpp
  Smtp/MailCommand.cpp
  Smtp/RcptCommand.cpp
  Smtp/DataCommand.cpp
  Smtp/QuitCommand.cpp
  Smtp/NoopCommand.cpp
  Smtp/RsetCommand.cpp
  Smtp/StartTlsCommand.cpp
  State/StateMachine.cpp
  State/StateTransition.cpp
  State/State.cpp
  State/StateTable.cpp)

set(CMAKE_CXX_STANDARD 14)

add_definitions(-DASIO_STANDALONE)

add_executable(email ${SOURCES})

target_link_libraries(email ssl crypto)

if(WIN32)
  target_link_libraries(email wsock32 ws2_32)
endif()




#libraries for tests
add_library(SmtpParser STATIC 
  Server/SecuredStream.cpp
  Smtp/SmtpParser.cpp 
  Smtp/HeloCommand.cpp
  Smtp/EhloCommand.cpp
  Smtp/MailCommand.cpp
  Smtp/RcptCommand.cpp
  Smtp/DataCommand.cpp
  Smtp/QuitCommand.cpp
  Smtp/NoopCommand.cpp
  Smtp/RsetCommand.cpp
  Smtp/StartTlsCommand.cpp
  Server/ConnectionContext.cpp)