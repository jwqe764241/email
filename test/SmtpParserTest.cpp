#include <catch_amalgamated.hpp>

#include "Smtp/SmtpParser.hpp"

TEST_CASE("Smtp parser can parse HELO command")
{
    SmtpParser parser;
    std::shared_ptr<SmtpCommand> parsedCommand = parser.parse("HELO aaa.example.com");
    REQUIRE(parsedCommand != nullptr);

    HeloCommand* heloCommand = static_cast<HeloCommand*>(parsedCommand.get());
    REQUIRE(heloCommand->getCommandId() == SmtpCommandId::Helo);
    REQUIRE(heloCommand->getDomain() == "aaa.example.com");
}

TEST_CASE("Smtp parser can parse MAIL command")
{
    SmtpParser parser;
    std::shared_ptr<SmtpCommand> parsedCommand = parser.parse("MAIL FROM:<example@example.com>");
    REQUIRE(parsedCommand != nullptr);

    MailCommand* mailCommand = static_cast<MailCommand*>(parsedCommand.get());
    REQUIRE(mailCommand->getCommandId() == SmtpCommandId::Mail);
    REQUIRE(mailCommand->getOriginator() == "example@example.com");
}

TEST_CASE("Smtp parser can parse RCPT command")
{
    SmtpParser parser;
    std::shared_ptr<SmtpCommand> parsedCommand = parser.parse("RCPT TO:<example@example.com");
    REQUIRE(parsedCommand != nullptr);

    RcptCommand* rcptCommand = static_cast<RcptCommand*>(parsedCommand.get());
    REQUIRE(rcptCommand->getCommandId() == SmtpCommandId::Rcpt);
    REQUIRE(rcptCommand->getRecipient() == "example@example.com");
}

TEST_CASE("Smtp parser can parse DATA command")
{
    SmtpParser parser;
    std::shared_ptr<SmtpCommand> parsedCommand = parser.parse("DATA");
    REQUIRE(parsedCommand != nullptr);

    DataCommand* dataCommand = static_cast<DataCommand*>(parsedCommand.get());
    REQUIRE(dataCommand->getCommandId() == SmtpCommandId::Data);
}