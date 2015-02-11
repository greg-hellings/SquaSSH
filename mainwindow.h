#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class TermWidget;
class QLabel;

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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
