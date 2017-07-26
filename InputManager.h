#pragma once

class InputManager
{
private:
	unsigned int keyValue[8];//»óÇÏÁÂ¿ìÄ®ÃÑÆ÷¶Ü
public:
	InputManager();
	void Initailize();
	void KeyEvent(unsigned int value);
	~InputManager();
};