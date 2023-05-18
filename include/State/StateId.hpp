#pragma once

typedef enum class _StateId{
  None,
  Idle, // Before HELO.
  WaitForMail, // HELO command received. Waiting for mail command.
  WithinTransaction, // MAIL command received. Within transaction.
  CanAcceptData // RCPT command received. Can accept DATA command.
} StateId;