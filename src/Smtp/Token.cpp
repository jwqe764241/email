#include "Smtp/Token.hpp"

Token::Token()
    : text("")
    , kind(TokenKind::None)
{}

Token::Token(std::string text, TokenKind kind)
    : text(text)
    , kind(kind)
{}

const std::string& Token::getText() const
{
    return text;
}

TokenKind Token::getKind() const
{
    return kind;
}