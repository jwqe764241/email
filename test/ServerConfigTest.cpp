#include <catch_amalgamated.hpp>
#include <sstream>

#include "Server/ServerConfig.hpp"

TEST_CASE("fromFile parses strings written as [key]=[value]")
{
    std::string str = R"(
        HOST = 127.0.0.1
        PORT = 8080
        CERT_PATH = ./aaa.example.com.pem
    )";
    std::stringstream sstream(str);

    auto config = ServerConfig::fromFile(sstream);

    REQUIRE(config.host == "127.0.0.1");
    REQUIRE(config.port == "8080");
    REQUIRE(config.certPath == "./aaa.example.com.pem");
}

TEST_CASE("fromFile ignores comment starts with #")
{
    std::string str = R"(
        # Server Config
        HOST = 127.0.0.1
        PORT = 8080 # something blah blah

        # Certificate Config
        CERT_PATH = ./aaa.example.com.pem # path your .pem file
    )";
    std::stringstream sstream(str);

    auto config = ServerConfig::fromFile(sstream);

    REQUIRE(config.host == "127.0.0.1");
    REQUIRE(config.port == "8080");
    REQUIRE(config.certPath == "./aaa.example.com.pem");
}

TEST_CASE("fromFile throws runtime_error when bad file stream")
{
    std::ifstream failBitFile;
    failBitFile.setstate(failBitFile.failbit);
    std::ifstream badBitFile;
    badBitFile.setstate(badBitFile.badbit);

    REQUIRE_THROWS_AS([&]() { ServerConfig::fromFile(failBitFile); }(), std::runtime_error);
    REQUIRE_THROWS_AS([&]() { ServerConfig::fromFile(badBitFile); }(), std::runtime_error);
}

TEST_CASE("fromFile throws runtime_error when invalid config form")
{
    SECTION("Key is empty")
    {
        std::string str = "  = 127.0.0.1";
        std::stringstream sstream(str);

        REQUIRE_THROWS_AS([&]() { ServerConfig::fromFile(sstream); }(), std::runtime_error);
    }

    SECTION("Value is empty")
    {
        std::string str = "HOST = ";
        std::stringstream sstream(str);

        auto config = ServerConfig::fromFile(sstream);

        REQUIRE(config.host.empty());
    }

    SECTION("Wrong separator")
    {
        std::string str = "HOST : 127.0.0.1";
        std::stringstream sstream(str);

        REQUIRE_THROWS_AS([&]() { ServerConfig::fromFile(sstream); }(), std::runtime_error);
    }
}