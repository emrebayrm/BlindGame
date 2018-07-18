//
// Created by patates on 7/18/18.
//

#include "../mqttHandler.h"
#include <string>
#include <unistd.h>
#include <iostream>

using namespace std;

int main(){
    string topicName = "topic";
    string address = "tcp://localhost:1883";
    string clientId = "Client1";

    mqttPublisher *pub = new mqttPublisher(topicName,address,clientId);
    pub->init();
    while(1){
        pub->publish("asdkasdoa");
        cout << "publised" << endl;
        sleep(1);
    }
    
    
}
