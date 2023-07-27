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
    return stateMap.at(stateId);
}

StateTable& StateTable::getInstance()
{
    static StateTable stateTable(
        {{StateId::Idle,
          {{SmtpCommandId::Quit, StateTransition([]() { return StateId::Idle; })},
           {SmtpCommandId::Noop, StateTransition([]() { return StateId::Idle; })},
           {SmtpCommandId::Rset, StateTransition([]() { return StateId::Idle; })},
           {SmtpCommandId::Helo, StateTransition([]() { return StateId::WaitForMail; })},
           {SmtpCommandId::Ehlo, StateTransition([]() { return StateId::WaitForMail; })}}},
         {StateId::WaitForMail,
          {{SmtpCommandId::Quit, StateTransition([]() { return StateId::WaitForMail; })},
           {SmtpCommandId::StartTls, StateTransition([]() { return StateId::WaitForMail; })},
           {SmtpCommandId::Noop, StateTransition([]() { return StateId::WaitForMail; })},
           {SmtpCommandId::Rset, StateTransition([]() { return StateId::WaitForMail; })},
           {SmtpCommandId::Ehlo, StateTransition([]() { return StateId::WaitForMail; })},
           {SmtpCommandId::Mail, StateTransition([]() { return StateId::WithinTransaction; })}}},
         {StateId::WithinTransaction,
          {{SmtpCommandId::Quit, StateTransition([]() { return StateId::WithinTransaction; })},
           {SmtpCommandId::Noop, StateTransition([]() { return StateId::WithinTransaction; })},
           {SmtpCommandId::Rset, StateTransition([]() { return StateId::WaitForMail; })},
           {SmtpCommandId::Rcpt, StateTransition([]() { return StateId::CanAcceptData; })}}},
         {StateId::CanAcceptData,
          {{SmtpCommandId::Quit, StateTransition([]() { return StateId::CanAcceptData; })},
           {SmtpCommandId::Noop, StateTransition([]() { return StateId::CanAcceptData; })},
           {SmtpCommandId::Rset, StateTransition([]() { return StateId::WaitForMail; })},
           {SmtpCommandId::Rcpt, StateTransition([]() { return StateId::CanAcceptData; })},
           {SmtpCommandId::Data, StateTransition([]() { return StateId::Idle; })}}}});

    return stateTable;
}