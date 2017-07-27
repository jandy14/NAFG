#pragma once
#include <WinSock2.h>

#define WINAPI __stdcall
class Event;

class NetworkManager
{
private:
	GameManager* gm;
	char ipAdress[16];
	bool isHost;
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAddr, clntAddr;
	int szClntAddr;

	unsigned WINAPI ConnectFunc(void * arg); //초기화중에 연결에 쓰일 쓰레드 함수
	unsigned WINAPI ReceiveFunc(void * arg); //초기화한 후에 값을 받아오는 쓰레드 함수
public:
	void Initailize(bool isHost, char* ipAdress = "");
	void SendEvent(Event* evt);
};