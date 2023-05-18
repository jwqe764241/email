#include "Smtp/SmtpParser.hpp"

std::shared_ptr<SmtpCommand> SmtpParser::parse(const std::string& str)
{
  return parseHelo(str);
}

std::shared_ptr<HeloCommand> SmtpParser::parseHelo(const std::string& str)
{
  TokenReader reader(str);

  Token command = reader.take();
  if(command.getStr() != "HELO") {
    return nullptr;
  }

  reader.skip(TokenKind::SPACE);

  std::string domain;
  bool result = reader.tryRead(std::bind(SmtpParser::tryReadDomain, this, std::placeholders::_1), &domain);
  
  return result ? std::make_shared<HeloCommand>(domain) : nullptr;
}

bool SmtpParser::tryReadDomain(TokenReader& reader) {
  //read first subdomain
  if(!tryReadSubDomain(reader)) {
    return false;
  }

  while(reader.peek().getKind() == TokenKind::PERIOD) {
    reader.take();

    if(!tryReadSubDomain(reader)) {
      return false;
    }
  }

  return true;
}

bool SmtpParser::tryReadSubDomain(TokenReader& reader) {
  //check first is alphanumeric
  if(tryReadAlphanumeric(reader) == false) {
    return false;
  }
  
  reader.skip([](TokenKind tokenKind){
    return tokenKind == TokenKind::TEXT || tokenKind == TokenKind::NUMBER;
  });

  return true;
}

bool SmtpParser::tryReadAlphanumeric(TokenReader& reader)
{
  TokenKind tokenKind = reader.peek().getKind();
  if(tokenKind == TokenKind::TEXT || tokenKind == TokenKind::NUMBER) {
    reader.take();
    return true;
  }
  return false;
}