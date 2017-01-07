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

    buttonLayout.addWidget(&setTextModeButton);
    buttonLayout.addWidget(&setManuModeButton);
    buttonLayout.addWidget(&clearButton);

    boardLayout.setSpacing(0);
    boardLayout.setMargin(0);
    for (int i=0; i<BOARD_ROW; ++i)
        for (int j=0; j<BOARD_COL; ++j) {
            boardLayout.addWidget(&grid[i][j], i, j);
            if (i == 2) grid[i][j].addArrowUp();
            if (j == 3) grid[i][j].addArrowDown();
            if (i == 5) grid[i][j].addArrowLeft();
            if (j == 6) grid[i][j].addArrowRight();
        }

    board = new QWidget(this);
    board->setLayout(&boardLayout);

    mainAreaLayout.addWidget(board);
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
}

MainWindow::~MainWindow()
{
    delete ui;
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
                grid[i][j].allClear();
}
