#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>

#include "asio.hpp"

#include "Connection.hpp"

class Server
{
public:
    Server();
    void start(std::string host, std::string port);

private:
    void handleAccept(const asio::error_code &ec);
    void removeConnection(std::weak_ptr<Connection> connectionRef);

private:
    std::string host;
    int port;
    asio::io_context ctx;
    asio::ip::tcp::socket listenSocket;
    asio::ip::tcp::acceptor acceptor;

    std::unordered_set<std::shared_ptr<Connection>> connections;
};