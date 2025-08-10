#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"
#include "AST.h"
#include <map>

class Parser
{
public:
  explicit Parser(Lexer &lexer);
  std::unique_ptr<Expr> parseExpression();

private:
  Lexer &lexer;
  Token currentToken;
  std::map<TokenType, int> opPrecedence;

  void getNextToken();
  std::unique_ptr<Expr> parsePrimary();
  std::unique_ptr<Expr> parseBinaryOpExpr(std::unique_ptr<Expr> left, int exprPrec);
  int getOpPrecedence();
};

#endif