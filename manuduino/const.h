#ifndef CONST_H
#define CONST_H

#include "pos.h"

const int MODE_RANGE = 2;
const int TEXT_MODE = 0;
const int MANU_MODE = 1;

const int MAIN_WINDOW_TEXT_MODE_HEIGHT = 500;
const int MAIN_WINDOW_TEXT_MODE_WIDTH = 400;
const int MAIN_WINDOW_MANU_MODE_HEIGHT = 800;
const int MAIN_WINDOW_MANU_MODE_WIDTH = 1050;

const int TEXT_EDITOR_ROW = 4;
const int TEXT_EDITOR_COL = 32;
const int MANU_BOARD_ROW = 8;
const int MANU_BOARD_COL = 16;

typedef enum {
    UP,
    RIGHT,
    DOWN,
    LEFT
} direct;

const Pos UP_UNIT = Pos(-1, 0);
const Pos RIGHT_UNIT = Pos(0, 1);
const Pos DOWN_UNIT = Pos(1, 0);
const Pos LEFT_UNIT = Pos(0, -1);

const int BOARD_GRID_HEIGHT = 64;
const int BOARD_GRID_WIDTH = 64;
const int ARROW_UP_DOWN_HEIGHT = 12;
const int ARROW_UP_DOWN_WIDTH = 40;
const int ARROW_LEFT_RIGHT_HEIGHT = 40;
const int ARROW_LEFT_RIGHT_WIDTH = 12;

typedef enum {
    NO_UD,
    IS_UP,
    IS_DOWN
} arrowUpDownInBoardGrid;

typedef enum {
    NO_LR,
    IS_RIGHT,
    IS_LEFT
} arrowLeftRightInBoardGrid;

#endif // CONST_H

