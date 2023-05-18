#pragma once

#include <map>
#include <initializer_list>
#include <utility>

#include "StateId.hpp"
#include "State.hpp"
#include "Smtp/SmtpCommandId.hpp"

class StateTable
{
public:
  StateTable(std::initializer_list<State> states);

  State& getState(StateId stateId);

private:
  std::map<StateId, State> stateMap;
};