#include "Server/Connection.hpp"

Connection::Connection(SecuredStream stream)
    : stream(std::move(stream))
    , context(this->stream)
    , stateMachine(context, StateTable::getInstance())
{}

Connection::~Connection() {}

std::shared_ptr<Connection> Connection::getPtr()
{
    return shared_from_this();
}

void Connection::start(std::function<void()> onDisconnect)
{
    context.setOnDisconnect(onDisconnect);
    sendGreeting();
}

void Connection::sendGreeting()
{
    stream.writeAsync("220 hello\r\n",
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
    stream.readUntilAsync(
        context.getBuffer(), "\r\n",
        std::bind(&Connection::handleReadRequest, this, std::placeholders::_1, std::placeholders::_2));
}

void Connection::handleReadRequest(const asio::error_code ec, int bytesTransferred)
{
    if (!ec)
    {
        std::string request;
        std::istream is(&context.getBuffer());
        std::getline(is, request);
        std::shared_ptr<SmtpCommand> command = parseSmtpCommand(request);

        if (!command)
        {
            auto self(shared_from_this());
            stream.writeAsync("500 Syntax error or Command unrecognized\r\n",
                              [this, self](const asio::error_code& ec, int bytesTransffered) {
                                  if (!ec)
                                  {

                                      readRequest();
                                  }
                              });
            return;
        }

        bool canAccept = false;
        try
        {
            canAccept = stateMachine.canAccept(command);
        }
        catch (const std::out_of_range& e)
        {
            auto self(shared_from_this());
            stream.writeAsync("503 Bad sequence of commands\r\n",
                              [this, self](const asio::error_code& ec, int bytesTransffered) {
                                  if (!ec)
                                  {
                                      readRequest();
                                  }
                              });
            return;
        }

        if (canAccept)
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

void Connection::handleExecuteCommand(std::shared_ptr<SmtpCommand> command, const asio::error_code ec,
                                      int bytesTransferred)
{
    stateMachine.transition(command);
    readRequest();
}