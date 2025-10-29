#include "SysYFormatter.h"

std::string SysYFormatter::getIndent()
{
    return std::string(indentLevel * indentSpaces, ' ');
}

std::any SysYFormatter::visitCompUnit(SysYParser::CompUnitContext *ctx)
{
    std::string result;
    bool firstLine = true;
    for (size_t i = 0; i < ctx->children.size(); i++)
    {
        if (auto declCtx = dynamic_cast<SysYParser::DeclContext *>(ctx->children[i]))
        {
            result += getIndent();
            result += std::any_cast<std::string>(visit(declCtx));
        }
        else if (auto funcDefCtx = dynamic_cast<SysYParser::FuncDefContext *>(ctx->children[i]))
        {
            if (!firstLine)
            {
                result += "\n";
            }
            result += std::any_cast<std::string>(visit(funcDefCtx));
        }
        if (i != ctx->children.size() - 1) // No last eof
        {
            result += "\n";
        }
        firstLine = false;
    }
    return result;
}

std::any SysYFormatter::visitDecl(SysYParser::DeclContext *ctx)
{
    std::string result;
    if (auto constDeclCtx = ctx->constDecl())
    {
        result += std::any_cast<std::string>(visit(constDeclCtx));
    }
    else if (auto varDeclCtx = ctx->varDecl())
    {
        result += std::any_cast<std::string>(visit(varDeclCtx));
    }
    return result;
}

std::any SysYFormatter::visitConstDecl(SysYParser::ConstDeclContext *ctx)
{
    std::string result;
    result += "const ";
    result += std::any_cast<std::string>(visit(ctx->bType()));
    result += " ";
    for (size_t i = 0; i < ctx->constDef().size(); i++)
    {
        result += std::any_cast<std::string>(visit(ctx->constDef(i)));
        if (i != ctx->constDef().size() - 1)
        {
            result += ", ";
        }
    }
    result += ";";
    return result;
}

std::any SysYFormatter::visitBType(SysYParser::BTypeContext *ctx)
{
    return ctx->getText();
}

std::any SysYFormatter::visitConstDef(SysYParser::ConstDefContext *ctx)
{
    std::string result;
    result += ctx->IDENT()->getText();
    if (ctx->L_BRACKT().size() > 0)
    {
        for (size_t i = 0; i < ctx->L_BRACKT().size(); i++)
        {
            result += "[";
            result += std::any_cast<std::string>(visit(ctx->constExp(i)));
            result += "]";
        }
    }
    if (ctx->ASSIGN())
    {
        result += " = ";
        result += std::any_cast<std::string>(visit(ctx->constInitVal()));
    }
    return result;
}

std::any SysYFormatter::visitConstInitVal(SysYParser::ConstInitValContext *ctx)
{
    std::string result;
    if (ctx->L_BRACE())
    {
        result += "{";
        for (size_t i = 0; i < ctx->constInitVal().size(); i++)
        {
            result += std::any_cast<std::string>(visit(ctx->constInitVal(i)));
            if (i != ctx->constInitVal().size() - 1)
            {
                result += ", ";
            }
        }
        result += "}";
    }
    else
    {
        result += std::any_cast<std::string>(visit(ctx->constExp()));
    }
    return result;
}

std::any SysYFormatter::visitConstExp(SysYParser::ConstExpContext *ctx)
{
    return visit(ctx->addExp());
}

std::any SysYFormatter::visitVarDecl(SysYParser::VarDeclContext *ctx)
{
    std::string result;
    result += std::any_cast<std::string>(visit(ctx->bType()));
    result += " ";
    for (size_t i = 0; i < ctx->varDef().size(); i++)
    {
        result += std::any_cast<std::string>(visit(ctx->varDef(i)));
        if (i != ctx->varDef().size() - 1)
        {
            result += ", ";
        }
    }
    result += ";";
    return result;
}

std::any SysYFormatter::visitVarDef(SysYParser::VarDefContext *ctx)
{
    std::string result;
    result += ctx->IDENT()->getText();
    if (ctx->L_BRACKT().size() > 0)
    {
        for (size_t i = 0; i < ctx->L_BRACKT().size(); i++)
        {
            result += "[";
            result += std::any_cast<std::string>(visit(ctx->constExp(i)));
            result += "]";
        }
    }
    if (ctx->ASSIGN())
    {
        result += " = ";
        result += std::any_cast<std::string>(visit(ctx->initVal()));
    }
    return result;
}

std::any SysYFormatter::visitInitVal(SysYParser::InitValContext *ctx)
{
    std::string result;
    if (ctx->L_BRACE())
    {
        result += "{";
        for (size_t i = 0; i < ctx->initVal().size(); i++)
        {
            result += std::any_cast<std::string>(visit(ctx->initVal(i)));
            if (i != ctx->initVal().size() - 1)
            {
                result += ", ";
            }
        }
        result += "}";
    }
    else
    {
        result += std::any_cast<std::string>(visit(ctx->exp()));
    }
    return result;
}

std::any SysYFormatter::visitExp(SysYParser::ExpContext *ctx)
{
    return visit(ctx->addExp());
}

std::any SysYFormatter::visitFuncDef(SysYParser::FuncDefContext *ctx)
{
    std::string result;
    result += std::any_cast<std::string>(visit(ctx->funcType()));
    result += " ";
    result += ctx->IDENT()->getText();
    result += "(";
    if (auto funcFParamsCtx = ctx->funcFParams())
    {
        result += std::any_cast<std::string>(visit(funcFParamsCtx));
    }
    result += ") ";
    result += std::any_cast<std::string>(visit(ctx->block()));
    return result;
}

std::any SysYFormatter::visitFuncType(SysYParser::FuncTypeContext *ctx)
{
    return ctx->getText();
}

std::any SysYFormatter::visitFuncFParams(SysYParser::FuncFParamsContext *ctx)
{
    std::string result;
    for (size_t i = 0; i < ctx->funcFParam().size(); i++)
    {
        result += std::any_cast<std::string>(visit(ctx->funcFParam(i)));
        if (i != ctx->funcFParam().size() - 1)
        {
            result += ", ";
        }
    }
    return result;
}

std::any SysYFormatter::visitFuncFParam(SysYParser::FuncFParamContext *ctx)
{
    std::string result;
    result += std::any_cast<std::string>(visit(ctx->bType()));
    result += " ";
    result += ctx->IDENT()->getText();
    if (ctx->L_BRACKT().size() > 0)
    {
        for (size_t i = 0; i < ctx->L_BRACKT().size(); i++)
        {
            result += "[";
            if (i > 0)
            {
                result += std::any_cast<std::string>(visit(ctx->exp(i - 1)));
            }
            result += "]";
        }
    }
    return result;
}

// No indent provided before '{'
std::any SysYFormatter::visitBlock(SysYParser::BlockContext *ctx)
{
    std::string result;
    result += "{\n";
    indentLevel++;
    for (auto blockItemCtx : ctx->blockItem())
    {
        // Apply indent for the firstline
        result += getIndent();
        result += std::any_cast<std::string>(visit(blockItemCtx));
        result += "\n";
    }
    indentLevel--;
    result += getIndent();
    result += "}";
    return result;
}

// Does not apply indent here
std::any SysYFormatter::visitBlockItem(SysYParser::BlockItemContext *ctx)
{
    if (auto declCtx = ctx->decl())
    {
        return visit(declCtx);
    }
    else if (auto stmtCtx = ctx->stmt())
    {
        return visit(stmtCtx);
    }
    // Shouldn't be here
    return "";
}

std::any SysYFormatter::visitStmt(SysYParser::StmtContext *ctx)
{
    std::string result;
    if (ctx->lVal())
    {
        result += std::any_cast<std::string>(visit(ctx->lVal()));
        result += " = ";
        result += std::any_cast<std::string>(visit(ctx->exp()));
        result += ";";
    }
    else if (ctx->IF())
    {
        result += "if (";
        result += std::any_cast<std::string>(visit(ctx->cond()));
        result += ")";
        // If stmt
        if (ctx->stmt(0)->block()) // with block
        {
            result += " ";
            result += std::any_cast<std::string>(visit(ctx->stmt(0)));
        }
        else
        { // single line
            result += "\n";
            indentLevel++;
            result += getIndent();
            indentLevel--;
            result += std::any_cast<std::string>(visit(ctx->stmt(0)));
        }
        if (ctx->ELSE()) // else stmt
        {
            result += "\n";
            result += getIndent();
            result += "else";
            if (ctx->stmt(1)->block()) // with block
            {
                result += " ";
                result += std::any_cast<std::string>(visit(ctx->stmt(1)));
            }
            else
            {                           // single line or if follows
                if (ctx->stmt(1)->IF()) // IF follows
                {
                    result += " ";
                    result += std::any_cast<std::string>(visit(ctx->stmt(1)));
                }
                else
                {
                    result += "\n";
                    indentLevel++;
                    result += getIndent();
                    indentLevel--;
                    result += std::any_cast<std::string>(visit(ctx->stmt(1)));
                }
            }
        }
    }
    else if (ctx->WHILE())
    {
        result += "while (";
        result += std::any_cast<std::string>(visit(ctx->cond()));
        result += ")";
        if (ctx->stmt(0)->block()) // with block
        {
            result += " ";
            result += std::any_cast<std::string>(visit(ctx->stmt(0)));
        }
        else
        { // single line
            result += "\n";
            indentLevel++;
            result += getIndent();
            indentLevel--;
            result += std::any_cast<std::string>(visit(ctx->stmt(0)));
        }
    }
    else if (ctx->BREAK())
    {
        result += "break;";
    }
    else if (ctx->CONTINUE())
    {
        result += "continue;";
    }
    else if (ctx->RETURN())
    {
        result += "return";
        if (ctx->exp())
        {
            result += " ";
            result += std::any_cast<std::string>(visit(ctx->exp()));
        }
        result += ";";
    }
    else if (ctx->block())
    {
        result += std::any_cast<std::string>(visit(ctx->block()));
    }
    else if (ctx->exp())
    {
        result += std::any_cast<std::string>(visit(ctx->exp()));
        result += ";";
    }
    else
    {
        result += ";";
    }
    return result;
}

std::any SysYFormatter::visitCond(SysYParser::CondContext *ctx)
{
    return visit(ctx->lOrExp());
}

std::any SysYFormatter::visitLVal(SysYParser::LValContext *ctx)
{
    std::string result;
    result += ctx->IDENT()->getText();
    if (ctx->L_BRACKT().size() > 0)
    {
        for (auto expCtx : ctx->exp())
        {
            result += "[";
            result += std::any_cast<std::string>(visit(expCtx));
            result += "]";
        }
    }
    return result;
}

std::any SysYFormatter::visitPrimaryExp(SysYParser::PrimaryExpContext *ctx)
{
    std::string result;
    if (ctx->L_PAREN())
    {
        result += "(";
        result += std::any_cast<std::string>(visit(ctx->exp()));
        result += ")";
    }
    else if (auto lValCtx = ctx->lVal())
    {
        result += std::any_cast<std::string>(visit(lValCtx));
    }
    else if (auto numberCtx = ctx->number())
    {
        result += std::any_cast<std::string>(visit(numberCtx));
    }
    return result;
}

std::any SysYFormatter::visitNumber(SysYParser::NumberContext *ctx)
{
    return ctx->INTEGER_CONST()->getText();
}

std::any SysYFormatter::visitUnaryExp(SysYParser::UnaryExpContext *ctx)
{
    std::string result;
    if (auto primaryExpCtx = ctx->primaryExp())
    {
        result += std::any_cast<std::string>(visit(primaryExpCtx));
    }
    else if (ctx->IDENT())
    {
        result += ctx->IDENT()->getText();
        result += "(";
        if (auto funcRParamsCtx = ctx->funcRParams())
        {
            result += std::any_cast<std::string>(visit(funcRParamsCtx));
        }
        result += ")";
    }
    else if (auto unaryOpCtx = ctx->unaryOp())
    {
        result += std::any_cast<std::string>(visit(unaryOpCtx));
        result += std::any_cast<std::string>(visit(ctx->unaryExp()));
    }
    return result;
}

std::any SysYFormatter::visitUnaryOp(SysYParser::UnaryOpContext *ctx)
{
    return ctx->getText();
}

std::any SysYFormatter::visitFuncRParams(SysYParser::FuncRParamsContext *ctx)
{
    std::string result;
    for (size_t i = 0; i < ctx->exp().size(); i++)
    {
        result += std::any_cast<std::string>(visit(ctx->exp(i)));
        if (i != ctx->exp().size() - 1)
        {
            result += ", ";
        }
    }
    return result;
}

std::any SysYFormatter::visitMulExp(SysYParser::MulExpContext *ctx)
{
    std::string result;
    result += std::any_cast<std::string>(visit(ctx->unaryExp(0)));
    for (size_t i = 1; i < ctx->unaryExp().size(); i++)
    {
        result += " ";
        result += ctx->children[2 * i - 1]->getText();
        result += " ";
        result += std::any_cast<std::string>(visit(ctx->unaryExp(i)));
    }
    return result;
}

std::any SysYFormatter::visitAddExp(SysYParser::AddExpContext *ctx)
{
    std::string result;
    result += std::any_cast<std::string>(visit(ctx->mulExp(0)));
    for (size_t i = 1; i < ctx->mulExp().size(); i++)
    {
        result += " ";
        result += ctx->children[2 * i - 1]->getText();
        result += " ";
        result += std::any_cast<std::string>(visit(ctx->mulExp(i)));
    }
    return result;
}
std::any SysYFormatter::visitRelExp(SysYParser::RelExpContext *ctx)
{
    std::string result;
    result += std::any_cast<std::string>(visit(ctx->addExp(0)));
    for (size_t i = 1; i < ctx->addExp().size(); i++)
    {
        result += " ";
        result += ctx->children[2 * i - 1]->getText();
        result += " ";
        result += std::any_cast<std::string>(visit(ctx->addExp(i)));
    }
    return result;
}

std::any SysYFormatter::visitEqExp(SysYParser::EqExpContext *ctx)
{
    std::string result;
    result += std::any_cast<std::string>(visit(ctx->relExp(0)));
    for (size_t i = 1; i < ctx->relExp().size(); i++)
    {
        result += " ";
        result += ctx->children[2 * i - 1]->getText();
        result += " ";
        result += std::any_cast<std::string>(visit(ctx->relExp(i)));
    }
    return result;
}

std::any SysYFormatter::visitLAndExp(SysYParser::LAndExpContext *ctx)
{
    std::string result;
    result += std::any_cast<std::string>(visit(ctx->eqExp(0)));
    for (size_t i = 1; i < ctx->eqExp().size(); i++)
    {
        result += " ";
        result += ctx->children[2 * i - 1]->getText();
        result += " ";
        result += std::any_cast<std::string>(visit(ctx->eqExp(i)));
    }
    return result;
}

std::any SysYFormatter::visitLOrExp(SysYParser::LOrExpContext *ctx)
{
    std::string result;
    result += std::any_cast<std::string>(visit(ctx->lAndExp(0)));
    for (size_t i = 1; i < ctx->lAndExp().size(); i++)
    {
        result += " ";
        result += ctx->children[2 * i - 1]->getText();
        result += " ";
        result += std::any_cast<std::string>(visit(ctx->lAndExp(i)));
    }
    return result;
}