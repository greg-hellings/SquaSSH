#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class TermWidget;
class QLabel;
class Account;
class AccountEntry;
class AccountListModel;

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
    void newTab();
    void removeTab();
    void addAccount();
    void addAccount(AccountEntry* entry);
    void editAccount();
    void editAccount(AccountEntry* entry);
    void removeAccount();

private:
    Ui::MainWindow *ui;
    Ui::AccountList* accountListUi;
    Account* accountWindow;
    AccountListModel* accountListModel;
};

#endif // MAINWINDOW_H
