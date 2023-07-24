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
    context.getStream().writeAsync("250 OK\r\n", handler);
}