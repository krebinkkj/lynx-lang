#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "AST.h"
#include <map>

class Evaluator {
    public:
        double evaluate(const Expr* ast);

    private:
        std::map<std::string, double> variables;
};

#endif