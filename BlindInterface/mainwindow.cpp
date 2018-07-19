#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    printf("asd");
    thread = new communucationThread(this);
    printf("asd");

    connect(thread,SIGNAL(updateUi(int,int)),this,SLOT(updatethisUi(int,int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::init(string topic,string address,string clientid){
    sender = new mqttPublisher(topic,address,clientid);

    thread->setMqttOptions(topic,address,clientid);
    thread->init();

    thread->run();
    sender->init();

}

void MainWindow::updatethisUi(int x,int y){
    location.setX(x);
    location.setY(y);
    repaint();
}

void MainWindow::paintEvent(QPaintEvent *e) {
    QPainter painter(this);
    int margin = 50;

    QPen paintpen(Qt::black);
    paintpen.setWidth(2);
    painter.setPen(paintpen);

    int recLen = 40;
    for(int i = 0; i < mapRow; ++i) {
        for(int j = 0; j < mapCol; ++j) {
            painter.drawRect(margin + i*recLen, margin + j*recLen, recLen,recLen);
        }
    }



}

void MainWindow::on_UpBut_clicked()
{
    string message;
    message.append(to_string(id));
    message.append(",");
    message.append("0");
    sender->publish(message);
}

void MainWindow::on_LeftBut_clicked()
{
    string message;
    message.append(to_string(id));
    message.append(",");
    message.append("3");
    sender->publish(message);
}

void MainWindow::on_RightBut_clicked()
{
    string message;
    message.append(to_string(id));
    message.append(",");
    message.append("1");
    sender->publish(message);
}

void MainWindow::on_DownBut_clicked()
{
    string message;
    message.append(to_string(id));
    message.append(",");
    message.append("2");
    sender->publish(message);
}
