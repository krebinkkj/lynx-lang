#include <iostream>
#include <string>
#include "Lexer.h"
#include "Parser.h"
#include "AST.h"

// Função para imprimir a AST
void printAST(const Expr *expr, int indent = 0)
{
  if (!expr)
    return;

  for (int i = 0; i < indent; ++i)
    std::cout << "  ";

  if (const auto *numExpr = dynamic_cast<const NumberExpr *>(expr))
  {
    std::cout << "Number: " << numExpr->value << std::endl;
  }
  else if (const auto *binExpr = dynamic_cast<const BinaryExpr *>(expr))
  {
    std::cout << "Binary Op: " << binExpr->op << std::endl;
    printAST(binExpr->left.get(), indent + 1);
    printAST(binExpr->right.get(), indent + 1);
  }
}

int main()
{
  std::string source_code = "10 + 5";
  Lexer lexer(source_code);
  Parser parser(lexer);

  std::cout << "Código-fonte: " << source_code << std::endl;
  std::cout << "AST:" << std::endl;

  auto ast = parser.parseExpression();
  printAST(ast.get());

  return 0;
}