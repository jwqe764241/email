#include "Server/Connection.hpp"

Connection::Connection(asio::ip::tcp::socket sock)
    : context(std::move(sock))
{
}

Connection::~Connection()
{
}

void Connection::start(std::function<void()> onDisconnect)
{
    context.setOnDisconnect(onDisconnect);
    sendGreeting();
}

std::shared_ptr<Connection> Connection::getPtr()
{
    return shared_from_this();
}

void Connection::sendGreeting()
{
    context.getSocket().async_write_some(asio::buffer("220 hello\n"), 
        std::bind(Connection::onSendGreeting, this,
            std::placeholders::_1, std::placeholders::_2));
}

void Connection::onSendGreeting(const asio::error_code ec, int bytesTransferred)
{
    if (!ec) {
        readRequest();
    }
}

void Connection::readRequest()
{
    asio::async_read_until(context.getSocket(), context.getBuffer(), "\n",
        std::bind(Connection::onReadRequest, this,
            std::placeholders::_1, std::placeholders::_2));
}

void Connection::onReadRequest(const asio::error_code ec, int bytesTransferred)
{
    if(!ec)
    {
        std::stringstream sstream;
        sstream << std::istream(&context.getBuffer()).rdbuf();
        std::string rawRequest = sstream.str();
        SmtpParser parser;
        std::unique_ptr<SmtpCommand> command = parser.parse(rawRequest);
    }
    else
    {
        context.disconnect();
    }
    /*
    if (!ec)
    {
        std::stringstream sstream;
        sstream << std::istream(&buffer).rdbuf();
        std::string rawRequest = sstream.str();

        try
        {

        }
        catch (const std::exception &e)
        {
            sock.write_some(asio::buffer("500 Syntax error or Command unrecognized\r\n"));
        }

        buffer.consume(bytesTransferred);
        asio::async_read_until(sock, buffer, "\r\n",
                               std::bind(Connection::handleRead, this,
                                         std::placeholders::_1,
                                         std::placeholders::_2));
    }
    else if (ec == asio::error::not_found)
    {
        //request size is bigger than buffer size
        buffer.consume(buffer.size());
        asio::async_read_until(sock, buffer, "\r\n",
                std::bind(Connection::handleRead, this,
                            std::placeholders::_1,
                            std::placeholders::_2));
    }
    else
    {
        // This will be like self desturcting
        onDisconnect();
    */
}