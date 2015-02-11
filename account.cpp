#include "account.h"
#include "ui_account.h"

Account::Account(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::account)
{
    ui->setupUi(this);
}

Account::~Account()
{
    delete ui;
}

QString Account::displayName() const
{
    return this->ui->displayName->text();
}

QString Account::username() const
{
    return this->ui->username->text();
}

QString Account::host() const
{
    return this->ui->host->text();
}

QString Account::remoteDirectory() const
{
    return this->ui->remoteDirectory->text();
}

bool Account::isSocksEnabled() const
{
    return this->ui->socksEnabled->isChecked();
}

int Account::socksPort() const
{
    return this->ui->socksPort->value();
}

bool Account::isRemoteEnabled() const
{
    return this->ui->remoteEnabled->isChecked();
}

int Account::remotePort() const
{
    return this->ui->remotePort->value();
}

bool Account::isLocalEnabled() const
{
    return this->ui->localEnabled->isChecked();
}

int Account::localPort() const
{
    return this->ui->localPort->value();
}
