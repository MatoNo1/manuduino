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

QString idx2boolOp(int idx)
{
    switch(idx)
    {
        case 0: return QString("==");
        case 1: return QString(">");
        case 2: return QString(">=");
        case 3: return QString("<");
        case 4: return QString("<=");
        case 5: return QString("!=");
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
        case BOOL_CONTROLLER:
            outputStream << "__booleanArray[" << grid[r][c]->getCentralArg(0) << "]";
            if(grid[r][c]->getCentralArg(1) == 0)
                outputStream << " = false;";
            else if(grid[r][c]->getCentralArg(1) == 1)
                outputStream << " = true;";
            else
                outputStream << " = !__booleanArray[" << grid[r][c]->getCentralArg(0) << "];";
            break;
        case BIT_SETTER:
            outputStream << "if(__booleanArray[" << grid[r][c]->getCentralArg(2) << "]) ";
            outputStream << idx2variable(grid[r][c]->getCentralArg(0)) << " |= (1 << " <<
                            QString::number(grid[r][c]->getCentralArg(1)) << " );\n";
            outputStream << "else ";
            outputStream << idx2variable(grid[r][c]->getCentralArg(0)) << " &= ~(1 << " <<
                            QString::number(grid[r][c]->getCentralArg(1)) << " );\n";
            break;
        case COMPARATOR:
            outputStream << "__booleanArray[" << grid[r][c]->getCentralArg(0) << "] = ";
            outputStream << "( " << idx2variable(grid[r][c]->getCentralArg(1)) <<
                            idx2boolOp(grid[r][c]->getCentralArg(2)) << "0 );\n";
            break;
    /*
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
    outputStream << "boolean __programTerminated = false;\n";
    outputStream << "boolean[] __booleanArray = new boolean[8];\n";
    outputStream << "int __currentRow = 0;\n";
    outputStream << "int __currentCol = 7;\n";
    outputStream << "int __rSpeed = 1;\n";
    outputStream << "int __cSpeed = 0;\n";
    outputStream << "int[][] __rMoveArray = new int[" + QString::number(ROW) + "][" + QString::number(COL) + "];\n";
    outputStream << "int[][] __cMoveArray = new int[" + QString::number(ROW) + "][" + QString::number(COL) + "];\n";
    outputStream << "void setup()\n";
    outputStream << "{\n";
    outputStream << "fullScreen();\n";
    outputStream << "textSize(60);\n";
    outputStream << "fill(0);\n";
    outputStream << "i = 0; j = 0; k = 0;\n";
    outputStream << "for(int t = 0; t < 8; t++) __booleanArray[t] = false;\n";
    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j < COL; j++)
        {
            outputStream << "__cMoveArray[" + QString::number(i) + "][" + QString::number(j) + "] = ";
            outputStream << (grid[i][j]->getLRState() == NO_LR ? 0 : (grid[i][j]->getLRState() == IS_LEFT ? -1 : 1)) << ";\n";
            outputStream << "__rMoveArray[" + QString::number(i) + "][" + QString::number(j) + "] = ";
            outputStream << (grid[i][j]->getUDState() == NO_UD ? 0 : (grid[i][j]->getUDState() == IS_UP ? -1 : 1)) << ";\n";
        }
    }
    outputStream << "}\n";

    //Draw function
    outputStream << "void draw()\n";
    outputStream << "{\n";
    outputStream << "background(255);\n";
    outputStream << "text(__programTerminated?\"Terminated\" : \"Running\" , 100, 100);\n";
    outputStream << "String __booleanDebugString = \"\";";
    outputStream << "text(\"i=\" + i + \" j=\" + j + \" k=\" + k , 100, 200);\n";
    outputStream << "for(int t = 0; t < 8; t++) __booleanDebugString += __booleanArray[t] + \",\";\n";
    outputStream << "text(__booleanDebugString , 100, 300);\n";
    outputStream << "if(__programTerminated) return;\n";
    bool first = true;
    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j < COL; j++)
        {
            if(grid[i][j]->getCentralState() != NO_CENTRAL_ENTITY)
            {
                if(first)
                {
                    first = false;
                    outputStream << "if(__currentRow == " + QString::number(i) << " && ";
                }
                else
                {
                    outputStream << "else if(__currentRow == " + QString::number(i) << " && ";
                }
                outputStream << "__currentCol == " + QString::number(j) << ")\n";
                outputStream << "{\n";
                compileCell(outputStream, i, j);
                outputStream << "}\n";
            }
        }
    }
    outputStream << "if(__cMoveArray[__currentRow][__currentCol] == 0 && __rMoveArray[__currentRow][__currentCol] == 0)\n"
                    "{\n"
                    "    __programTerminated = true;\n"
                    "}\n"
                    "else if (__cMoveArray[__currentRow][__currentCol] == 0)"
                    "{\n"
                    "    __rSpeed = __rMoveArray[__currentRow][__currentCol]; __cSpeed = 0;"
                    "    __currentRow += __rSpeed;"
                    "}\n"
                    "else if (__rMoveArray[__currentRow][__currentCol] == 0)"
                    "{\n"
                    "    __cSpeed = __cMoveArray[__currentRow][__currentCol]; __rSpeed = 0;"
                    "    __currentCol += __cSpeed;"
                    "}\n"
                    "else\n"
                    "{\n"
                    "    if(__cSpeed == 0)\n"
                    "    {\n"
                    "        __rSpeed = __rMoveArray[__currentRow][__currentCol]; __cSpeed = 0;"
                    "        __currentRow += __rSpeed;"
                    "    }\n"
                    "    if(__rSpeed == 0)\n"
                    "    {\n"
                    "        __cSpeed = __cMoveArray[__currentRow][__currentCol]; __rSpeed = 0;"
                    "        __currentCol += __cSpeed;"
                    "    }\n"
                    "}\n";
    outputStream << "}\n";
}
