#include "Lexer.h"
#include <cctype>

Lexer::Lexer(const std::string& source) : source(source), currentPos(0) {}

Token Lexer::getNextToken() {
  while(currentPos < source.length() && isspace(source[currentPos])) {
    currentPos++;
  }

  if (currentPos >= source.length()) {
    return {TokenType::EOF_TOKEN, ""};
  }

  char currentChar = source[currentPos];

  if (isdigit(currentChar)) {
    std::string number;
    while (currentPos < source.length() && isdigit(source[currentPos])) {
      number += source[currentPos];
      currentPos++;
    }
    return {TokenType::NUMBER, number};
  }

  if (isalpha(currentChar) || currentChar == '_') {
    std::string identifier;
    while (currentPos < source.length() && (isalnum(source[currentPos]) || source[currentPos] == '_')) {
      identifier += source[currentPos];
      currentPos++;
    }
    return {TokenType::IDENTIFIER, identifier};

    switch(currentChar) {
      case '+':
        currentPos++;
        return {TokenType::PLUS, "+"};
      case '-':
        currentPos++;
        return {TokenType::MINUS, "-"};

      case '*':
        currentPos++;
        return {TokenType::MULTIPLY, "*"};

      case '/':
        currentPos++;
        return {TokenType::DIVIDE, "/"};
      }
  }

  return {TokenType::EOF_TOKEN, ""};
}