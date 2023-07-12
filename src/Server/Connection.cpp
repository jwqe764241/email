#include "Server/Connection.hpp"

Connection::Connection(asio::ip::tcp::socket sock)
    : context(std::move(sock))
    , stateMachine(context, StateTable::getInstance())
{}

Connection::~Connection() {}

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
    context.getStream().async_write_some(
        asio::buffer("220 hello\n"),
        std::bind(&Connection::handleSendGreeting, this, std::placeholders::_1, std::placeholders::_2));
}

void Connection::handleSendGreeting(const asio::error_code ec, int bytesTransferred)
{
    if (!ec)
    {
        readRequest();
    }
}

void Connection::readRequest()
{
    context.getStream().async_read_until(
        context.getBuffer(), "\r\n",
        std::bind(&Connection::handleReadRequest, this, std::placeholders::_1, std::placeholders::_2));
}

void Connection::handleReadRequest(const asio::error_code ec, int bytesTransferred)
{
    if (!ec)
    {
        std::stringstream sstream;
        sstream << std::istream(&context.getBuffer()).rdbuf();
        std::string rawRequest = sstream.str();
        std::shared_ptr<SmtpCommand> command = parseSmtpCommand(rawRequest);

        if (!command)
        {
            context.getStream().write_some(asio::buffer("500 Syntax error or Command unrecognized\r\n"));
            readRequest();
            return;
        }

        if (stateMachine.canAccept(command))
        {
            command->execute(context, std::bind(&Connection::handleExecuteCommand, this, command, std::placeholders::_1,
                                                std::placeholders::_2));
        }
    }
    else
    {
        context.disconnect();
    }
}

// TODO:: rename this method
void Connection::handleExecuteCommand(std::shared_ptr<SmtpCommand> command, const asio::error_code ec,
                                      int bytesTransferred)
{
    stateMachine.transition(command);
    readRequest();
}