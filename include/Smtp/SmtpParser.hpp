#pragma once

#include <iostream>
#include <memory>

#include "HeloCommand.hpp"
#include "MailCommand.hpp"
#include "SmtpCommand.hpp"
#include "TokenReader.hpp"

class SmtpParser
{
public:
    SmtpParser() {}
    std::shared_ptr<SmtpCommand> parse(const std::string& str);

private:
    std::shared_ptr<HeloCommand> parseHelo(const std::string& str);
    std::shared_ptr<MailCommand> parseMail(const std::string& str);
    bool tryReadDomain(TokenReader& reader);
    bool tryReadSubDomain(TokenReader& reader);
    bool tryReadMail(TokenReader& reader);
    bool tryReadAlphanumeric(TokenReader& reader);
};