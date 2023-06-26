#pragma once

#include "SmtpCommand.hpp"

class HeloCommand : public SmtpCommand
{
public:
    HeloCommand(const std::string& domain);

    SmtpCommandId getCommandId() override;
    void execute(ConnectionContext& context, std::function<void(const asio::error_code, int)> handler) override;

private:
    std::string domain;
};