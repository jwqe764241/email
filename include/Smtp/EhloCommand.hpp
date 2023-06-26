#pragma once

#include "SmtpCommand.hpp"

class EhloCommand : public SmtpCommand
{
public:
    EhloCommand(const std::string& domain);

    SmtpCommandId getCommandId() override;
    void execute(ConnectionContext& context, std::function<void(const asio::error_code, int)> handler) override;

private:
    std::string domain;
};