#pragma once
#include "Vector2D.h"

struct HDC__;
typedef HDC__* HDC;

class Object
{
private:
	static int bottom, right;
protected:
	short id;			//id number
	Vector2D velocity;	//�ӵ�
	bool isAlive;		//��������

	//�浹 ����
public:
	Vector2D pos;		//�����쿡���� ��ġ
	short dir;			//�ٶ󺸴� ����

	static void SetViewSize(int x, int y);
	Object();
	Object(short id, Vector2D pos, short dir);
	Object(short id, short posX, short posY, short dir);
	void Physics();
	short GetID() { return id; }
	void SetPosition(short x, short y) { pos.x = x; pos.y = y; }
	void SetDir(short dir);
	virtual bool IsDead();
	virtual void Collide() = 0;
	virtual void Update() = 0;
	virtual void Draw(HDC hdc) = 0;
	~Object() { }
};