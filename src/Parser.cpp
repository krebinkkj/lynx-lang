#include "Parser.h"
#include <iostream>

Parser::Parser(Lexer& lexer) : lexer(lexer) {
  opPrecedence[TokenType::PLUS] = 10;
  opPrecedence[TokenType::MINUS] = 10;
  opPrecedence[TokenType::MULTIPLY] = 20;
  opPrecedence[TokenType::DIVIDE] = 20;

  getNextToken();
}

void Parser::getNextToken() {
  currentToken = lexer.getNextToken();
}

int Parser::getOpPrecedence() {
  auto it = opPrecedence.find(currentToken.type);
  if (it != opPrecedence.end()) {
    return it->second;
  }
  return -1; // -1 to invalid operators
}

std::unique_ptr<Expr> Parser::parsePrimary() {
  if (currentToken.type == TokenType::NUMBER) {
    auto result = std::make_unique<NumberExpr>(std::stod(currentToken.value));
    getNextToken();
    return result;
  }
  std::cerr << "Error: Token inesperado '" << currentToken.value << "'" << std::endl;
  return nullptr;
}

std::unique_ptr<Expr>
Parser::parseBinaryOpExpr(std::unique_ptr<Expr> left, int exprPrec) {
  while (true) {
    int opPrec = getOpPrecedence();

    if (opPrec < exprPrec) {
      return left;
    }

    std::string binOp = currentToken.value;
    getNextToken();

    auto right = parsePrimary();
    if (!right) {
      return nullptr;
    }

    int nextPrec = getOpPrecedence();
    if (opPrec < nextPrec) {
      right = parseBinaryOpExpr(std::move(right), opPrec + 1);
      if (!right) {
        return nullptr;
      }
    }

    left = std::make_unique<BinaryExpr>(binOp, std::move(left), std::move(right));
  }
}

std::unique_ptr<Expr> Parser::parseExpression() {
  auto left = parsePrimary();
  if (!left) {
    return nullptr;
  }

  return parseBinaryOpExpr(std::move(left), 0);
}