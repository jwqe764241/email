#pragma once

#include "SmtpCommand.hpp"

class QuitCommand : public SmtpCommand
{
public:
    SmtpCommandId getCommandId() override;
    void execute(ConnectionContext& context, std::function<void(const asio::error_code, int)> handler) override;
};