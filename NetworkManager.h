#pragma once
#include <WinSock2.h>

class GameManager;
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

	void ConnectFunc(); //�ʱ�ȭ�߿� ���ῡ ���� ������ �Լ�
	void ReceiveFunc(); //�ʱ�ȭ�� �Ŀ� ���� �޾ƿ��� ������ �Լ�
public:
	void Initailize(bool isHost, char* ipAdress = "");
	void SendEvent(Event* evt);

	void StartThread(); //������ ���� �Լ�
	~NetworkManager();
};