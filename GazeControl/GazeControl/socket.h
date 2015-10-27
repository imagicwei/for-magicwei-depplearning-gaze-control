#include "stdafx.h"

#if !defined( CONNECT_H ) 
#define CONNECT_H

class socketPair
{
public:

	char *serverIP;
	char *clientIP;
	int port;
	bool isConnected;
	char *sendMsgContent;
	char *getMsgContent;
	bool newMsg;



	//Server
	int r;
	WSAData wsaData;
	WORD DLLVSERION;

	SOCKADDR_IN addr;
	int addrlen;

	//建立 socket
	SOCKET sListen; //listening for an incoming connection
	SOCKET sConnect; //operating if a connection was found

	//等待連線
	SOCKADDR_IN clinetAddr;

	/***********************************************************************************/

	//Client
	char message[200];
	char messageSave[200];
	WORD DLLVersion;
	int addlen;

	void initialServer();
	void runServer();
	void initialClient();
	void runClient();
	void closeSocket();


	socketPair()
	{
		message[0] = '\0';
		messageSave[0] = '\0';
		newMsg = false;
		isConnected = false;
	}

};

//extern可以聲明變數會在其它的位置被定義，這個位置可能是在同一份文件之中，或是在其它文件之中
extern socketPair *cntPair;


#endif