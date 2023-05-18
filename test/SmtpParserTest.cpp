#include <catch_amalgamated.hpp>

#include "Smtp/SmtpParser.hpp"

TEST_CASE("Smtp parser can parse HELO command") {
  SmtpParser parser;
  std::shared_ptr<SmtpCommand> parsedCommand = parser.parse("HELO aaa.example.com");
  HeloCommand* heloCommand = static_cast<HeloCommand*>(parsedCommand.get());

  REQUIRE(heloCommand->getCommandId() == SmtpCommandId::Helo);
  REQUIRE(heloCommand->getDomain() == "aaa.example.com");
}