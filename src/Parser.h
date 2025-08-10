#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"
#include "AST.h"
#include <map>

class Parser
{
public:
  explicit Parser(Lexer& lexer);
  std::unique_ptr<Expr> parseExpression();
  std::unique_ptr<Program> parseProgram();

private:
  Lexer &lexer;
  Token currentToken;
  std::map<TokenType, int> opPrecedence;

  void getNextToken();
  std::unique_ptr<Expr> parsePrimary();
  std::unique_ptr<Expr> parseVariableExpr();
  std::unique_ptr<Expr> parseBinaryOpExpr(std::unique_ptr<Expr> left, int exprPrec);
  std::unique_ptr<Expr> parseStatement();
  int getOpPrecedence();
};

#endif