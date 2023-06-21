#include "State/State.hpp"

State::State() {}

State::State(std::initializer_list<std::pair<SmtpCommandId, StateTransition>> transitions)
{
    transitionMap.insert(transitions.begin(), transitions.end());
}

State::State(const State& rhs)
{
    assert(this != &rhs);
    transitionMap = rhs.transitionMap;
}

StateTransition& State::getTransition(SmtpCommandId smtpCommandId)
{
    return transitionMap[smtpCommandId];
}