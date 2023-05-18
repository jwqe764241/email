#pragma once

#include <string>
#include <functional>

#include "SmtpCommandId.hpp"
#include "Server/ConnectionContext.hpp"

class SmtpCommand
{
public:
  virtual ~SmtpCommand() {}
  virtual SmtpCommandId getCommandId() = 0;
  virtual void execute(ConnectionContext& context, std::function<void(const asio::error_code, int)> handler) = 0;
};