//
// Created by patates on 7/18/18.
//

#include "../mqttHandler.h"
#include <string>

#include <iostream>

using namespace std;

int main(){
    string topicName = "topic";
    string address = "tcp://localhost:1883";
    string clientId = "Client2";
    mqttSubscriber *sub = new mqttSubscriber(topicName, address,clientId);

    int sub_i;
    sub_i=sub->init();
    char *buffer;
    buffer = static_cast<char *>(calloc(sizeof(char), 20));
    while(1){
        sub->receive(buffer);
        cout << buffer << endl;
    }

}
