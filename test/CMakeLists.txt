add_executable(SmtpParserTest SmtpParserTest.cpp)
target_link_libraries(SmtpParserTest SmtpParser Catch2::Catch2 ssl crypto)
if(WIN32)
  target_link_libraries(SmtpParserTest wsock32 ws2_32)
endif()
catch_discover_tests(SmtpParserTest TEST_PREFIX SmtpParserTest_)

add_executable(ConfigParserTest ConfigParserTest.cpp)
target_link_libraries(ConfigParserTest ConfigParser Catch2::Catch2)
catch_discover_tests(ConfigParserTest TEST_PREFIX ConfigParserTest_)