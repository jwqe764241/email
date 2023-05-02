#include "Smtp/HeloCommand.hpp"

HeloCommand::HeloCommand(const std::string& domain)
  : domain(domain)
{
}

std::string HeloCommand::getName()
{
  return "HELO";
}

void HeloCommand::execute(ConnectionContext& context)
{
}

std::string HeloCommand::getDomain()
{
  return domain;
}