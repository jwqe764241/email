#pragma once

#include <initializer_list>
#include <map>
#include <utility>

#include "Smtp/SmtpCommandId.hpp"
#include "State.hpp"
#include "StateId.hpp"

class StateTable
{
public:
    StateTable(std::initializer_list<State> states);

    State& getState(StateId stateId);

private:
    std::map<StateId, State> stateMap;
};