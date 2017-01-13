#ifndef COMPARATORDIALOG_H
#define COMPARATORDIALOG_H

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

struct ComparatorDialog : public QDialog {
    Q_OBJECT

public:
    ComparatorDialog(QWidget* parent = 0, int _selectedBoolVar = 0, int _selectedIntVar = 0, int _selectedOperator = 0);
    ~ComparatorDialog();
    int getSelectedBoolVar();
    int getSelectedIntVar();
    int getSelectedOperator();
    bool getConfirmed();

private:
    static const int HEIGHT = COMPARATOR_DIALOG_HEIGHT;
    static const int WIDTH = COMPARATOR_DIALOG_WIDTH;

    QRadioButton boolVarButtons[BOOL_VAR_CNT];
    QRadioButton intVarButtons[INT_VAR_CNT];
    QRadioButton operatorButtons[COMPARATOR_OPERATOR_CNT];
    QButtonGroup boolVarButtonGroup, intVarButtonGroup, operatorButtonGroup;
    QLabel boolVarLabel, intVarLabel, operatorLabel;
    QPushButton ok, cancel;

    QGridLayout buttonsLayout;
    QHBoxLayout okAndCancelLayout;
    QVBoxLayout mainLayout;

    int selectedBoolVar, selectedIntVar, selectedOperator;
    bool confirmed;

public slots:
    void okClicked();
    void cancelClicked();
};

#endif // COMPARATORDIALOG_H

