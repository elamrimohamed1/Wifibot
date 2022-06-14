#ifndef MYROBOT_H
#define MYROBOT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QTimer>
#include <QMutex>

class MyRobot : public QObject {
    Q_OBJECT
public:
    explicit MyRobot(QObject *parent = 0);
    void doConnect();
    void disConnect();
    void update(short gspeed, short dspeed, float godometry, float dodometry);
    QByteArray DataToSend;
    QByteArray DataReceived;
    QMutex Mutex;

signals:
    void updateUI(const QByteArray Data);
public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void MyTimerSlot();
    short Crc16(QByteArray Adresse_tab,unsigned int Taille_max);
    void velocityRight(quint8 value);
    void velocityLeft(quint8 value);
    void move(unsigned char dir, unsigned char rVelocity, unsigned char lVelocity);


private:
    QTcpSocket *socket;
    QTimer *TimerEnvoi;
    quint16 crc16(unsigned int pos);
};

#endif // MYROBOT_H
