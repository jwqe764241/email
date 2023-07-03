#include "Smtp/RcptCommand.hpp"

RcptCommand::RcptCommand(const std::string& recipient)
    : recipient(recipient)
{}

SmtpCommandId RcptCommand::getCommandId()
{
    return SmtpCommandId::Rcpt;
}

void RcptCommand::execute(ConnectionContext& context, std::function<void(const asio::error_code, int)> handler)
{
    context.addTo(recipient);
    context.getStream().async_write_some(asio::buffer("250 OK\r\n"), handler);
}