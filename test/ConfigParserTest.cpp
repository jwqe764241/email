#include <catch_amalgamated.hpp>
#include <sstream>

#include "Server/ConfigParser.hpp"

TEST_CASE("parseConfig parses strings written as [key]=[value]")
{
    std::string str = R"(
        IP = 127.0.0.1
        PORT = 8080
        CERT_PATH=./aaa.example.com.pem
    )";
    std::stringstream sstream(str);

    auto map = parseConfig(sstream);

    REQUIRE(map.size() == 3);
    REQUIRE(map["IP"] == "127.0.0.1");
    REQUIRE(map["PORT"] == "8080");
    REQUIRE(map["CERT_PATH"] == "./aaa.example.com.pem");
}

TEST_CASE("parseConfig ignores empty lines, blanks and tabs")
{
    std::string str = R"(
        AAA =     AAA


        BBB =            BBB



        CCC         =       CCC
    )";
    std::stringstream sstream(str);

    auto map = parseConfig(sstream);

    REQUIRE(map.size() == 3);
    REQUIRE(map["AAA"] == "AAA");
    REQUIRE(map["BBB"] == "BBB");
    REQUIRE(map["CCC"] == "CCC");
}

TEST_CASE("parseConfig parses value as empty string when value is empty")
{
    std::string str = "AAA=";
    std::stringstream sstream(str);

    auto map = parseConfig(sstream);

    REQUIRE(map.size() == 1);
    REQUIRE(map["AAA"] == "");
}

TEST_CASE("parseConfig ignores comment starts with #")
{
    std::string str = R"(
        # Server Config
        IP = 127.0.0.1
        PORT = 8080 # something blah blah

        # Certificate Config
        CERT_PATH=./aaa.example.com.pem // path your .pem file
    )";
    std::stringstream sstream(str);

    auto map = parseConfig(sstream);

    REQUIRE(map.size() == 3);
    REQUIRE(map["IP"] == "127.0.0.1");
    REQUIRE(map["PORT"] == "8080");
    REQUIRE(map["CERT_PATH"] == "./aaa.example.com.pem");
}