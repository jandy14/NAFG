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
		//��
		//�÷��̾� ���� ����
	}
	else if (pValue == keyValue[1])
	{
		//��
		//�÷��̾� ���� ����
	}
	else if (pValue == keyValue[2])
	{
		//��
		//�÷��̾� ���� ����
	}
	else if (pValue == keyValue[3])
	{
		//��
		//�÷��̾� ���� ����
	}
	else if (pValue == keyValue[4])
	{
		//Į
		//�����̺�Ʈ ����
		//�̺�Ʈ ����
	}
	else if (pValue == keyValue[5])
	{
		//��
		//�����̺�Ʈ ����
		//�̺�Ʈ ����
	}
	else if (pValue == keyValue[6])
	{
		//��
		//�����̺�Ʈ ����
		//�̺�Ʈ ����
	}
	else if (pValue == keyValue[7])
	{
		//��
		//�÷��̾� ���� ����
	}
}