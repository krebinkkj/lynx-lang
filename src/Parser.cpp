#include "Parser.h"
#include <iostream>

Parser::Parser(Lexer& lexer) : lexer(lexer) {
  getNextToken();
}

void Parser::getNextToken() {
  currentToken = lexer.getNextToken();
}

std::unique_ptr<Expr> Parser::parseNumberExpr() {
  auto result = std::make_unique<NumberExpr>(std::stod(currentToken.value));
  getNextToken();
  return result;
}

std::unique_ptr<Expr> Parser::parseExpression() {
  auto left = parseNumberExpr();

  if (currentToken.type != TokenType::PLUS && currentToken.type != TokenType::MINUS) {
    return left;
  }

  std::string op = currentToken.value;
  getNextToken();

  auto right = parseNumberExpr();

  return std::make_unique<BinaryExpr>(op, std::move(left), std::move(right));
}