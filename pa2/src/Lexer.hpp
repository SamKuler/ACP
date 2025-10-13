#pragma once
#include <string>
#include "Token.hpp"

class Lexer {
public:
  static const int EOF_CHAR = -1;

  Lexer(const std::string &input);

  virtual ~Lexer() = default;
  virtual Token nextToken() = 0;

protected:
  std::string input;
  int pos;  // current position in input
  int peek; // current char or EOF_CHAR
  int line; // current line number

  void advance(); // consume current char and advance to next char
  void resetPos(int newPos); // reset pos to newPos and update peek accordingly
};
