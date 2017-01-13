#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QStackedLayout>
#include <QPushButton>
#include "base.h"
#include "texteditor.h"
#include "boardgrid.h"
#include "operationentity.h"
#include "compiler.h"

namespace Ui {
    struct MainWindow;
}

class ServerConfigurationDialog;

struct MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void mouseReleaseEvent(QMouseEvent* ev);
    void mouseMoveEvent(QMouseEvent* ev);

private:
    static const int TEXT_MODE_HEIGHT = MAIN_WINDOW_TEXT_MODE_HEIGHT;
    static const int TEXT_MODE_WIDTH = MAIN_WINDOW_TEXT_MODE_WIDTH;
    static const int MANU_MODE_HEIGHT = MAIN_WINDOW_MANU_MODE_HEIGHT;
    static const int MANU_MODE_WIDTH = MAIN_WINDOW_MANU_MODE_WIDTH;
    static const int BOARD_ROW = MANU_BOARD_ROW;
    static const int BOARD_COL = MANU_BOARD_COL;

    Ui::MainWindow *ui;
    QWidget *mainWidget, *board, *operationAndBoard;
    ServerConfigurationDialog *configurationDialog;
    OperationEntity *arrowUpOperation, *arrowRightOperation, *arrowDownOperation, *arrowLeftOperation;
    OperationEntity *selectorOperation;
    OperationEntity *boolControllerOperation;
    OperationEntity *intControllerOperation;
    OperationEntity *comparatorOperation;
    OperationEntity *bitSetterOperation;
    OperationEntity *outputOperation;
    OperationEntity *clearOperation;

    QVBoxLayout mainLayout, operationAndBoardLayout;
    QHBoxLayout buttonLayout, operationLayout;
    QGridLayout boardLayout;
    QStackedLayout mainAreaLayout;
    QPushButton setTextModeButton, setManuModeButton, clearButton;
    TextEditor *textArea;
    BoardGrid *grid[BOARD_ROW][BOARD_COL];

    Compiler *compiler;

    int mode;
    operationType activatedOperation;

public slots:
    void setTextMode();
    void setManuMode();
    void allClear();
    void onDeployAction();
    void onExecuteAction();
    void activateHandler(operationType type);
};

#endif // MAINWINDOW_H
