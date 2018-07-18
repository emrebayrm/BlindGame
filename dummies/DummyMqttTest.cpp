//
// Created by patates on 7/18/18.
//

#include "mqttHandler.h"
#include <string>

#include <iostream>

using namespace std;

int main(){
    
    mqttPublisher *pub = new mqttPublisher("topic", "127.0.0.1", "1");
    pub->init();
    pub->publish("asdkasdoa");
    
    mqttSubscriber *sub = new mqttSubscriber("topic", "127.0.0.1", "2");
    
    int sub_i=sub->init();
    //cout << sub_i << endl;
    void *buf;
    buf=malloc(sizeof(10));
    cout << "buf" << endl;
    //sub->receive(buf);
    cout << "1234" << endl;
    //cout << buf << endl;
    int a;
    cin >> a;
    
}
