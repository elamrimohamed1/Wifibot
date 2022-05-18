#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myrobot.h"
#include "myrobot.cpp"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnSeConnecter_clicked()
{
    robot.doConnect();

}


void MainWindow::on_btnSeDeconnecter_clicked()
{
    robot.disConnect();
}




