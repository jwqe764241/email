#include "Smtp/QuitCommand.hpp"

SmtpCommandId QuitCommand::getCommandId()
{
    return SmtpCommandId::Quit;
}

void QuitCommand::execute(ConnectionContext& context, std::function<void(const asio::error_code, int)> handler)
{
    context.getStream().writeAsync(
        "221 OK\r\n", [&context](const asio::error_code& ec, int bytesTransferred) { context.disconnect(); });
}