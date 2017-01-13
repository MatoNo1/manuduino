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
