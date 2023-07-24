#pragma once

#include <functional>
#include <iostream>
#include <memory>

#include "asio.hpp"
#include "asio/ssl.hpp"

class SecuredStream
{
public:
    SecuredStream(asio::ip::tcp::socket sock, asio::ssl::context& ctx);
    SecuredStream(SecuredStream&& securedStream);

    void upgrade(std::function<void()> handler);
    void readUntilAsync(asio::streambuf& buffer, std::string delim,
                        std::function<void(const asio::error_code&, int)> readToken);
    void writeAsync(const std::string message, std::function<void(const asio::error_code&, int)> writeToken);
    void write(const std::string message);

private:
    void writeToBuffer(const std::string& str, asio::streambuf& buffer);

private:
    asio::ssl::stream<asio::ip::tcp::socket> stream;
    bool isSecured;
};