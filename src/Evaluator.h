#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "AST.h"

class Evaluator {
  public:
    double evaluate(const Expr *ast);
};

#endif