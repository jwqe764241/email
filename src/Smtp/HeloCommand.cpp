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
    context.getStream().writeAsync("250 " + domain + "\r\n", handler);
}