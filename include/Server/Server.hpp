#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <unordered_set>

#include "asio.hpp"
#include "asio/ssl.hpp"

#include "Connection.hpp"

struct ServerConfig
{
    std::string host;
    std::string port;
    std::string certPemPath;

    ServerConfig(const std::map<std::string, std::string>& map)
        : host(map.at("HOST"))
        , port(map.at("PORT"))
        , certPemPath(map.at("CERT_PATH"))
    {}
};

class Server
{
public:
    Server(const ServerConfig& config);
    void start();

private:
    void handleAccept(const asio::error_code& ec);
    void removeConnection(std::weak_ptr<Connection> connectionRef);

private:
    const ServerConfig config;
    asio::io_context ctx;
    asio::ssl::context sslCtx;
    asio::ip::tcp::socket listenSocket;
    asio::ip::tcp::acceptor acceptor;
    std::unordered_set<std::shared_ptr<Connection>> connections;
};