#include <catch_amalgamated.hpp>

#include "Smtp/SmtpParser.hpp"

TEST_CASE("Smtp parser can parse HELO command")
{
    std::shared_ptr<SmtpCommand> command = parseSmtpCommand("HELO a-a-a.e-x-ample.c-o-m\r\n");
    REQUIRE(command != nullptr);
    REQUIRE(command->getCommandId() == SmtpCommandId::Helo);
}

TEST_CASE("Smtp parser can parse EHLO command")
{
    std::shared_ptr<SmtpCommand> command = parseSmtpCommand("EHLO a-a-a.e-x-ample.c-o-m\r\n");
    REQUIRE(command != nullptr);
    REQUIRE(command->getCommandId() == SmtpCommandId::Ehlo);
}

TEST_CASE("Smtp parser can parse MAIL command")
{
    std::shared_ptr<SmtpCommand> command = parseSmtpCommand("MAIL FROM:<example@example.com>\r\n");
    REQUIRE(command != nullptr);
    REQUIRE(command->getCommandId() == SmtpCommandId::Mail);
}

TEST_CASE("Smtp parser can parse RCPT command")
{
    std::shared_ptr<SmtpCommand> command = parseSmtpCommand("RCPT TO:<example@example.com>\r\n");
    REQUIRE(command != nullptr);
    REQUIRE(command->getCommandId() == SmtpCommandId::Rcpt);
}

TEST_CASE("Smtp parser can parse DATA command")
{
    std::shared_ptr<SmtpCommand> command = parseSmtpCommand("DATA\r\n");
    REQUIRE(command != nullptr);
    REQUIRE(command->getCommandId() == SmtpCommandId::Data);
}

TEST_CASE("Smtp parser can parse QUIT command")
{
    std::shared_ptr<SmtpCommand> command = parseSmtpCommand("QUIT\r\n");
    REQUIRE(command != nullptr);
    REQUIRE(command->getCommandId() == SmtpCommandId::Quit);
}

TEST_CASE("Smtp parser can parse Noop command")
{
    std::shared_ptr<SmtpCommand> command = parseSmtpCommand("NOOP\r\n");
    REQUIRE(command != nullptr);
    REQUIRE(command->getCommandId() == SmtpCommandId::Noop);
}

TEST_CASE("Smtp parser can parse Rset command")
{
    std::shared_ptr<SmtpCommand> command = parseSmtpCommand("RSET\r\n");
    REQUIRE(command != nullptr);
    REQUIRE(command->getCommandId() == SmtpCommandId::Rset);
}

TEST_CASE("Smtp parser can parse StartTls command")
{
    std::shared_ptr<SmtpCommand> command = parseSmtpCommand("STARTTLS\r\n");
    REQUIRE(command != nullptr);
    REQUIRE(command->getCommandId() == SmtpCommandId::StartTls);
}