#include "Server/ConfigParser.hpp"

namespace
{
void removeWhitespace(std::string& str)
{
    for (auto it = str.begin(); it != str.end(); ++it)
    {
        if (*it == ' ' || *it == '\t')
        {
            str.erase(it);
            --it;
        }
    }
}

void removeComment(std::string& str)
{
    auto commentIt = std::find(str.begin(), str.end(), '#');
    if (commentIt != str.end())
    {
        str.erase(commentIt, str.end());
    }
}

std::pair<std::string, std::string> parseLine(const std::string& line)
{
    std::size_t separatorPos = line.find('=');
    if (separatorPos == std::string::npos)
    {
        throw std::runtime_error("Invalid config form.");
    }

    std::string key = line.substr(0, separatorPos);
    if (key.empty())
    {
        throw std::runtime_error("Config name must not be empty.");
    }

    return std::make_pair(key, line.substr(separatorPos + 1));
}
} // namespace

std::map<std::string, std::string> parseConfig(std::istream& source)
{
    if (source.fail())
    {
        throw std::runtime_error("Stream was fail state");
    }

    std::map<std::string, std::string> configMap;
    while (!source.eof())
    {
        std::string str;
        std::getline(source, str);
        removeComment(str);
        removeWhitespace(str);
        if (str.empty())
        {
            continue;
        }

        configMap.insert(parseLine(str));
    }

    return configMap;
}