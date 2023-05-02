#pragma once

#include <string>
#include <vector>
#include <functional>

#include "asio.hpp"

class ConnectionContext
{
public:
  ConnectionContext(asio::ip::tcp::socket sock);
  ~ConnectionContext();
  
  asio::ip::tcp::socket& getSocket();
  asio::streambuf& getBuffer();
  void setOnDisconnect(std::function<void()> onDisconnect);
  void disconnect();
  const std::string& getDomain() const;
  void setDomain(const std::string& domain);
  const std::string& getFrom() const;
  void setFrom(const std::string& from);
  const std::vector<std::string> getTo() const;
  void addTo(const std::string& to);
  
private:
  asio::ip::tcp::socket sock;
  asio::streambuf buffer;
  std::function<void()> onDisconnect;
  std::string domain;
  std::string from;
  std::vector<std::string> to;
};