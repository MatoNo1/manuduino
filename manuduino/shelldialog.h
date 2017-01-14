#ifndef SHELLDIALOG_H
#define SHELLDIALOG_H

#include <QWidget>
#include <QString>
#include <QDialog>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "const.h"

struct ShellDialog : public QDialog {
    Q_OBJECT

public:
    ShellDialog(QWidget* parent = 0, QString code = "");
    ~ShellDialog();
    QString getCode();
    bool getConfirmed();

private:
    static const int HEIGHT = SHELL_DIALOG_HEIGHT;
    static const int WIDTH = SHELL_DIALOG_WIDTH;

    QLabel codeLabel;
    QTextEdit codeEditor;
    QPushButton ok, cancel;

    QHBoxLayout okAndCancelLayout;
    QVBoxLayout mainLayout;

    bool confirmed;

public slots:
    void okClicked();
    void cancelClicked();
};

#endif // SHELLDIALOG_H

