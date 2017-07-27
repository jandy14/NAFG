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

	unsigned WINAPI ConnectFunc(void * arg); //�ʱ�ȭ�߿� ���ῡ ���� ������ �Լ�
	unsigned WINAPI ReceiveFunc(void * arg); //�ʱ�ȭ�� �Ŀ� ���� �޾ƿ��� ������ �Լ�
public:
	void Initailize(bool isHost, char* ipAdress = "");
	void SendEvent(Event* evt);
};