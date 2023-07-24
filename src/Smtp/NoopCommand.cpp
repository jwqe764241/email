#include "Smtp/NoopCommand.hpp"

SmtpCommandId NoopCommand::getCommandId()
{
    return SmtpCommandId::Noop;
}

void NoopCommand::execute(ConnectionContext& context, std::function<void(const asio::error_code, int)> handler)
{
    context.getStream().writeAsync("250 OK\r\n", handler);
}