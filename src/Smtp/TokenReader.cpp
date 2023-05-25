#include "Smtp/TokenReader.hpp"

bool isText(char c) 
{
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}

bool isNumber(char c)
{
    return '0' <= c && c <= '9';
}

TokenReader::TokenReader(const std::string& str)
    : str(str), pointer(0), hasPeeked(false), peeked()
{
}

Token TokenReader::peek()
{
    if (!hasPeeked)
    {
        peeked = readToken();
        hasPeeked = true;
    }

    return peeked;
}

Token TokenReader::take()
{
    if (hasPeeked)
    {
        hasPeeked = false;
        pointer += peeked.getStr().length();
        return peeked;
    }
    else
    {
        Token token = readToken();
        pointer += token.getStr().length();
        return token;
    }
}

void TokenReader::skip(TokenKind tokenKind)
{
    while(peek().getKind() == tokenKind) {
        take();
    }
}

void TokenReader::skip(std::function<bool(TokenKind)> predicate)
{
    while(predicate(peek().getKind())) {
        take();
    }
}

bool TokenReader::tryRead(std::function<bool(TokenReader&)> predicate, std::string* outStr)
{
    size_t prevPointer = pointer;

    if(predicate(*this)) {
        *outStr = std::string(str.begin() + prevPointer, str.begin() + pointer);
        return true;
    }
    else {
        pointer = prevPointer;
        peeked = Token();
        hasPeeked = false;
        return false;
    }
}

Token TokenReader::readToken()
{
    if (pointer >= str.length()) {
        return Token();
    }

    char c = str.at(pointer);

    if (isText(c)) {
        return Token(readWhile(isText), TokenKind::TEXT);
    }
    else if (isNumber(c)) {
        return Token(readWhile(isNumber), TokenKind::NUMBER);
    }
    else if(c == ' ') {
        return Token(readOne(), TokenKind::SPACE);
    }
    else if(c == '.') {
        return Token(readOne(), TokenKind::PERIOD);
    }
    else if(c == '@') {
        return Token(readOne(), TokenKind::AT);
    }
    else if(c == '-') {
        return Token(readOne(), TokenKind::HYPHEN);
    }
    else if(c == ':') {
        return Token(readOne(), TokenKind::COLON);
    }
    else if(c == '<') {
        return Token(readOne(), TokenKind::LESS_THAN);
    }
    else if(c == '>') {
        return Token(readOne(), TokenKind::GREATER_THAN);
    }
    else {
        return Token(readOne(), TokenKind::OTHER);
    }
}

std::string TokenReader::readOne()
{
    return str.substr(pointer, 1);
}

std::string TokenReader::readWhile(std::function<bool(char)> predicate)
{
    size_t count = 0;
    while (pointer + count < str.length() && predicate(str.at(pointer + count))) {
        ++count;
    }

    return str.substr(pointer, count);
}