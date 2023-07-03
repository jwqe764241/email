#include "Smtp/StartTlsCommand.hpp"

SmtpCommandId StartTlsCommand::getCommandId()
{
    return SmtpCommandId::StartTls;
}

void StartTlsCommand::execute(ConnectionContext& context, std::function<void(const asio::error_code, int)> handler)
{
    this->handler = handler;
    context.getStream().async_write_some(asio::buffer("220 ready\r\n"),
                                         std::bind(&StartTlsCommand::handleSendReady, this, std::ref(context),
                                                   std::placeholders::_1, std::placeholders::_2));
}

void StartTlsCommand::handleSendReady(ConnectionContext& context, const asio::error_code& ec, int bytesTransffered)
{
    context.getStream().upgrade(std::bind(handler, std::error_code{}, 0));
}