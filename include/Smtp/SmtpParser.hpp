#pragma once

#include <iostream>
#include <memory>

#include "TokenReader.hpp"
#include "SmtpCommand.hpp"
#include "HeloCommand.hpp"

class SmtpParser
{
public:
  SmtpParser() {}
  std::shared_ptr<SmtpCommand> parse(const std::string& str); 
  
private:
  std::shared_ptr<HeloCommand> parseHelo(const std::string& str);
  bool tryReadDomain(TokenReader& reader);
  bool tryReadSubDomain(TokenReader& reader);
  bool tryReadAlphanumeric(TokenReader& reader);
}; 