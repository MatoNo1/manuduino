#ifndef INTCONTROLLERDIALOG_H
#define INTCONTROLLERDIALOG_H

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

struct IntControllerDialog : public QDialog {
    Q_OBJECT

public:
    IntControllerDialog(QWidget* parent = 0, int _selectedIntVar = 0, int _selectedOperator = 0, int _selectedVal = 0);
    ~IntControllerDialog();
    int getSelectedIntVar();
    int getSelectedOperator();
    int getSelectedVal();
    bool getConfirmed();

private:
    static const int HEIGHT = INT_CONTROLLER_DIALOG_HEIGHT;
    static const int WIDTH = INT_CONTROLLER_DIALOG_WIDTH;

    QRadioButton intVarButtons[INT_VAR_CNT];
    QRadioButton operatorButtons[INT_CONTROLLER_OPERATOR_CNT];
    QRadioButton valButtons[INT_CONTROLLER_VAL_CNT];
    QButtonGroup intVarButtonGroup, operatorButtonGroup, valButtonGroup;
    QLabel intVarLabel, operatorLabel, valLabel;
    QPushButton ok, cancel;

    QGridLayout buttonsLayout;
    QHBoxLayout okAndCancelLayout;
    QVBoxLayout mainLayout;

    int selectedIntVar, selectedOperator, selectedVal;
    bool confirmed;

public slots:
    void setValRange0ToF();
    void setValRange1ToF();
    void setValRange2ToF();
    void setValIJKCheckable();
    void okClicked();
    void cancelClicked();
};

#endif // INTCONTROLLERDIALOG_H

