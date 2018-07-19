#ifndef COMMUNCATIONTHREAD_H
#define COMMUNCATIONTHREAD_H

#include <QtCore>
#include <QThread>
#include "../mqttHandler.h"
#include <string>

using namespace std;

class communucationThread : public QThread
{
    Q_OBJECT
public:
    explicit communucationThread(QObject* parent=0);
    void run();
    void setMqttOptions(string _topic, string _address, string _clientid){
        topic = _topic;
        address = _address;
        clientid = _clientid;
    }
    void init();
private:
    string topic;
    string address;
    string clientid;
    int myId;
    mqttSubscriber *collecter;

signals:
    void updateUi(int row,int col);
public slots:
};

#endif // COMMUNCATIONTHREAD_H
