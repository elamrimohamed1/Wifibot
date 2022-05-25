#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myrobot.h"

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

short Crc16(QByteArray Adresse_tab , unsigned char Taille_max)
{
    unsigned int Crc = 0xFFFF;
    unsigned int Polynome = 0xA001;
    unsigned int CptOctet = 0;
    unsigned int CptBit = 0;
    unsigned int Parity= 0;
    Crc = 0xFFFF;
    Polynome = 0xA001;
    for ( CptOctet= 1 ; CptOctet < Taille_max ; CptOctet++)
    {
        Crc ^= Adresse_tab[CptOctet] ;
        for ( CptBit = 0; CptBit <= 7 ; CptBit++)
        {
            Parity= Crc;
            Crc >>= 1;
            if (Parity%2 == true) Crc ^= Polynome;
        }
    }
    return(Crc);
}

void MainWindow::on_stop_clicked()
{
    robot.DataToSend[0] = 0xFF;
    robot.DataToSend[1] = 0x07;
    robot.DataToSend[2] = 0x0;
    robot.DataToSend[3] = 0x0;
    robot.DataToSend[4] = 0x0;
    robot.DataToSend[5] = 0x0;
    robot.DataToSend[6] = 0x0;
    robot.DataToSend[7] = 0x0;
    robot.DataToSend[8] = 0x0;
}


void MainWindow::on_droite_pressed()
{
    robot.DataToSend[0] = 0xFF;
    robot.DataToSend[1] = 0x07;
    robot.DataToSend[2] = 120;
    robot.DataToSend[4] = 60;
    robot.DataToSend[6] = 80;
    short Crc=Crc16(robot.DataToSend,7);
    robot.DataToSend[7] = char(Crc);
    robot.DataToSend[8] = char(Crc>>8);
}


void MainWindow::on_devant_pressed()
{
    robot.DataToSend[0] = 0xFF;
    robot.DataToSend[1] = 0x07;
    robot.DataToSend[2] = 120;
    robot.DataToSend[4] = 120;
    robot.DataToSend[6] = 80;
    short Crc=Crc16(robot.DataToSend,7);
    robot.DataToSend[7] = char(Crc);
    robot.DataToSend[8] = char(Crc>>8);
}


void MainWindow::on_gauche_pressed()
{
    robot.DataToSend[0] = 0xFF;
    robot.DataToSend[1] = 0x07;
    robot.DataToSend[2] = 60;
    robot.DataToSend[4] = 120;
    robot.DataToSend[6] = 80;
    short Crc=Crc16(robot.DataToSend,7);
    robot.DataToSend[7] = char(Crc);
    robot.DataToSend[8] = char(Crc>>8);
}


void MainWindow::on_derriere_pressed()
{
    robot.DataToSend[0] = 0xFF;
    robot.DataToSend[1] = 0x07;
    robot.DataToSend[2] = 120;
    robot.DataToSend[4] = 120;
    robot.DataToSend[6] = 0;
    short Crc=Crc16(robot.DataToSend,7);
    robot.DataToSend[7] = char(Crc);
    robot.DataToSend[8] = char(Crc>>8);
}

