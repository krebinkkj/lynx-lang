#ifndef LEXER_H
#define LEXER_H

#include <string>
#include "Token.h"

class Lexer {
  public:
    explicit Lexer(const std::string &source);
    Token getNextToken();
    Token peekNextToken();

  private:
    std::string source;
    size_t currentPos;
};

#endif