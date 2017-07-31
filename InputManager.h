#pragma once

class GameManager;

class InputManager
{
private:
	unsigned int keyValue[8];//»óÇÏÁÂ¿ìÄ®ÃÑÆ÷¶Ü
	GameManager* gm;
public:
	InputManager() {}
	void Initailize();
	void KeyEvent(unsigned int value, bool isKeyDown);
	~InputManager() {}
};