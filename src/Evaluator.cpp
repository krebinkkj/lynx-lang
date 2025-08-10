#include "Evaluator.h"
#include <iostream>

double Evaluator::evaluate(const Expr *ast)
{
  if (!ast)
  {
    return 0;
  }

  if (const auto *numExpr = dynamic_cast<const NumberExpr *>(ast))
  {
    return numExpr->value;
  }
  else if (const auto *binExpr = dynamic_cast<const BinaryExpr *>(ast))
  {
    double left = evaluate(binExpr->left.get());
    double right = evaluate(binExpr->right.get());

    if (binExpr->op == "+")
    {
      return left + right;
    }
    else if (binExpr->op == "-")
    {
      return left - right;
    }
    else if (binExpr->op == "*")
    {
      return left * right;
    }
    else if (binExpr->op == "/")
    {
      if (right == 0)
      {
        std::cerr << "Erro: Divisão por zero!" << std::endl;
        return 0;
      }
      return left / right;
    }
  }

  return 0;
}
