#ifndef ACCOUNTS_H
#define ACCOUNTS_H

#include <QDialog>

namespace Ui {
class account;
}

class AccountEntry;

class Account : public QDialog
{
    Q_OBJECT

public:
    explicit Account(QWidget *parent = 0);
    Account(AccountEntry* entry, QWidget* parent = 0);
    ~Account();

    QString displayName() const;
    QString username() const;
    QString host() const;
    QString remoteDirectory() const;
    bool isSocksEnabled() const;
    QString socksPort() const;
    bool isLocalEnabled() const;
    QString localPort() const;
    bool isRemoteEnabled() const;
    QString remotePort() const;
    bool isXForwardingEnabled() const;
    bool isCompressionEnabled() const;

public slots:
    void ok();

signals:
    void accepted(AccountEntry* entry);

private:
    Ui::account *ui;
};

#endif // ACCOUNTS_H
