#include "shelldialog.h"

ShellDialog::ShellDialog(QWidget *parent, QString code):
    QDialog(parent)
{
    setWindowTitle("Code Shell...");
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedSize(WIDTH, HEIGHT);

    codeLabel.setText("Code:");
    codeEditor.setPlainText(code);

    ok.setText("OK");
    cancel.setText("Cancel");
    okAndCancelLayout.addWidget(&ok);
    okAndCancelLayout.addWidget(&cancel);
    connect(&ok, SIGNAL(clicked()), this, SLOT(okClicked()));
    connect(&cancel, SIGNAL(clicked()), this, SLOT(cancelClicked()));

    mainLayout.addWidget(&codeLabel);
    mainLayout.addWidget(&codeEditor);
    mainLayout.addLayout(&okAndCancelLayout);
    setLayout(&mainLayout);

    confirmed = 0;
    setVisible(1);
    exec();
}

ShellDialog::~ShellDialog()
{
    setVisible(0);
}

QString ShellDialog::getCode()
{
    return codeEditor.toPlainText();
}

bool ShellDialog::getConfirmed()
{
    return confirmed;
}

void ShellDialog::okClicked()
{
    confirmed = 1;
    close();
}

void ShellDialog::cancelClicked()
{
    confirmed = 0;
    close();
}
