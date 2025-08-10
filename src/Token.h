#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType
{
  // Fim do arquivo
  EOF_TOKEN,

  // Identificadores (nomes de variáveis, funções)
  IDENTIFIER,

  // Literais
  NUMBER,

  // Operadores
  PLUS,     // +
  MINUS,    // -
  MULTIPLY, // *
  DIVIDE,   // /

  // Parênteses
  LPAREN, // (
  RPAREN, // )

  // Atribuição
  ASSIGN, // =
};

struct Token
{
  TokenType type;
  std::string value;
};

#endif