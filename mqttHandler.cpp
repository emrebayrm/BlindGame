//
// Created by patates on 7/18/18.
//

#include <MQTTClient.h>
#include <cstring>
#include "mqttHandler.h"
#include <iostream>

mqttPublisher::mqttPublisher(const string &_topic, const string &_address, const string & _clientId) :
        mqttHandler(_topic, _address, _clientId) {}

int mqttPublisher::init() {

    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    int rc = 0;

    MQTTClient_create(&(this->mqttClient), this->getAddress().c_str(), this->getClientId().c_str(),
                      MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    if ((rc = MQTTClient_connect(this->mqttClient, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        rc = -1;
    }


    return rc;
}

int mqttPublisher::publish(string message) {
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    int rc;

    pubmsg.payload = (void *) message.c_str();
    pubmsg.payloadlen = message.size();
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    MQTTClient_publishMessage(this->mqttClient, getTopic().c_str(), &pubmsg, &token);

    rc = MQTTClient_waitForCompletion(this->mqttClient, token, TIMEOUT);

    return rc;
}

mqttSubscriber::mqttSubscriber(const string &_topic, const string &_address, const string & _clientId) :
        mqttHandler(_topic, _address, _clientId) {}

int mqttSubscriber::init() {
    broker = mqtt_connect(getClientId().c_str(), getAddress().c_str(), 1883);
    int result = mqtt_subscribe(broker, getTopic().c_str(), QoS1);
    
    if(result != 1) {
        puts("failed to Subscribe");
        exit(1);
    }
    void mqtt_display_message(mqtt_broker_handle_t *broker, int (*print)(int));
    mqtt_display_message(broker,&this->receive);
    return result;
}

int mqttSubscriber::receive(int message) {
  putchar(message);
   return 1;
}
