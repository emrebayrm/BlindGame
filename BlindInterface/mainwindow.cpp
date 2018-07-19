#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
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
