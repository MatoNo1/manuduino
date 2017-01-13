#ifndef BOOLCONTROLLERDIALOG_H
#define BOOLCONTROLLERDIALOG_H

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

struct BoolControllerDialog : public QDialog {
    Q_OBJECT

public:
    BoolControllerDialog(QWidget* parent = 0, int _selectedBoolVar = 0, int _selectedType = 0);
    ~BoolControllerDialog();
    int getSelectedBoolVar();
    int getSelectedType();
    bool getConfirmed();

private:
    static const int HEIGHT = BOOL_CONTROLLER_DIALOG_HEIGHT;
    static const int WIDTH = BOOL_CONTROLLER_DIALOG_WIDTH;

    QRadioButton boolVarButtons[BOOL_VAR_CNT];
    QRadioButton typeButtons[BOOL_CONTROLLER_TYPE_CNT];
    QButtonGroup boolVarButtonGroup, typeButtonGroup;
    QLabel boolVarLabel, typeLabel;
    QPushButton ok, cancel;

    QGridLayout buttonsLayout;
    QHBoxLayout okAndCancelLayout;
    QVBoxLayout mainLayout;

    int selectedBoolVar, selectedType;
    bool confirmed;

public slots:
    void okClicked();
    void cancelClicked();
};

#endif // BOOLCONTROLLERDIALOG_H

