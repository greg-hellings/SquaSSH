#ifndef ACCOUNTLIST_H
#define ACCOUNTLIST_H

#include <QAbstractListModel>
#include <QVector>

#include "accountentry.h"

class AccountListModel : public QAbstractListModel
{
public:
    AccountListModel();
    ~AccountListModel();

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const;
    bool removeRow(int row, const QModelIndex &parent = QModelIndex());
    bool append(AccountEntry* entry);
    bool update(int row, AccountEntry* entry);

private:
    QVector<AccountEntry*> items;
    const QModelIndex wat;
};

#endif // ACCOUNTLIST_H
