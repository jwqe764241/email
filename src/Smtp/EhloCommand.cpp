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
    context.getSocket().async_write_some(asio::buffer("502 Command not implemented\r\n"), handler);
}

std::string EhloCommand::getDomain()
{
    return domain;
}