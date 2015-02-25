#include "accountentry.h"

#include <QSettings>

AccountEntry::AccountEntry()
{

}

AccountEntry::AccountEntry(const QSettings *settings)
{
    this->displayName = settings->value("displayName").toString();
    this->username = settings->value("username").toString();
    this->host = settings->value("host").toString();
    this->remoteDirectory = settings->value("remoteDirectory").toString();
    // Proxies
    this->isSocksPortEnabled = settings->value("isSocksPortEnabled").toBool();
    this->socksPort = settings->value("socksPort").toString();
    this->isRemotePortEnabled = settings->value("isRemotePortEnabled").toBool();
    this->remotePort = settings->value("remotePort").toString();
    this->isLocalPortEnabled = settings->value("isLocalPortEnabled").toBool();
    this->localPort = settings->value("localPort").toString();
    // Flags
    this->isXForwardingEnabled = settings->value("isXForwardingEnabled").toBool();
    this->isCompressionEnabled = settings->value("isCompressionEnabled").toBool();
}

AccountEntry::~AccountEntry()
{

}

void AccountEntry::writeToSettings(QSettings *settings)
{
    settings->setValue("displayName", this->displayName);
    settings->setValue("username", this->username);
    settings->setValue("host", this->host);
    settings->setValue("remoteDirectory", this->remoteDirectory);
    // Proxies
    settings->setValue("isSocksPortEnabled", this->isSocksPortEnabled);
    settings->setValue("socksPort", this->socksPort);
    settings->setValue("isRemotePortEnabled", this->isRemotePortEnabled);
    settings->setValue("remotePort", this->remotePort);
    settings->setValue("isLocalPortEnabled", this->isLocalPortEnabled);
    settings->setValue("localPort", this->localPort);
    // Flags
    settings->setValue("isXForwardingEnabled", this->isXForwardingEnabled);
    settings->setValue("isCompressionEnabled", this->isCompressionEnabled);
}
