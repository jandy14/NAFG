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
		//나
		obj = new Player(Vector2D(posX, posY));
		GameManager::GetInstance()->SetColor(dir, tmpVar, true);
		break;
	case 11:
		//내 칼
		obj = new Blade(id, Vector2D(posX, posY), dir);
		break;
	case 12:
		//내 공
		obj = new Ball(id, Vector2D(posX, posY), dir);
		break;
	case 13:
		//내 포
		obj = new Missile(id, Vector2D(posX, posY), dir);
		break;
	case 20:
		//상대
		obj = new Player(Vector2D(posX, posY));
		GameManager::GetInstance()->SetColor(dir, tmpVar, false);
		break;
	case 21:
		//상대 칼
		obj = new Blade(id, Vector2D(posX, posY), dir);
		break;
	case 22:
		//상대 공
		obj = new Ball(id, Vector2D(posX, posY), dir);
		break;
	case 23:
		//상대 포
		obj = new Missile(id, Vector2D(posX, posY), dir);
		break;
	case 31:
		//상대 오브젝트 위치
		GameManager::GetInstance()->SetPosition(id, posX, posY, dir);
		break;
	case 41:
		//충돌
		GameManager::GetInstance()->CollisionHandling(id);
		GameManager::GetInstance()->CollisionHandling(tmpVar);
		break;
	}
	//완전 같을줄은 몰랐는데 일단은 이렇게 둬야겠다
	return obj;
}