#include "Smtp/EhloCommand.hpp"

EhloCommand::EhloCommand(const std::string& domain)
    : domain(domain)
{}

SmtpCommandId EhloCommand::getCommandId()
{
    return SmtpCommandId::Ehlo;
}

void EhloCommand::execute(ConnectionContext& context, std::function<void(const asio::error_code, int)> handler)
{
    context.setDomain(domain);
    context.getStream().writeAsync("250-" + domain + "\r\n250 STARTTLS\r\n", handler);
}