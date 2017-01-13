#include "intcontrollerdialog.h"
#include <QString>

IntControllerDialog::IntControllerDialog(QWidget *parent, int _selectedIntVar, int _selectedOperator, int _selectedVal):
    QDialog(parent), selectedIntVar(_selectedIntVar), selectedOperator(_selectedOperator), selectedVal(_selectedVal)
{
    setWindowTitle("Int Controller...");
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedSize(WIDTH, HEIGHT);

    intVarLabel.setText("Int Variable: ");
    buttonsLayout.addWidget(&intVarLabel, 0, 0, 1, 6);
    for (int i=0; i<INT_VAR_CNT; ++i) {
        QString buttonName;
        switch (i) {
            case 0: {buttonName = "i"; break;}
            case 1: {buttonName = "j"; break;}
            case 2: {buttonName = "k"; break;}
            default: buttonName = "";
        }

        intVarButtons[i].setText(buttonName);
        intVarButtonGroup.addButton(&(intVarButtons[i]), i);

        buttonsLayout.addWidget(&(intVarButtons[i]), 1, i);
    }
    intVarButtons[_selectedIntVar].setChecked(1);
    intVarButtonGroup.setExclusive(1);

    operatorLabel.setText("Operator: ");
    buttonsLayout.addWidget(&operatorLabel, 2, 0, 1, 6);
    for (int i=0; i<INT_CONTROLLER_OPERATOR_CNT; ++i) {
        QString buttonName;
        switch (i) {
            case 0: {buttonName = "="; break;}
            case 1: {buttonName = "+="; break;}
            case 2: {buttonName = "-="; break;}
            case 3: {buttonName = "*="; break;}
            case 4: {buttonName = "/="; break;}
            case 5: {buttonName = "%="; break;}
            default: buttonName = "";
        }

        operatorButtons[i].setText(buttonName);
        operatorButtonGroup.addButton(&(operatorButtons[i]), i);

        buttonsLayout.addWidget(&(operatorButtons[i]), 3, i);
    }
    operatorButtons[_selectedOperator].setChecked(1);
    operatorButtonGroup.setExclusive(1);

    valLabel.setText("Value: ");
    buttonsLayout.addWidget(&valLabel, 4, 0, 1, 6);
    for (int i=0; i<INT_CONTROLLER_VAL_CNT; ++i) {
        QString buttonName;
        if (i < 10)
            buttonName = (char) (i + 48);
        else if (i < 16) {
            buttonName = "1";
            buttonName += (char) (i + 38);
        } else if (i == 16)
            buttonName = "i";
        else if (i == 17)
            buttonName = "j";
        else if (i == 18)
            buttonName = "k";
        else
            buttonName = "";

        valButtons[i].setText(buttonName);
        valButtonGroup.addButton(&(valButtons[i]), i);

        buttonsLayout.addWidget(&(valButtons[i]), i / 6 + 5, i % 6);
    }
    valButtons[_selectedVal].setChecked(1);
    valButtonGroup.setExclusive(1);

    switch (_selectedOperator) {
        case 0: {
            valButtons[0].setCheckable(1); valButtons[1].setCheckable(1);
            break;
        }
        case 1: case 2: {
            valButtons[0].setCheckable(0); valButtons[1].setCheckable(1);
            break;
        }
        case 3: case 4: case 5: {
            valButtons[0].setCheckable(0); valButtons[1].setCheckable(0);
            break;
        }
        default: {
            valButtons[0].setCheckable(1); valButtons[1].setCheckable(1);
        }
    }

    switch (_selectedIntVar) {
        case 0: {
            valButtons[16].setCheckable(_selectedOperator == 3);
            valButtons[17].setCheckable(1);
            valButtons[18].setCheckable(1);
            break;
        }
        case 1: {
            valButtons[16].setCheckable(1);
            valButtons[17].setCheckable(_selectedOperator == 3);
            valButtons[18].setCheckable(1);
            break;
        }
        case 2: {
            valButtons[16].setCheckable(1);
            valButtons[17].setCheckable(1);
            valButtons[18].setCheckable(_selectedOperator == 3);
            break;
        }
        default: {
            valButtons[16].setCheckable(1);
            valButtons[17].setCheckable(1);
            valButtons[18].setCheckable(1);
            break;
        }
    }

    connect(&operatorButtons[0], SIGNAL(clicked()), this, SLOT(setValRange0ToF()));
    connect(&operatorButtons[1], SIGNAL(clicked()), this, SLOT(setValRange1ToF()));
    connect(&operatorButtons[2], SIGNAL(clicked()), this, SLOT(setValRange1ToF()));
    connect(&operatorButtons[3], SIGNAL(clicked()), this, SLOT(setValRange2ToF()));
    connect(&operatorButtons[4], SIGNAL(clicked()), this, SLOT(setValRange2ToF()));
    connect(&operatorButtons[5], SIGNAL(clicked()), this, SLOT(setValRange2ToF()));

    connect(&intVarButtons[0], SIGNAL(clicked()), this, SLOT(setValIJKCheckable()));
    connect(&intVarButtons[1], SIGNAL(clicked()), this, SLOT(setValIJKCheckable()));
    connect(&intVarButtons[2], SIGNAL(clicked()), this, SLOT(setValIJKCheckable()));
    connect(&operatorButtons[0], SIGNAL(clicked()), this, SLOT(setValIJKCheckable()));
    connect(&operatorButtons[1], SIGNAL(clicked()), this, SLOT(setValIJKCheckable()));
    connect(&operatorButtons[2], SIGNAL(clicked()), this, SLOT(setValIJKCheckable()));
    connect(&operatorButtons[3], SIGNAL(clicked()), this, SLOT(setValIJKCheckable()));
    connect(&operatorButtons[4], SIGNAL(clicked()), this, SLOT(setValIJKCheckable()));
    connect(&operatorButtons[5], SIGNAL(clicked()), this, SLOT(setValIJKCheckable()));

    ok.setText("OK");
    cancel.setText("Cancel");
    okAndCancelLayout.addWidget(&ok);
    okAndCancelLayout.addWidget(&cancel);
    connect(&ok, SIGNAL(clicked()), this, SLOT(okClicked()));
    connect(&cancel, SIGNAL(clicked()), this, SLOT(cancelClicked()));

    mainLayout.addLayout(&buttonsLayout);
    mainLayout.addLayout(&okAndCancelLayout);
    setLayout(&mainLayout);

    confirmed = 0;
    setVisible(1);
    exec();
}

IntControllerDialog::~IntControllerDialog()
{
    setVisible(0);
}

int IntControllerDialog::getSelectedIntVar()
{
    return selectedIntVar;
}

int IntControllerDialog::getSelectedOperator()
{
    return selectedOperator;
}

int IntControllerDialog::getSelectedVal()
{
    return selectedVal;
}

bool IntControllerDialog::getConfirmed()
{
    return confirmed;
}

void IntControllerDialog::setValRange0ToF()
{
    valButtons[0].setCheckable(1); valButtons[1].setCheckable(1);
}

void IntControllerDialog::setValRange1ToF()
{
    valButtons[0].setCheckable(0); valButtons[1].setCheckable(1);
}

void IntControllerDialog::setValRange2ToF()
{
    valButtons[0].setCheckable(0); valButtons[1].setCheckable(0);
}

void IntControllerDialog::setValIJKCheckable()
{
    int tmpIntVar = intVarButtonGroup.checkedId();
    int tmpOperator = operatorButtonGroup.checkedId();

    switch (tmpIntVar) {
        case 0: {
            valButtons[16].setCheckable(tmpOperator == 3);
            valButtons[17].setCheckable(1);
            valButtons[18].setCheckable(1);
            break;
        }
        case 1: {
            valButtons[16].setCheckable(1);
            valButtons[17].setCheckable(tmpOperator == 3);
            valButtons[18].setCheckable(1);
            break;
        }
        case 2: {
            valButtons[16].setCheckable(1);
            valButtons[17].setCheckable(1);
            valButtons[18].setCheckable(tmpOperator == 3);
            break;
        }
        default: {
            valButtons[16].setCheckable(1);
            valButtons[17].setCheckable(1);
            valButtons[18].setCheckable(1);
            break;
        }
    }
}

void IntControllerDialog::okClicked()
{
    selectedIntVar = intVarButtonGroup.checkedId();
    selectedOperator = operatorButtonGroup.checkedId();
    selectedVal = valButtonGroup.checkedId();

    confirmed = 1;
    close();
}

void IntControllerDialog::cancelClicked()
{
    confirmed = 0;
    close();
}
