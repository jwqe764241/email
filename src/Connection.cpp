#include "Connection.hpp"

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
    currentState = std::make_shared<IdleState>(getPtr());
    asio::async_read_until(sock, buffer, "\r\n",
                           std::bind(Connection::handleRead, this,
                                     std::placeholders::_1,
                                     std::placeholders::_2));
}

std::shared_ptr<Connection> Connection::getPtr()
{
    return shared_from_this();
}

asio::ip::tcp::socket& Connection::getSocket()
{
    return sock;
}

void Connection::setDomain(const std::string& domain)
{
    this->domain = domain;
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