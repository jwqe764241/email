#pragma once

#include <memory>

#include "StateId.hpp"
#include "StateTable.hpp"
#include "StateTransition.hpp"
#include "Smtp/SmtpCommand.hpp"
#include "Server/ConnectionContext.hpp"

class StateMachine
{
public:
  StateMachine(ConnectionContext& context);

  bool canAccept(std::shared_ptr<SmtpCommand> command);
  void transition(std::shared_ptr<SmtpCommand> command);

private:
  StateId stateId;
  ConnectionContext& context;
  StateTable stateTable;
};