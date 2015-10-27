#include "stdafx.h"

socketPair *cntPair = new socketPair();


void socketPair::initialServer()
{
	DLLVSERION = MAKEWORD(2,1);//Winsocket-DLL 版本

	//用 WSAStartup 開始 Winsocket-DLL
	r = WSAStartup(DLLVSERION, &wsaData);
	if ( r != NO_ERROR) {
		printf("WSAStartup failed with error: %d\n", r );
	}

	//宣告 socket 位址資訊(不同的通訊,有不同的位址資訊,所以會有不同的資料結構存放這些位址資訊)
	addrlen = sizeof(addr);

	//AF_INET：表示建立的 socket 屬於 internet family
	//SOCK_STREAM：表示建立的 socket 是 connection-oriented socket
	sConnect = socket(AF_INET, SOCK_STREAM, NULL);
	if ( sConnect == INVALID_SOCKET) {
		printf("socket failed with error: %d\n", WSAGetLastError());
		WSACleanup();
	}

	//設定位址資訊的資料
	//addr.sin_addr.s_addr = inet_addr("192.168.1.100");
	addr.sin_addr.s_addr = inet_addr(serverIP);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);


	//設定 Listen
	sListen = socket(AF_INET, SOCK_STREAM, NULL);
	if( bind(sListen, (SOCKADDR*)&addr, sizeof(addr)) )
	{
		printf("bind failed with error: %d\n", WSAGetLastError());
		closesocket( sListen );
		WSACleanup();
	}

	if( listen(sListen, SOMAXCONN) ) //SOMAXCONN: listening without any limit
	{
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket( sListen );
		WSACleanup();
	}

}

void socketPair::runServer()
{

	sConnect = accept(sListen, (SOCKADDR*)&clinetAddr, &addrlen);

	while(1)
	{

		try
		{
			if ( sConnect == INVALID_SOCKET) {
				isConnected = false;
				newMsg = false;
				printf("accept failed with error: %d\n", WSAGetLastError());
				throw sConnect;		// throw exception
			}

			else
			{
				isConnected = true;

				//接收 server 端的訊息
				ZeroMemory(message, 200 );
				r = recv(sConnect, message, sizeof(message), 0);

				if ( r > 0 )
				{		
					newMsg = true;
					strcpy(messageSave,message);
					//printf("%s \n",message );

				}
				else if ( r == 0 )
				{
					printf("Client Closed\n");
					throw r;	// throw exception
				}
				else
				{
					printf("recv failed: %d\n", WSAGetLastError());
					throw r;	// throw exception
				}
			}

		}

		catch ( ... )
		{

			isConnected = false;
			newMsg = false;

			//關閉 socket
			int closeSocketState = closesocket(sConnect);
			if (closeSocketState == SOCKET_ERROR)
				printf("closesocket function \" for server-Connect \" failed with error: %d\n", WSAGetLastError());
			WSACleanup();

			//重新初始化
			this->initialServer();
			sConnect = accept(sListen, (SOCKADDR*)&clinetAddr, &addrlen);
		}


	}




}


void socketPair::initialClient()
{
	//開始 Winsock-DLL
	DLLVersion = MAKEWORD(2,1);
	r = WSAStartup(DLLVersion, &wsaData);
	if ( r != NO_ERROR) {
		printf("WSAStartup failed with error: %d\n", r );
	}

	//宣告 socket 位址資訊(不同的通訊,有不同的位址資訊,所以會有不同的資料結構存放這些位址資訊)
	addlen = sizeof(addr);

	//AF_INET：表示建立的 socket 屬於 internet family
	//SOCK_STREAM：表示建立的 socket 是 connection-oriented socket
	sConnect = socket(AF_INET, SOCK_STREAM, NULL);
	if ( sConnect == INVALID_SOCKET) {
		printf("socket failed with error: %d\n", WSAGetLastError());
		WSACleanup();
	}

	//設定位址資訊的資料
	addr.sin_addr.s_addr = inet_addr(serverIP);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

}

void socketPair::runClient()
{

	int estConnectState = connect(sConnect, (SOCKADDR*)&addr, sizeof(addr));

	while(1)
	{

		try
		{

			if ( estConnectState == SOCKET_ERROR ) {
				printf("connect function failed with error: %d\n", WSAGetLastError());
				throw estConnectState;	//throw exception
			}

			else
			{
				isConnected = true;

				//接收 server 端的訊息
				ZeroMemory(message, 200);
				r = recv(sConnect, message, sizeof(message), 0);

				if ( r > 0 )
				{		
					newMsg = true;
					strcpy(messageSave,message);
					//printf("%s \n",message );

				}
				else if ( r == 0 )
				{
					printf("Client Closed\n");
					throw r;	// throw exception
				}
				else
				{
					printf("recv failed: %d\n", WSAGetLastError());
					throw r;	// throw exception
				}
			}

		}

		catch (...)
		{
			isConnected = false;
			newMsg = false;

			//關閉 socket
			int closeSocketState = closesocket(sConnect);
			if (closeSocketState == SOCKET_ERROR)
				printf("closesocket function failed \" for client-Connect \" with error: %d\n", WSAGetLastError());
			WSACleanup();

			//重新初始化
			this->initialClient();
			estConnectState = connect(sConnect, (SOCKADDR*)&addr, sizeof(addr));
		}

	}



}

void socketPair::closeSocket()
{
	newMsg = false;
	isConnected = false;

	//關閉 socket

	if ( sConnect != INVALID_SOCKET)
	{
		int closeSocketState = closesocket(sConnect);
		if (closeSocketState == SOCKET_ERROR)
			printf("closesocket function \" for close-Connect \" failed with error: %d\n", WSAGetLastError());
		//WSACleanup();
	}

	if ( sListen != INVALID_SOCKET)
	{
		int closeSocketState = closesocket(sConnect);
		if (closeSocketState == SOCKET_ERROR)
			printf("closesocket function \" for close-Listen \" failed with error: %d\n", WSAGetLastError());
		//WSACleanup();
	}


	// 	if(sConnect)
	// 		closesocket(sConnect);
	// 	if (sListen)
	// 		closesocket(sListen);

	WSACleanup();
}