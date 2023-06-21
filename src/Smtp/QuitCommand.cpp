#include "Smtp/QuitCommand.hpp"

SmtpCommandId QuitCommand::getCommandId()
{
    return SmtpCommandId::Quit;
}

void QuitCommand::execute(ConnectionContext& context, std::function<void(const asio::error_code, int)> handler)
{
    context.disconnect();
}