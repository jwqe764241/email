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

std::pair<std::string, std::string> parseLine(const std::string& line)
{
    std::size_t separatorPos = line.find('=');
    if (separatorPos == std::string::npos)
    {
        throw std::runtime_error("Invalid config form.");
    }

    return std::make_pair(line.substr(0, separatorPos), line.substr(separatorPos + 1));
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

        removeWhitespace(str);
        if (str.empty())
        {
            continue;
        }

        std::pair<std::string, std::string> parsedConfig = parseLine(str);
        configMap.insert(parsedConfig);
    }

    return configMap;
}