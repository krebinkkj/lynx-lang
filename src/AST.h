#ifndef AST_H
#define AST_H

#include <memory>
#include <vector>
#include <string>
#include <utility>
#include "Token.h"

// Classe base para todos os nós da árvore
class Expr {
  public:
    virtual ~Expr() = default;
};

class NumberExpr : public Expr {
  public:
    double value;
    explicit NumberExpr(double val) : value(val) {}
};

class BinaryExpr : public Expr {
  public:
    std::string op;
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;

    BinaryExpr(std::string op, std::unique_ptr<Expr> left, std::unique_ptr<Expr> right)
        : op(std::move(op)), left(std::move(left)), right(std::move(right)) {}
};

#endif