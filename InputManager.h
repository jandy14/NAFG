#pragma once

class InputManager
{
private:
	unsigned int keyValue[8];//�����¿�Į������
public:
	InputManager();
	void Initailize();
	void KeyEvent(unsigned int value);
	~InputManager();
};