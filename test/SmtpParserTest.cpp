#include <catch_amalgamated.hpp>

#include "Smtp/SmtpParser.hpp"

TEST_CASE("Smtp parser can parse HELO command") {
  SmtpParser parser;
  std::shared_ptr<SmtpCommand> parsedCommand = parser.parse("HELO aaa.example.com");
  REQUIRE(parsedCommand != nullptr);

  HeloCommand* heloCommand = static_cast<HeloCommand*>(parsedCommand.get());
  REQUIRE(heloCommand->getCommandId() == SmtpCommandId::Helo);
  REQUIRE(heloCommand->getDomain() == "aaa.example.com");
}

TEST_CASE("Smtp parser can parse MAIL command") {
  SmtpParser parser;
  std::shared_ptr<SmtpCommand> parsedCommand = parser.parse("MAIL FROM:<example@example.com>");
  REQUIRE(parsedCommand != nullptr);

  MailCommand* mailCommand = static_cast<MailCommand*>(parsedCommand.get());
  REQUIRE(mailCommand->getCommandId() == SmtpCommandId::Mail);
  REQUIRE(mailCommand->getOriginator() == "example@example.com");
}