#pragma once

#include <algorithm>
#include <fstream>
#include <map>
#include <stdexcept>

std::map<std::string, std::string> parseConfig(std::istream& source);