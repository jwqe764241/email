#pragma once

#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

#include "asio.hpp"

#include "Data.hpp"
#include "Request.hpp"
#include "State.hpp"

const int BUFFER_SIZE = 1024;

class Connection
{
public:
    Connection(asio::ip::tcp::socket sock_);
    ~Connection();

    void start(std::function<void()> &&onDisconnect);

private:
    void handleRead(const asio::error_code ec, int bytesTransferred);
    void processEvent(const Request &request);

private:
    asio::ip::tcp::socket sock;
    asio::streambuf buffer;
    std::function<void()> onDisconnect;
    std::shared_ptr<State> currentState;
    Data connectionData;
};