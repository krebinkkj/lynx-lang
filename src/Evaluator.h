#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "AST.h"
#include <map>

class Evaluator {
    public:
        void evaluateProgram(const Program *program);

    private:
        std::map<std::string, double> variables;
        double evaluate(const Expr *ast);
};

#endif