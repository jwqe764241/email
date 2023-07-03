#include "Smtp/DataCommand.hpp"

SmtpCommandId DataCommand::getCommandId()
{
    return SmtpCommandId::Data;
}

void DataCommand::execute(ConnectionContext& context, std::function<void(const asio::error_code, int)> handler)
{
    this->handler = handler;
    context.getStream().async_write_some(
        asio::buffer("354 End data with <CR><LF>.<CR><LF>\r\n"),
        std::bind(&DataCommand::readMessage, this, std::ref(context), std::placeholders::_1, std::placeholders::_2));
}

void DataCommand::readMessage(ConnectionContext& context, const asio::error_code ec, int bytesTransferred)
{
    assert(handler);

    if (!ec)
    {
        context.getStream().async_read_until(messageBuffer, "\r\n.\r\n",
                                             std::bind(&DataCommand::handleReadMessage, this, std::ref(context),
                                                       std::placeholders::_1, std::placeholders::_2));
    }
}

void DataCommand::handleReadMessage(ConnectionContext& context, const asio::error_code ec, int bytesTransferred)
{
    assert(handler);

    if (!ec)
    {
        std::stringstream sstream;
        sstream << std::istream(&messageBuffer).rdbuf();
        std::string message = sstream.str();
        context.setMessage(message);
        context.getStream().async_write_some(asio::buffer("250 Ok\r\n"), handler);
    }
}