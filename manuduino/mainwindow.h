#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QStackedLayout>
#include <QPushButton>
#include "texteditor.h"
#include "boardgrid.h"

namespace Ui {
    struct MainWindow;
}

struct MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    static const int TEXT_MODE_HEIGHT = MAIN_WINDOW_TEXT_MODE_HEIGHT;
    static const int TEXT_MODE_WIDTH = MAIN_WINDOW_TEXT_MODE_WIDTH;
    static const int MANU_MODE_HEIGHT = MAIN_WINDOW_MANU_MODE_HEIGHT;
    static const int MANU_MODE_WIDTH = MAIN_WINDOW_MANU_MODE_WIDTH;
    static const int BOARD_ROW = MANU_BOARD_ROW;
    static const int BOARD_COL = MANU_BOARD_COL;

    Ui::MainWindow *ui;
    QWidget *mainWidget, *board;

    QVBoxLayout mainLayout;
    QHBoxLayout buttonLayout;
    QGridLayout boardLayout;
    QStackedLayout mainAreaLayout;
    QPushButton setTextModeButton, setManuModeButton, clearButton;
    TextEditor *textArea;
    BoardGrid grid[BOARD_ROW][BOARD_COL];

    int mode;

public slots:
    void setTextMode();
    void setManuMode();
    void allClear();
};

#endif // MAINWINDOW_H
