#include "Smtp/SmtpParser.hpp"

std::shared_ptr<SmtpCommand> SmtpParser::parse(const std::string& str)
{
    std::shared_ptr<SmtpCommand> parsedCommand = nullptr;

    parsedCommand = parseHelo(str);
    if (parsedCommand)
    {
        return parsedCommand;
    }

    parsedCommand = parseMail(str);
    if (parsedCommand)
    {
        return parsedCommand;
    }

    parsedCommand = parseRcpt(str);
    if (parsedCommand)
    {
        return parsedCommand;
    }

    parsedCommand = parseData(str);
    if (parsedCommand)
    {
        return parsedCommand;
    }

    return nullptr;
}

std::shared_ptr<HeloCommand> SmtpParser::parseHelo(const std::string& str)
{
    TokenReader reader(str);

    Token command = reader.take();
    if (command.getStr() != "HELO")
    {
        return nullptr;
    }

    reader.skip(TokenKind::Space);

    std::string domain;
    bool result = reader.tryRead(std::bind(&SmtpParser::tryReadDomain, this, std::placeholders::_1), &domain);

    return result ? std::make_shared<HeloCommand>(domain) : nullptr;
}

std::shared_ptr<MailCommand> SmtpParser::parseMail(const std::string& str)
{
    TokenReader reader(str);

    Token command = reader.take();
    if (command.getStr() != "MAIL")
    {
        return nullptr;
    }

    reader.skip(TokenKind::Space);

    if (reader.take().getStr() != "FROM" || reader.take().getKind() != TokenKind::Colon)
    {
        return nullptr;
    }

    Token lessThan = reader.take();
    if (lessThan.getKind() != TokenKind::LessThan)
    {
        return nullptr;
    }

    std::string originator;
    bool result = reader.tryRead(std::bind(&SmtpParser::tryReadMail, this, std::placeholders::_1), &originator);

    return result ? std::make_shared<MailCommand>(originator) : nullptr;
}

std::shared_ptr<RcptCommand> SmtpParser::parseRcpt(const std::string& str)
{
    TokenReader reader(str);

    Token command = reader.take();
    if (command.getStr() != "RCPT")
    {
        return nullptr;
    }

    reader.skip(TokenKind::Space);

    if (reader.take().getStr() != "TO" || reader.take().getKind() != TokenKind::Colon)
    {
        return nullptr;
    }

    Token lessThan = reader.take();
    if (lessThan.getKind() != TokenKind::LessThan)
    {
        return nullptr;
    }

    std::string recipient;
    bool result = reader.tryRead(std::bind(&SmtpParser::tryReadMail, this, std::placeholders::_1), &recipient);

    return result ? std::make_shared<RcptCommand>(recipient) : nullptr;
}

std::shared_ptr<DataCommand> SmtpParser::parseData(const std::string& str)
{
    TokenReader reader(str);

    Token command = reader.take();
    if (command.getStr() != "DATA")
    {
        return nullptr;
    }

    return std::make_shared<DataCommand>();
}

bool SmtpParser::tryReadDomain(TokenReader& reader)
{
    // read first subdomain
    if (!tryReadSubDomain(reader))
    {
        return false;
    }

    while (reader.peek().getKind() == TokenKind::Period)
    {
        reader.take();

        if (!tryReadSubDomain(reader))
        {
            return false;
        }
    }

    return true;
}

bool SmtpParser::tryReadSubDomain(TokenReader& reader)
{
    // check first is alphanumeric
    if (tryReadAlphanumeric(reader) == false)
    {
        return false;
    }

    reader.skip([](TokenKind tokenKind) { return tokenKind == TokenKind::Text || tokenKind == TokenKind::Number; });

    return true;
}

bool SmtpParser::tryReadMail(TokenReader& reader)
{
    // parse username
    if (tryReadAlphanumeric(reader) == false)
    {
        return false;
    }

    reader.skip([](TokenKind tokenKind) { return tokenKind == TokenKind::Text || tokenKind == TokenKind::Number; });

    // check at
    if (reader.take().getKind() != TokenKind::At)
    {
        return false;
    }

    // parse host part
    if (!tryReadSubDomain(reader))
    {
        return false;
    }

    while (reader.peek().getKind() == TokenKind::Period)
    {
        reader.take();

        if (!tryReadSubDomain(reader))
        {
            return false;
        }
    }

    return true;
}

bool SmtpParser::tryReadAlphanumeric(TokenReader& reader)
{
    TokenKind tokenKind = reader.peek().getKind();
    if (tokenKind == TokenKind::Text || tokenKind == TokenKind::Number)
    {
        reader.take();
        return true;
    }
    return false;
}