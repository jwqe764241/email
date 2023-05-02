#pragma once

#include <string>

typedef enum class _TokenKind {
  NONE,
  TEXT,
  NUMBER,
  SPACE,
  PERIOD,
  AT,
  HYPHEN,
  OTHER
} TokenKind;

class Token
{
public:
  Token();
  Token(std::string str, TokenKind tokenKind);

  const std::string& getStr() const;
  TokenKind getKind() const;

private:
  std::string str;
  TokenKind tokenKind;
};