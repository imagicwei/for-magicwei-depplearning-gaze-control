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

	//�إ� socket
	SOCKET sListen; //listening for an incoming connection
	SOCKET sConnect; //operating if a connection was found

	//���ݳs�u
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

//extern�i�H�n���ܼƷ|�b�䥦����m�Q�w�q�A�o�Ӧ�m�i��O�b�P�@����󤧤��A�άO�b�䥦��󤧤�
extern socketPair *cntPair;


#endif