#include "Smtp/HeloCommand.hpp"

HeloCommand::HeloCommand(const std::string& domain)
    : domain(domain)
{}

SmtpCommandId HeloCommand::getCommandId()
{
    return SmtpCommandId::Helo;
}

void HeloCommand::execute(ConnectionContext& context, std::function<void(const asio::error_code, int)> handler)
{
    context.setDomain(domain);
    context.getSocket().async_write_some(asio::buffer("250 " + domain + "\r\n"), handler);
}

std::string HeloCommand::getDomain()
{
    return domain;
}