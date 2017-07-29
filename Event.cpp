#include "Event.h"
#include "Player.h"
#include "Weapon.h"
#include "Vector2D.h"
#include "GameManager.h"

Object* Event::EventProcess()
{
	Object* obj = nullptr;
	switch (type)
	{
	case 10:
		//��
		obj = new Player(Vector2D(posX, posY));
		GameManager::GetInstance()->SetColor(dir, tmpVar, true);
		break;
	case 11:
		//�� Į
		obj = new Blade(id, Vector2D(posX, posY), dir);
		break;
	case 12:
		//�� ��
		obj = new Ball(id, Vector2D(posX, posY), dir);
		break;
	case 13:
		//�� ��
		obj = new Missile(id, Vector2D(posX, posY), dir);
		break;
	case 20:
		//���
		obj = new Player(Vector2D(posX, posY));
		GameManager::GetInstance()->SetColor(dir, tmpVar, false);
		break;
	case 21:
		//��� Į
		obj = new Blade(id, Vector2D(posX, posY), dir);
		break;
	case 22:
		//��� ��
		obj = new Ball(id, Vector2D(posX, posY), dir);
		break;
	case 23:
		//��� ��
		obj = new Missile(id, Vector2D(posX, posY), dir);
		break;
	case 31:
		//��� ������Ʈ ��ġ
		GameManager::GetInstance()->SetPosition(id, posX, posY, dir);
		break;
	case 41:
		//�浹
		GameManager::GetInstance()->CollisionHandling(id);
		GameManager::GetInstance()->CollisionHandling(tmpVar);
		break;
	}
	//���� �������� �����µ� �ϴ��� �̷��� �־߰ڴ�
	return obj;
}