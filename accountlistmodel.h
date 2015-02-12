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
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    bool append(AccountEntry* entry);

private:
    QVector<AccountEntry*> items;
    const QModelIndex wat;
};

#endif // ACCOUNTLIST_H
