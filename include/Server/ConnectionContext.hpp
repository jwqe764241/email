#pragma once

#include <functional>
#include <string>
#include <vector>

#include "asio.hpp"

class ConnectionContext
{
public:
    ConnectionContext(asio::ip::tcp::socket sock);
    ~ConnectionContext();

    asio::ip::tcp::socket &getSocket();
    asio::streambuf &getBuffer();
    void setOnDisconnect(std::function<void()> onDisconnect);
    void disconnect();
    const std::string &getDomain() const;
    void setDomain(const std::string &domain);
    const std::string &getOriginator() const;
    void setOriginator(const std::string &originator);
    const std::vector<std::string> getTo() const;
    void addTo(const std::string &to);

private:
    asio::ip::tcp::socket sock;
    asio::streambuf buffer;
    std::function<void()> onDisconnect;
    std::string domain;
    std::string originator;
    std::vector<std::string> to;
};