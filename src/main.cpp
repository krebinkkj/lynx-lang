#include <iostream>
#include <string>
#include "Lexer.h"
#include "Parser.h"
#include "AST.h"
#include "Evaluator.h"

// Função para imprimir a AST (opcional, mas útil para verificação)
// void printAST(const Expr *expr, int indent = 0)
// {
//   if (!expr)
//     return;

//   for (int i = 0; i < indent; ++i)
//     std::cout << "  ";

//   if (const auto *numExpr = dynamic_cast<const NumberExpr *>(expr))
//   {
//     std::cout << "Number: " << numExpr->value << std::endl;
//   }
//   else if (const auto *binExpr = dynamic_cast<const BinaryExpr *>(expr))
//   {
//     std::cout << "Binary Op: " << binExpr->op << std::endl;
//     printAST(binExpr->left.get(), indent + 1);
//     printAST(binExpr->right.get(), indent + 1);
//   }
// }

int main()
{
  std::string source_code_1 = "x = 10";
  Lexer lexer_1(source_code_1);
  Parser parser_1(lexer_1);
  Evaluator evaluator_1;
  auto ast_1 = parser_1.parseExpression();
  double result_1 = evaluator_1.evaluate(ast_1.get());
  std::cout << "Resultado da atribuição: " << result_1 << std::endl;

  std::cout << "------------------------" << std::endl;

  std::string source_code_2 = "x + 5";
  Lexer lexer_2(source_code_2);
  Parser parser_2(lexer_2);
  Evaluator evaluator_2;
  auto ast_2 = parser_2.parseExpression();
  double result_2 = evaluator_2.evaluate(ast_2.get());
  std::cout << "Resultado do uso: " << result_2 << std::endl;

  return 0;
}
