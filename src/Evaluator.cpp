#include "Evaluator.h"
#include <iostream>

void Evaluator::evaluateProgram(const Program* program) {
    for (const auto &statement : program->statements) {
        if (const auto *funcDef = dynamic_cast<const FunctionDef*>(statement.get())) {
            functions[funcDef->name] = funcDef;
        } else {
            double result = evaluate(statement.get());
            std::cout << "Resultado: " << result << std::endl;
        }
    }
}

double Evaluator::evaluate(const Expr* ast) {
    if (!ast) {
        return 0;
    }

    if (const auto *numExpr = dynamic_cast<const NumberExpr*>(ast)) {
        return numExpr->value;
    } else if (const auto *varExpr = dynamic_cast<const VariableExpr *>(ast)) {
        if (variables.count(varExpr->name)) {
            return variables[varExpr->name];
        }
        std::cerr << "Erro: Variável '" << varExpr->name << "' não definida" << std::endl;
        return 0;
    } else if (const auto * assignExpr = dynamic_cast<const AssignmentExpr *>(ast)) {
        double value = evaluate(assignExpr->value.get());
        variables[assignExpr->name] = value;
        return value;
    } else if (const auto *binExpr = dynamic_cast<const BinaryExpr *>(ast)) {
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
                std::cerr << "Erro: Divisão por zero!" << std::endl;
                return 0;
            }
            return left / right;
        } else if (binExpr->op == "==") {
            return left == right ? 1 : 0;
        } else if (binExpr->op == "!=") {
            return left != right ? 1 : 0;
        } else if (binExpr->op == "<") {
            return left < right ? 1 : 0;
        } else if (binExpr->op == ">") {
            return left > right ? 1 : 0;
        }
    } else if (const auto *ifStmt = dynamic_cast<const IfStmt *>(ast)) {
        double condition_result = evaluate(ifStmt->condition.get());
        if (condition_result != 0) {
            if (ifStmt->thenBlock->statements.empty()) {
                return evaluate(ifStmt->thenBlock->statements.back().get());
            }
        } else if (ifStmt->elseBlock) {
            if (!ifStmt->elseBlock->statements.empty()) {
                return evaluate(ifStmt->elseBlock->statements.back().get());
            }
        }
        return 0;
    } else if (const auto *funcCall = dynamic_cast<const FunctionCall *>(ast)) {
        if (functions.count(funcCall->name)) {
            const FunctionDef *funcDef = functions.at(funcCall->name);
            Evaluator localEvaluator;
            for (size_t i = 0; i < funcDef->params.size(); ++i) {
                localEvaluator.variables[funcDef->params[i]] = evaluate(funcCall->args[i].get());
            }
            localEvaluator.evaluateProgram(funcDef->body.get());
            if (funcDef->body->statements.size() > 0) {
                return localEvaluator.evaluate(funcDef->body->statements.back().get());
            }
            return 0;
        }
    }
    return 0;
}