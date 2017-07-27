#include <string.h>
#include "GameManager.h"
#include "NetworkManager.h"
#include "EventManager.h"
#include "Event.h"

void NetworkManager::Initailize(bool pIsHost, char* pIPAdress = "")
{
	gm = GameManager::GetInstance();
	isHost = pIsHost;
	strcpy(ipAdress, pIPAdress);

	if (isHost)
	{
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		{ /* 오류 */ }
		hServSock = socket(PF_INET, SOCK_STREAM, 0);
		if (hServSock == INVALID_SOCKET)
		{ /* 오류 */ }
		memset(&servAddr, 0, sizeof(servAddr));
		servAddr.sin_family = AF_INET;
		servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
		servAddr.sin_port = htons(atoi("10001"));

		if (bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		{ /* 오류 */ }
	}
	else
	{
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		{ /* 오류 */ }
		hClntSock = socket(PF_INET, SOCK_STREAM, 0);
		if (hClntSock == INVALID_SOCKET)
		{ /* 오류 */ }
		memset(&servAddr, 0, sizeof(servAddr));
		servAddr.sin_family = AF_INET;
		servAddr.sin_addr.s_addr = inet_addr(ipAdress);
		servAddr.sin_port = htons(atoi("10001"));
	}
}
void NetworkManager::SendEvent(Event* pEvt)
{
	send(hClntSock, (char*)pEvt, sizeof(Event), 0);
}
unsigned WINAPI NetworkManager::ConnectFunc(void * arg)
{
	if (isHost)
	{
		if (listen(hServSock, 5) == SOCKET_ERROR)
		{ /* 오류 */ }
		szClntAddr = sizeof(clntAddr);
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr);
		if (hClntSock == INVALID_SOCKET)
		{ /* 오류 */ }
	}
	else
	{
		if (connect(hClntSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		{ /* 오류 */ }
	}
}
unsigned WINAPI NetworkManager::ReceiveFunc(void * arg)
{
	while (1)
	{
		Event* evt = new Event();
		recv(hClntSock, (char*)evt, sizeof(evt), 0);

		/* if recv end, delete evt and break loop */
		
		gm->ToEventManager(evt);
	}
}