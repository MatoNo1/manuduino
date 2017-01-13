#include <QTextStream>
#include "compiler.h"

Compiler::Compiler(BoardGrid *allGrid[][COL], Pos _startPos, direct _startDir):
    startPos(_startPos), startDir(_startDir)
{
    for (int i=0; i<ROW; ++i)
        for (int j=0; j<COL; ++j)
            grid[i][j] = allGrid[i][j];
}

Compiler::~Compiler()
{
    for (int i=0; i<ROW; ++i)
        for (int j=0; j<COL; ++j)
            grid[i][j] = NULL;
}

void Compiler::compile(QTextStream &outputStream)
{
    outputStream << "fullScreen();\n";
    outputStream << "background(255);\n";
    outputStream << "stroke(0);\n";
    outputStream << "fill(255, 0, 0);\n";
    outputStream << "rect(50, 50, 200, 200);\n";
}

void Compiler::compileText(QTextStream &outputStream, const QString& text)
{
    outputStream << "fullScreen();\n";
    outputStream << "background(255);\n";
    outputStream << "textSize(60);\n";
    outputStream << "fill(0);\n";
    outputStream << "text(\"" + text + "\", 100, 100);";
}

