#pragma once

typedef enum class _SmtpCommandId
{
    None,
    Helo,
    Ehlo,
    Mail,
    Rcpt,
    Data,
    Quit,
    Noop
} SmtpCommandId;