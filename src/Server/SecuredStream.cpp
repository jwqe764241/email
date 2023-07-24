#include "Server/SecuredStream.hpp"

SecuredStream::SecuredStream(asio::ip::tcp::socket sock, asio::ssl::context& ctx)
    : stream(std::move(sock), ctx)
    , isSecured(false)
{}

SecuredStream::SecuredStream(SecuredStream&& securedStream)
    : stream(std::move(securedStream.stream))
    , isSecured(std::exchange(securedStream.isSecured, false))
{}

void SecuredStream::upgrade(std::function<void()> handler)
{
    stream.async_handshake(asio::ssl::stream_base::handshake_type::server, [this, handler](const asio::error_code& ec) {
        if (!ec)
        {
            isSecured = true;
            handler();
        }
    });
}

void SecuredStream::readUntilAsync(asio::streambuf& buffer, std::string delim,
                                   std::function<void(const asio::error_code&, int)> readToken)
{
    if (isSecured)
    {
        asio::async_read_until(stream, buffer, delim, readToken);
    }
    else
    {
        asio::async_read_until(stream.next_layer(), buffer, delim, readToken);
    }
}

void SecuredStream::writeAsync(const std::string message, std::function<void(const asio::error_code&, int)> writeToken)
{
    asio::streambuf buffer;
    writeToBuffer(message, buffer);

    if (isSecured)
    {
        asio::async_write(stream, buffer, writeToken);
    }
    else
    {
        asio::async_write(stream.next_layer(), buffer, writeToken);
    }
}

void SecuredStream::write(const std::string message)
{
    asio::streambuf buffer;
    writeToBuffer(message, buffer);

    if (isSecured)
    {
        asio::write(stream, buffer);
    }
    else
    {
        asio::write(stream.next_layer(), buffer);
    }
}

void SecuredStream::writeToBuffer(const std::string& str, asio::streambuf& buffer)
{
    std::ostream os(&buffer);
    std::ostream_iterator<char> osIt(os);
    std::copy(str.begin(), str.end(), osIt);
}