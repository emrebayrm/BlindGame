//
// Created by patates on 7/18/18.
//

#include "mqttHandler.h"
#include <string>

#include <iostream>

using namespace std;

int main(){
    
    
    mqttSubscriber *sub = new mqttSubscriber("topic", "127.0.0.1", "2");
    
    int sub_i=sub->init();
    while(1){
        sub->dis();
       // cin >> sub_i;
    }

}
