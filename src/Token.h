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

  // Separador de intruções
  SEMICOLON, // ;

  // Palavras-chave
  IF, // if
  ELSE, // else
  FUNC, // func

  // Operadores de comparação
  EQ, // ==
  NEQ, // !=
  LT, // <
  GT, // >

  // Símbolos de escopo
  LBRACE, // {
  RBRACE, // }
  COMMA, // ,

  // Booleans
  TRUE, // true
  FALSE, // false
};

struct Token
{
  TokenType type;
  std::string value;
};

#endif