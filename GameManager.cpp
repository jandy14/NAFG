#include "GameManager.h"
#include "InputManager.h"
#include "EventManager.h"
#include "NetworkManager.h"

void GameManager::KeyEvent(unsigned int pValue)
{
	inputManager->KeyEvent(pValue);
}
