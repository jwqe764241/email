#include <catch_amalgamated.hpp>

#include "Smtp/SmtpParser.hpp"

TEST_CASE("Smtp parser can parse HELO command")
{
    SmtpParser parser;
    std::shared_ptr<SmtpCommand> command = parser.parse("HELO a-a-a.e-x-ample.c-o-m");
    REQUIRE(command != nullptr);
    REQUIRE(command->getCommandId() == SmtpCommandId::Helo);
}

TEST_CASE("Smtp parser can parse EHLO command")
{
    SmtpParser parser;
    std::shared_ptr<SmtpCommand> command = parser.parse("EHLO a-a-a.e-x-ample.c-o-m");
    REQUIRE(command != nullptr);
    REQUIRE(command->getCommandId() == SmtpCommandId::Ehlo);
}

TEST_CASE("Smtp parser can parse MAIL command")
{
    SmtpParser parser;
    std::shared_ptr<SmtpCommand> command = parser.parse("MAIL FROM:<example@example.com>");
    REQUIRE(command != nullptr);
    REQUIRE(command->getCommandId() == SmtpCommandId::Mail);
}

TEST_CASE("Smtp parser can parse RCPT command")
{
    SmtpParser parser;
    std::shared_ptr<SmtpCommand> command = parser.parse("RCPT TO:<example@example.com");
    REQUIRE(command != nullptr);
    REQUIRE(command->getCommandId() == SmtpCommandId::Rcpt);
}

TEST_CASE("Smtp parser can parse DATA command")
{
    SmtpParser parser;
    std::shared_ptr<SmtpCommand> command = parser.parse("DATA");
    REQUIRE(command != nullptr);
    REQUIRE(command->getCommandId() == SmtpCommandId::Data);
}

TEST_CASE("Smtp parser can parse QUIT command")
{
    SmtpParser parser;
    std::shared_ptr<SmtpCommand> command = parser.parse("QUIT");
    REQUIRE(command != nullptr);
    REQUIRE(command->getCommandId() == SmtpCommandId::Quit);
}

TEST_CASE("Smtp parser can parse Noop command")
{
    SmtpParser parser;
    std::shared_ptr<SmtpCommand> command = parser.parse("NOOP");
    REQUIRE(command != nullptr);
    REQUIRE(command->getCommandId() == SmtpCommandId::Noop);
}

TEST_CASE("Smtp parser can parse Rset command")
{
    SmtpParser parser;
    std::shared_ptr<SmtpCommand> command = parser.parse("RSET");
    REQUIRE(command != nullptr);
    REQUIRE(command->getCommandId() == SmtpCommandId::Rset);
}

TEST_CASE("Smtp parser can parse StartTls command")
{
    SmtpParser parser;
    std::shared_ptr<SmtpCommand> command = parser.parse("STARTTLS");
    REQUIRE(command != nullptr);
    REQUIRE(command->getCommandId() == SmtpCommandId::StartTls);
}