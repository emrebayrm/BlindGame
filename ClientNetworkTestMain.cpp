#include <iostream>
#include "NetworkModule.h"
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#define PAYLOAD_MAX 200
using namespace std;
main(){
	ClientNetworkModule network;
	Command *cmd_recv;
	Command *cmd_send;
	int sent_data_size,recv_data_size;
	cmd_send =(Command *) malloc(PAYLOAD_MAX);
	cmd_recv =(Command *) malloc(PAYLOAD_MAX);
	memset(cmd_send, 0 ,PAYLOAD_MAX);
	memset(cmd_recv, 0 ,PAYLOAD_MAX);
	cmd_send->commandType = JOIN ;
	memcpy(cmd_send->context, "Oguz" ,5);
	cmd_send->length=sizeof(Command)+5;
	network.init(5000);
	sent_data_size=network.sendData(cmd_send,cmd_send->length);
	recv_data_size=network.recvData(cmd_recv,PAYLOAD_MAX);
	cout << cmd_recv->context << endl ;
}