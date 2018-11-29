#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <vector>
#include "../mqttHandler.h"
#include "communcationthread.h"
using namespace std;

namespace Ui {
class MainWindow;

}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init(string topic,string address,string clientid);
private:

    Ui::MainWindow *ui;
    int mapRow = 12;
    int mapCol = 12;
    int id;
    QPoint location;
    mqttPublisher *sender;
    communucationThread *thread;
protected:
    void paintEvent(QPaintEvent *e);
private slots:
    void updatethisUi(int,int);
    void on_UpBut_clicked();
    void on_LeftBut_clicked();
    void on_RightBut_clicked();
    void on_DownBut_clicked();
};

#endif // MAINWINDOW_H
