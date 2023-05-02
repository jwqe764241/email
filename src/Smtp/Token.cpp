#include "Smtp/Token.hpp"

Token::Token()
  : str(""), tokenKind(TokenKind::NONE)
{
}

Token::Token(std::string str, TokenKind tokenKind)
  : str(str), tokenKind(tokenKind)
{
}

const std::string& Token::getStr() const
{
  return str;
}

TokenKind Token::getKind() const
{
  return tokenKind;
}