#pragma once

#include <iostream>
#include <string>

#include <asio.hpp>

class Server
{
public:
  Server();
  void start(std::string host, std::string port);

private:
  void handleAccept(const asio::error_code &ec);

private:
  std::string host;
  int port;
  asio::io_context ctx;
  asio::ip::tcp::socket listenSocket;
  asio::ip::tcp::acceptor acceptor;
};