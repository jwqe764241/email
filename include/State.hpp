#pragma once

#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "asio.hpp"

#include "Connection.hpp"
#include "Request.hpp"

class Connection;

class State
{
public:
    virtual ~State() = default;
    virtual std::shared_ptr<State> processEvent(const Request &request) = 0;
};

class IdleState : public State, public std::enable_shared_from_this<IdleState>
{
public:
    IdleState(std::weak_ptr<Connection> connection);
    std::shared_ptr<State> processEvent(const Request &request);
    std::shared_ptr<IdleState> getPtr();

private:
    std::weak_ptr<Connection> connection;
};

class HeloState : public State, public std::enable_shared_from_this<HeloState>
{
public:
    HeloState();
    std::shared_ptr<State> processEvent(const Request &request);
    std::shared_ptr<HeloState> getPtr();
};

class MailState : public State, public std::enable_shared_from_this<MailState>
{
public:
    MailState();
    std::shared_ptr<State> processEvent(const Request &request);
    std::shared_ptr<MailState> getPtr();
};
