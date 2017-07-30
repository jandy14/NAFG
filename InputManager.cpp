#include <stdio.h>
#include "InputManager.h"
#include "GameManager.h"
#include "Player.h"
void InputManager::Initailize()
{
	FILE* f;
	fopen_s(&f, "input.txt", "rt");
	for (int i = 0; i < 8; ++i)
	{
		fscanf_s(f, "%u", keyValue[i]);
	}
	fclose(f);

	gm = GameManager::GetInstance();
}

void InputManager::KeyEvent(unsigned int pValue, bool pIsKeyDown)
{
	if (pValue == keyValue[0])
	{
		//��
		//�÷��̾� ���� ����
		gm->GetPlayer()->SetDir(pIsKeyDown, DIRECTION::UP);
		
	}
	else if (pValue == keyValue[1])
	{
		//��
		//�÷��̾� ���� ����
		gm->GetPlayer()->SetDir(pIsKeyDown, DIRECTION::DOWN);
	}
	else if (pValue == keyValue[2])
	{
		//��
		//�÷��̾� ���� ����
		gm->GetPlayer()->SetDir(pIsKeyDown, DIRECTION::LEFT);
	}
	else if (pValue == keyValue[3])
	{
		//��
		//�÷��̾� ���� ����
		gm->GetPlayer()->SetDir(pIsKeyDown, DIRECTION::RIGHT);
	}
	else if (pValue == keyValue[4])
	{
		//Į
		//�̺�Ʈ ����
		if(pIsKeyDown)
			gm->LocalToEventManager(11, gm->GetPlayer());
	}
	else if (pValue == keyValue[5])
	{
		//��
		//�̺�Ʈ ����
		if (pIsKeyDown)
			gm->LocalToEventManager(12, gm->GetPlayer());
	}
	else if (pValue == keyValue[6])
	{
		//��
		//�̺�Ʈ ����
		if (pIsKeyDown)
			gm->LocalToEventManager(13, gm->GetPlayer());
	}
	else if (pValue == keyValue[7])
	{
		//��
		//�÷��̾� ���� ����
		if (pIsKeyDown)
			gm->GetPlayer()->Dash();
	}
}