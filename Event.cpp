#include "Event.h"
#include "Player.h"
#include "Weapon.h"
#include "Vector2D.h"

void Event::EventProcess()
{
	switch (type)
	{
	case 10:
		//��
		/*unsigned int color = ((unsigned int)dir << 16) | tmpVar;
		new Player(Vector2D(posX, posY), color);*/
		break;
	case 11:
		//�� Į
		break;
	case 12:
		//�� ��
		break;
	case 13:
		//�� ��
		break;
	case 20:
		//���
		break;
	case 21:
		//��� Į
		break;
	case 22:
		//��� ��
		break;
	case 23:
		//��� ��
		break;
	case 31:
		//��� ������Ʈ ��ġ
		break;
	case 41:
		//�浹
		break;
	}
}