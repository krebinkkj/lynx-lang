#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "AST.h"
#include <map>

class Evaluator {
    public:
        void evaluateProgram(const Program *program);
        double evaluate(const Expr *ast);

    private:
        std::map<std::string, double> variables;
        std::map<std::string, const FunctionDef *> functions;
};

#endif