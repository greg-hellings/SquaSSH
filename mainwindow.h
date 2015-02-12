#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class TermWidget;
class QLabel;
class Account;
class AccountEntry;
class AccountListModel;
class QSettings;

namespace Ui {
class MainWindow;
class AccountList;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void openConnection();
    void newTab();
    void quickOpen();
    void removeTab();
    void addAccount();
    void addAccount(AccountEntry* entry);
    void editAccount();
    void editAccount(AccountEntry* entry);
    void removeAccount();

protected:
    QModelIndex currentSelection();
    void createTab(const AccountEntry* entry);

private:
    Ui::MainWindow *ui;
    Ui::AccountList* accountListUi;
    QDialog* accountListDialog;
    Account* accountWindow;
    AccountListModel* accountListModel;
    QSettings* settings;
};

#endif // MAINWINDOW_H
