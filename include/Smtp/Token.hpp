#pragma once

#include <string>

#include "TokenKind.hpp"

class Token
{
public:
    Token();
    Token(std::string text, TokenKind kind);

    const std::string& getText() const;
    TokenKind getKind() const;

private:
    std::string text;
    TokenKind kind;
};