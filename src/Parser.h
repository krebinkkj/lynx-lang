#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"
#include "AST.h"

class Parser
{
public:
  explicit Parser(Lexer &lexer);
  std::unique_ptr<Expr> parseExpression();

private:
  Lexer &lexer;
  Token currentToken;

  void getNextToken();
  std::unique_ptr<Expr> parseNumberExpr();
};

#endif