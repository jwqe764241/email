#include "State/StateTable.hpp"

StateTable::StateTable(std::initializer_list<std::pair<StateId, State>> states)
{
    for (auto& state : states)
    {
        stateMap[state.first] = state.second;
    }
}

State& StateTable::getState(StateId stateId)
{
    return stateMap[stateId];
}

StateTable& StateTable::getInstance()
{
    static StateTable stateTable(
        {{StateId::Idle,
          {{SmtpCommandId::Quit, StateTransition([]() { return StateId::Idle; })},
           {SmtpCommandId::Helo, StateTransition([]() { return StateId::WaitForMail; })},
           {SmtpCommandId::Ehlo, StateTransition([]() { return StateId::WaitForMail; })}}},
         {StateId::WaitForMail,
          {{SmtpCommandId::Quit, StateTransition([]() { return StateId::Idle; })},
           {SmtpCommandId::Mail, StateTransition([]() { return StateId::WithinTransaction; })}}},
         {StateId::WithinTransaction,
          {{SmtpCommandId::Quit, StateTransition([]() { return StateId::Idle; })},
           {SmtpCommandId::Rcpt, StateTransition([]() { return StateId::CanAcceptData; })}}},
         {StateId::CanAcceptData,
          {{SmtpCommandId::Quit, StateTransition([]() { return StateId::Idle; })},
           {SmtpCommandId::Rcpt, StateTransition([]() { return true; }, []() { return StateId::CanAcceptData; })},
           {SmtpCommandId::Data, StateTransition([]() { return true; }, []() { return StateId::Idle; })}}}});

    return stateTable;
}