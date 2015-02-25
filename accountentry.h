#ifndef ACCOUNTENTRY_H
#define ACCOUNTENTRY_H

#include <QString>

class QSettings;

class AccountEntry
{
public:
    AccountEntry();
    AccountEntry(const QSettings* settings);
    ~AccountEntry();

    void writeToSettings(QSettings* settings);

    QString displayName;
    QString username;
    QString host;
    QString remoteDirectory;
    bool isSocksPortEnabled;
    QString socksPort;
    bool isLocalPortEnabled;
    QString localPort;
    bool isRemotePortEnabled;
    QString remotePort;
    bool isXForwardingEnabled;
    bool isCompressionEnabled;
};

#endif // ACCOUNTENTRY_H
