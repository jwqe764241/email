#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <array>
#include <functional>

class Request
{
public:
  Request(std::string request);

  const std::string &getCommand();
  const std::vector<std::string> &getParameters();

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