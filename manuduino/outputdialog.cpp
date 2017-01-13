#include "outputdialog.h"
#include <QString>

OutputDialog::OutputDialog(QWidget *parent, int _selectedFormat, int _selectedIntVar):
    QDialog(parent), selectedFormat(_selectedFormat), selectedIntVar(_selectedIntVar)
{
    setWindowTitle("Output...");
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedSize(WIDTH, HEIGHT);

    formatLabel.setText("Format: ");
    buttonsLayout.addWidget(&formatLabel, 0, 0, 1, 3);
    for (int i=0; i<OUTPUT_FORMAT_CNT; ++i) {
        QString buttonName;
        switch (i) {
            case 0: {buttonName = "int8"; break;}
            case 1: {buttonName = "unsigned int8"; break;}
            case 2: {buttonName = "char"; break;}
            default: buttonName = "";
        }

        formatButtons[i].setText(buttonName);
        formatButtonGroup.addButton(&(formatButtons[i]), i);

        buttonsLayout.addWidget(&(formatButtons[i]), 1, i);
    }
    formatButtons[_selectedFormat].setChecked(1);
    formatButtonGroup.setExclusive(1);

    intVarLabel.setText("Int Variable: ");
    buttonsLayout.addWidget(&intVarLabel, 2, 0, 1, 3);
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

        buttonsLayout.addWidget(&(intVarButtons[i]), 3, i);
    }
    intVarButtons[_selectedIntVar].setChecked(1);
    intVarButtonGroup.setExclusive(1);

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

OutputDialog::~OutputDialog()
{
    setVisible(0);
}

int OutputDialog::getSelectedFormat()
{
    return selectedFormat;
}

int OutputDialog::getSelectedIntVar()
{
    return selectedIntVar;
}

bool OutputDialog::getConfirmed()
{
    return confirmed;
}

void OutputDialog::okClicked()
{
    selectedFormat = formatButtonGroup.checkedId();
    selectedIntVar = intVarButtonGroup.checkedId();

    confirmed = 1;
    close();
}

void OutputDialog::cancelClicked()
{
    confirmed = 0;
    close();
}

