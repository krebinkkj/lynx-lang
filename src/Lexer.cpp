#include "Lexer.h"
#include <cctype>
#include <iostream>

Lexer::Lexer(const std::string &source)
    : source(source), currentPos(0) {}

Token Lexer::getNextToken()
{
  // Pular espaços em branco
  while (currentPos < source.length() && isspace(source[currentPos]))
  {
    currentPos++;
  }

  // Checar se chegamos ao fim do arquivo
  if (currentPos >= source.length())
  {
    return {TokenType::EOF_TOKEN, ""};
  }

  char currentChar = source[currentPos];

  // Checar por números
  if (isdigit(currentChar))
  {
    std::string number;
    while (currentPos < source.length() && isdigit(source[currentPos]))
    {
      number += source[currentPos];
      currentPos++;
    }
    return {TokenType::NUMBER, number};
  }

  // Checar por identificadores e palavras-chave
  if (isalpha(currentChar) || currentChar == '_')
  {
    std::string identifier;
    while (currentPos < source.length() && (isalnum(source[currentPos]) || source[currentPos] == '_'))
    {
      identifier += source[currentPos];
      currentPos++;
    }

    // Verifica se o identificador é uma palavra-chave
    if (identifier == "if") {
      return {TokenType::IF, "if"};
    } else if (identifier == "else") {
      return {TokenType::ELSE, "else"};
    } else if (identifier == "func") {
      return {TokenType::FUNC, "func"};
    }
    return {TokenType::IDENTIFIER, identifier};
  }

  // Checar por operadores e parênteses
  switch (currentChar)
  {
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
  case '(':
    currentPos++;
    return {TokenType::LPAREN, "("}; // Token temporário para '(', será corrigido
  case ')':
    currentPos++;
    return {TokenType::RPAREN, ")"}; // Token temporário para ')', será corrigido
  case '=':
    if (source[currentPos + 1] == '=') {
      currentPos += 2;
      return {TokenType::EQ, "=="};
    }
    currentPos++;
    return {TokenType::ASSIGN, "="};
  case ';':
    currentPos++;
    return {TokenType::SEMICOLON, ";"};

  case '!':
    if (source[currentPos + 1] == '=') {
      currentPos += 2;
      return {TokenType::NEQ, "!="};
    }
    break;

  case '<':
    currentPos++;
    return {TokenType::LT, "<"};

  case '>':
    currentPos++;
    return {TokenType::GT, ">"};
  case '{':
    currentPos++;
    return {TokenType::LBRACE, "{"};

  case '}':
    currentPos++;
    return {TokenType::RBRACE, "}"};

  case ',':
    currentPos++;
    return {TokenType::COMMA, ","};
  }

  std::cerr << "Erro léxico: Caractere inesperado '" << currentChar << "'" << std::endl;
  return {TokenType::EOF_TOKEN, ""};
}

Token Lexer::peekNextToken() {
  size_t oldPos = currentPos;
  Token nextToken = getNextToken();
  currentPos = oldPos;
  return nextToken;
}