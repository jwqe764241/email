#include "Server/ConnectionContext.hpp"

ConnectionContext::ConnectionContext(asio::ip::tcp::socket sock)
  : sock(std::move(sock))
{
}

ConnectionContext::~ConnectionContext()
{
  sock.close();
}

asio::ip::tcp::socket& ConnectionContext::getSocket()
{
  return sock;
}

asio::streambuf& ConnectionContext::getBuffer()
{
  return buffer;
}

void ConnectionContext::setOnDisconnect(std::function<void()> onDisconnect)
{
  this->onDisconnect = onDisconnect;
}

void ConnectionContext::disconnect()
{
  onDisconnect();
}

const std::string& ConnectionContext::getDomain() const
{
  return domain;
}

void ConnectionContext::setDomain(const std::string& domain)
{
  this->domain = domain;
}

const std::string& ConnectionContext::getOriginator() const
{
  return originator;
}

void ConnectionContext::setOriginator(const std::string& originator)
{
  this->originator = originator;
}

const std::vector<std::string> ConnectionContext::getTo() const
{
  return to;
}

void ConnectionContext::addTo(const std::string& to)
{
  this->to.push_back(to);
}