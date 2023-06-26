#pragma once

#include "SmtpCommand.hpp"

class MailCommand : public SmtpCommand
{
public:
    MailCommand(const std::string& originator);

    SmtpCommandId getCommandId() override;
    void execute(ConnectionContext& context, std::function<void(const asio::error_code, int)> handler) override;

private:
    std::string originator;
};