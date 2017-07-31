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
	case 02:
		gm->GameOver((id == 1) ? true : false);

	case 10:
		//��
		obj = new Player(Vector2D(posX, posY));
		gm->SetPlayer(obj);
		break;
	case 11:
		//�� Į
		if(gm->state == STATE::GAMING)
			obj = new Blade(id, Vector2D(posX, posY), dir);
		break;
	case 12:
		//�� ��
		if (gm->state == STATE::GAMING)
			obj = new Ball(id, Vector2D(posX, posY), dir);
		break;
	case 13:
		//�� ��
		if (gm->state == STATE::GAMING)
			obj = new Missile(id, Vector2D(posX, posY), dir);
		break;
	case 20:
		//���
		obj = new Player(Vector2D(posX, posY));
		gm->SetColor(dir, tmpVar, false);
		break;
	case 21:
		//��� Į
		if (gm->state == STATE::GAMING)
			obj = new Blade(id, Vector2D(posX, posY), dir);
		break;
	case 22:
		//��� ��
		if (gm->state == STATE::GAMING)
			obj = new Ball(id, Vector2D(posX, posY), dir);
		break;
	case 23:
		//��� ��
		if (gm->state == STATE::GAMING)
			obj = new Missile(id, Vector2D(posX, posY), dir);
		break;
	case 31:
		//��� ������Ʈ ��ġ
		if (gm->state == STATE::GAMING)
			gm->SetPosition(id, posX, posY, dir);
		break;
	case 41:
		//�浹
		if (gm->state == STATE::GAMING)
		{
			gm->CollisionHandling(id);
			gm->CollisionHandling(tmpVar);
		}
		break;
	case 91:
		//�÷��̾� ����
		tmp = ((int)dir << 16) | tmpVar; //blade delay
		//SetAbility(speed, maxgauge, charging speed, blade delay);
		Player::SetAbility(id, posX, posY, *((float*)&tmp));
		break;
	case 92:
		tmp = ((int)posX << 16) | posY; //gaugeStopTime
		tmp2 = ((int)dir << 16) | tmpVar; //dashTime
		//SetAbility(dashSpeed, gaugeStopTime, dashTime) (overloading)
		Player::SetAbility(id, *((float*)&tmp), *((float*)&tmp2));
		break;
	case 93:
		//Į ����
		//SetAbility(minGauge);
		Blade::SetAbility(id);
		gm->bladeCost = posX;
		break;
	case 94:
		//�� ����
		tmp = ((int)id << 16) | posX; //castingTime
		tmp2 = ((int)posY << 16) | dir; //durationTime
		//SetAbility(castingTime, durationTime);
		Ball::SetAbility(*((float*)&tmp), *((float*)&tmp2));
		gm->ballCost = tmpVar;
		break;
	case 95:
		//�� ����
		tmp = ((int)id << 16) | posX; //durationTime(LifeTime)
		Missile::SetAbility(*((float*)&tmp), posY);
		gm->missileCost = dir;
		break;
	case 96:
		gm->hostPoint = Vector2D(id, posX); //x,y
		gm->guestPoint = Vector2D(posY, dir); //x,y
		break;
	}
	//(11==21, 12==22, 13==23)
	//���� �������� �����µ� �ϴ��� �̷��� �־߰ڴ�
	return obj;
}
