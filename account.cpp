#include "account.h"
#include "ui_account.h"
#include "accountentry.h"

Account::Account(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::account)
{
    ui->setupUi(this);
    this->connect(this->ui->buttonBox, SIGNAL(accepted()), SLOT(ok()));
    this->connect(this->ui->buttonBox, SIGNAL(rejected()), SLOT(close()));
}

Account::Account(AccountEntry* entry, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::account)
{
    this->ui->setupUi(this);
    this->connect(this->ui->buttonBox, SIGNAL(accepted()), SLOT(ok()));
    this->connect(this->ui->buttonBox, SIGNAL(rejected()), SLOT(close()));
    this->ui->displayName->setText(entry->displayName);
    this->ui->host->setText(entry->host);
    this->ui->username->setText(entry->username);
    this->ui->remoteDirectory->setText(entry->remoteDirectory);
    // Ports
    this->ui->localEnabled->setChecked(entry->isLocalPortEnabled);
    this->ui->localPort->setValue(entry->localPort);
    this->ui->remoteEnabled->setChecked(entry->isRemotePortEnabled);
    this->ui->remotePort->setValue(entry->remotePort);
    this->ui->socksEnabled->setChecked(entry->isSocksPortEnabled);
    this->ui->socksPort->setValue(entry->socksPort);
    // Flags
    this->ui->xEnabled->setChecked(entry->isXForwardingEnabled);
    this->ui->compressionEnabled->setChecked(entry->isCompressionEnabled);
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

bool Account::isCompressionEnabled() const
{
    return this->ui->compressionEnabled->isChecked();
}

bool Account::isXForwardingEnabled() const
{
    return this->ui->xEnabled->isChecked();
}

void Account::ok()
{
    AccountEntry* entry = new AccountEntry;
    // Necessary parts
    entry->displayName = this->displayName();
    entry->host = this->host();
    entry->username = this->username();
    // Options
    entry->remoteDirectory = this->remoteDirectory();
    // Proxies
    entry->isLocalPortEnabled = this->isLocalEnabled();
    entry->localPort = this->localPort();
    entry->isRemotePortEnabled = this->isRemoteEnabled();
    entry->remotePort = this->remotePort();
    entry->isSocksPortEnabled = this->isSocksEnabled();
    entry->socksPort = this->socksPort();
    // Flags
    entry->isCompressionEnabled = this->isCompressionEnabled();
    entry->isXForwardingEnabled = this->isXForwardingEnabled();

    emit accepted(entry);
}
