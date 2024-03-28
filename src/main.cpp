#include <iostream>

#include "Server/Server.hpp"

int main(int argc, char** argv)
{
    std::string configFilePath = argc >= 2 ? argv[1] : "./config.cnf";
    std::ifstream configFile(configFilePath);

    Server server(ServerConfig::fromFile(configFile));
    server.start();

    return 0;
}