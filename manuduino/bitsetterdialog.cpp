#include "bitsetterdialog.h"
#include <QString>

BitSetterDialog::BitSetterDialog(QWidget *parent, int _selectedIntVar, int _selectedBit, int _selectedBoolVar):
    QDialog(parent), selectedIntVar(_selectedIntVar), selectedBit(_selectedBit), selectedBoolVar(_selectedBoolVar)
{
    setWindowTitle("Bit Setter...");
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedSize(WIDTH, HEIGHT);

    intVarLabel.setText("Int Variable: ");
    buttonsLayout.addWidget(&intVarLabel, 0, 0, 1, 4);
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

    bitLabel.setText("Bit No.: ");
    buttonsLayout.addWidget(&bitLabel, 2, 0, 1, 4);
    for (int i=0; i<INT_BIT_LEN; ++i) {
        QString buttonName = "[";
        buttonName += (char) (i + 48);
        buttonName += "]";

        bitButtons[i].setText(buttonName);
        bitButtonGroup.addButton(&(bitButtons[i]), i);

        buttonsLayout.addWidget(&(bitButtons[i]), i / 4 + 3, i % 4);
    }
    bitButtons[_selectedBit].setChecked(1);
    bitButtonGroup.setExclusive(1);

    boolVarLabel.setText("Bool Variable: ");
    buttonsLayout.addWidget(&boolVarLabel, 5, 0, 1, 4);
    for (int i=0; i<BOOL_VAR_CNT; ++i) {
        QString buttonPixPath = "://bool_";
        buttonPixPath += (char) (i + 48);
        buttonPixPath += ".jpeg";

        boolVarButtons[i].setIcon(QIcon(buttonPixPath));
        boolVarButtonGroup.addButton(&(boolVarButtons[i]), i);

        buttonsLayout.addWidget(&(boolVarButtons[i]), i / 4 + 6, i % 4);
    }
    boolVarButtons[_selectedBoolVar].setChecked(1);
    boolVarButtonGroup.setExclusive(1);

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

BitSetterDialog::~BitSetterDialog()
{
    setVisible(0);
}

int BitSetterDialog::getSelectedIntVar()
{
    return selectedIntVar;
}

int BitSetterDialog::getSelectedBit()
{
    return selectedBit;
}

int BitSetterDialog::getSelectedBoolVar()
{
    return selectedBoolVar;
}

bool BitSetterDialog::getConfirmed()
{
    return confirmed;
}

void BitSetterDialog::okClicked()
{
    selectedIntVar = intVarButtonGroup.checkedId();
    selectedBit = bitButtonGroup.checkedId();
    selectedBoolVar = boolVarButtonGroup.checkedId();

    confirmed = 1;
    close();
}

void BitSetterDialog::cancelClicked()
{
    confirmed = 0;
    close();
}

