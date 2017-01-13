#ifndef OUTPUTDIALOG_H
#define OUTPUTDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QRadioButton>
#include <QPushButton>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include "const.h"

struct OutputDialog : public QDialog {
    Q_OBJECT

public:
    OutputDialog(QWidget* parent = 0, int _selectedFormat = 0, int _selectedIntVar = 0);
    ~OutputDialog();
    int getSelectedFormat();
    int getSelectedIntVar();
    bool getConfirmed();

private:
    static const int HEIGHT = OUTPUT_DIALOG_HEIGHT;
    static const int WIDTH = OUTPUT_DIALOG_WIDTH;

    QRadioButton formatButtons[OUTPUT_FORMAT_CNT];
    QRadioButton intVarButtons[INT_VAR_CNT];
    QButtonGroup formatButtonGroup, intVarButtonGroup;
    QLabel formatLabel, intVarLabel;
    QPushButton ok, cancel;

    QGridLayout buttonsLayout;
    QHBoxLayout okAndCancelLayout;
    QVBoxLayout mainLayout;

    int selectedFormat, selectedIntVar;
    bool confirmed;

public slots:
    void okClicked();
    void cancelClicked();
};

#endif // OUTPUTDIALOG_H

