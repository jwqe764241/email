#include "Server/Connection.hpp"

Connection::Connection(asio::ip::tcp::socket sock)
    : context(std::move(sock))
    , stateMachine(context)
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
        std::shared_ptr<SmtpCommand> command = parser.parse(rawRequest);

        if(!command) {
            context.getSocket().write_some(asio::buffer("500 Syntax error or Command unrecognized\r\n"));
            readRequest();
            return;
        }

        if (stateMachine.canAccept(command))
        {
            command->execute(context, std::bind(Connection::onExecuteCommand, this, 
                command, std::placeholders::_1, std::placeholders::_2));
        }
    }
    else
    {
        context.disconnect();
    }
}

//TODO:: rename this method
void Connection::onExecuteCommand(std::shared_ptr<SmtpCommand> command, const asio::error_code ec, int bytesTransferred)
{
    stateMachine.transition(command);
    readRequest();
}