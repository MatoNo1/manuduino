#include <QAction>
#include <QMessageBox>
#include <QProcess>
#include <QTextStream>
#include "ManuduinoCompiler.h"
#include "RemoteManager.h"
//#include <QDebug>
#include <QCursor>
#include "ServerConfigurationDialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mode = MANU_MODE;
    setWindowTitle("ManuDuino");
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedSize(MANU_MODE_WIDTH, MANU_MODE_HEIGHT);

    setTextModeButton.setText("Text Mode");
    setManuModeButton.setText("Manu Mode");
    clearButton.setText("Clear");
    connect(&setTextModeButton, SIGNAL(clicked()), this, SLOT(setTextMode()));
    connect(&setManuModeButton, SIGNAL(clicked()), this, SLOT(setManuMode()));
    connect(&clearButton, SIGNAL(clicked()), this, SLOT(allClear()));

    textArea = new TextEditor(this, "");

    arrowUpOperation = new OperationEntity(this, OP_ARROW_UP, "://Arrow_Up.jpeg");
    arrowRightOperation = new OperationEntity(this, OP_ARROW_RIGHT, "://Arrow_Right.jpeg");
    arrowDownOperation = new OperationEntity(this, OP_ARROW_DOWN, "://Arrow_Down.jpeg");
    arrowLeftOperation = new OperationEntity(this, OP_ARROW_LEFT, "://Arrow_Left.jpeg");
    selectorOperation = new OperationEntity(this, OP_SELECTOR, "://Selector/00.jpeg");
    boolControllerOperation = new OperationEntity(this, OP_BOOL_CONTROLLER, "://BoolController/00.jpeg");
    intControllerOperation = new OperationEntity(this, OP_INT_CONTROLLER, "://IntController/000.jpeg");
    comparatorOperation = new OperationEntity(this, OP_COMPARATOR, "://Comparator/000.jpeg");
    bitSetterOperation = new OperationEntity(this, OP_BIT_SETTER, "://BitSetter/000.jpeg");
    outputOperation = new OperationEntity(this, OP_OUTPUT, "://Output/00.jpeg");
    clearOperation = new OperationEntity(this, OP_CLEAR, "://Clear.jpeg");

    arrowUpOperation->setToolTip("Arrow Up");
    arrowRightOperation->setToolTip("Arrow Right");
    arrowDownOperation->setToolTip("Arrow Down");
    arrowLeftOperation->setToolTip("Arrow Left");
    selectorOperation->setToolTip("Selector");
    boolControllerOperation->setToolTip("Bool Controller");
    intControllerOperation->setToolTip("Int Controller");
    comparatorOperation->setToolTip("Comparator");
    bitSetterOperation->setToolTip("Bit Setter");
    outputOperation->setToolTip("Output");
    clearOperation->setToolTip("Clear Grid");

    connect(arrowUpOperation, SIGNAL(activate(operationType)), this, SLOT(activateHandler(operationType)));
    connect(arrowRightOperation, SIGNAL(activate(operationType)), this, SLOT(activateHandler(operationType)));
    connect(arrowDownOperation, SIGNAL(activate(operationType)), this, SLOT(activateHandler(operationType)));
    connect(arrowLeftOperation, SIGNAL(activate(operationType)), this, SLOT(activateHandler(operationType)));
    connect(selectorOperation, SIGNAL(activate(operationType)), this, SLOT(activateHandler(operationType)));
    connect(boolControllerOperation, SIGNAL(activate(operationType)), this, SLOT(activateHandler(operationType)));
    connect(intControllerOperation, SIGNAL(activate(operationType)), this, SLOT(activateHandler(operationType)));
    connect(comparatorOperation, SIGNAL(activate(operationType)), this, SLOT(activateHandler(operationType)));
    connect(bitSetterOperation, SIGNAL(activate(operationType)), this, SLOT(activateHandler(operationType)));
    connect(outputOperation, SIGNAL(activate(operationType)), this, SLOT(activateHandler(operationType)));
    connect(clearOperation, SIGNAL(activate(operationType)), this, SLOT(activateHandler(operationType)));

    operationLayout.addSpacing(MAIN_WINDOW_OPERATION_MENU_MARGIN);
    operationLayout.addWidget(arrowLeftOperation);
    operationLayout.addWidget(arrowRightOperation);
    operationLayout.addSpacing(MAIN_WINDOW_OPERATION_MENU_SPACING);
    operationLayout.addWidget(arrowUpOperation);
    operationLayout.addWidget(arrowDownOperation);
    operationLayout.addSpacing(MAIN_WINDOW_OPERATION_MENU_SPACING);
    operationLayout.addWidget(selectorOperation);
    operationLayout.addWidget(boolControllerOperation);
    operationLayout.addWidget(intControllerOperation);
    operationLayout.addWidget(comparatorOperation);
    operationLayout.addWidget(bitSetterOperation);
    operationLayout.addWidget(outputOperation);
    operationLayout.addWidget(clearOperation);
    operationLayout.addSpacing(MAIN_WINDOW_OPERATION_MENU_MARGIN);

    buttonLayout.addWidget(&setTextModeButton);
    buttonLayout.addWidget(&setManuModeButton);
    buttonLayout.addWidget(&clearButton);

    boardLayout.setSpacing(0);
    boardLayout.setMargin(0);
    for (int i=0; i<BOARD_ROW; ++i)
        for (int j=0; j<BOARD_COL; ++j) {
            grid[i][j] = new BoardGrid(this);
            boardLayout.addWidget(grid[i][j], i, j);
            //if (i == 2) grid[i][j]->addArrowUp();
            //if (j == 3) grid[i][j]->addArrowDown();
            //if (i == 5) grid[i][j]->addArrowLeft();
            //if (j == 6) grid[i][j]->addArrowRight();
        }

    board = new QWidget(this);
    board->setLayout(&boardLayout);

    operationAndBoardLayout.addLayout(&operationLayout);
    operationAndBoardLayout.addWidget(board);
    operationAndBoard = new QWidget(this);
    operationAndBoard->setLayout(&operationAndBoardLayout);

    mainAreaLayout.addWidget(operationAndBoard);
    mainAreaLayout.addWidget(textArea);
    mainAreaLayout.setCurrentIndex(0);

    mainLayout.addLayout(&buttonLayout);
    mainLayout.addLayout(&mainAreaLayout);

    setTextModeButton.setEnabled(1);
    setManuModeButton.setEnabled(0);
    clearButton.setEnabled(1);

    mainWidget = new QWidget(this);
    mainWidget->setLayout(&mainLayout);
    setCentralWidget(mainWidget);

    setCursor(Qt::ArrowCursor);

    // Initialize other dialogs may be invoked by main window
    configurationDialog = new ServerConfigurationDialog(this);
    connect(ui->actionServer_Configuration_S, SIGNAL(triggered(bool)), configurationDialog, SLOT(exec()));

    connect(ui->actionDeploy, SIGNAL(triggered(bool)), this, SLOT(onDeployAction()));
    connect(ui->actionExecute, SIGNAL(triggered(bool)), this, SLOT(onExecuteAction()));

    // About compiler
    compiler = new Compiler(grid, COMPILER_START_POS, COMPILER_START_DIR);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton && activatedOperation != NO_OP) {
        Pos target = Pos(ev->globalY(), ev->globalX());
        //printf("SSS %d %d\n", target.x, target.y);

        int targetGridRow = -1, targetGridCol = -1;
        for (int i=0; i<BOARD_ROW; ++i)
            for (int j=0; j<BOARD_COL; ++j) {
                QPoint upLeftPoint = grid[i][j]->mapToGlobal(QPoint(0, 0));
                Pos upLeft = Pos(upLeftPoint.y(), upLeftPoint.x());
                Pos downRight = upLeft + Pos(BOARD_GRID_HEIGHT, BOARD_GRID_WIDTH);
                if (target.x >= upLeft.x && target.y >= upLeft.y
                 && target.x < downRight.x && target.y < downRight.y) {
                    targetGridRow = i; targetGridCol = j;
                }
            }

        if (targetGridRow >= 0 && targetGridCol >= 0) {
            Entity centralEntity;
            switch (activatedOperation) {
                case OP_ARROW_UP: {
                    grid[targetGridRow][targetGridCol]->addArrowUp();
                    break;
                }
                case OP_ARROW_RIGHT: {
                    grid[targetGridRow][targetGridCol]->addArrowRight();
                    break;
                }
                case OP_ARROW_DOWN: {
                    grid[targetGridRow][targetGridCol]->addArrowDown();
                    break;
                }
                case OP_ARROW_LEFT: {
                    grid[targetGridRow][targetGridCol]->addArrowLeft();
                    break;
                }
                case OP_SELECTOR: {
                    centralEntity = Entity(grid[targetGridRow][targetGridCol], selectorOperation->getPixPath());
                    grid[targetGridRow][targetGridCol]->setCentralEntity(&centralEntity, SELECTOR);
                    for (int i=0; i<CENTRAL_ENTITY_ARG_CNT; ++i)
                        grid[targetGridRow][targetGridCol]->setCentralArg(i, selectorOperation->getArg(i));
                    break;
                }
                case OP_BOOL_CONTROLLER: {
                    centralEntity = Entity(grid[targetGridRow][targetGridCol], boolControllerOperation->getPixPath());
                    grid[targetGridRow][targetGridCol]->setCentralEntity(&centralEntity, BOOL_CONTROLLER);
                    for (int i=0; i<CENTRAL_ENTITY_ARG_CNT; ++i)
                        grid[targetGridRow][targetGridCol]->setCentralArg(i, boolControllerOperation->getArg(i));
                    break;
                }
                case OP_INT_CONTROLLER: {
                    centralEntity = Entity(grid[targetGridRow][targetGridCol], intControllerOperation->getPixPath());
                    grid[targetGridRow][targetGridCol]->setCentralEntity(&centralEntity, INT_CONTROLLER);
                    for (int i=0; i<CENTRAL_ENTITY_ARG_CNT; ++i)
                        grid[targetGridRow][targetGridCol]->setCentralArg(i, intControllerOperation->getArg(i));
                    break;
                }
                case OP_COMPARATOR: {
                    centralEntity = Entity(grid[targetGridRow][targetGridCol], comparatorOperation->getPixPath());
                    grid[targetGridRow][targetGridCol]->setCentralEntity(&centralEntity, COMPARATOR);
                    for (int i=0; i<CENTRAL_ENTITY_ARG_CNT; ++i)
                        grid[targetGridRow][targetGridCol]->setCentralArg(i, comparatorOperation->getArg(i));
                    break;
                }
                case OP_BIT_SETTER: {
                    centralEntity = Entity(grid[targetGridRow][targetGridCol], bitSetterOperation->getPixPath());
                    grid[targetGridRow][targetGridCol]->setCentralEntity(&centralEntity, BIT_SETTER);
                    for (int i=0; i<CENTRAL_ENTITY_ARG_CNT; ++i)
                        grid[targetGridRow][targetGridCol]->setCentralArg(i, bitSetterOperation->getArg(i));
                    break;
                }
                case OP_OUTPUT: {
                    centralEntity = Entity(grid[targetGridRow][targetGridCol], outputOperation->getPixPath());
                    grid[targetGridRow][targetGridCol]->setCentralEntity(&centralEntity, OUTPUT);
                    for (int i=0; i<CENTRAL_ENTITY_ARG_CNT; ++i)
                        grid[targetGridRow][targetGridCol]->setCentralArg(i, outputOperation->getArg(i));
                    break;
                }
                case OP_CLEAR: {
                    grid[targetGridRow][targetGridCol]->allClear();
                    break;
                }
            }
        }

        activatedOperation = NO_OP;
        setCursor(Qt::ArrowCursor);
    }

    QMainWindow::mouseReleaseEvent(ev);
}

void MainWindow::mouseMoveEvent(QMouseEvent *ev)
{
    if (activatedOperation != NO_OP) {
        QCursor cursor;
        switch (activatedOperation) {
            case OP_ARROW_UP: {
                cursor = QCursor(QPixmap(arrowUpOperation->getPixPath()));
                break;
            }
            case OP_ARROW_RIGHT: {
                cursor = QCursor(QPixmap(arrowRightOperation->getPixPath()));
                break;
            }
            case OP_ARROW_DOWN: {
                cursor = QCursor(QPixmap(arrowDownOperation->getPixPath()));
                break;
            }
            case OP_ARROW_LEFT: {
                cursor = QCursor(QPixmap(arrowLeftOperation->getPixPath()));
                break;
            }
            case OP_SELECTOR: {
                cursor = QCursor(QPixmap(selectorOperation->getPixPath()));
                break;
            }
            case OP_BOOL_CONTROLLER: {
                cursor = QCursor(QPixmap(boolControllerOperation->getPixPath()));
                break;
            }
            case OP_INT_CONTROLLER: {
                cursor = QCursor(QPixmap(intControllerOperation->getPixPath()));
                break;
            }
            case OP_COMPARATOR: {
                cursor = QCursor(QPixmap(comparatorOperation->getPixPath()));
                break;
            }
            case OP_BIT_SETTER: {
                cursor = QCursor(QPixmap(bitSetterOperation->getPixPath()));
                break;
            }
            case OP_OUTPUT: {
                cursor = QCursor(QPixmap(outputOperation->getPixPath()));
                break;
            }
            case OP_CLEAR: {
                cursor = QCursor(QPixmap(clearOperation->getPixPath()));
                break;
            }
        }
        setCursor(cursor);
    } else
        setCursor(Qt::ArrowCursor);

    QMainWindow::mouseMoveEvent(ev);
}

void MainWindow::setTextMode()
{
    mode = TEXT_MODE;
    setFixedSize(TEXT_MODE_WIDTH, TEXT_MODE_HEIGHT);
    setTextModeButton.setEnabled(0);
    setManuModeButton.setEnabled(1);
    mainAreaLayout.setCurrentIndex(1);
}

void MainWindow::setManuMode()
{
    mode = MANU_MODE;
    setFixedSize(MANU_MODE_WIDTH, MANU_MODE_HEIGHT);
    setTextModeButton.setEnabled(1);
    setManuModeButton.setEnabled(0);
    mainAreaLayout.setCurrentIndex(0);
}

void MainWindow::allClear()
{
    if (mode == TEXT_MODE)
        textArea->clear();
    else
        for (int i=0; i<BOARD_ROW; ++i)
            for (int j=0; j<BOARD_COL; ++j)
                grid[i][j]->allClear();
}

void MainWindow::activateHandler(operationType type)
{
    activatedOperation = type;
}

void MainWindow::onDeployAction()
{
    QString s;
    QTextStream stream(&s);
    compiler->compileText(stream, textArea->toPlainText());
    auto remoteManager = RemoteManager::getInstance();
    remoteManager->uploadCode("demo01", s);
}

void MainWindow::onExecuteAction()
{
    auto remoteManager = RemoteManager::getInstance();
    remoteManager->executeCode("demo01");
}
