#include <stdio.h>
#include "InputManager.h"
#include "GameManager.h"

void InputManager::Initailize()
{
	FILE* f;
	fopen_s(&f, "input.txt", "rt");
	for (int i = 0; i < 8; ++i)
	{
		fscanf_s(f, "%u", keyValue[i]);
	}
	fclose(f);
}

void InputManager::KeyEvent(unsigned int pValue)
{
	if (pValue == keyValue[0])
	{
		//상
		//플레이어 상태 조절
	}
	else if (pValue == keyValue[1])
	{
		//하
		//플레이어 상태 조절
	}
	else if (pValue == keyValue[2])
	{
		//좌
		//플레이어 상태 조절
	}
	else if (pValue == keyValue[3])
	{
		//우
		//플레이어 상태 조절
	}
	else if (pValue == keyValue[4])
	{
		//칼
		//로컬이벤트 생성
		//이벤트 전송
	}
	else if (pValue == keyValue[5])
	{
		//총
		//로컬이벤트 생성
		//이벤트 전송
	}
	else if (pValue == keyValue[6])
	{
		//포
		//로컬이벤트 생성
		//이벤트 전송
	}
	else if (pValue == keyValue[7])
	{
		//뜀
		//플레이어 상태 조절
	}
}