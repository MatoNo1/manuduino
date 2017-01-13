#ifndef BOARDGRID_H
#define BOARDGRID_H

#include <QWidget>
#include <QGridLayout>
#include "arrow.h"
#include "emptyentity.h"

struct BoardGrid : public QWidget {
    Q_OBJECT

public:
    BoardGrid(QWidget* parent = 0);
    ~BoardGrid();
    void setCentralEntity(Entity* _centralEntity = 0, centralEntityType type = NO_CENTRAL_ENTITY);
    void setCentralArg(int idx, int argVal = 0);
    void addArrowUp();
    void addArrowRight();
    void addArrowDown();
    void addArrowLeft();
    void allClear();
    centralEntityType getCentralState();
    arrowUpDownInBoardGrid getUDState();
    arrowLeftRightInBoardGrid getLRState();
    int getCentralArg(int idx);

protected:
    static const int HEIGHT = BOARD_GRID_HEIGHT;
    static const int WIDTH = BOARD_GRID_WIDTH;
    static const int UP_DOWN_HEIGHT = ARROW_UP_DOWN_HEIGHT;
    static const int UP_DOWN_WIDTH = ARROW_UP_DOWN_WIDTH;
    static const int LEFT_RIGHT_HEIGHT = ARROW_LEFT_RIGHT_HEIGHT;
    static const int LEFT_RIGHT_WIDTH = ARROW_LEFT_RIGHT_WIDTH;

    EmptyEntity tempUL, tempUR, tempDL, tempDR;
    Arrow arrowUp, arrowRight, arrowDown, arrowLeft;
    Entity centralEntity;

    QGridLayout thisLayout;

    centralEntityType centralState;
    int centralArg[CENTRAL_ENTITY_ARG_CNT];
    arrowUpDownInBoardGrid UDState;
    arrowLeftRightInBoardGrid LRState;
};

#endif // BOARDGRID_H

