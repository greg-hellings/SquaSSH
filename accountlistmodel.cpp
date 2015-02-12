#include "accountlistmodel.h"

AccountListModel::AccountListModel() :
    items(),
    wat()
{

}

AccountListModel::~AccountListModel()
{

}

int AccountListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return this->items.count();
}

QVariant AccountListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (role != Qt::DisplayRole)
        return QVariant();
    return (static_cast<AccountEntry*>(index.internalPointer()))->displayName;
}

QModelIndex AccountListModel::index(int row, int column, const QModelIndex &parent) const
{
    return hasIndex(row, column, parent) ?
           createIndex(row, column, this->items[row]) :
           QModelIndex();
}

bool AccountListModel::append(AccountEntry* entry)
{
    int count = this->items.count();
    beginInsertRows(QModelIndex(), count, count);
    this->items.append(entry);
    endInsertRows();
    return true;
}

bool AccountListModel::update(int row, AccountEntry *entry)
{
    this->items.replace(row, entry);
    emit dataChanged(this->index(row), this->index(row));
    return true;
}

bool AccountListModel::removeRow(int row, const QModelIndex &parent)
{
    if (row < this->items.count()) {
        beginRemoveRows(QModelIndex(), row, row);
        this->items.remove(row);
        endRemoveRows();
    }
}
