#include "Parser.h"
#include <iostream>

Parser::Parser(Lexer &lexer) : lexer(lexer)
{
    opPrecedence[TokenType::PLUS] = 10;
    opPrecedence[TokenType::MINUS] = 10;
    opPrecedence[TokenType::MULTIPLY] = 20;
    opPrecedence[TokenType::DIVIDE] = 20;
    opPrecedence[TokenType::EQ] = 5;
    opPrecedence[TokenType::NEQ] = 5;
    opPrecedence[TokenType::LT] = 6;
    opPrecedence[TokenType::GT] = 6;
    opPrecedence[TokenType::ASSIGN] = 1;

    getNextToken();
}

void Parser::getNextToken()
{
    currentToken = lexer.getNextToken();
}

int Parser::getOpPrecedence()
{
    auto it = opPrecedence.find(currentToken.type);
    if (it != opPrecedence.end())
    {
        return it->second;
    }
    return -1;
}

std::unique_ptr<Expr> Parser::parsePrimary()
{
    if (currentToken.type == TokenType::NUMBER)
    {
        auto result = std::make_unique<NumberExpr>(std::stod(currentToken.value));
        getNextToken();
        return result;
    }

    if (currentToken.type == TokenType::LPAREN)
    {
        getNextToken();
        auto expr = parseExpression();
        if (currentToken.type != TokenType::RPAREN)
        {
            std::cerr << "Erro: Esperado ')' após a expressão" << std::endl;
            return nullptr;
        }
        getNextToken();
        return expr;
    }

    if (currentToken.type == TokenType::IDENTIFIER)
    {
        Token nextToken = lexer.peekNextToken();
        if (nextToken.type == TokenType::LPAREN)
        {
            return parseFunctionCall();
        }
        return parseVariableExpr();
    }

    std::cerr << "Erro: Token inesperado '" << currentToken.value << "'" << std::endl;
    return nullptr;
}

std::unique_ptr<Expr> Parser::parseVariableExpr()
{
    std::string name = currentToken.value;
    getNextToken();

    if (currentToken.type == TokenType::ASSIGN)
    {
        getNextToken();
        auto value = parseExpression();
        if (!value)
        {
            return nullptr;
        }
        return std::make_unique<AssignmentExpr>(name, std::move(value));
    }
    return std::make_unique<VariableExpr>(name);
}

std::unique_ptr<Expr> Parser::parseBinaryOpExpr(std::unique_ptr<Expr> left, int exprPrec)
{
    while (true)
    {
        int opPrec = getOpPrecedence();
        if (opPrec < exprPrec)
        {
            return left;
        }

        std::string binOp = currentToken.value;
        getNextToken();

        auto right = parsePrimary();
        if (!right)
        {
            return nullptr;
        }

        int nextPrec = getOpPrecedence();
        if (opPrec < nextPrec)
        {
            right = parseBinaryOpExpr(std::move(right), opPrec + 1);
            if (!right)
            {
                return nullptr;
            }
        }
        left = std::make_unique<BinaryExpr>(binOp, std::move(left), std::move(right));
    }
}

std::unique_ptr<Expr> Parser::parseExpression()
{
    auto left = parsePrimary();
    if (!left)
    {
        return nullptr;
    }
    return parseBinaryOpExpr(std::move(left), 0);
}

std::unique_ptr<Expr> Parser::parseStatement()
{
    if (currentToken.type == TokenType::IF)
    {
        return parseIfStmt();
    }
    if (currentToken.type == TokenType::FUNC)
    {
        return parseFunctionDef();
    }

    auto expr = parseExpression();
    if (currentToken.type == TokenType::SEMICOLON)
    {
        getNextToken();
    }
    return expr;
}

std::unique_ptr<Program> Parser::parseBlock()
{
    if (currentToken.type != TokenType::LBRACE)
    {
        std::cerr << "Erro: Esperado '{' para o bloco de código." << std::endl;
        return nullptr;
    }
    getNextToken();

    auto program = std::make_unique<Program>();
    while (currentToken.type != TokenType::RBRACE && currentToken.type != TokenType::EOF_TOKEN)
    {
        auto statement = parseStatement();
        if (statement)
        {
            program->statements.push_back(std::move(statement));
        }
        else
        {
            return nullptr;
        }
    }

    if (currentToken.type != TokenType::RBRACE)
    {
        std::cerr << "Erro: Esperado '}' para fechar o bloco de código." << std::endl;
        return nullptr;
    }
    getNextToken();

    return program;
}

std::unique_ptr<Expr> Parser::parseIfStmt()
{
    getNextToken();

    auto condition = parseExpression();
    if (!condition)
        return nullptr;

    auto thenBlock = parseBlock();
    if (!thenBlock)
        return nullptr;

    std::unique_ptr<Program> elseBlock = nullptr;
    if (currentToken.type == TokenType::ELSE)
    {
        getNextToken();
        elseBlock = parseBlock();
        if (!elseBlock)
            return nullptr;
    }

    return std::make_unique<IfStmt>(std::move(condition), std::move(thenBlock), std::move(elseBlock));
}

std::unique_ptr<Expr> Parser::parseFunctionDef()
{
    getNextToken();
    std::string name = currentToken.value;
    getNextToken();

    if (currentToken.type != TokenType::LPAREN)
    {
        std::cerr << "Erro: Esperado '(' para a lista de parâmetros." << std::endl;
        return nullptr;
    }
    getNextToken();
    std::vector<std::string> params;
    while (currentToken.type != TokenType::RPAREN)
    {
        if (currentToken.type != TokenType::IDENTIFIER)
        {
            std::cerr << "Erro: Esperado nome de parâmetro." << std::endl;
            return nullptr;
        }
        params.push_back(currentToken.value);
        getNextToken();
        if (currentToken.type == TokenType::COMMA)
        {
            getNextToken();
        }
    }
    getNextToken();

    auto body = parseBlock();

    return std::make_unique<FunctionDef>(name, std::move(params), std::move(body));
}

std::unique_ptr<Expr> Parser::parseFunctionCall()
{
    std::string name = currentToken.value;
    getNextToken();
    getNextToken();

    std::vector<std::unique_ptr<Expr>> args;
    while (currentToken.type != TokenType::RPAREN)
    {
        auto arg = parseExpression();
        if (!arg)
            return nullptr;
        args.push_back(std::move(arg));
        if (currentToken.type == TokenType::COMMA)
        {
            getNextToken();
        }
    }
    getNextToken();

    return std::make_unique<FunctionCall>(name, std::move(args));
}

std::unique_ptr<Program> Parser::parseProgram()
{
    auto program = std::make_unique<Program>();
    while (currentToken.type != TokenType::EOF_TOKEN)
    {
        auto statement = parseStatement();
        if (statement)
        {
            program->statements.push_back(std::move(statement));
        }
        else
        {
            return nullptr;
        }
    }
    return program;
}
