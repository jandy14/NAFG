#include "Event.h"
#include "Player.h"
#include "Weapon.h"
#include "Vector2D.h"
#include "GameManager.h"

Object* Event::EventProcess()
{
	GameManager* gm = GameManager::GetInstance();
	Object* obj = nullptr;
	int tmp,tmp2;
	switch (type)
	{
	case 00:
		gm->GameReady();
	case 01:
		gm->GameStart();
	case 10:
		//나
		obj = new Player(Vector2D(posX, posY));
		gm->SetColor(dir, tmpVar, true);
		break;
	case 11:
		//내 칼
		if(gm->state == STATE::GAMING)
			obj = new Blade(id, Vector2D(posX, posY), dir);
		break;
	case 12:
		//내 공
		if (gm->state == STATE::GAMING)
			obj = new Ball(id, Vector2D(posX, posY), dir);
		break;
	case 13:
		//내 포
		if (gm->state == STATE::GAMING)
			obj = new Missile(id, Vector2D(posX, posY), dir);
		break;
	case 20:
		//상대
		obj = new Player(Vector2D(posX, posY));
		gm->SetColor(dir, tmpVar, false);
		break;
	case 21:
		//상대 칼
		if (gm->state == STATE::GAMING)
			obj = new Blade(id, Vector2D(posX, posY), dir);
		break;
	case 22:
		//상대 공
		if (gm->state == STATE::GAMING)
			obj = new Ball(id, Vector2D(posX, posY), dir);
		break;
	case 23:
		//상대 포
		if (gm->state == STATE::GAMING)
			obj = new Missile(id, Vector2D(posX, posY), dir);
		break;
	case 31:
		//상대 오브젝트 위치
		if (gm->state == STATE::GAMING)
			gm->SetPosition(id, posX, posY, dir);
		break;
	case 41:
		//충돌
		if (gm->state == STATE::GAMING)
		{
			gm->CollisionHandling(id);
			gm->CollisionHandling(tmpVar);
		}
		break;
	case 91:
		//플레이어 설정
		tmp = ((int)dir << 16) | tmpVar; //blade delay
		//SetAbility(speed, maxgage, charging speed, blade delay);
		Player::SetAbility(id, posX, posY, *((float*)&tmp));
		break;
	case 92:
		//칼 설정
		//SetAbility(minGage);
		Blade::SetAbility(id);
		gm->bladeCost = posX;
		break;
	case 93:
		//공 설정
		tmp = ((int)id << 16) | posX; //castingTime
		tmp2 = ((int)posY << 16) | dir; //durationTime
		//SetAbility(castingTime, durationTime);
		Ball::SetAbility(*((float*)&tmp), *((float*)&tmp2));
		gm->ballCost = tmpVar;
		break;
	case 94:
		//포 설정
		tmp = ((int)id << 16) | posX; //durationTime(LifeTime)
		Missile::SetAbility(*((float*)&tmp), posY);
		gm->missileCost = dir;
		break;
	case 95:
		gm->hostPoint = Vector2D(id, posX); //x,y
		gm->guestPoint = Vector2D(posY, dir); //x,y
	}
	//(11==21, 12==22, 13==23)
	//완전 같을줄은 몰랐는데 일단은 이렇게 둬야겠다
	return obj;
}