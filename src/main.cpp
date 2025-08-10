#include <iostream>
#include <string>
#include "Lexer.h"
#include "Parser.h"
#include "AST.h"
#include "Evaluator.h"

int main() {
  std::string source_code = "10 * 5";
  Lexer lexer(source_code);
  Parser parser(lexer);

  std::cout << "Código-fonte: " << source_code << std::endl;

  auto ast = parser.parseExpression();

  Evaluator evaluator;
  double result = evaluator.evaluate(ast.get());

  std::cout << "Resultado da avaliação: " << result << std::endl;

  return 0;
}