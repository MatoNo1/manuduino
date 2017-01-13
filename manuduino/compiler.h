#ifndef COMPILER_H
#define COMPILER_H

#include "boardgrid.h"

class QTextStream;

struct Compiler {
protected:
    static const int ROW = MANU_BOARD_ROW;
    static const int COL = MANU_BOARD_COL;

    BoardGrid *grid[ROW][COL];
    Pos startPos;
    direct startDir;

public:
    Compiler(BoardGrid* allGrid[][COL], Pos _startPos, direct _startDir);
    ~Compiler();
    void compile(QTextStream &outputStream);
    void compileText(QTextStream &outputStream, const QString& text);
};

#endif // COMPILER_H

