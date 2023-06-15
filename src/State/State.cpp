#include "State/State.hpp"

State::State() {}

State::State(StateId stateId, std::initializer_list<std::pair<SmtpCommandId, StateTransition>> transitions)
    : stateId(stateId)
{
    transitionMap.insert(transitions.begin(), transitions.end());
}

State::State(const State &rhs)
{
    assert(this != &rhs);
    stateId = rhs.stateId;
    transitionMap = rhs.transitionMap;
}

StateId State::getStateId() const
{
    return stateId;
}

StateTransition &State::getTransition(SmtpCommandId smtpCommandId)
{
    return transitionMap[smtpCommandId];
}