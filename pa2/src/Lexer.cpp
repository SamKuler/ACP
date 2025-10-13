#include "Lexer.hpp"

Lexer::Lexer(const std::string &input)
  : input(input), pos(0), peek(0), line(1) {
  if (input.empty()) {
    peek = EOF_CHAR;
  } else {
    peek = static_cast<unsigned char>(input[0]);
  }
}

void Lexer::advance() {
  if (peek == '\n') ++line;
  // TODO: finish me. The advance() method moves the pointer 'pos' forward by one position. 
  // When the end of the string is reached, set 'peek' to EOF_CHAR.
  // You should use static_cast<unsigned char> to ensure 'peek' stores an unsigned char value.
}

void Lexer::resetPos(int newPos) {
  // TODO: finish me. The resetPos(int newPos) method resets 'pos' to newPos 
  // and updates 'peek' accordingly.
}
