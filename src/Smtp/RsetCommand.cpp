#include "Smtp/RsetCommand.hpp"

SmtpCommandId RsetCommand::getCommandId()
{
    return SmtpCommandId::Rset;
}

void RsetCommand::execute(ConnectionContext& context, std::function<void(const asio::error_code, int)> handler)
{
    context.reset();
    context.getStream().writeAsync("250 OK\r\n", handler);
}