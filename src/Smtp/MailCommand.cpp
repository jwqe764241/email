#include "Smtp/MailCommand.hpp"

MailCommand::MailCommand(const std::string& originator)
    : originator(originator)
{}

SmtpCommandId MailCommand::getCommandId()
{
    return SmtpCommandId::Mail;
}

void MailCommand::execute(ConnectionContext& context, std::function<void(const asio::error_code, int)> handler)
{
    context.setOriginator(originator);
    context.getSocket().async_write_some(asio::buffer("250 OK"), handler);
}

std::string MailCommand::getOriginator()
{
    return originator;
}