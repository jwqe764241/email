#pragma once

#include "SmtpCommand.hpp"

class StartTlsCommand : public SmtpCommand
{
public:
    SmtpCommandId getCommandId() override;
    void execute(ConnectionContext& context, std::function<void(const asio::error_code, int)> handler) override;

private:
    void handleSendReady(ConnectionContext& context, const asio::error_code& ec, int bytesTransffered);

private:
    std::function<void(const asio::error_code, int)> handler;
};