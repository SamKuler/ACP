#pragma once
#include "Lexer.hpp"
#include "KeywordTable.hpp"

class DragonLexer : public Lexer {
public:
  DragonLexer(const std::string &input);
  Token nextToken() override;

private:
  KeywordTable kwTable;

  Token WS();
  Token ID();
  Token NUMBER(); // handles INT/REAL/SCI
};
