#pragma once

#include <functional>
#include <string>
#include <vector>

#include "asio.hpp"
#include "asio/ssl.hpp"

#include "SecuredStream.hpp"

class ConnectionContext
{
public:
    ConnectionContext(SecuredStream stream);
    ~ConnectionContext();

    SecuredStream& getStream();
    asio::streambuf& getBuffer();
    void setOnDisconnect(std::function<void()> onDisconnect);
    void disconnect();
    const std::string& getDomain() const;
    void setDomain(const std::string& domain);
    const std::string& getOriginator() const;
    void setOriginator(const std::string& originator);
    const std::vector<std::string>& getTo() const;
    void addTo(const std::string& to);
    const std::string& getMessage() const;
    void setMessage(const std::string& message);
    void reset();

private:
    SecuredStream stream;
    asio::streambuf buffer;
    std::function<void()> onDisconnect;
    std::string domain;
    std::string originator;
    std::vector<std::string> to;
    std::string message;
};