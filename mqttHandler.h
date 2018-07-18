//
// Created by patates on 7/18/18.
//

#ifndef BLINDGAME_MQTTHANDLER_H
#define BLINDGAME_MQTTHANDLER_H

#include <string>
#include <MQTTClient.h>

#define QOS         1
#define TIMEOUT     10000L

using namespace std;

class mqttHandler{
private:
    string topic;
    string address;
    string clientId;
public:
    mqttHandler(string _topic, string _address, string _clientId) {
        topic = _topic;
        address = _address;
        clientId = _clientId;
    }

    const string &getClientId() const {
        return clientId;
    }

    void setClientId(const string &clientId) {
        mqttHandler::clientId = clientId;
    }

    const string &getTopic() const {
        return topic;
    }

    void setTopic(const string &topic) {
        mqttHandler::topic = topic;
    }

    const string &getAddress() const {
        return address;
    }

    void setAddress(const string &address) {
        mqttHandler::address = address;
    }

    virtual  int init() = 0;

};

class mqttPublisher : public mqttHandler {
private:
    MQTTClient mqttClient;
public:
    mqttPublisher(const string &_topic, const string &_address , const string & _clientId);

    int init() override ;
    int publish(string message);
};

class mqttSubscriber : public mqttHandler{
private:
    MQTTClient_connectOptions conn_opts;
    MQTTClient mqttClient;
public:
    mqttSubscriber(const string &_topic, const string &_address, const string & _clientId);

    int init() override ;
    int receive(void *message);
};


#endif //BLINDGAME_MQTTHANDLER_H
