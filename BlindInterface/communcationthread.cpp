#include "communcationthread.h"

communucationThread::communucationThread(QObject *parent):QThread(parent)
{

}

void communucationThread::init(){
    collecter = new mqttSubscriber(topic,address,clientid);
    collecter->init();

}

void communucationThread::run(){
    char *buffer =NULL;
    char *temp;
    int id;
    int x;
    int y;

    while(1){
        collecter->receive(buffer);
        //parse
        printf("somthing has arrived \n");
        if(buffer != NULL){
            temp = strtok(buffer,",");
            while( temp != NULL){
                id = atoi(temp);
                temp = strtok(NULL,",");
                x = atoi(temp);
                temp = strtok(NULL,",");
                y = atoi(temp);
                if(myId = id){
                    emit(x,y);
                }
            }
        }
    }
}
