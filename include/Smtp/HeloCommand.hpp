#pragma once

#include "SmtpCommand.hpp"

class HeloCommand : public SmtpCommand
{
public:
  HeloCommand(const std::string& domain);
  
  std::string getName() override;
  void execute(ConnectionContext& context);
  std::string getDomain();

private:
  std::string domain;
};