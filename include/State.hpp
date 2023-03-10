#pragma once

#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "asio.hpp"

#include "ConnectionData.hpp"
#include "Request.hpp"

class State;

using EventProcessor = std::function<std::shared_ptr<State>(const Request &)>;
using EventProcessorMap = std::unordered_map<std::string, EventProcessor>;

class State
{
public:
    virtual ~State() = default;
    virtual std::shared_ptr<State> processEvent(const Request &request) = 0;
};

class IdleState : public State, public std::enable_shared_from_this<IdleState>
{
public:
    IdleState(asio::ip::tcp::socket &sock, ConnectionData &connectionData);
    std::shared_ptr<State> processEvent(const Request &request);
    std::shared_ptr<IdleState> getPtr();

private:
    EventProcessorMap eventMap;
    asio::ip::tcp::socket &sock;
    ConnectionData &connectionData;
};

class HeloState : public State, public std::enable_shared_from_this<HeloState>
{
public:
    HeloState();
    std::shared_ptr<State> processEvent(const Request &request);
    std::shared_ptr<HeloState> getPtr();

private:
    EventProcessorMap eventMap;
};

class MailState : public State, public std::enable_shared_from_this<MailState>
{
public:
    MailState();
    std::shared_ptr<State> processEvent(const Request &request);
    std::shared_ptr<MailState> getPtr();

private:
    EventProcessorMap eventMap;
};
