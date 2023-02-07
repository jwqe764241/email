#include <iostream>

#include "server.hpp"

int main(int argc, char **argv)
{
  Server server;
  server.start("127.0.0.1", "25");

  return 0;
}