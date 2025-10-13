cmake_minimum_required(VERSION 3.10)
project(DragonLexerCPP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(dragon_lexer
  src/main.cpp
  src/Lexer.cpp
  src/DragonLexer.cpp
  src/Token.cpp
  src/KeywordTable.cpp
)

target_include_directories(dragon_lexer PRIVATE src)
