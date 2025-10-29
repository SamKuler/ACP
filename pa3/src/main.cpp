#include <iostream>
#include <fstream>
#include "antlr4-runtime.h"
#include "SysYLexer.h"
#include "SysYParser.h"
#include "SysYFormatter.h"

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: sysy_formatter <input-file>" << std::endl;
        return 1;
    }

    std::ifstream stream;
    stream.open(argv[1]);
    antlr4::ANTLRInputStream input(stream); // 创建 ANTLRInputStream 对象

    SysYLexer lexer(&input);          // 创建 SysYLexer 对象
    antlr4::CommonTokenStream tokens(&lexer); // 创建 CommonTokenStream 对象
    SysYParser parser(&tokens);       // 创建 SysYParser 对象

    antlr4::tree::ParseTree *tree = parser.compUnit(); // 获取语法分析树

    SysYFormatter formatter;
    std::string formatted = std::any_cast<std::string>(formatter.visit(tree));
    
    std::cout << formatted;

    return 0;
}