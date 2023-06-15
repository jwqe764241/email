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
    State(StateId stateId, std::initializer_list<std::pair<SmtpCommandId, StateTransition>> transitions);
    State(const State &rhs);

    StateId getStateId() const;
    StateTransition &getTransition(SmtpCommandId smtpCommandId);

private:
    StateId stateId;
    std::map<SmtpCommandId, StateTransition> transitionMap;
};