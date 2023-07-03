#include "Server/SecuredStream.hpp"

SecuredStream::SecuredStream(asio::ip::tcp::socket sock)
    : unsecuredStream(std::make_unique<asio::ip::tcp::socket>(std::move(sock)))
    , securedStream(nullptr)
    , isSecured(false)
{}

void SecuredStream::upgrade(std::function<void()> handler)
{
    asio::ssl::context sslCtx(asio::ssl::context::tlsv12);
    sslCtx.use_certificate_chain_file("standardkim.com.pem");
    sslCtx.use_private_key_file("standardkim.com.pem", asio::ssl::context::pem);
    securedStream = std::make_unique<asio::ssl::stream<asio::ip::tcp::socket>>(std::move(*unsecuredStream), sslCtx);
    unsecuredStream.reset(nullptr);
    securedStream->async_handshake(asio::ssl::stream_base::handshake_type::server,
                                   [this, handler](const asio::error_code& ec) {
                                       if (!ec)
                                       {
                                           isSecured = true;
                                           handler();
                                       }
                                   });
}

void SecuredStream::async_read_until(asio::streambuf& buffer, std::string delim,
                                     std::function<void(const asio::error_code&, int)> readToken)
{
    if (isSecured)
    {
        asio::async_read_until(*securedStream, buffer, delim, readToken);
    }
    else
    {
        asio::async_read_until(*unsecuredStream, buffer, delim, readToken);
    }
}

void SecuredStream::async_write_some(const asio::const_buffer& buffer,
                                     std::function<void(const asio::error_code&, int)> writeToken)
{
    if (isSecured)
    {
        securedStream->async_write_some(buffer, writeToken);
    }
    else
    {
        unsecuredStream->async_write_some(buffer, writeToken);
    }
}

void SecuredStream::write_some(const asio::const_buffer& buffer)
{
    if (isSecured)
    {
        securedStream->write_some(buffer);
    }
    else
    {
        unsecuredStream->write_some(buffer);
    }
}