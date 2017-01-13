#ifndef BITSETTERDIALOG_H
#define BITSETTERDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QIcon>
#include <QLabel>
#include <QRadioButton>
#include <QPushButton>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include "const.h"

struct BitSetterDialog : public QDialog {
    Q_OBJECT

public:
    BitSetterDialog(QWidget* parent = 0, int _selectedIntVar = 0, int _selectedBit = 0, int _selectedBoolVar = 0);
    ~BitSetterDialog();
    int getSelectedIntVar();
    int getSelectedBit();
    int getSelectedBoolVar();
    bool getConfirmed();

private:
    static const int HEIGHT = BIT_SETTER_DIALOG_HEIGHT;
    static const int WIDTH = BIT_SETTER_DIALOG_WIDTH;

    QRadioButton intVarButtons[INT_VAR_CNT];
    QRadioButton bitButtons[INT_BIT_LEN];
    QRadioButton boolVarButtons[BOOL_VAR_CNT];
    QButtonGroup intVarButtonGroup, bitButtonGroup, boolVarButtonGroup;
    QLabel intVarLabel, bitLabel, boolVarLabel;
    QPushButton ok, cancel;

    QGridLayout buttonsLayout;
    QHBoxLayout okAndCancelLayout;
    QVBoxLayout mainLayout;

    int selectedIntVar, selectedBit, selectedBoolVar;
    bool confirmed;

public slots:
    void okClicked();
    void cancelClicked();
};

#endif // BITSETTERDIALOG_H

