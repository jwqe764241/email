#pragma once

#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

#include "asio.hpp"
#include "asio/ssl.hpp"

#include "ConnectionContext.hpp"
#include "Smtp/SmtpParser.hpp"
#include "State/StateMachine.hpp"

class Connection : public std::enable_shared_from_this<Connection>
{
public:
    Connection(asio::ip::tcp::socket sock);
    ~Connection();

    void start(std::function<void()> onDisconnect);
    std::shared_ptr<Connection> getPtr();

private:
    void sendGreeting();
    void handleSendGreeting(const asio::error_code ec, int bytesTransferred);
    void readRequest();
    void handleReadRequest(const asio::error_code ec, int bytesTransferred);
    void handleExecuteCommand(std::shared_ptr<SmtpCommand> command, const asio::error_code ec, int bytesTransferred);

private:
    ConnectionContext context;
    StateMachine stateMachine;
};
// StateMachine, StateContext