#ifndef AST_H
#define AST_H

#include <memory>
#include <vector>
#include <string>
#include <utility>
#include "Token.h"

// Classe base para todos os nós da árvore
class Expr
{
public:
  virtual ~Expr() = default;
};

// Nó raiz para um programa e blocos de código
class Program
{
public:
  std::vector<std::unique_ptr<Expr>> statements;
};

// Nó para números literais
class NumberExpr : public Expr
{
public:
  double value;
  explicit NumberExpr(double val) : value(val) {}
};

// Nó para operações binárias (como 10 + 5)
class BinaryExpr : public Expr
{
public:
  std::string op;
  std::unique_ptr<Expr> left;
  std::unique_ptr<Expr> right;

  BinaryExpr(std::string op, std::unique_ptr<Expr> left, std::unique_ptr<Expr> right)
      : op(std::move(op)), left(std::move(left)), right(std::move(right)) {}
};

// Nó para variáveis (lookup)
class VariableExpr : public Expr
{
public:
  std::string name;
  explicit VariableExpr(std::string name) : name(std::move(name)) {}
};

// Nó para atribuição (e.g., x = 10)
class AssignmentExpr : public Expr
{
public:
  std::string name;
  std::unique_ptr<Expr> value;
  AssignmentExpr(std::string name, std::unique_ptr<Expr> value)
      : name(std::move(name)), value(std::move(value)) {}
};

// Nó para a instrução if-else
class IfStmt : public Expr
{
public:
  std::unique_ptr<Expr> condition;
  std::unique_ptr<Program> thenBlock;
  std::unique_ptr<Program> elseBlock;

  IfStmt(std::unique_ptr<Expr> cond, std::unique_ptr<Program> thenB, std::unique_ptr<Program> elseB) : condition(std::move(cond)), thenBlock(std::move(thenB)), elseBlock(std::move(elseB)) {}
};

// Nó para a definição de uma função
class FunctionDef : public Expr
{
public:
  std::string name;
  std::vector<std::string> params;
  std::unique_ptr<Program> body;

  FunctionDef(std::string name, std::vector<std::string> params, std::unique_ptr<Program> body)
      : name(std::move(name)), params(std::move(params)), body(std::move(body)) {}
};

// Nó para a chamada de uma função
class FunctionCall : public Expr
{
public:
  std::string name;
  std::vector<std::unique_ptr<Expr>> args;

  FunctionCall(std::string name, std::vector<std::unique_ptr<Expr>> args)
      : name(std::move(name)), args(std::move(args)) {}
};

class BooleanExpr : public Expr {
  public:
    bool value;
    explicit BooleanExpr(bool val) : value(val) {}
};

#endif