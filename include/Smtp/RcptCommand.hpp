#pragma once

#include "SmtpCommand.hpp"

class RcptCommand : public SmtpCommand
{
public:
    RcptCommand(const std::string& recipient);

    SmtpCommandId getCommandId() override;
    void execute(ConnectionContext& context, std::function<void(const asio::error_code, int)> handler) override;
    std::string getRecipient();

private:
    std::string recipient;
};