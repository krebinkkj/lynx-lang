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
  std::string code = "x = 3; if (x > 5) y = 2; else y = 90 * x;";

  Lexer lexer(code);
  Parser parser(lexer);

  std::cout << "Código-fonte: " << code << std::endl;

  auto program_ast = parser.parseProgram();

  Evaluator evaluator;
  evaluator.evaluateProgram(program_ast.get());

  return 0;
}
