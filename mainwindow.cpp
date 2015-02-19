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
    int size = this->settings->beginReadArray("accounts");
    for (int i = 0; i < size; ++i) {
        this->settings->setArrayIndex(i);
        AccountEntry* entry = new AccountEntry(settings);
        this->accountListModel->append(entry);
    }
    this->settings->endArray();
    // Set models
    this->ui->quickSelect->setModel(this->accountListModel);
    // Listeners
    this->connect(this->ui->openConnection, SIGNAL(clicked()), SLOT(openConnection()));
    this->connect(this->ui->quickOpen, SIGNAL(clicked()), SLOT(quickOpen()));
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
    this->accountListDialog = new QDialog(this);
    this->accountListUi = new Ui::AccountList;
    this->accountListUi->setupUi(this->accountListDialog);
    // Bind UI to account listing
    this->accountListUi->accounts->setModel(this->accountListModel);
    this->accountListDialog->show();
    // Button bindings
    this->connect(this->accountListUi->add, SIGNAL(clicked()), SLOT(addAccount()));
    this->connect(this->accountListUi->edit, SIGNAL(clicked()), SLOT(editAccount()));
    this->connect(this->accountListUi->remove, SIGNAL(clicked()), SLOT(removeAccount()));
    this->connect(this->accountListUi->ok, SIGNAL(clicked()), SLOT(newTab()));
    QObject::connect(this->accountListUi->cancel, SIGNAL(clicked()), this->accountListDialog, SLOT(close()));
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
    QModelIndexList selection = this->accountListUi->accounts->selectionModel()->selectedIndexes();
    for (int i = 0; i < selection.count(); ++i) {
        QModelIndex host = selection.at(i);
        if (host.internalPointer() != NULL) {
            const AccountEntry* entry = static_cast<AccountEntry*>(host.internalPointer());
            this->createTab(entry);
        }
    }
    this->accountListDialog->close();
}

void MainWindow::quickOpen()
{
    QModelIndex selected = this->accountListModel->index(this->ui->quickSelect->currentIndex());
    const AccountEntry* entry = static_cast<AccountEntry*>(selected.internalPointer());
    this->createTab(entry);
}

void MainWindow::createTab(const AccountEntry *entry)
{
    QTermWidget* term = new QTermWidget(false, this);
    term->setScrollBarPosition(QTermWidget::ScrollBarRight);
    term->setShellProgram("ssh");
    QStringList args;
    QStringList env;
    env.append("TERM=xterm-256color");
    args.append( ( (entry->username != "") ? (entry->username + "@") : "") + entry->host);
    if (entry->isSocksPortEnabled) {
        args.append("-D");
        args.append(QString::number(entry->socksPort));
    }
    // Still needs additional options
//    if (entry->isLocalPortEnabled) {
//        args.append("-L");
//        args.append(QString::number(entry->localPort));
//    }
//    if (entry->isRemotePortEnabled) {
//        args.append("-R");
//        args.append(QString::number(entry->remotePort));
//    }
    if (entry->isXForwardingEnabled) {
        args.append("-X");
    }
    if (entry->isCompressionEnabled) {
        args.append("-C");
    }
    term->setArgs(args);
    term->setEnvironment(env);
    term->startShellProgram();
    // Remove when session ends
    this->connect(term, SIGNAL(finished()), SLOT(removeTab()));
    // Add to deck
    OpenTab* tab = this->ui->tabWidget->newTab(term);
    tab->setText(entry->displayName);
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
