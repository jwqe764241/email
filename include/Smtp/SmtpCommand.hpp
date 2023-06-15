#pragma once

#include <functional>
#include <string>

#include "Server/ConnectionContext.hpp"
#include "SmtpCommandId.hpp"

class SmtpCommand
{
public:
    virtual ~SmtpCommand() {}
    virtual SmtpCommandId getCommandId() = 0;
    virtual void execute(ConnectionContext &context, std::function<void(const asio::error_code, int)> handler) = 0;
};