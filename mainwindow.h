#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QWebEngineView>
#include <QKeyEvent>
#include "myrobot.h"
#include <QtGamepad>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE


class MainWindow : public QDialog
{
    Q_OBJECT

public :
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots :


    //Connexion
    void connexion();

    //Collision
       void maj_collision();


    //Lancement du mouvement
    void avancer();
    void gauche();
    void droite();
    void reculer();
    void stop();
    void hgauche();
    void bgauche();
    void hdroite();
    void bdroite();
    void odometrie_g();
    void odometrie_d();

    //batterie
    void maj_batterie(QByteArray data);
    void update();

    //Clavier
    void keyPressEvent(QKeyEvent* key_robot);
    void keyReleaseEvent(QKeyEvent* key_robot);
     void move_xbox();

    //DonnÃ©es du robot

    void on_slide_vitesse_valueChanged(int value);


    //Boutons connexion et mouvement


    void on_Gauche_pressed();
    void on_avancer_pressed();
    void on_droite_pressed();
    void on_reculer_pressed();
    void on_hgauche_pressed();
    void on_hdroite_pressed();
    void on_bgauche_pressed();
    void on_bdroite_pressed();
    void on_connexion_clicked();
    void on_avancer_released();
    void on_hdroite_released();
    void on_droite_released();
    void on_bdroite_released();
    void on_reculer_released();
    void on_bgauche_released();
    void on_Gauche_released();
    void on_hgauche_released();

    //Mouvements cameras
    void on_haut_camera_pressed();
    void on_gauche_camera_pressed();
    void on_droite_camera_pressed();
    void on_bas_camera_pressed();

    void cam_haut();
    void cam_bas();
    void cam_gauche();
    void cam_droite();
    void cam_filtre(int valeur);
    void cam_reset();



private:

    //Affichage camera
    QWebEngineView *view;
    //infrarouge
    QTimer *TimerReceiveIR;
    //odo
    //QTimer *TimerReceiveOD;
    //Mouvement camera
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    
    //Robot
    MyRobot* robot;

    //Manette
       QGamepad* xbox;


    Ui::Dialog *ui;
    void display_irArD();
    void display_irAvD();
    void display_irArG();
    void display_irAvG();

};
#endif // MAINWINDOW_H
