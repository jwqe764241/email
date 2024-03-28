#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>

struct ServerConfig
{
    std::string host;
    std::string port;
    std::string certPath;

    static ServerConfig fromFile(std::istream& file);
};