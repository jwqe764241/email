#include "State/StateMachine.hpp"

StateMachine::StateMachine(ConnectionContext& context, StateTable& stateTable)
    : context(context)
    , stateTable(stateTable)
    , currentState(StateId::Idle)
{}

bool StateMachine::canAccept(std::shared_ptr<SmtpCommand> command)
{
    State& state = stateTable.getState(currentState);
    StateTransition& transition = state.getTransition(command->getCommandId());
    return transition.canTransition();
}

void StateMachine::transition(std::shared_ptr<SmtpCommand> command)
{
    State& state = stateTable.getState(currentState);
    StateTransition& transition = state.getTransition(command->getCommandId());
    currentState = transition.transition();
}