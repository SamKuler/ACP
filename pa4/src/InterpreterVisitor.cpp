#include "InterpreterVisitor.h"
#include <iostream>

std::any InterpreterVisitor::visitProgram(CalculatorParser::ProgramContext *ctx) {
    scopes.push_back({}); // Global scope
    visitChildren(ctx);
    scopes.pop_back();
    return 0;
}

std::any InterpreterVisitor::visitAssignment(CalculatorParser::AssignmentContext *ctx) {
    std::string id = ctx->ID()->getText();
    std::any valAny = visit(ctx->expr());
    int val = std::any_cast<int>(valAny);
    scopes.back()[id] = val;
    return val;
}

std::any InterpreterVisitor::visitBlock(CalculatorParser::BlockContext *ctx) {
    scopes.push_back({}); // New scope
    visitChildren(ctx);
    scopes.pop_back();
    return 0;
}

std::any InterpreterVisitor::visitPrintStmt(CalculatorParser::PrintStmtContext *ctx) {
    std::any valAny = visit(ctx->expr());
    int val = std::any_cast<int>(valAny);
    std::cout << val << std::endl;
    return 0;
}

std::any InterpreterVisitor::visitIntExpr(CalculatorParser::IntExprContext *ctx) {
    return std::stoi(ctx->INT()->getText());
}

std::any InterpreterVisitor::visitMulExpr(CalculatorParser::MulExprContext *ctx) {
    int left = std::any_cast<int>(visit(ctx->expr(0)));
    int right = std::any_cast<int>(visit(ctx->expr(1)));
    
    if (ctx->MUL()) return left * right;
    if (ctx->DIV()) return left / right;
    if (ctx->MOD()) return left % right;
    return 0;
}

std::any InterpreterVisitor::visitLvalExpr(CalculatorParser::LvalExprContext *ctx) {
    std::string id = ctx->ID()->getText();
    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
        if (it->count(id)) {
            return (*it)[id];
        }
    }
    std::cout << "Error: Undefined symbol '" << id << "' at line " << ctx->getStart()->getLine() << std::endl;
    exit(1);
}

std::any InterpreterVisitor::visitParenExpr(CalculatorParser::ParenExprContext *ctx) {
    return visit(ctx->expr());
}

std::any InterpreterVisitor::visitPlusExpr(CalculatorParser::PlusExprContext *ctx) {
    int left = std::any_cast<int>(visit(ctx->expr(0)));
    int right = std::any_cast<int>(visit(ctx->expr(1)));
    
    if (ctx->PLUS()) return left + right;
    if (ctx->MINUS()) return left - right;
    return 0;
}
