#include "ServerConfigurationDialog.h"
#include "ui_ServerConfigurationDialog.h"

ServerConfigurationDialog::ServerConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerConfigurationDialog)
{

  ui->setupUi(this);
}

ServerConfigurationDialog::~ServerConfigurationDialog()
{
  delete ui;
}
