#include <iostream>

#include "Server/ConfigParser.hpp"
#include "Server/Server.hpp"

int main(int argc, char** argv)
{
    std::ifstream configFile(argc >= 2 ? argv[1] : "./config.cnf");
    if (!configFile.is_open())
    {
        std::cout << "Can't open config file. Make sure your config file exists." << std::endl;
        std::cout << "Usage: email [config path=./config.cnf]" << std::endl;
        return 0;
    }

    Server server(parseConfig(configFile));
    server.start();

    return 0;
}