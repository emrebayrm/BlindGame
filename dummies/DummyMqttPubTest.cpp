//
// Created by patates on 7/18/18.
//

#include "mqttHandler.h"
#include <string>
#include <unistd.h>
#include <iostream>

using namespace std;

int main(){
    
    mqttPublisher *pub = new mqttPublisher("topic", "127.0.0.1", "1");
    pub->init();
    while(1){
        pub->publish("asdkasdoa");
        sleep(1);
    }
    
    
}
