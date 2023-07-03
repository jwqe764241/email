#pragma once

#include <functional>
#include <iostream>
#include <memory>

#include "asio.hpp"
#include "asio/ssl.hpp"

class SecuredStream
{
public:
    SecuredStream(asio::ip::tcp::socket sock);

    void upgrade(std::function<void()> handler);
    void async_read_until(asio::streambuf& buffer, std::string delim,
                          std::function<void(const asio::error_code&, int)> readToken);
    void async_write_some(const asio::const_buffer& buffer,
                          std::function<void(const asio::error_code&, int)> writeToken);
    void write_some(const asio::const_buffer& buffer);

private:
    std::unique_ptr<asio::ip::tcp::socket> unsecuredStream;
    std::unique_ptr<asio::ssl::stream<asio::ip::tcp::socket>> securedStream;
    bool isSecured;
};