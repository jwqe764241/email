#pragma once

#include <iostream>
#include <memory>

#include "DataCommand.hpp"
#include "EhloCommand.hpp"
#include "HeloCommand.hpp"
#include "MailCommand.hpp"
#include "NoopCommand.hpp"
#include "QuitCommand.hpp"
#include "RcptCommand.hpp"
#include "RsetCommand.hpp"
#include "SmtpCommand.hpp"
#include "TokenReader.hpp"

class SmtpParser
{
public:
    SmtpParser() {}
    std::shared_ptr<SmtpCommand> parse(const std::string& str);

private:
    std::shared_ptr<HeloCommand> parseHelo(const std::string& str);
    std::shared_ptr<EhloCommand> parseEhlo(const std::string& str);
    std::shared_ptr<MailCommand> parseMail(const std::string& str);
    std::shared_ptr<RcptCommand> parseRcpt(const std::string& str);
    std::shared_ptr<DataCommand> parseData(const std::string& str);
    std::shared_ptr<QuitCommand> parseQuit(const std::string& str);
    std::shared_ptr<NoopCommand> parseNoop(const std::string& str);
    std::shared_ptr<RsetCommand> parseRset(const std::string& str);
    bool tryReadDomain(TokenReader& reader);
    bool tryReadSubDomain(TokenReader& reader);
    bool tryReadMail(TokenReader& reader);
    bool tryReadAlphanumeric(TokenReader& reader);
};