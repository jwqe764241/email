#pragma once

#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

#include "asio.hpp"

#include "Request.hpp"
#include "State.hpp"

class State;

class Connection : public std::enable_shared_from_this<Connection>
{
public:
    Connection(asio::ip::tcp::socket sock_);
    ~Connection();

    void start(std::function<void()> &&onDisconnect);
    std::shared_ptr<Connection> getPtr();
    asio::ip::tcp::socket& getSocket();
    void setDomain(const std::string& domain);

private:
    void handleRead(const asio::error_code ec, int bytesTransferred);
    void processEvent(const Request &request);

private:
    asio::ip::tcp::socket sock;
    asio::streambuf buffer;
    std::function<void()> onDisconnect;
    std::shared_ptr<State> currentState;
    std::string domain;
};