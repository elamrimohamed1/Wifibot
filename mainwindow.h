#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myrobot.h"
#include <qnetworkaccessmanager.h>
#include <qprogressbar.h>
#include <QLCDNumber>
#include <qpushbutton.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateBattery(quint8 battery);
    void updateIRSensor(quint8 lFront, quint8 rFront, quint8 back);


private slots:
    void on_btnSeDeconnecter_clicked();

    void on_btnSeConnecter_clicked();

    void on_stop_clicked();

    void on_droite_pressed();

    void on_devant_pressed();

    void on_gauche_pressed();

    void on_derriere_pressed();

    void updateWindows(const QByteArray);

    void on_horizontalSlider_valueChanged(int value);

    void on_MaxSpeed_clicked(bool checked);

    void on_top_pressed();

    void on_left_pressed();

    void on_buttom_pressed();

    void on_right_pressed();

    void keyPressEvent(QKeyEvent *e);

private:
    Ui ::MainWindow *ui;
    MyRobot robot;
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    bool connected;
    int speed;
    int MaxSpeed;
    QLCDNumber *lcdBattery;
    QPushButton *lFrontSensor;
    QPushButton *rFrontSensor;
    QPushButton *backSensor;

    static void updateSensorDisplay(QPushButton *button, quint8 value);


};
#endif // MAINWINDOW_H
