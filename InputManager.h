#pragma once

class GameManager;

class InputManager
{
private:
	unsigned int keyValue[8];//�����¿�Į������
	GameManager* gm;
public:
	InputManager() {}
	void Initailize();
	void KeyEvent(unsigned int value, bool isKeyDown);
	~InputManager() {}
};