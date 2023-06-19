#include <iostream>

#include "Server/Server.hpp"

int main(int argc, char** argv)
{
    Server server;
    server.start("192.168.0.5", "2500");

    return 0;
}