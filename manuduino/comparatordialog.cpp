#include "comparatordialog.h"
#include <QString>

ComparatorDialog::ComparatorDialog(QWidget *parent, int _selectedBoolVar, int _selectedIntVar, int _selectedOperator):
    QDialog(parent), selectedBoolVar(_selectedBoolVar), selectedIntVar(_selectedIntVar), selectedOperator(_selectedOperator)
{
    setWindowTitle("Comparator...");
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedSize(WIDTH, HEIGHT);

    boolVarLabel.setText("Bool Variable: ");
    buttonsLayout.addWidget(&boolVarLabel, 0, 0, 1, 6);
    for (int i=0; i<BOOL_VAR_CNT; ++i) {
        QString buttonPixPath = "://bool_";
        buttonPixPath += (char) (i + 48);
        buttonPixPath += ".jpeg";

        boolVarButtons[i].setIcon(QIcon(buttonPixPath));
        boolVarButtonGroup.addButton(&(boolVarButtons[i]), i);

        buttonsLayout.addWidget(&(boolVarButtons[i]), i / 6 + 1, i % 6);
    }
    boolVarButtons[_selectedBoolVar].setChecked(1);
    boolVarButtonGroup.setExclusive(1);

    intVarLabel.setText("Int Variable: ");
    buttonsLayout.addWidget(&intVarLabel, 3, 0, 1, 6);
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

        buttonsLayout.addWidget(&(intVarButtons[i]), 4, i);
    }
    intVarButtons[_selectedIntVar].setChecked(1);
    intVarButtonGroup.setExclusive(1);

    operatorLabel.setText("Operator: ");
    buttonsLayout.addWidget(&operatorLabel, 5, 0, 1, 6);
    for (int i=0; i<COMPARATOR_OPERATOR_CNT; ++i) {
        QString buttonName;
        switch (i) {
            case 0: {buttonName = "=="; break;}
            case 1: {buttonName = ">"; break;}
            case 2: {buttonName = ">="; break;}
            case 3: {buttonName = "<"; break;}
            case 4: {buttonName = "<="; break;}
            case 5: {buttonName = "!="; break;}
            default: buttonName = "";
        }

        operatorButtons[i].setText(buttonName);
        operatorButtonGroup.addButton(&(operatorButtons[i]), i);

        buttonsLayout.addWidget(&(operatorButtons[i]), 6, i);
    }
    operatorButtons[_selectedOperator].setChecked(1);
    operatorButtonGroup.setExclusive(1);

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

ComparatorDialog::~ComparatorDialog()
{
    setVisible(0);
}

int ComparatorDialog::getSelectedBoolVar()
{
    return selectedBoolVar;
}

int ComparatorDialog::getSelectedIntVar()
{
    return selectedIntVar;
}

int ComparatorDialog::getSelectedOperator()
{
    return selectedOperator;
}

bool ComparatorDialog::getConfirmed()
{
    return confirmed;
}

void ComparatorDialog::okClicked()
{
    selectedBoolVar = boolVarButtonGroup.checkedId();
    selectedIntVar = intVarButtonGroup.checkedId();
    selectedOperator = operatorButtonGroup.checkedId();

    confirmed = 1;
    close();
}

void ComparatorDialog::cancelClicked()
{
    confirmed = 0;
    close();
}

