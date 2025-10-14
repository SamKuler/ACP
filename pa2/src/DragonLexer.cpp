#include "DragonLexer.hpp"
#include "Token.hpp"
#include <cctype>
#include <string>

DragonLexer::DragonLexer(const std::string &input)
    : Lexer(input) {}

Token DragonLexer::nextToken()
{
  if (peek == EOF_CHAR)
  {
    return Token(TokenType::EOF_T, "EOF", line);
  }

  if (std::isspace(peek))
  {
    return WS();
  }

  // TODO: finish me. You need to consider when to call ID()
  if (std::isalpha(peek)) // According to DragonLexerGrammer.g4: ID : LETTER (LETTER | DIGIT)* ;
  {
    return ID();
  }

  if (std::isdigit(peek))
  {
    return NUMBER();
  }

  int cur = peek;
  switch (cur)
  {
  // TODO: finish me. You need to consider EQ, NE, LT, LE, GT, GE
  case '=':
    advance();
    return Token(TokenType::EQ, "=", line);
  case '<':
    advance();
    if (peek == '=')
    {
      advance();
      return Token(TokenType::LE, "<=", line);
    }
    if (peek == '>')
    {
      advance();
      return Token(TokenType::NE, "<>", line);
    }
    return Token(TokenType::LT, "<", line);
  case '>':
    advance();
    if (peek == '=')
    {
      advance();
      return Token(TokenType::GE, ">=", line);
    }
    return Token(TokenType::GT, ">", line);
  case '(':
    advance();
    return Token(TokenType::L_PAREN, "(", line);
  case ')':
    advance();
    return Token(TokenType::R_PAREN, ")", line);
  case '{':
    advance();
    return Token(TokenType::L_BRACE, "{", line);
  case '}':
    advance();
    return Token(TokenType::R_BRACE, "}", line);
  case '[':
    advance();
    return Token(TokenType::L_BRACKET, "[", line);
  case ']':
    advance();
    return Token(TokenType::R_BRACKET, "]", line);
  case ',':
    advance();
    return Token(TokenType::COMMA, ",", line);
  case ';':
    advance();
    return Token(TokenType::SEMI, ";", line);
  case '+':
    advance();
    return Token(TokenType::PLUS, "+", line);
  case '-':
    advance();
    return Token(TokenType::MINUS, "-", line);
  case '*':
    advance();
    return Token(TokenType::MUL, "*", line);
  case '/':
    advance();
    return Token(TokenType::DIV, "/", line);
  case '.':
    advance();
    return Token(TokenType::DOT, ".", line);
  case '\'':
    advance();
    return Token(TokenType::SQUOTE, "\'", line);
  default:
    char ch = static_cast<char>(peek);
    std::string s(1, ch);
    advance();
    return Token(TokenType::UNKNOWN, s, line);
  }
}

Token DragonLexer::WS()
{
  // TODO: finish me. The WS() method should consume all whitespace characters (spaces, tabs, newlines)
  int startLine = line;
  int startPos = pos;
  while (isspace(peek))
  {
    advance();
  }
  std::string tx = input.substr(startPos, pos - startPos);
  return Token(TokenType::WS, std::move(tx), startLine);
}

Token DragonLexer::ID()
{
  // TODO: finish me. The ID() method should consume an identifier or keyword.
  int startPos = pos;
  int startLine = line;
  while ((isalpha(peek) && pos == startPos) || (isalnum(peek) && pos != startPos))
  {
    advance();
  }
  std::string tx = input.substr(startPos, pos - startPos);
  Token tk = kwTable.getKeyword(tx);
  tk.line = startLine;
  return tk;
}

Token DragonLexer::NUMBER()
{
  // TODO: finish me. The NUMBER() method should consume an integer, real number, or scientific notation number.
  int startPos = pos;
  int startLine = line;
  TokenType tkType = TokenType::INT;
  // 1. Check integer
  while (isdigit(peek))
  {
    advance();
    // skip '\'' and there's number left.
    if (peek == '\'' && pos + 1 < input.length() && std::isdigit(input[pos + 1]))
    {
      advance();
    }
  }
  // 2. Check real and sci if there's '.'
  if (peek == '.')
  {
    // next char must be digit
    if (pos + 1 < input.length() && std::isdigit(input[pos + 1]))
    {
      tkType = TokenType::REAL;
      advance(); // consume '.'
      // now get the decimal part
      while (isdigit(peek))
      {
        advance();
        // skip '\'' and there's number left.
        if (peek == '\'' && pos + 1 < input.length() && std::isdigit(input[pos + 1]))
        {
          advance();
        }
      }
    }
  }
  // real ends here.
  // 3. Check extra 'e' or 'E' for sci
  if (peek == 'e' || peek == 'E')
  {
    // try to get the rest part
    int savedPos = pos;
    advance(); // consume 'e' or 'E'
    // optional '+' or '-'
    if (peek == '+' || peek == '-')
    {
      advance();
    }
    if (std::isdigit(peek))
    {
      // yes, it's sci.
      tkType = TokenType::SCI;
      // now consume the digits.
      while (isdigit(peek))
      {
        advance();
        // skip '\'' and there's number left.
        if (peek == '\'' && pos + 1 < input.length() && std::isdigit(input[pos + 1]))
        {
          advance();
        }
      }
    }
    else // match failure
    {
      resetPos(savedPos);
    }
  }

  std::string tx = input.substr(startPos, pos - startPos);
  return Token(tkType, std::move(tx), startLine);
}
