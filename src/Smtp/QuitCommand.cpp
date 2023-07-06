#include "Smtp/QuitCommand.hpp"

SmtpCommandId QuitCommand::getCommandId()
{
    return SmtpCommandId::Quit;
}

void QuitCommand::execute(ConnectionContext& context, std::function<void(const asio::error_code, int)> handler)
{
    context.getStream().async_write_some(
        asio::buffer("221 OK"), [&context](const asio::error_code& ec, int bytesTransferred) { context.disconnect(); });
}