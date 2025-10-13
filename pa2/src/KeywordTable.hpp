#pragma once
#include <string>
#include <unordered_map>
#include "Token.hpp"

class KeywordTable {
public:
  KeywordTable();
  Token getKeyword(const std::string &s) const;

private:
  std::unordered_map<std::string, Token> table;
};
