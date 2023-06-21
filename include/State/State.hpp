#pragma once

#include <cassert>
#include <initializer_list>
#include <map>
#include <string>
#include <utility>

#include "Smtp/SmtpCommandId.hpp"
#include "StateId.hpp"
#include "StateTransition.hpp"

class State
{
public:
    State();
    State(std::initializer_list<std::pair<SmtpCommandId, StateTransition>> transitions);
    State(const State& rhs);

    StateTransition& getTransition(SmtpCommandId smtpCommandId);

private:
    std::map<SmtpCommandId, StateTransition> transitionMap;
};