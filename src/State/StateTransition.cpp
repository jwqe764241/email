#include "State/StateTransition.hpp"

StateTransition::StateTransition()
{
}

StateTransition::StateTransition(std::function<bool()> canTransitionDelegate, std::function<StateId()> transitionDelegate)
  : canTransitionDelegate(canTransitionDelegate)
  , transitionDelegate(transitionDelegate)
{
}

bool StateTransition::canTransition() const
{
  assert(canTransitionDelegate);
  return canTransitionDelegate();
}

StateId StateTransition::transition() const
{
  assert(transitionDelegate);
  return transitionDelegate();
}