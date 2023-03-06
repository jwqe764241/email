#include "request.hpp"

const std::array<std::string, 8> Request::commandList = {
    "HELO", "MAIL", "RCPT", "DATA", "RSET", "NOOP", "VRFY"};

Request::Request(std::string request)
{
  size_t terminateFound = request.find("\r\n");
  if (terminateFound != std::string::npos)
    request.erase(request.begin() + terminateFound, request.end());

  size_t spaceFound = request.find(' ');
  std::string command = spaceFound != std::string::npos ? std::string(request.begin(), request.begin() + spaceFound) : request;

  if (std::find(commandList.begin(), commandList.end(), command) == commandList.end())
  {
    throw std::runtime_error("invalid request string");
  }

  this->command = command;

  // TODO: Refactor..
  if (command == "HELO")
  {
    parseHeloParameters(request.substr(spaceFound + 1));
  }
  else if (command == "MAIL")
  {
    parseMailParameters(request.substr(spaceFound + 1));
  }
  else if (command == "RCPT")
  {
    parseRcptParameters(request.substr(spaceFound + 1));
  }
  else if (command == "VRFY")
  {
    parseVrfyParameters(request.substr(spaceFound + 1));
  }
}

const std::string &Request::getCommand()
{
  return command;
}

const std::vector<std::string> &Request::getParameters()
{
  return parameters;
}

void Request::parseHeloParameters(std::string rawParameter)
{
  parameters.push_back(rawParameter);
}

void Request::parseMailParameters(std::string rawParameter)
{
  size_t startFound = rawParameter.find("FROM:<");
  size_t endFound = rawParameter.find(">");

  if (startFound == 0 && startFound < endFound)
  {
    parameters.push_back(
        std::string(rawParameter.begin() + startFound + 6, rawParameter.begin() + endFound));
  }
  else
  {
    throw std::invalid_argument("invalid MAIL command request");
  }
}

void Request::parseRcptParameters(std::string rawParameter)
{
  size_t startFound = rawParameter.find("TO:<");
  size_t endFound = rawParameter.find(">");

  if (startFound == 0 && startFound < endFound)
  {
    parameters.push_back(
        std::string(rawParameter.begin() + startFound + 4, rawParameter.begin() + endFound));
  }
  else
  {
    throw std::invalid_argument("invalid RCPT command request");
  }
}

void Request::parseVrfyParameters(std::string rawParameter)
{
  parameters.push_back(rawParameter);
}