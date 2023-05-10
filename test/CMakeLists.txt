add_executable(TokenReaderTest TokenReaderTest.cpp)
target_link_libraries(TokenReaderTest PRIVATE TokenReader Catch2::Catch2)

add_executable(SmtpParserTest SmtpParserTest.cpp)
target_link_libraries(SmtpParserTest PRIVATE SmtpParser Catch2::Catch2 wsock32 ws2_32)