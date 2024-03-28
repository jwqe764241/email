#include "Server/ServerConfig.hpp"

void trimWhitespace(std::string& str)
{
    str.erase(std::remove_if(str.begin(), str.end(), [](unsigned char c) { return std::isspace(c); }), str.end());
}

void trimComment(std::string& str)
{
    str.erase(std::find(str.begin(), str.end(), '#'), str.end());
}

std::pair<std::string, std::string> parseLine(const std::string& line)
{
    std::size_t separatorPos = line.find('=');
    std::string key = line.substr(0, separatorPos);
    if (separatorPos == std::string::npos || key.empty())
    {
        throw std::runtime_error("invalid configuration form.");
    }

    return std::make_pair(key, line.substr(++separatorPos));
}

ServerConfig ServerConfig::fromFile(std::istream& file)
{
    if (!file)
    {
        throw std::runtime_error("cannot open configuration file");
    }

    std::map<std::string, std::string> configMap;
    while (!file.eof())
    {
        std::string str;
        std::getline(file, str);

        trimComment(str);
        trimWhitespace(str);

        if (str.empty())
        {
            continue;
        }

        configMap.insert(parseLine(str));
    }

    ServerConfig config;
    config.host = configMap["HOST"];
    config.port = configMap["PORT"];
    config.certPath = configMap["CERT_PATH"];

    return config;
}