#include <iostream>
#include <sstream>
#include "DragonLexer.hpp"
#include "Token.hpp"

int main() {
  std::ostringstream ss;
  ss << std::cin.rdbuf();
  std::string input = ss.str();

  DragonLexer lexer(input);
  while (true) {
    Token t = lexer.nextToken();
    if (t.type == TokenType::WS) {
      continue;
    } else if (t.type == TokenType::EOF_T) {
      break;
    } else {
      std::string typ = tokenTypeToString(t.type);
      std::cout << typ << " " << t.text << " at Line " << t.line << "." << std::endl;
    }
  }
  return 0;
}
