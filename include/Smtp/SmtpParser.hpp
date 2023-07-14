#pragma once

#include <algorithm>
#include <exception>
#include <iostream>
#include <memory>
#include <regex>

#include "DataCommand.hpp"
#include "EhloCommand.hpp"
#include "HeloCommand.hpp"
#include "MailCommand.hpp"
#include "NoopCommand.hpp"
#include "QuitCommand.hpp"
#include "RcptCommand.hpp"
#include "RsetCommand.hpp"
#include "SmtpCommand.hpp"
#include "StartTlsCommand.hpp"

std::string parseMailArgument(std::string& argument);

std::string parseRcptArgument(std::string& argument);

std::shared_ptr<SmtpCommand> parseSmtpCommand(std::string request);
