#pragma once

#include <memory>

#include "Server/ConnectionContext.hpp"
#include "Smtp/SmtpCommand.hpp"
#include "StateId.hpp"
#include "StateTable.hpp"
#include "StateTransition.hpp"

class StateMachine
{
public:
    StateMachine(ConnectionContext& context, StateTable& stateTable);

    bool canAccept(std::shared_ptr<SmtpCommand> command);
    void transition(std::shared_ptr<SmtpCommand> command);

private:
    StateId currentState;
    ConnectionContext& context;
    StateTable stateTable;
};