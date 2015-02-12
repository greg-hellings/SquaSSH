#include "mainwindow.h"
#include "accountlistmodel.h"
#include "ui_mainwindow.h"
#include "ui_accountlist.h"
#include "account.h"

#include "qtermwidget.h"
#include <qtreetabs.h>
#include <QLabel>

#define EMPTY_TAB_INDEX 0
#define EMPTY_TAB_COUNT 1

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    accountWindow(NULL),
    accountListModel(new AccountListModel())
{
    ui->setupUi(this);
    this->connect(this->ui->openConnection, SIGNAL(clicked()), SLOT(newTab()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newTab()
{
    // Create dialog and its UI
    QDialog* dialog = new QDialog();
    this->accountListUi = new Ui::AccountList;
    this->accountListUi->setupUi(dialog);
    // Bind UI to account listing
    this->accountListUi->accounts->setModel(this->accountListModel);
    dialog->show();
    // Button bindings
    this->connect(this->accountListUi->add, SIGNAL(clicked()), SLOT(addAccount()));
    this->connect(this->accountListUi->edit, SIGNAL(clicked()), SLOT(editAccount()));
    this->connect(this->accountListUi->remove, SIGNAL(clicked()), SLOT(removeAccount()));
    QObject::connect(this->accountListUi->cancel, SIGNAL(clicked()), dialog, SLOT(close()));
    // Create shell term
//    QTermWidget* term = new QTermWidget(this);
//    term->setScrollBarPosition(QTermWidget::ScrollBarRight);
//    term->setShellProgram("ssh");
//    QStringList args;
//    term->setArgs(args);
//    term->startShellProgram();
//    // Remove it when the session ends
//    this->connect(term, SIGNAL(finished()), SLOT(removeTab()));
//    // Add it to the tab deck
//    this->ui->tabWidget->newTab(term);

}

void MainWindow::addAccount()
{
    this->accountWindow = new Account();
    this->connect(this->accountWindow, SIGNAL(accepted(AccountEntry*)), SLOT(addAccount(AccountEntry*)));
    this->accountWindow->show();
}

void MainWindow::addAccount(AccountEntry *entry)
{
    this->accountWindow->close();
    this->accountListModel->append(entry);
}

void MainWindow::editAccount()
{
    QModelIndexList selection = this->accountListUi->accounts->selectionModel()->selectedIndexes();
    if (selection.count() > 0) {
        AccountEntry* entry = static_cast<AccountEntry*>(this->accountListModel->index(selection.first().row(), 0, QModelIndex()).internalPointer());
        this->accountWindow = new Account(entry, this);
        this->connect(this->accountWindow, SIGNAL(accepted(AccountEntry*)), SLOT(editAccount(AccountEntry*)));
        this->accountWindow->show();
    }
}

void MainWindow::editAccount(AccountEntry* entry)
{
    this->accountWindow->close();
    this->accountListModel->update(this->accountListUi->accounts->selectionModel()->selectedIndexes().first().row(), entry);
}

void MainWindow::removeAccount()
{
    this->accountListModel->removeRow(this->accountListUi->accounts->selectionModel()->selectedIndexes().first().row());
}

void MainWindow::removeTab()
{
    QWidget* sender = (QWidget*)QObject::sender();
    this->ui->tabWidget->closeTab(this->ui->tabWidget->findTabByWidget(sender));
}
