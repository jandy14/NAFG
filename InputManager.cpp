#include <stdio.h>
#include "InputManager.h"
#include "GameManager.h"
#include "Player.h"
void InputManager::Initailize()
{
	FILE* f;
	fopen_s(&f, "KeySetting.txt", "rt");
	for (int i = 0; i < 8; ++i)
	{
		fscanf_s(f, "%*s : %d\n", &keyValue[i]);
	}
	fclose(f);

	gm = GameManager::GetInstance();
}

void InputManager::KeyEvent(unsigned int pValue, bool pIsKeyDown)
{
	if (pValue == keyValue[0])
	{
		//상
		//플레이어 상태 조절
		gm->GetPlayer()->SetDir(pIsKeyDown, DIRECTION::UP);
		
	}
	else if (pValue == keyValue[1])
	{
		//하
		//플레이어 상태 조절
		gm->GetPlayer()->SetDir(pIsKeyDown, DIRECTION::DOWN);
	}
	else if (pValue == keyValue[2])
	{
		//좌
		//플레이어 상태 조절
		gm->GetPlayer()->SetDir(pIsKeyDown, DIRECTION::LEFT);
	}
	else if (pValue == keyValue[3])
	{
		//우
		//플레이어 상태 조절
		gm->GetPlayer()->SetDir(pIsKeyDown, DIRECTION::RIGHT);
	}
	else if (pValue == keyValue[4])
	{
		//칼
		//이벤트 생성
		if (pIsKeyDown)
		{
			if(gm->SpendGauge(11))
				gm->LocalToEventManager(11, gm->GetPlayer());
		}
	}
	else if (pValue == keyValue[5])
	{
		//총
		//이벤트 생성
		if (pIsKeyDown)
		{
			if (gm->SpendGauge(12))
				gm->LocalToEventManager(12, gm->GetPlayer());
		}
	}
	else if (pValue == keyValue[6])
	{
		//포
		//이벤트 생성
		if (pIsKeyDown)
		{
			if (gm->SpendGauge(13))
				gm->LocalToEventManager(13, gm->GetPlayer());
		}
	}
	else if (pValue == keyValue[7])
	{
		//뜀
		//플레이어 상태 조절
		if (pIsKeyDown)
		{
			if (gm->SpendGauge(14))
				gm->GetPlayer()->Dash();
		}
	}
}