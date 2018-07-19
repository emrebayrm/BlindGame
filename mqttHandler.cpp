//
// Created by patates on 7/18/18.
//

#include <MQTTClient.h>
#include <cstring>
#include "mqttHandler.h"

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
    conn_opts = MQTTClient_connectOptions_initializer;
    int rc;

    MQTTClient_create(&this->mqttClient,getAddress().c_str() , getClientId().c_str(),
                      MQTTCLIENT_PERSISTENCE_NONE, NULL);

    if ((rc = MQTTClient_connect(this->mqttClient, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        rc = -1;
    }

    if( (rc =  MQTTClient_subscribe(this->mqttClient,getTopic().c_str(),QOS)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to subscribe, return code %d\n",rc);
        rc = -1;
    }

    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    return rc;
}

int mqttSubscriber::receive(void *message) {
    MQTTClient_message *_message;
    int lenTopic,rc;
    lenTopic = 30;
    int i = 0;

    char *topic = static_cast<char *>(malloc(sizeof(char) * 30));
    sprintf(topic,"%s",getTopic().c_str());
    if ((rc = MQTTClient_receive(this->mqttClient, &topic, &lenTopic, &_message, TIMEOUT)) != MQTTCLIENT_SUCCESS) {
        perror("Failed ");
        //exit(-1);
    }

    if(_message != NULL) {
        message = _message->payload;
        return _message->payloadlen;
    }
    else{
        printf("No message Received \n");
    }

    return 0;
}
