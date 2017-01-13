#include "boolcontrollerdialog.h"
#include <QString>

BoolControllerDialog::BoolControllerDialog(QWidget *parent, int _selectedBoolVar, int _selectedType):
    QDialog(parent), selectedBoolVar(_selectedBoolVar), selectedType(_selectedType)
{
    setWindowTitle("Bool Controller...");
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedSize(WIDTH, HEIGHT);

    boolVarLabel.setText("Bool Variable: ");
    buttonsLayout.addWidget(&boolVarLabel, 0, 0, 1, 4);
    for (int i=0; i<BOOL_VAR_CNT; ++i) {
        QString buttonPixPath = "://bool_";
        buttonPixPath += (char) (i + 48);
        buttonPixPath += ".jpeg";

        boolVarButtons[i].setIcon(QIcon(buttonPixPath));
        boolVarButtonGroup.addButton(&(boolVarButtons[i]), i);

        buttonsLayout.addWidget(&(boolVarButtons[i]), i / 4 + 1, i % 4);
    }
    boolVarButtons[_selectedBoolVar].setChecked(1);
    boolVarButtonGroup.setExclusive(1);

    typeLabel.setText("Type: ");
    buttonsLayout.addWidget(&typeLabel, 3, 0, 1, 4);
    for (int i=0; i<BOOL_CONTROLLER_TYPE_CNT; ++i) {
        QString buttonPixPath = "://BoolController/BoolController_Frame_";
        buttonPixPath += (char) (i + 48);
        buttonPixPath += ".jpeg";

        typeButtons[i].setIcon(QIcon(buttonPixPath));
        typeButtonGroup.addButton(&(typeButtons[i]), i);

        buttonsLayout.addWidget(&(typeButtons[i]), 4, i);
    }
    typeButtons[_selectedType].setChecked(1);
    typeButtonGroup.setExclusive(1);

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

BoolControllerDialog::~BoolControllerDialog()
{
    setVisible(0);
}

int BoolControllerDialog::getSelectedBoolVar()
{
    return selectedBoolVar;
}

int BoolControllerDialog::getSelectedType()
{
    return selectedType;
}

bool BoolControllerDialog::getConfirmed()
{
    return confirmed;
}

void BoolControllerDialog::okClicked()
{
    selectedBoolVar = boolVarButtonGroup.checkedId();
    selectedType = typeButtonGroup.checkedId();

    confirmed = 1;
    close();
}

void BoolControllerDialog::cancelClicked()
{
    confirmed = 0;
    close();
}

