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


class VariableExpr : public Expr {
  public:
    std::string name;
    explicit VariableExpr(std::string name) : name(std::move(name)) {}
};

class AssignmentExpr : public Expr {
  public:
    std::string name;
    std::unique_ptr<Expr> value;
    AssignmentExpr(std::string name, std::unique_ptr<Expr> value) : name(std::move(name)), value(std::move(value)) {}
};

class Program {
  public:
    std::vector<std::unique_ptr<Expr>> statements;
};

class IfStmt : public Expr {
  public:
    std::unique_ptr<Expr> condition;
    std::unique_ptr<Expr> thenBlock;
    std::unique_ptr<Expr> elseBlock;

    IfStmt(std::unique_ptr<Expr> cond, std::unique_ptr<Expr> thenB, std::unique_ptr<Expr> elseB) : condition(std::move(cond)), thenBlock(std::move(thenB)), elseBlock(std::move(elseB)) {}
};

#endif