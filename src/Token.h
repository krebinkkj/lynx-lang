#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType
{
  EOF_TOKEN,
  IDENTIFIER,
  NUMBER
};

struct Token {
  TokenType type;
  std::string value;
};

#endif