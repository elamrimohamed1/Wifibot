#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myrobot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnSeDeconnecter_clicked();

    void on_btnSeConnecter_clicked();

private:
    Ui::MainWindow *ui;
    MyRobot robot;

};
#endif // MAINWINDOW_H
