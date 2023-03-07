#include "State.hpp"

IdleState::IdleState(asio::ip::tcp::socket &sock, Data &connectionData)
    : sock(sock), connectionData(connectionData)
{
    eventMap.emplace("HELO", [&](const Request &request) {
        std::string domain = request.getParameters()[0];
        connectionData.domain = domain;
        return std::make_shared<HeloState>();
    });
    sock.write_some(asio::buffer("220 Hello\r\n"));
}

std::shared_ptr<State> IdleState::processEvent(const Request &request)
{
    auto it = eventMap.find(request.getCommand());
    if (it != eventMap.end())
    {
        auto processor = it->second;
        return processor(request);
    }
    else
    {
        std::cout << "not allowed" << std::endl;
        return getPtr();
    }
}

std::shared_ptr<IdleState> IdleState::getPtr()
{
    return shared_from_this();
}

HeloState::HeloState()
{
    eventMap.emplace("MAIL", [&](const Request &request) {
        std::cout << "transit to MailState" << std::endl;
        return std::make_shared<MailState>();
    });
}

std::shared_ptr<State> HeloState::processEvent(const Request &request)
{
    auto it = eventMap.find(request.getCommand());
    if (it != eventMap.end())
    {
        auto processor = it->second;
        return processor(request);
    }
    else
    {
        std::cout << "not allowed" << std::endl;
        return getPtr();
    }
}

std::shared_ptr<HeloState> HeloState::getPtr()
{
    return shared_from_this();
}

MailState::MailState()
{
    eventMap.emplace("HELO", [&](const Request &request) {
        std::cout << "transit to HeloState";
        return std::make_shared<HeloState>();
    });
}

std::shared_ptr<State> MailState::processEvent(const Request &request)
{
    auto it = eventMap.find(request.getCommand());
    if (it != eventMap.end())
    {
        auto processor = it->second;
        return processor(request);
    }
    else
    {
        std::cout << "not allowed" << std::endl;
        return getPtr();
    }
}

std::shared_ptr<MailState> MailState::getPtr()
{
    return shared_from_this();
}
