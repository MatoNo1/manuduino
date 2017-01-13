#ifndef SELECTORDIALOG_H
#define SELECTORDIALOG_H

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

struct SelectorDialog : public QDialog {
    Q_OBJECT

public:
    SelectorDialog(QWidget* parent = 0, int _selectedBoolVar = 0, int _selectedDir = 0);
    ~SelectorDialog();
    int getSelectedBoolVar();
    int getSelectedDir();
    bool getConfirmed();

private:
    static const int HEIGHT = SELECTOR_DIALOG_HEIGHT;
    static const int WIDTH = SELECTOR_DIALOG_WIDTH;

    QRadioButton boolVarButtons[BOOL_VAR_CNT];
    QRadioButton dirButtons[SELECTOR_DIRECT_CNT];
    QButtonGroup boolVarButtonGroup, dirButtonGroup;
    QLabel boolVarLabel, dirLabel;
    QPushButton ok, cancel;

    QGridLayout buttonsLayout;
    QHBoxLayout okAndCancelLayout;
    QVBoxLayout mainLayout;

    int selectedBoolVar, selectedDir;
    bool confirmed;

public slots:
    void okClicked();
    void cancelClicked();
};

#endif // SELECTORDIALOG_H

