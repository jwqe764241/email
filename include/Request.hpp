#pragma once

#include <algorithm>
#include <array>
#include <functional>
#include <stdexcept>
#include <string>
#include <vector>

class Request
{
public:
    Request();
    Request(std::string request);

    void parse(std::string request);
    const std::string &getCommand() const;
    const std::vector<std::string> &getParameters() const;

private:
    void parseHeloParameters(std::string rawParameter);
    void parseMailParameters(std::string rawParameter);
    void parseRcptParameters(std::string rawParameter);
    void parseVrfyParameters(std::string rawParameter);

private:
    std::string command;
    std::vector<std::string> parameters;
    const static std::array<std::string, 8> commandList;
};