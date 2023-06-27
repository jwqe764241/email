#pragma once

typedef enum class _TokenKind
{
    None,
    Text,
    Number,
    Space,
    Period,
    At,
    Hyphen,
    Colon,
    LessThan,
    GreaterThan,
    Other
} TokenKind;