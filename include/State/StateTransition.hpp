#pragma once

#include <functional>
#include <cassert>

#include "StateId.hpp"

class StateTransition
{
public:
  StateTransition();
  StateTransition(std::function<bool()> canTransitionDelegate, std::function<StateId()> transitionDelegate);

  bool canTransition() const;
  StateId transition() const;

private:
  std::function<bool()> canTransitionDelegate;
  std::function<StateId()> transitionDelegate;
};