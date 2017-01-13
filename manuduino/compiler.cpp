#include <QTextStream>
#include "compiler.h"

QString idx2variable(int idx)
{
    switch(idx)
    {
        case 0: return QString("i");
        case 1: return QString("j");
        case 2: return QString("k");
    }
}

QString idx2intOp(int idx)
{
    switch(idx)
    {
        case 0: return QString("=");
        case 1: return QString("+=");
        case 2: return QString("-=");
        case 3: return QString("*=");
        case 4: return QString("/=");
        case 5: return QString("%=");
    }
}

QString idx2intOprand(int idx)
{
    if(idx < 16)
        return QString::number(idx);
    switch(idx)
    {
        case 16: return QString("i");
        case 17: return QString("j");
        case 18: return QString("k");
    }
}

void Compiler::compileCell(QTextStream &outputStream, int r, int c)
{
    switch(grid[r][c]->getCentralState())
    {
        case NO_CENTRAL_ENTITY:
            return;
        case INT_CONTROLLER:
            outputStream << idx2variable(grid[r][c]->getCentralArg(0)) << " ";
            outputStream << idx2intOp(grid[r][c]->getCentralArg(1)) << " ";
            outputStream << idx2intOprand(grid[r][c]->getCentralArg(2)) << ";\n";
            break;

    /*BOOL_CONTROLLER,
    INT_CONTROLLER,
    COMPARATOR,
    BIT_SETTER,
    OUTPUT*/
    }

    //grid[r][c]->
    //outputStream << "i += 1;\n";
}

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

void Compiler::compileManufacture(QTextStream &outputStream)
{
    outputStream << "byte i, j, k;\n";
    outputStream << "boolean[] __booleanArray = new boolean[8];\n";
    outputStream << "void setup()\n";
    outputStream << "{\n";
    outputStream << "fullScreen();\n";
    outputStream << "i = 0; j = 0; k = 0;\n";
    outputStream << "for(int t = 0; t < 8; t++) __booleanArray[t] = false;\n";
    compileCell(outputStream, 0, 7);
    outputStream << "}\n";
    outputStream << "void draw()\n";
    outputStream << "{\n";
    outputStream << "background(255);\n";
    outputStream << "textSize(60);\n";
    outputStream << "fill(0);\n";
    outputStream << "String __booleanDebugString = \"\";";
    outputStream << "text(\"i=\" + i + \" j=\" + j + \" k=\" + k , 100, 100);\n";
    outputStream << "for(int t = 0; t < 8; t++) __booleanDebugString += __booleanArray[i] + \",\";\n";
    outputStream << "text(__booleanDebugString , 100, 200);\n";
    outputStream << "}\n";
}
