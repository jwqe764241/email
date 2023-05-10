#include <catch_amalgamated.hpp>

#include "Smtp/SmtpParser.hpp"

TEST_CASE("Smtp parser can parse HELO command") {
  SmtpParser parser;
  std::unique_ptr<SmtpCommand> command = parser.parse("HELO aaa.example.com");
  HeloCommand* p = static_cast<HeloCommand*>(command.get());

  REQUIRE(p->getName() == "HELO");
  REQUIRE(p->getDomain() == "aaa.example.com");
}