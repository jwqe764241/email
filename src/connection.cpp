#include "connection.hpp"

Connection::Connection(asio::ip::tcp::socket sock_)
    : sock(std::move(sock_)), buffer(1024)
{
}

Connection::~Connection()
{
    sock.close();
}

void Connection::start(std::function<void()> &&onDisconnect)
{
    this->onDisconnect = std::move(onDisconnect);
    currentState = std::make_shared<IdleState>(sock, connectionData);
    asio::async_read_until(sock, buffer, "\r\n",
                           std::bind(Connection::handleRead, this, std::placeholders::_1, std::placeholders::_2));
}

void Connection::handleRead(const asio::error_code ec, int bytesTransferred)
{
    if (!ec)
    {
        std::stringstream sstream;
        sstream << std::istream(&buffer).rdbuf();
        std::string rawRequest = sstream.str();

        try
        {
            Request request(rawRequest);
            processEvent(request);
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }

        buffer.consume(bytesTransferred);
        asio::async_read_until(sock, buffer, "\r\n",
                               std::bind(Connection::handleRead, this, std::placeholders::_1, std::placeholders::_2));
    }
    else if (ec == asio::error::eof)
    {
        // This will be like self desturcting
        onDisconnect();
    }
    else
    {
        std::cout << ec.message() << std::endl;
        buffer.consume(buffer.size());
        asio::async_read_until(sock, buffer, "\r\n",
                               std::bind(Connection::handleRead, this, std::placeholders::_1, std::placeholders::_2));
    }
}

void Connection::processEvent(const Request &request)
{
    if (currentState == nullptr)
    {
        throw std::runtime_error("current state is nullptr");
    }

    auto nextState = currentState->processEvent(request);
    if (nextState != currentState)
    {
        currentState = nextState;
    }
}