#include <iostream>
#include <string>
#include "Lexer.h"
#include "Token.h"

int main() {
  std::string source_code = "123 var_nome 456";
  Lexer lexer(source_code);
  Token token;

  do {
    token = lexer.getNextToken();
    std::cout << "Token Type: " << static_cast<int>(token.type) << ", Value: " << token.value << "" << std::endl;
  } while (token.type != TokenType::EOF_TOKEN);

  return 0;
}