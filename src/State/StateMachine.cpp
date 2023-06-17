#include "State/StateMachine.hpp"

StateMachine::StateMachine(ConnectionContext& context)
    : context(context)
    , stateTable(
          {State(
               StateId::Idle,
               {{SmtpCommandId::Helo, StateTransition([]() { return true; }, []() { return StateId::WaitForMail; })},
                {SmtpCommandId::Ehlo, StateTransition([]() { return true; }, []() { return StateId::WaitForMail; })}}),
           State(StateId::WaitForMail,
                 {{SmtpCommandId::Mail,
                   StateTransition([]() { return true; }, []() { return StateId::WithinTransaction; })}}),
           State(StateId::WithinTransaction,
                 {{SmtpCommandId::Rcpt,
                   StateTransition([]() { return true; }, []() { return StateId::CanAcceptData; })}}),
           State(StateId::CanAcceptData,
                 {{SmtpCommandId::Rcpt,
                   StateTransition([]() { return true; }, []() { return StateId::CanAcceptData; })}})})
{
    stateId = StateId::Idle;
}

bool StateMachine::canAccept(std::shared_ptr<SmtpCommand> command)
{
    State& state = stateTable.getState(stateId);
    StateTransition& transition = state.getTransition(command->getCommandId());
    return transition.canTransition();
}

void StateMachine::transition(std::shared_ptr<SmtpCommand> command)
{
    State& state = stateTable.getState(stateId);
    StateTransition& transition = state.getTransition(command->getCommandId());
    stateId = transition.transition();
}