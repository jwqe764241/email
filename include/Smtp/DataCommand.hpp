#pragma once

#include <fstream>
#include <sstream>

#include "SmtpCommand.hpp"

class DataCommand : public SmtpCommand
{
public:
    SmtpCommandId getCommandId() override;
    void execute(ConnectionContext& context, std::function<void(const asio::error_code, int)> handler) override;

private:
    void readMessage(ConnectionContext& context, const asio::error_code ec, int bytesTransferred);
    void handleReadMessage(ConnectionContext& context, const asio::error_code ec, int bytesTransferred);

private:
    std::function<void(const asio::error_code, int)> handler;
    asio::streambuf messageBuffer;
};