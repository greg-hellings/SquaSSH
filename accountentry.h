#ifndef ACCOUNTENTRY_H
#define ACCOUNTENTRY_H

#include <QString>

class AccountEntry
{
public:
    AccountEntry();
    ~AccountEntry();

    QString displayName;
    QString username;
    QString host;
    QString remoteDirectory;
    bool isSocksPortEnabled;
    int socksPort;
    bool isLocalPortEnabled;
    int localPort;
    bool isRemotePortEnabled;
    int remotePort;
    bool isXForwardingEnabled;
    bool isCompressionEnabled;
};

#endif // ACCOUNTENTRY_H
