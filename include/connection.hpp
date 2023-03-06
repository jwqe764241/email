#pragma once

#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <functional>

#include "asio.hpp"

const int BUFFER_SIZE = 1024;

class Connection
{
public:
  Connection(asio::ip::tcp::socket sock_);
  ~Connection();

  void start(std::function<void()> &&onDisconnect);

private:
  void handleRead(const asio::error_code ec, int bytesTransferred);

private:
  asio::ip::tcp::socket sock;
  asio::streambuf buffer;
  std::function<void()> onDisconnect;
};