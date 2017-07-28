#include "Event.h"
#include "Player.h"
#include "Weapon.h"
#include "Vector2D.h"

void Event::EventProcess()
{
	switch (type)
	{
	case 10:
		//나
		/*unsigned int color = ((unsigned int)dir << 16) | tmpVar;
		new Player(Vector2D(posX, posY), color);*/
		break;
	case 11:
		//내 칼
		break;
	case 12:
		//내 공
		break;
	case 13:
		//내 포
		break;
	case 20:
		//상대
		break;
	case 21:
		//상대 칼
		break;
	case 22:
		//상대 공
		break;
	case 23:
		//상대 포
		break;
	case 31:
		//상대 오브젝트 위치
		break;
	case 41:
		//충돌
		break;
	}
}