#ifndef SERVERCONFIGURATIONDIALOG_H
#define SERVERCONFIGURATIONDIALOG_H

#include <QDialog>

namespace Ui {
    class ServerConfigurationDialog;
}

class ServerConfigurationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServerConfigurationDialog(QWidget *parent = 0);
    ~ServerConfigurationDialog();

private:
    Ui::ServerConfigurationDialog *ui;
};

#endif // SERVERCONFIGURATIONDIALOG_H
