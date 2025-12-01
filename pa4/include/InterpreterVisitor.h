#pragma once

#include "CalculatorBaseVisitor.h"
#include <vector>
#include <map>
#include <string>
#include <any>

class InterpreterVisitor : public CalculatorBaseVisitor {
private:
    std::vector<std::map<std::string, int>> scopes;

public:
    std::any visitProgram(CalculatorParser::ProgramContext *ctx) override;
    std::any visitAssignment(CalculatorParser::AssignmentContext *ctx) override;
    std::any visitBlock(CalculatorParser::BlockContext *ctx) override;
    std::any visitPrintStmt(CalculatorParser::PrintStmtContext *ctx) override;
    std::any visitIntExpr(CalculatorParser::IntExprContext *ctx) override;
    std::any visitMulExpr(CalculatorParser::MulExprContext *ctx) override;
    std::any visitLvalExpr(CalculatorParser::LvalExprContext *ctx) override;
    std::any visitParenExpr(CalculatorParser::ParenExprContext *ctx) override;
    std::any visitPlusExpr(CalculatorParser::PlusExprContext *ctx) override;
};
