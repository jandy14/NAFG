#pragma once
#include "Vector2D.h"

class Object
{
protected:
	short id;			//id number
	Vector2D velocity;	//�ӵ�
	bool isAlive;		//��������

	//�浹 ����
public:
	Vector2D pos;		//�����쿡���� ��ġ
	short dir;			//�ٶ󺸴� ����

	Object() {}
	Object(short id, Vector2D pos, short dir);
	Object(short id, short posX, short posY, short dir);
	void Pysics();
	short GetID() { return id; }
	void SetPosition(short x, short y) { pos.x = x; pos.y = y; }
	void SetDir(short pDir) { dir = pDir; }
	virtual bool IsDead();
	virtual void Collide() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	~Object();
};