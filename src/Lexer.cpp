#include "Lexer.h"
#include <cctype>

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

  // Checar por identificadores (letras e _)
  if (isalpha(currentChar) || currentChar == '_')
  {
    std::string identifier;
    while (currentPos < source.length() && (isalnum(source[currentPos]) || source[currentPos] == '_'))
    {
      identifier += source[currentPos];
      currentPos++;
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
  }

  // Se não for nenhum dos tipos acima, consideramos o fim
  return {TokenType::EOF_TOKEN, ""};
}