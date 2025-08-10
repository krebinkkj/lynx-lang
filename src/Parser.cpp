#include "Parser.h"
#include <iostream>

Parser::Parser(Lexer &lexer) : lexer(lexer)
{
  getNextToken(); // Pega o primeiro token
}

void Parser::getNextToken()
{
  currentToken = lexer.getNextToken();
}

std::unique_ptr<Expr> Parser::parseNumberExpr()
{
  auto result = std::make_unique<NumberExpr>(std::stod(currentToken.value));
  getNextToken(); // Avança para o próximo token
  return result;
}

std::unique_ptr<Expr> Parser::parseExpression()
{
  auto left = parseNumberExpr(); // Pega o primeiro número

  // Verifica se o próximo token é um operador
  if (currentToken.type != TokenType::PLUS && currentToken.type != TokenType::MINUS)
  {
    return left;
  }

  std::string op = currentToken.value;
  getNextToken(); // Avança o token do operador

  auto right = parseNumberExpr(); // Pega o segundo número

  // Constrói o nó da operação binária
  return std::make_unique<BinaryExpr>(op, std::move(left), std::move(right));
}