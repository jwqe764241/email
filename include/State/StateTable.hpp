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
    StateTable(){};
    StateTable(std::initializer_list<std::pair<StateId, State>>);

    State& getState(StateId stateId);

    static StateTable& getInstance();

private:
    std::map<StateId, State> stateMap;
};
