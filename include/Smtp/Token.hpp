#pragma once

#include <string>

#include "TokenId.hpp"

class Token
{
public:
    Token();
    Token(std::string str, TokenKind tokenKind);

    const std::string &getStr() const;
    TokenKind getKind() const;

private:
    std::string str;
    TokenKind tokenKind;
};