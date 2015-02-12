#include "mainwindow.h"
#include "accountlistmodel.h"
#include "ui_mainwindow.h"
#include "ui_accountlist.h"
#include "account.h"

#include "qtermwidget.h"
#include "opentab.h"
#include <qtreetabs.h>
#include <QLabel>
#include <QSettings>

#define EMPTY_TAB_INDEX 0
#define EMPTY_TAB_COUNT 1

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    accountWindow(NULL),
    accountListModel(new AccountListModel()),
    settings(new QSettings("thehellings.com", "SquaSSH"))
{
    ui->setupUi(this);
    this->connect(this->ui->openConnection, SIGNAL(clicked()), SLOT(openConnection()));

    int size = this->settings->beginReadArray("accounts");
    for (int i = 0; i < size; ++i) {
        this->settings->setArrayIndex(i);
        AccountEntry* entry = new AccountEntry(settings);
        this->accountListModel->append(entry);
    }
    this->settings->endArray();
}

MainWindow::~MainWindow()
{
    this->settings->remove("accounts");
    this->settings->beginWriteArray("accounts", this->accountListModel->rowCount());
    for (int i = 0; i < this->accountListModel->rowCount(); ++i) {
        this->settings->setArrayIndex(i);
        AccountEntry* entry = static_cast<AccountEntry*>(this->accountListModel->index(i).internalPointer());
        entry->writeToSettings(this->settings);
    }
    this->settings->endArray();
    this->settings->sync();
    delete ui;
    delete accountListModel;
    delete settings;
}

void MainWindow::openConnection()
{
    // Create dialog and its UI
    QDialog* dialog = new QDialog(this);
    this->accountListUi = new Ui::AccountList;
    this->accountListUi->setupUi(dialog);
    // Bind UI to account listing
    this->accountListUi->accounts->setModel(this->accountListModel);
    dialog->show();
    // Button bindings
    this->connect(this->accountListUi->add, SIGNAL(clicked()), SLOT(addAccount()));
    this->connect(this->accountListUi->edit, SIGNAL(clicked()), SLOT(editAccount()));
    this->connect(this->accountListUi->remove, SIGNAL(clicked()), SLOT(removeAccount()));
    this->connect(this->accountListUi->ok, SIGNAL(clicked()), SLOT(newTab()));
    QObject::connect(this->accountListUi->cancel, SIGNAL(clicked()), dialog, SLOT(close()));
}

QModelIndex MainWindow::currentSelection()
{
    QModelIndexList selection = this->accountListUi->accounts->selectionModel()->selectedIndexes();
    if (selection.count() > 0)
        return selection.first();
    return QModelIndex();
}

/**********************************************************************************************
 * TAB MANAGEMENT
 **********************************************************************************************/
void MainWindow::newTab()
{
    QModelIndex host = this->currentSelection();
    if (host.internalPointer() != NULL) {
        const AccountEntry* entry = static_cast<AccountEntry*>(host.internalPointer());
        QTermWidget* term = new QTermWidget(false, this);
        term->setScrollBarPosition(QTermWidget::ScrollBarRight);
        term->setShellProgram("ssh");
        QStringList args;
        args.append( ( (entry->username != "") ? (entry->username + "@") : "") + entry->host);
        if (entry->isSocksPortEnabled) {
            args.append("-D");
            args.append(QString::number(entry->socksPort));
        }
        term->setArgs(args);
        term->startShellProgram();
        // Remove when session ends
        this->connect(term, SIGNAL(finished()), SLOT(removeTab()));
        // Add to deck
        OpenTab* tab = this->ui->tabWidget->newTab(term);
        tab->setText(entry->displayName);
    }
}

void MainWindow::removeTab()
{
    QWidget* sender = (QWidget*)QObject::sender();
    this->ui->tabWidget->closeTab(this->ui->tabWidget->findTabByWidget(sender));
}

/**********************************************************************************************
 * ADDING A NEW ACCOUNT TO THE LIST
 **********************************************************************************************/
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

/**********************************************************************************************
 * EDITING AN EXISTING ACCOUNT
 **********************************************************************************************/
void MainWindow::editAccount()
{
    QModelIndex index = this->currentSelection();
    if (index.internalPointer() != NULL) {
        AccountEntry* entry = static_cast<AccountEntry*>(index.internalPointer());
        this->accountWindow = new Account(entry, this);
        this->connect(this->accountWindow, SIGNAL(accepted(AccountEntry*)), SLOT(editAccount(AccountEntry*)));
        this->accountWindow->show();
    }
}

void MainWindow::editAccount(AccountEntry* entry)
{
    this->accountWindow->close();
    this->accountListModel->update(this->currentSelection().row(), entry);
}

/**********************************************************************************************
 * DELETING AN ACCOUNT FROM THE LIST
 **********************************************************************************************/
void MainWindow::removeAccount()
{
    this->accountListModel->removeRow(this->currentSelection().row());
}
