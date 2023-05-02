#pragma once

#include <string>

#include "Server/ConnectionContext.hpp"

class SmtpCommand
{
public:
  virtual ~SmtpCommand() {}
  virtual std::string getName() = 0;
  virtual void execute(ConnectionContext& context) = 0;
};