#pragma once

#include <map>
#include <string>
#include <initializer_list>
#include <utility>
#include <cassert>

#include "StateId.hpp"
#include "StateTransition.hpp"
#include "Smtp/SmtpCommandId.hpp"

class State
{
public:
  State();
  State(StateId stateId, std::initializer_list<std::pair<SmtpCommandId, StateTransition>> transitions);
  State(const State& rhs);

  StateId getStateId() const;
  StateTransition& getTransition(SmtpCommandId smtpCommandId);

private:
  StateId stateId;
  std::map<SmtpCommandId, StateTransition> transitionMap;
};