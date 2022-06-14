#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myrobot.h"

#include <QWebEngineView>
#include <QUrl>
#include <QNetworkReply>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , robot(parent)
    , connected(false)
    , speed(120)
    , MaxSpeed(0)


{
    ui->setupUi(this);
    QWebEngineView *page = ui->Camera;
    page->load(QUrl("http://192.168.1.106:8080/?action=stream"));
    page->show();
    connect(&robot, SIGNAL(updateUI(const QByteArray)), this, SLOT(updateWindows(const QByteArray)));


    manager = new QNetworkAccessManager();
        QObject::connect(manager, &QNetworkAccessManager::finished,
              this, [=](QNetworkReply *reply) {
                  if (reply->error()) {
                      qDebug() << reply->errorString();
                      return;
                  }
                  QString answer = reply->readAll();

                  qDebug() << answer;
        });

        connect(&robot, &MyRobot::updateUI, this, &MainWindow::updateWindows);

    lcdBattery = new QLCDNumber(this);
    lcdBattery->setDigitCount(3);
    lcdBattery->display(0);


}

MainWindow::~MainWindow()
{
    if (connected) {
            robot.disconnect();
    }

    delete ui;
    delete manager;
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


void MainWindow::on_top_pressed()
{
    request.setUrl(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=-200"));
            manager->get(request);

}


void MainWindow::on_left_pressed()
{
    request.setUrl(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=200"));
                manager->get(request);

}


void MainWindow::on_buttom_pressed()
{
    request.setUrl(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=200"));
            manager->get(request);

}


void MainWindow::on_right_pressed()
{
    request.setUrl(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=-200"));
               manager->get(request);

}



void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    speed=value;
}


void MainWindow::on_MaxSpeed_clicked(bool checked)
{
    {
        if(checked==true){
            MaxSpeed=1;
        }
        else{
            MaxSpeed=0;
        }
    }
}

void MainWindow::updateBattery(quint8 battery)
{
    if(battery > 175)
    {
        lcdBattery->display(100);
        lcdBattery->setStyleSheet("background-color: dark; color: rgb(0, 255, 0); border-radius: 10px;border-width: 2px");
    }
    else if(battery >100)
    {
        lcdBattery->display(100);
        lcdBattery->setStyleSheet("background-color: dark; color: rgb(255, 0, 0); border-radius: 10px;border-width: 2px");
    }
    else
    {
        lcdBattery->setStyleSheet("background-color: dark; color: rgb(255, 0, 0); border-radius: 10px;border-width: 2px");
        lcdBattery->display(battery);
    }

}

void MainWindow::updateWindows(const QByteArray data)
{
    this->updateBattery(data[2]);
}

void MainWindow::keyPressEvent(QKeyEvent *e){
    if(e->key() == Qt::Key_Z) { //si la touche "Z" est enfoncée alors on fait appel à la fonction pour faire avancer le robot avec les boutons
        this->on_devant_pressed();
    }

    else if(e->key() == Qt::Key_D) {//si la touche "D" est enfoncée alors on fait appel à la fonction pour faire tourner le robot à droite avec les boutons
        this->on_droite_pressed();
    }

    else if(e->key() == Qt::Key_S) {//si la touche "S" est enfoncée alors on fait appel à la fonction pour faire reculer le robot avec les boutons
        this->on_derriere_pressed();
    }

    else if(e->key() == Qt::Key_Q) {//si la touche "Q" est enfoncée alors on fait appel à la fonction pour faire tourner à gauche le robot avec les boutons
        this->on_gauche_pressed();
    }

    else if(e->key() == Qt::Key_Space) {//si la barre epace est enfoncée alors on fait appel à la fonction pour arrêter le robot avec les boutons
        this->on_stop_clicked();
    }
}
