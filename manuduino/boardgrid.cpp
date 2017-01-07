#include "boardgrid.h"

BoardGrid::BoardGrid(QWidget* parent):
    QWidget(parent)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedSize(WIDTH, HEIGHT);

    tempUL.setPixPath("://EmptyBoard_UL.jpeg");
    tempUL.setSize(UP_DOWN_HEIGHT, LEFT_RIGHT_WIDTH);
    tempUR.setPixPath("://EmptyBoard_UR.jpeg");
    tempUR.setSize(UP_DOWN_HEIGHT, LEFT_RIGHT_WIDTH);
    tempDL.setPixPath("://EmptyBoard_DL.jpeg");
    tempDL.setSize(UP_DOWN_HEIGHT, LEFT_RIGHT_WIDTH);
    tempDR.setPixPath("://EmptyBoard_DR.jpeg");
    tempDR.setSize(UP_DOWN_HEIGHT, LEFT_RIGHT_WIDTH);
    arrowUp.setPixPath("://EmptyBoard_U.jpeg");
    arrowUp.setDir(UP);
    arrowUp.setSize(UP_DOWN_HEIGHT, UP_DOWN_WIDTH);
    arrowRight.setPixPath("://EmptyBoard_R.jpeg");
    arrowRight.setDir(RIGHT);
    arrowRight.setSize(LEFT_RIGHT_HEIGHT, LEFT_RIGHT_WIDTH);
    arrowDown.setPixPath("://EmptyBoard_D.jpeg");
    arrowDown.setDir(DOWN);
    arrowDown.setSize(UP_DOWN_HEIGHT, UP_DOWN_WIDTH);
    arrowLeft.setPixPath("://EmptyBoard_L.jpeg");
    arrowLeft.setDir(LEFT);
    arrowLeft.setSize(LEFT_RIGHT_HEIGHT, LEFT_RIGHT_WIDTH);
    centralEntity.setPixPath("://EmptyBoard_Central.jpeg");

    thisLayout.setSpacing(0);
    thisLayout.setMargin(0);
    thisLayout.addWidget(&tempUL, 0, 0);
    thisLayout.addWidget(&arrowUp, 0, 1);
    thisLayout.addWidget(&tempUR, 0, 2);
    thisLayout.addWidget(&arrowLeft, 1, 0);
    thisLayout.addWidget(&centralEntity, 1, 1);
    thisLayout.addWidget(&arrowRight, 1, 2);
    thisLayout.addWidget(&tempDL, 2, 0);
    thisLayout.addWidget(&arrowDown, 2, 1);
    thisLayout.addWidget(&tempDR, 2, 2);
    setLayout(&thisLayout);

    centralIsSelector = 0;
    UDState = NO_UD;
    LRState = NO_LR;
}

BoardGrid::~BoardGrid()
{
    tempUL.~EmptyEntity();
    tempUR.~EmptyEntity();
    tempDL.~EmptyEntity();
    tempDR.~EmptyEntity();
    arrowUp.~Arrow();
    arrowRight.~Arrow();
    arrowDown.~Arrow();
    arrowLeft.~Arrow();
    centralEntity.~Entity();
    thisLayout.~QGridLayout();
}

void BoardGrid::setCentralEntity(Entity* _centralEntity, bool isSelector)
{
    centralEntity = _centralEntity;
    centralIsSelector = isSelector;
    if (isSelector) {
        arrowUp.setPixPath("://EmptyBoard_U.jpeg");
        arrowRight.setPixPath("://EmptyBoard_R.jpeg");
        arrowDown.setPixPath("://EmptyBoard_D.jpeg");
        arrowLeft.setPixPath("://EmptyBoard_L.jpeg");
        UDState = NO_UD;
        LRState = NO_LR;
    }
}

void BoardGrid::addArrowUp()
{
    if (!centralIsSelector) {
        arrowUp.setPixPath("://Arrow_Up.jpeg");
        if (UDState == IS_DOWN)
            arrowDown.setPixPath("://EmptyBoard_D.jpeg");
        UDState = IS_UP;
    }
}

void BoardGrid::addArrowRight()
{
    if (!centralIsSelector) {
        arrowRight.setPixPath("://Arrow_Right.jpeg");
        if (LRState == IS_LEFT)
            arrowLeft.setPixPath("://EmptyBoard_L.jpeg");
        LRState = IS_RIGHT;
    }
}

void BoardGrid::addArrowDown()
{
    if (!centralIsSelector) {
        arrowDown.setPixPath("://Arrow_Down.jpeg");
        if (UDState == IS_UP)
            arrowUp.setPixPath("://EmptyBoard_U.jpeg");
        UDState = IS_DOWN;
    }
}

void BoardGrid::addArrowLeft()
{
    if (!centralIsSelector) {
        arrowLeft.setPixPath("://Arrow_Left.jpeg");
        if (LRState == IS_RIGHT)
            arrowRight.setPixPath("://EmptyBoard_R.jpeg");
        LRState = IS_LEFT;
    }
}

void BoardGrid::allClear()
{
    arrowUp.setPixPath("://EmptyBoard_U.jpeg");
    arrowRight.setPixPath("://EmptyBoard_R.jpeg");
    arrowDown.setPixPath("://EmptyBoard_D.jpeg");
    arrowLeft.setPixPath("://EmptyBoard_L.jpeg");
    centralEntity.setPixPath("://EmptyBoard_Central.jpeg");

    centralIsSelector = 0;
    UDState = NO_UD;
    LRState = NO_LR;
}
