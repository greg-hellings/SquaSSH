#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "rotatetabtext.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ui->tabWidget->tabBar()->setStyle(new RotateTabText());
    this->ui->tabWidget->tabBar()->setExpanding(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
