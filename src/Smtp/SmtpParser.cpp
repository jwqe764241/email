#include "Smtp/SmtpParser.hpp"

bool equalsIgnoreCase(const std::string& str1, const std::string& str2)
{
    return std::equal(str1.begin(), str1.end(), str2.begin(), str2.end(),
                      [](const char& c1, const char& c2) { return tolower(c1) == tolower(c2); });
}

size_t findIgnoreCase(const std::string& str, const std::string& subStr)
{
    auto it = std::search(str.begin(), str.end(), subStr.begin(), subStr.end(),
                          [](const char& c1, const char& c2) { return tolower(c1) == tolower(c2); });
    return it != str.end() ? it - str.begin() : std::string::npos;
}

void trimLineBreak(std::string& str)
{
    auto it = std::find(str.begin(), str.end(), '\r');
    if (it != str.end())
    {
        str.erase(it, str.end());
    }
}

void splitSmtpRequest(const std::string& request, std::string* outCommand, std::string* outArg)
{
    if (outCommand == nullptr || outArg == nullptr)
    {
        return;
    }

    auto whitespacePos = request.find_first_of(' ');
    if (whitespacePos != std::string::npos)
    {
        *outCommand = request.substr(0, whitespacePos);
        *outArg = request.substr(whitespacePos + 1);
    }
    else
    {
        *outCommand = request;
    }
}

bool isPatternMatched(const std::string& pattern, const std::string& str)
{
    std::regex re(pattern);
    return std::regex_match(str, re);
}

bool isValidDomain(const std::string& domain)
{
    return isPatternMatched("(?:[a-z0-9](?:[a-z0-9-]{0,61}[a-z0-9])?\\.)+[a-z0-9][a-z0-9-]{0,61}[a-z0-9]", domain);
}

bool isValidAddress(const std::string& address)
{
    return isPatternMatched("[a-z0-9]+@(?:[a-z0-9](?:[a-z0-9-]{0,61}[a-z0-9])?\\.)+[a-z0-9][a-z0-9-]{0,61}[a-z0-9]",
                            address);
}

std::string getStringBetween(const std::string& str, const std::string& start, const std::string& end)
{
    size_t startPos = findIgnoreCase(str, start);
    if (startPos == std::string::npos || startPos != 0)
    {
        return "";
    }

    size_t endPos = findIgnoreCase(str, end);
    if (endPos == std::string::npos || endPos < startPos)
    {
        return "";
    }

    return str.substr(start.size(), endPos - start.size());
}

std::string parseMailArgument(std::string& argument)
{
    std::string address = getStringBetween(argument, "FROM:<", ">");

    if (address.empty() || !isValidAddress(address))
    {
        return "";
    }

    return address;
}

std::string parseRcptArgument(std::string& argument)
{
    std::string address = getStringBetween(argument, "TO:<", ">");

    if (address.empty() || !isValidAddress(address))
    {
        return "";
    }

    return address;
}

std::shared_ptr<SmtpCommand> parseSmtpCommand(std::string request)
{
    trimLineBreak(request);

    if (request.empty())
    {
        return nullptr;
    }

    std::string command, argument;
    splitSmtpRequest(request, &command, &argument);

    if (equalsIgnoreCase(command, "HELO"))
    {
        if (!isValidDomain(argument))
        {
            return nullptr;
        }
        return std::make_shared<HeloCommand>(argument);
    }
    else if (equalsIgnoreCase(command, "EHLO"))
    {
        if (!isValidDomain(argument))
        {
            return nullptr;
        }
        return std::make_shared<EhloCommand>(argument);
    }
    else if (equalsIgnoreCase(command, "MAIL"))
    {
        std::string originator = parseMailArgument(argument);
        if (originator.empty())
        {
            return nullptr;
        }
        return std::make_shared<MailCommand>(originator);
    }
    else if (equalsIgnoreCase(command, "RCPT"))
    {
        std::string recipient = parseRcptArgument(argument);
        if (recipient.empty())
        {
            return nullptr;
        }
        return std::make_shared<RcptCommand>(recipient);
    }
    else if (equalsIgnoreCase(command, "DATA"))
    {
        return std::make_shared<DataCommand>();
    }
    else if (equalsIgnoreCase(command, "NOOP"))
    {
        return std::make_shared<NoopCommand>();
    }
    else if (equalsIgnoreCase(command, "QUIT"))
    {
        return std::make_shared<QuitCommand>();
    }
    else if (equalsIgnoreCase(command, "RSET"))
    {
        return std::make_shared<RsetCommand>();
    }
    else if (equalsIgnoreCase(command, "STARTTLS"))
    {
        return std::make_shared<StartTlsCommand>();
    }
    else
    {
        return nullptr;
    }
}