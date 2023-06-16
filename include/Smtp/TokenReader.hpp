#pragma once

#include <functional>
#include <string>

#include "Token.hpp"

class TokenReader
{
public:
    TokenReader(const std::string& str);

    Token peek();
    Token take();
    void skip(TokenKind tokenKind);
    void skip(std::function<bool(TokenKind)> predicate);
    bool tryRead(std::function<bool(TokenReader&)> predicate, std::string* outStr);

private:
    Token readToken();
    std::string readOne();
    std::string readWhile(std::function<bool(char)> predicate);

private:
    const std::string str;
    size_t pointer;
    Token peeked;
    bool hasPeeked;
};