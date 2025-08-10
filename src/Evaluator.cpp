#include "Evaluator.h"
#include <iostream>

double Evaluator::evaluate(const Expr* ast) {
    if (!ast) {
        return 0;
    }

    if (const auto* numExpr = dynamic_cast<const NumberExpr*>(ast)) {
        return numExpr->value;
    } else if (const auto* varExpr = dynamic_cast<const VariableExpr*>(ast)) {
        if (variables.count(varExpr->name)) {
            return variables[varExpr->name];
        }

        std::cerr << "Error: Variável '" << varExpr->name << "' não definida." << std::endl;
        return 0;
    } else if (const auto* assignExpr = dynamic_cast<const AssignmentExpr*>(ast)) {
        double value = evaluate(assignExpr->value.get());
        variables[assignExpr->name] = value;
        return value;
    } else if (const auto* binExpr = dynamic_cast<const BinaryExpr*>(ast)) {
        double left = evaluate(binExpr->left.get());
        double right = evaluate(binExpr->right.get());

        if (binExpr->op == "+") {
            return left + right;
        } else if (binExpr->op == "-") {
            return left - right;
        } else if (binExpr->op == "*") {
            return left * right;
        } else if (binExpr->op == "/") {
            if (right == 0) {
                std::cerr << "Error: Divisão por zero!" << std::endl;
                return 0;
            }
            return left / right;
        }
    }

    return 0;
}

void Evaluator::evaluateProgram(const Program* program) {
    for (const auto& statement : program->statements) {
        double result = evaluate(statement.get());
        std::cout << "Resultado: " << result << std::endl;
    }
}