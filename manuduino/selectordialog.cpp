#include "selectordialog.h"
#include <QString>

SelectorDialog::SelectorDialog(QWidget *parent, int _selectedBoolVar, int _selectedDir):
    QDialog(parent), selectedBoolVar(_selectedBoolVar), selectedDir(_selectedDir)
{
    setWindowTitle("Selector...");
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

    dirLabel.setText("Direct Type: ");
    buttonsLayout.addWidget(&dirLabel, 3, 0, 1, 4);
    for (int i=0; i<SELECTOR_DIRECT_CNT; ++i) {
        QString buttonPixPath = "://Selector/Selector_Frame_";
        buttonPixPath += (char) (i + 48);
        buttonPixPath += ".jpeg";

        dirButtons[i].setIcon(QIcon(buttonPixPath));
        dirButtonGroup.addButton(&(dirButtons[i]), i);

        buttonsLayout.addWidget(&(dirButtons[i]), 4, i);
    }
    dirButtons[_selectedDir].setChecked(1);
    dirButtonGroup.setExclusive(1);

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

SelectorDialog::~SelectorDialog()
{
    setVisible(0);
}

int SelectorDialog::getSelectedBoolVar()
{
    return selectedBoolVar;
}

int SelectorDialog::getSelectedDir()
{
    return selectedDir;
}

bool SelectorDialog::getConfirmed()
{
    return confirmed;
}

void SelectorDialog::okClicked()
{
    selectedBoolVar = boolVarButtonGroup.checkedId();
    selectedDir = dirButtonGroup.checkedId();

    confirmed = 1;
    close();
}

void SelectorDialog::cancelClicked()
{
    confirmed = 0;
    close();
}

