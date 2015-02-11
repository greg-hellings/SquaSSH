#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_accountlist.h"

#include "qtermwidget.h"
#include <qtreetabs.h>
#include <QLabel>

#define EMPTY_TAB_INDEX 0
#define EMPTY_TAB_COUNT 1

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
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
    QDialog* dialog = new QDialog();
    Ui::AccountList* accountList = new Ui::AccountList;
    accountList->setupUi(dialog);
    dialog->show();
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

void MainWindow::removeTab()
{
    QWidget* sender = (QWidget*)QObject::sender();
    this->ui->tabWidget->closeTab(this->ui->tabWidget->findTabByWidget(sender));
}
