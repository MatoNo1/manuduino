#ifndef CONST_H
#define CONST_H

#include "pos.h"

const int MODE_RANGE = 2;
const int TEXT_MODE = 0;
const int MANU_MODE = 1;

const int MAIN_WINDOW_TEXT_MODE_HEIGHT = 500;
const int MAIN_WINDOW_TEXT_MODE_WIDTH = 400;
const int MAIN_WINDOW_MANU_MODE_HEIGHT = 780;
const int MAIN_WINDOW_MANU_MODE_WIDTH = 1040;

const int MAIN_WINDOW_OPERATION_MENU_MARGIN = 220;
const int MAIN_WINDOW_OPERATION_MENU_SPACING = 100;

const int TEXT_EDITOR_ROW = 4;
const int TEXT_EDITOR_COL = 32;
const int MANU_BOARD_ROW = 9;
const int MANU_BOARD_COL = 15;

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
const int OPERATION_ENTITY_HEIGHT = 40;
const int OPERATION_ENTITY_WIDTH = 40;
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

const int BOOL_VAR_CNT = 8;
const int INT_VAR_CNT = 3;
const int INT_BIT_LEN = 8;

const int SELECTOR_DIALOG_HEIGHT = 300;
const int SELECTOR_DIALOG_WIDTH = 400;
const int BOOL_CONTROLLER_DIALOG_HEIGHT = 300;
const int BOOL_CONTROLLER_DIALOG_WIDTH = 400;
const int INT_CONTROLLER_DIALOG_HEIGHT = 425;
const int INT_CONTROLLER_DIALOG_WIDTH = 600;
const int COMPARATOR_DIALOG_HEIGHT = 400;
const int COMPARATOR_DIALOG_WIDTH = 600;
const int BIT_SETTER_DIALOG_HEIGHT = 450;
const int BIT_SETTER_DIALOG_WIDTH = 300;
const int OUTPUT_DIALOG_HEIGHT = 300;
const int OUTPUT_DIALOG_WIDTH = 400;

const int SELECTOR_DIRECT_CNT = 4;
const int BOOL_CONTROLLER_TYPE_CNT = 3;
const int INT_CONTROLLER_OPERATOR_CNT = 6;
const int INT_CONTROLLER_VAL_CNT = 19;
const int COMPARATOR_OPERATOR_CNT = 6;
const int OUTPUT_FORMAT_CNT = 3;
const int CENTRAL_ENTITY_ARG_CNT = 3;

typedef enum {
    NO_OP,
    OP_ARROW_UP,
    OP_ARROW_RIGHT,
    OP_ARROW_DOWN,
    OP_ARROW_LEFT,
    OP_SELECTOR,
    OP_BOOL_CONTROLLER,
    OP_INT_CONTROLLER,
    OP_COMPARATOR,
    OP_BIT_SETTER,
    OP_OUTPUT,
    OP_CLEAR
} operationType;

typedef enum {
    NO_CENTRAL_ENTITY,
    SELECTOR,
    BOOL_CONTROLLER,
    INT_CONTROLLER,
    COMPARATOR,
    BIT_SETTER,
    OUTPUT
} centralEntityType;

const Pos COMPILER_START_POS = Pos(0, MANU_BOARD_COL + 1 >> 1);
const direct COMPILER_START_DIR = DOWN;

#endif // CONST_H

