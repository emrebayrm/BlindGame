//
// Created by patates on 7/18/18.
//

#include "mqttHandler.h"
#include <string>

#include <iostream>

using namespace std;

int main(){
    
    mqttPublisher *pub = new mqttPublisher("topic", "192.168.2.236", "124123");
    pub->init();
    pub->publish("asdkasdoa");
    
    mqttSubscriber *sub = new mqttSubscriber("topic", "192.168.2.236", "1324312");
    sub->init();
    char buf[10];
    sub->receive(buf);
    
    cout << buf << endl;

}
